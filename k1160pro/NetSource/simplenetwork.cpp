
#include "simplenetwork.h"
#include "DataDef.h"


SimpleNetwork::SimpleNetwork(QTcpSocket *socket, QObject *parent) :
        QObject(parent),
        tcpSocket(socket),
        blockSize(0),
        downSpeed(0),
        upSpeed(0),
        m_pTransmit(NULL)
{
    // if no server is assigned.
    if( tcpSocket == NULL )
        tcpSocket = new QTcpSocket;

    // incoming flow of bytes
    in.setVersion(QDataStream::Qt_4_6);
    in.setDevice(tcpSocket);

    // creates signal slot connectionsyoudianeeen
    signalslots(true);

    // timer to calculate the speed by seconds
    //connect( &speedTimer, SIGNAL(timeout()),
             //this, SLOT(speedTimeout()) );
//   speedTimer.start(1050);
}

SimpleNetwork::~SimpleNetwork()
{
    // releases the memory
    if( tcpSocket )
    {
        qDebug() << "this 1";
        delete tcpSocket;
}
    transmit.clear();
    fileAttributes.removeAll();
    dataPackages.removeAll();
}

// ==[ creates signal slot connections ]==
void SimpleNetwork::signalslots(bool b)
{
    // connects signals to slots
    if(b)
    {
        // emits the current network state to the gui
        connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                this, SLOT(networkStateChanged(QAbstractSocket::SocketState)) );
        // connected
        connect(tcpSocket, SIGNAL(connected()),
                this, SLOT(successfullyConnected()) );
        // disconnected
        connect(tcpSocket, SIGNAL(disconnected()),
                this, SLOT(connectionClosed()) );
        // as soon as bytes are received.

        connect(tcpSocket, SIGNAL(readyRead()),
                this, SLOT(receiveBytes()) );

        connect(this, SIGNAL(emitTcpRead()),
                this->parent(), SLOT(ReceiveBytes()) );
        // emits the current network error to the gui
        connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(networkErrorOccured(QAbstractSocket::SocketError)) );
        // emits the currently wirtten bytes
        connect(tcpSocket, SIGNAL(bytesWritten(qint64)),
                this, SLOT(bytesWritten(qint64)));
    }

    // disconnects signals to slots
    else
    {
        disconnect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                   this, SLOT(networkStateChanged(QAbstractSocket::SocketState)) );

        disconnect(tcpSocket, SIGNAL(connected()),
                   this, SLOT(successfullyConnected()));

        disconnect(tcpSocket, SIGNAL(disconnected()),
                   this, SLOT(connectionClosed()) );

        disconnect(tcpSocket, SIGNAL(readyRead()),
                   this, SLOT(receiveBytes()) );

        disconnect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                   this, SLOT(networkErrorOccured(QAbstractSocket::SocketError)) );
    }
}

// ==[ established a connection to a suitable server ]==
bool SimpleNetwork::connectToServer(const QString &hostName, quint16 port)
{
    // if socket active -> not allowed to connect to host
    if( tcpSocket->state() != QAbstractSocket::UnconnectedState )
        return false;

    qDebug() << "state";
    // establishing a connection
    tcpSocket->connectToHost(QHostAddress(hostName), port);
    qDebug() << "connectToHost";
    int i = 0;//tcpSocket->state();

    if( !tcpSocket->waitForConnected(5000) )
    {
        i =  tcpSocket->error();
         qDebug() << "i :"<< i;
        return false;
    }
     qDebug() << "waitForConnected";
    return true;
}

// ==[ closes the current connection ]==
void SimpleNetwork::closeConection()
{
    if( isConnected() )
        tcpSocket->disconnectFromHost();
}

// ==[ returns the ip address of the active network device ]==
QString SimpleNetwork::getLocalAddress()
{
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address() )
            return ipAddressesList.at(i).toString();
    }

    return QHostAddress(QHostAddress::LocalHost).toString();
}

// ==[ sets the save directory for the incoming file transfer ]==
bool SimpleNetwork::setFileSavePath(const QString& path)
{
    QDir dir(path);

    if( !dir.exists() )
        return false;

    fileAttributes.setSaveFileDir(path + "/");

    return true;
}

// ==[ transmits bytes of an entire data set -> QString ]==
void SimpleNetwork::transmitData(const int ID, const QString& DATA){
    transmitDataX(ID, DATA);
}

// ==[ transmits bytes of an entire data set -> QByteArray ]==
void SimpleNetwork::transmitData(const int ID, const QByteArray DATA){
    transmitDataX(ID, DATA);
}

// ==[ transmits bytes of an entire data set -> int ]==
void SimpleNetwork::transmitData(const int ID, const int DATA){
    transmitDataX(ID, DATA);
}

// ==[ transmits bytes of an entire data set -> double ]==
void SimpleNetwork::transmitData(const int ID, const double DATA){
    transmitDataX(ID, DATA);
}

// ==[ transmits any bytes -> called by transmitData(int, datatype) ]==
template < typename T >
        void SimpleNetwork::transmitDataX(const int ID, const T& XDATA)
{
/*
    // new thread object
    transmit.append( new Transmit(ID, toByte(XDATA)) );

    // signal slot to check when the thread is finished
    connect( transmit.last(), SIGNAL(finished()),
             this, SLOT(transmitFinished()) );
    // signal slot to transmit bytes outside of the thread
    connect( transmit.last(), SIGNAL(emitTransmitByteBlock(QByteArray)),
             this, SLOT(transmitByteBlock(QByteArray)) );
    // signal slot to check for bytes outside of the thread
    connect( transmit.last(), SIGNAL(emitCheckBytesToWrite()),
             this, SLOT(checkBytesToWrite()) );

    transmit.last()->start(); // starts the thread and sends the data
*/
      if(NULL != m_pTransmit)
      {
          qDebug() << "this 2";
          delete m_pTransmit;
          m_pTransmit = NULL;
      }

      m_pTransmit = new Transmit(ID, toByte(XDATA));

      connect( m_pTransmit, SIGNAL(finished()),
               this, SLOT(transmitFinished()) );
      // signal slot to transmit bytes outside of the thread
      connect( m_pTransmit, SIGNAL(emitTransmitByteBlock(QByteArray)),
               this, SLOT(transmitByteBlock(QByteArray)) );
      // signal slot to check for bytes outside of the thread
      connect( m_pTransmit, SIGNAL(emitCheckBytesToWrite()),
               this, SLOT(checkBytesToWrite()) );

      m_pTransmit->start(); // starts the thread and sends the data
 //   TcpWrite(toByte(XDATA));
}

void SimpleNetwork::TcpWrite(QByteArray &Arry)
{
    tcpSocket->write(Arry);
    int i = 0;
}

// ==[ transmits a file, this function is the first step -> sends onyl file attributes ]==
bool SimpleNetwork::transmitFile(const int ID, const QString& FILE_NAME)
{
    QFile tmpFile(FILE_NAME);

    // if the file doesnt exist
    if( !tmpFile.exists() )
        return false;

    // opens the file in read only mode
    tmpFile.open(QIODevice::ReadOnly);

    // sends file attributes
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out << 0;  // placeholder
    out << FILE_DATA; // file transfer
    out << ID;  // ID
    out << tmpFile.fileName();  // file name
    out << tmpFile.size();     // filesize

    out.device()->seek(0);
    int i = block.size() - sizeof(int);
    out << i;

    tmpFile.close();  // closes the file

    tcpSocket->write(block);  // sends file attributes

    return true;
}

// ==[ transmit a file, this function is the second step
//     -> it is going to start to send the entire file over a thread ]==
void SimpleNetwork::transmitFile()
{
    int id;
    // next byte packet is the id
    in >> id;

    // next the increment size
    qint64 increment_size;
    in >> increment_size;

    // next the file name
    QString fileName;
    in >> fileName;

    // new thread object
    transmit.append( new Transmit(id, fileName, increment_size) );

    // signal slot to check when the thread is finished
    connect( transmit.last(), SIGNAL(finished()),
             this, SLOT(transmitFinished()) );
    // signal slot to transmit bytes outside of the thread
    connect( transmit.last(), SIGNAL(emitTransmitByteBlock(QByteArray)),
             this, SLOT(transmitByteBlock(QByteArray)) );
    // signal slot to check for bytes outside of the thread
    connect( transmit.last(), SIGNAL(emitCheckBytesToWrite()),
             this, SLOT(checkBytesToWrite()) );
    // signal slot to check the progress of the outgoing file transfer
    connect( transmit.last(), SIGNAL(emitFileProgressOut(int,qint64,qint64)),
             this, SLOT(fileProgressOut(int,qint64,qint64)) );
    // signals if a thread is terminated
    connect( transmit.last(), SIGNAL(terminated()),
             this, SLOT(transmitTerminated()) );
    // signals if the connection is closed
    connect( this, SIGNAL(emitConnectionClosed()),
             transmit.last(), SLOT(quit()) );

    transmit.last()->start(); // starts the thread and sends the file
}

// ==[ aborts the current file transfer ]==
void SimpleNetwork::abortFileTransfer(const int ID)
{
    for( int i = 0; i < transmit.count(); i++ )
    {
        if( transmit[i]->getId() == ID )
        {
            transmit[i]->terminate();
            transmit[i]->wait();

            return;
        }
    }
}

// ==[ resets the interrupted file attributes ]==
void SimpleNetwork::resetReceiveTransfer(const int ID)
{
    fileAttributes.removeFile(ID);
}

// ==[ transmits the bytes in a loop ]==
void Transmit::run()
{
    int TRANS_BYTES = 1024;//1024000; // size of the byte packages

    // data transfer
    if( !file_run )
    {
/*
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);

        out << data.data();
*/
        emit emitTransmitByteBlock(data);  // sends byte block

        // as long as data hasn't been written yet
        /*
        while( data.size() > 0 )
        {
            // if there outstanding bytes at the transmit interface
            if( bytesToWrite > 0 )
            {
                msleep(1); // short sleep time to reduce the cpu load
                emit emitCheckBytesToWrite();  // checks outstanding bytes
                continue;
            }

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            //out.setVersion(QDataStream::Qt_4_6);
            */
            /*
            out << 0;  // Placeholder
            out << NO_FILE; // No file transfer
            out << id;  // ID
            out << data.left(TRANS_BYTES);  // read the next bytes of the data

            data.remove(0, TRANS_BYTES);  // removes the readed byts

            out.device()->seek(0);
            out << block.size() - sizeof(int);
            */
            /*
            out << data.data();
            //out << data.left(TRANS_BYTES);  // read the next bytes of the data

            data.remove(0, TRANS_BYTES);  // removes the readed byts

            emit emitTransmitByteBlock(block);  // sends byte block
        }
        */
    }

    // file transfer
    else
    {
        // sets the variable to the size from where the transfer has last stopped
        // -> incremental data transfer
        remFileBytes = (file.size() - remFileBytes);

        // as long as there are bytes to transmit
        while( remFileBytes > 0 )
        {
            bool btw = true;

            // if there outstanding bytes at the transmit interface
            if( bytesToWrite > 0 )
            {
                btw = false;

                msleep(1); // short sleep time to reduce the cpu load
                emit emitCheckBytesToWrite(); // checks outstanding bytes
                continue;
            }

            // if the datatransfer to slow -> extend the byte package
            if( btw )
                TRANS_BYTES += 16;
            // if the bytetransfer overloaded -> reduce the byte package
            else
                TRANS_BYTES -= 1024;


            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_6);
            out << 0;  // placeholder
            out << FILE_DATA; // file transfer
            out << id;  // ID
            file.seek( file.size() - remFileBytes ); // jumps to offset to read next bytes
            out << file.read(TRANS_BYTES);  // reads the next bytes of the file

            remFileBytes -= TRANS_BYTES;   // removes the readed size from the variable

            out.device()->seek(0);
            int i = block.size() - sizeof(int);
            out << i;
            //out << block.size() - sizeof(int);


            // sends byte block
            emit emitTransmitByteBlock(block);
            // outgoing file transfer progress - id, progress, size
            emit emitFileProgressOut( id, (file.size() - remFileBytes), file.size() );

        }

        // outgoing file transfer progress - id, progress, size (to ensure the 100%)
        emit emitFileProgressOut( id, file.size(), file.size() );
    }
}

// ==[ checks the connection ]==
bool SimpleNetwork::isConnected()
{
    if( tcpSocket->state() == QAbstractSocket::ConnectedState )
        return true;

    return false;
}

// ==[ template: converts known datatypes into QByteArray ]==
template < typename T >
        QByteArray SimpleNetwork::toByte(const T& X)
{
    // if datatype a QByteArray -> ignore the convertion to QByteArray

#ifdef _MIPS_LINUX_ENV_
       if( QString::fromAscii(typeid(&X).name()) == "PK10QByteArray")
        return (QByteArray&)X;
#else
    if( QString::fromLatin1(typeid(&X).name()) == "PK10QByteArray")
       return (QByteArray&)X;
#endif

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out << X;

    return data;
}

// ==[ receives bytes of a dataset ]==
void SimpleNetwork::receiveData()
{
    int id;

    // second byte packet is the id
    in >> id;

    // if the size of the current data is still unknown
    if( dataPackages.getPackageSize(id) == 0 )
    {
        int tmpSize;
        // next byte packet ist the size of the data
        in >> tmpSize;
        // the dataSize depends on the id
        dataPackages.addPackage(id, tmpSize);
        // sets blockSize to 0 for the next, new block

        return;
    }

    QByteArray tmpBytes;
    // next bytes are the useable bytes for the data
    in >> tmpBytes;

    // write bytes to data
    dataPackages.appendBytesToPackage(id, tmpBytes);

    // when all bytes have been received
    if( dataPackages.isDataComplete(id) )
    {
        // triggers the signal when data are complete
        emit emitDataReceived( id, dataPackages.getPackage(id) );

        // removes the dataPackage which depends on the id for the next, new data
        dataPackages.removePackage(id);
    }
}

// ==[ receives bytes of a file ]==
void SimpleNetwork::receiveFile()
{
    int id;
    // nexz byte packet is the id
    in >> id;

    // if the file with the proper id doesnt exist
    if( !fileAttributes.existFileId(id) )
    {
        // next the file name
        QString tmpFileName;
        in >> tmpFileName;

        // next the file size
        qint64 tmpFileSize;
        in >> tmpFileSize;

        // creates a new file to write the bytes into it
        fileAttributes.addFile(id, tmpFileSize, removeFilePath(tmpFileName));

        // identify byte increment
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);
        out << 0;  // placeholder
        out << FILE_INCREMENT; // increment enum
        out << id;  // ID
        out << fileAttributes.getWrittenFileSize(id);  // continue at last stopped byte
        out << tmpFileName;
        out.device()->seek(0);
        int i = block.size() - sizeof(int);
        out << i;
        //out << block.size() - sizeof(int);

        tcpSocket->write(block);  // sends the byte block
        tcpSocket->flush();

        // if the file has already been transmitted - increment byte is 0
        if( fileAttributes.getWrittenFileSize(id) == tmpFileSize )
        {
            emit emitFileProgressIn( id, fileAttributes.getWrittenFileSize(id),
                                      fileAttributes.getFileSize(id) );
            emit emitFileReceived(id);
            fileAttributes.removeFile(id);
        }

        return;
    }

    QByteArray tmpBytes;
    // next bytes are the useable bytes for the file
    in >> tmpBytes;

    fileAttributes.appendBytesToFile(id, tmpBytes);  // write new bytes into file

    emit emitFileProgressIn( id, fileAttributes.getWrittenFileSize(id), 
			     fileAttributes.getFileSize(id) );

    // if the transfer is completed
    if( fileAttributes.isFileComplete(id) )
    {
        // triggers the signal if the file is complete
        emit emitFileReceived(id);
        fileAttributes.removeFile(id);
    }
}

QByteArray SimpleNetwork::ReadBytesAll()
{
    m_temp.clear();
    m_temp = tcpSocket->readAll();
    return m_temp;
}


/*************************************************************************
========================[ SLOTS ]=========================================
*************************************************************************/

// ==[ is triggered by the Trasnmit thread
//     -> the Transmit thread is finished ]==
void SimpleNetwork::transmitFinished()
{
    /* the finished data will be transmitted
       in the receiveData function */

    // deletes the transmit thread which has been finished
    for(int i = 0; i < transmit.count(); i++)
    {
        if( transmit[i]->getId() == ((Transmit*)QObject::sender())->getId() )
            transmit.remove(i);
    }
}

/*
// ==[ is triggered by the tcpSocket,
//     -> incoming bytes that are waiting to be read ]==
void SimpleNetwork::receiveBytes()
{

    // as long as there are bytes in the buffer receive-queue
    while( tcpSocket->bytesAvailable() > sizeof(int) )
    {
        // if the size of the current block is still unknown
        if( blockSize == 0 )
            in >> blockSize;

        // if not enough bytes available to read
        if( tcpSocket->bytesAvailable() < blockSize )
            return;

        // calculates the download speed
        downSpeed += ( blockSize + sizeof(int) );

        int enumFile;

        // first byte packet is the indicator whether file transfer or other data transfer
        in >> enumFile;

        // jumps to the correct function
        switch(enumFile)
        {
            // data transfer
        case NO_FILE: receiveData();
            break;
            // file transfer - receive
        case FILE_DATA: receiveFile();
            break;
            // file transfer - transmit: last stoped byte
        case FILE_INCREMENT: transmitFile();
            break;
        default: qDebug() << "BUG";
        }

        blockSize = 0;
    }
}
*/
void SimpleNetwork::receiveBytes()
{

    emit emitTcpRead();
}

// ==[ is triggered by the Trasnmit thread
//     -> writes bytes to the network interface buffer to transmit ]==
void SimpleNetwork::transmitByteBlock(QByteArray block)
{
    // if the connection has been lost -> terminate transmit thread
    if( !isConnected() )
    {
        ((Transmit*)QObject::sender())->terminate();

        return;
    }

    // tranmits bytes through the network interface
    tcpSocket->write(block);

    // tells the Transmit thread the size of the reamining bytes which must be written
    ((Transmit*)QObject::sender())->setBytesToWrite(tcpSocket->bytesToWrite());
}

// ==[ is triggered by the tcpSocket
//     -> currently written bytes ]==
void SimpleNetwork::bytesWritten(qint64 bytes)
{
    upSpeed += bytes;
}

// ==[ is triggered by the Trasmit thread
//     -> checks the size of the reamining bytes which must be written ]==
void SimpleNetwork::checkBytesToWrite()
{
    // if the connection has been lost -> terminate transmit thread
    if( !isConnected() )
    {
        ((Transmit*)QObject::sender())->terminate();

        return;
    }


    // tells the Transmit thread the size of the reamining bytes which must be written
    ((Transmit*)QObject::sender())->setBytesToWrite(tcpSocket->bytesToWrite());
}

// ==[ is triggered by the tcpSocket
//     -> if a connection will be established, disconnected etc. ]==
void SimpleNetwork::networkStateChanged(QAbstractSocket::SocketState socketState)
{
    // triggers the signal
    emit emitNetworkStateChanged(socketState);
}

// ==[ is triggered by tcpSocket,
//     -> if a connection was successfully established ]==
void SimpleNetwork::successfullyConnected()
{
    // triggers the signal
    emit emitSuccessfullyConnected();
}

// ==[ is triggered by tcpSocket,
//     -> if a network error occurred ]==
void SimpleNetwork::networkErrorOccured(QAbstractSocket::SocketError socketError)
{
    // closes the connection
    tcpSocket->close();

    // triggers the signal
    emit emitNetworkErrorOccured(socketError);
}

// ==[ is triggered by tcpSocket,D
//     -> if a connection was closed ]==
void SimpleNetwork::connectionClosed()
{
    blockSize = 0;
    fileAttributes.removeAll();
    dataPackages.removeAll();

    // closes the connection
    tcpSocket->close();

    // triggers the signal
    emit emitConnectionClosed();
}

// ==[ is triggered by the Trasmit thread
//     -> emits the id of the terminated thread ]==
void SimpleNetwork::transmitTerminated()
{
    int id = ((Transmit*)QObject::sender())->getId();

    emit emitTransmitTerminated(id);
}

// ==[ is triggered by speedTimer,
//     -> if the time is expired ]==
void SimpleNetwork::speedTimeout()
{
    // emits the speed values to the gui
    emit emitDownSpeed(downSpeed);
    emit emitUpSpeed(upSpeed);

    // resets the speed values
    downSpeed = 0;
    upSpeed = 0;
}
