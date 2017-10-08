
#ifndef SIMPLENETWORK_H
#define SIMPLENETWORK_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QtNetwork>
#include <typeinfo>

//======[ TRANSMIT (Thread) - TRANSMIT DATA AND/OR FILE ]=============================//
class Transmit : public QThread{

    Q_OBJECT

    // enum to identify the transfer policy
    enum{
        NO_FILE,
        FILE_DATA,
        FILE_INCREMENT
    };

public:
    // Constructor: transfers data which is dependent on the id
    Transmit(const int ID, const QByteArray& DATA) : id(ID), data(DATA), 
    file_run(false), bytesToWrite(0) {}

    // Constructor: transfers a file which is dependent on the id
    Transmit(const int ID, const QString& FILE_NAME, const qint64 INCREMENT_SIZE):
            id(ID), remFileBytes(INCREMENT_SIZE), file_run(true), bytesToWrite(0)
    { file.setFileName(FILE_NAME); file.open(QIODevice::ReadOnly); }

    // tells this thread how many bytes must be written
    void setBytesToWrite(qint64 size){ bytesToWrite = size; }

    // returns the id
    inline int getId(){ return id; }


private:
    // starts the thread
    virtual void run();

private:
    int id;     // transfer id
    QByteArray data;    // sending data
    QFile file;         // sending file
    qint64 remFileBytes;  // remaining bytes
    bool file_run;       // file transfer or data transfer
    qint64 bytesToWrite;  // the size bytes which must be written from the buffer

signals:
    void emitTransmitByteBlock(QByteArray); // if data transfer is finished
    void emitCheckBytesToWrite();   // checks how many bytes must be written from the buffer
    void emitFileProgressOut(int,qint64,qint64); // id, progress, size
};
//=================================================================//

//======[ DATA PACKAGES ]=================================================//
class DataPackages
{

public:
    // new data package
    inline bool addPackage(const int ID, const int SIZE){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID ) return false; }
        id.append(ID); size.append(SIZE); package.append(0); return true;
    }
    // size of the entire package
    inline int getPackageSize(const int ID){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID ) return size[i]; }
        return 0;
    }
    // delets package
    inline bool removePackage(const int ID){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID ){ id.removeAt(i); 
                size.removeAt(i); package.removeAt(i); return true;}
        } return false;
    }

    // delets all packages
    inline void removeAll(){
        for( int i = 0; i < id.count(); i++ ){ id.removeAt(i); size.removeAt(i);
            package.removeAt(i); }
    }

    // appends new incoming bytes
    inline bool appendBytesToPackage(const int ID, const QByteArray& DATA){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID ){ 
                package[i].append(DATA); return true;} }
        return false;
    }
    // size of the current bytes
    inline int getCurrentBytePackageSize(const int ID){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID ) return package[i].count(); }
        return -1;
    }
    // returns the package - package must be completed received
    inline  QByteArray getPackage(const int ID){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID ) return package[i]; }
        return 0;
    }
    // checks if the bytes have been completely received
    inline bool isDataComplete(const int ID){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID ){ 
                if( size[i] == package[i].count() ) return true; else return false;} }
        return false;
    }

private:
    QList<int> id;  // id
    QList<int> size; // package size
    QList<QByteArray> package;  // data package
};
//========================================================================//

//======[ FILE ATTRIBUTES ]=================================================//
class FileAttributes
{

public:
    // checks if the id already exist
    inline bool existFileId(const int ID){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID ) return true; }
        return false;
    }
    // sets the save directory for the incoming file transfer
    inline void setSaveFileDir(const QString& path){ saveFilePath = path; }
    // new file
    inline void addFile(const int ID, const qint64 SIZE, const QString& FILE_NAME){
        for( int i = 0; i < id.count(); i++ )
            if( id[i] == ID )
                return;
        id.append(ID); fileSize.append(SIZE); file.append( new QFile(saveFilePath + FILE_NAME) );
        file.last()->open(QIODevice::ReadWrite);
    }
    // deletes file
    inline void removeFile(const int ID){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID ){
                id.removeAt(i); fileSize.removeAt(i); file[i]->close();
                delete file[i]; file.removeAt(i);} }
    }

    // deletes all files
    inline void removeAll(){
        for( int i = 0; i < id.count(); i++ ){ id.removeAt(i); fileSize.removeAt(i);
            file[i]->close(); delete file[i]; file.removeAt(i); }
    }

    // append incoming bytes to file
    inline void appendBytesToFile(const int ID, const QByteArray& DATA){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID ){
                file[i]->seek(file[i]->size()); file[i]->write(DATA);} }
    }
    // checks if file is complete
    inline bool isFileComplete(const int ID){ for( int i = 0; i < id.count(); i++ ){
            if( id[i] == ID ){ if( fileSize[i] == file[i]->size() ) return true;
                else return false;} }
        return false;
    }
    // size of the file
    inline qint64 getFileSize(const int ID){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID )return fileSize[i];}
        return -1;
    }
    // size of the bytes which have already been written
    inline qint64 getWrittenFileSize(const int ID){
        for( int i = 0; i < id.count(); i++ ){ if( id[i] == ID )return file[i]->size();}
        return -1;
    }

private:
    QList<int> id;  // transfer id
    QList<qint64> fileSize;  // the size of the entire file
    QList<QFile*> file;     // the incoming file - bytes are written into it
    QString saveFilePath;
};
//========================================================================//

//======[ MAIN CLASS - NETWORK HANDLE ]=================================================//
class SimpleNetwork : public QObject
{
    Q_OBJECT

    // enum to identify the transfer policy
    enum{
        NO_FILE,
        FILE_DATA,
        FILE_INCREMENT
    };

    // [policies]
public:
    // constructor: defines the network tcp socket
    explicit SimpleNetwork(QTcpSocket *socket = 0, QObject *parent = 0);
    // destructor: delets all dynamic variables
    ~SimpleNetwork();
    // established a connection to a suitable server
    // important: the bool type doesnt represent the connection state
    bool connectToServer(const QString& hostName, quint16 port); 
    // closes the current connection
    void closeConection();
    // returns the ip address of the active network device
    QString getLocalAddress();
    // returns the ip address of the active, connected peer user
    inline QString getPeerAddress(){ return tcpSocket->peerAddress().toString(); }
    // sets the save directory for the incoming file transfer
    bool setFileSavePath(const QString& path);
    // transmits bytes of an entire data set -> int
    void transmitData(const int ID, const int DATA);
    // transmits bytes of an entire data set -> double
    void transmitData(const int ID, const double DATA);
    // transmits bytes of an entire data set -> QByteArray
    void transmitData(const int ID, const QByteArray DATA);
    // transmits bytes of an entire data set -> QString
    void transmitData(const int ID, const QString& DATA);
    // transmits bytes of an entire file
    bool transmitFile(const int ID, const QString& file_name);
    // aborts the file transfer
    void abortFileTransfer(const int ID);
    // resets the receive transfer
    void resetReceiveTransfer(const int ID);
    // checks if a connection is estableshed
    bool isConnected();
    // returns the current socket state - connected, unconnected, estableshing etc..
    inline QAbstractSocket::SocketState getConnectionState(){ return tcpSocket->state(); }

    void TcpWrite(QByteArray &Arry);
    //
    QByteArray ReadBytesAll();

    // [policies]
private:
    // creates signal slot connections
    void signalslots(bool b);
    // converts known datatypes into QByteArray
    template < typename T >
            QByteArray toByte(const T& X);
    // receives bytes of a dataset
    void receiveData();
    // receives bytes of a file
    void receiveFile();
    // transmit a file, this function is the second step
    // -> it is going to start to send the entire file over a thread
    void transmitFile();
    // removes the path string from file name
    inline QString removeFilePath(QString str){
        return str.right( (str.size() - str.lastIndexOf('/')) -1 ); }
    // transmits any bytes -> called by transmitData(int, datatype)
    template < typename T >
            void transmitDataX(const int ID, const T& XDATA);

    // [variables]
private:
    // the network tcp socket - handles the whole byte stream
    QTcpSocket *tcpSocket;
    // handles the incoming bytes which comes from the tcp socket
    QDataStream in;
    // the transmit thread object
    QVector <Transmit *>transmit;
    Transmit *m_pTransmit;
    // treats the parallel transfer of datas
    DataPackages dataPackages;
    // treats the parallel transfer of files
    FileAttributes fileAttributes;
    // saves the size of the incoming block of bytes
    int blockSize;
    // saves the download speed value
    int downSpeed;
    // saves the upload speed value
    int upSpeed;
    // timer to calculate the speed by seconds
    QTimer speedTimer;
    QByteArray m_temp;


    // [slots]
private slots:
    // is triggered by the tcpSocket
    // -> if a connection will be established, disconnected etc.
    void networkStateChanged(QAbstractSocket::SocketState);
    // is triggered by tcpSocket
    // -> if a connection was successfully established
    void successfullyConnected();
    // is triggered by tcpSocket
    // -> if a connection was closed
    void connectionClosed();
    // is triggered by the tcpSocket
    // -> incoming bytes that are waiting to be read
    void receiveBytes();
    // is triggered by tcpSocket
    // -> if a network error occurred
    void networkErrorOccured(QAbstractSocket::SocketError);
    // is triggered by the Trasnmit thread
    // -> writes bytes to the network interface buffer to transmit
    void transmitByteBlock(QByteArray);
    // is triggered by the Trasmit thread
    // -> checks the size of the reamining bytes which must be written
    void checkBytesToWrite();
    // is triggered by the Trasnmit thread
    // -> the Transmit thread is finished
    void transmitFinished();
    // is triggered by the Trasnmit thread
    // -> the Transmit thread is terminated
    void transmitTerminated();
    // is triggered by the tcpSocket
    // -> currently written bytes
    void bytesWritten(qint64);
    // is triggered by speedTimer,
    // -> if the time is expired
    void speedTimeout();
    // is triggered by the Trasnmit thread
    // -> outgoing file transfer progress - id, progress, size (emits the value to the gui)
    inline void fileProgressOut(int id, qint64 progress, qint64 size){
        emit emitFileProgressOut(id, progress, size); }

    // [signals]
signals:
    // emits the current network state to the gui
    void emitNetworkStateChanged(QAbstractSocket::SocketState);
    // successfully connected
    void emitSuccessfullyConnected();
    // disconnected
    void emitConnectionClosed();
    // emits received bytes to the gui
    void emitDataReceived(int, QByteArray);
    // emits the id of the recived file to the gui
    void emitFileReceived(int);
    // emits the terminated thread
    void emitTransmitTerminated(int);
    // error occured
    void emitNetworkErrorOccured(QAbstractSocket::SocketError);
    // emits the ingoing file transfer progress to the gui
    void emitFileProgressIn(int,qint64,qint64); // id, progress, size
    // emits the outgoing file transfer progress to the gui
    void emitFileProgressOut(int,qint64,qint64); // id, progress, size
    // emits the download speed value to the gui
    void emitDownSpeed(int);
    // emits the upload speed value to the gui
    void emitUpSpeed(int);
    //
    void emitTcpRead();
};

#endif // SIMPLENETWORK_H
