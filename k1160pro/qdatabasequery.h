#ifndef QDATABASEQUERY_H
#define QDATABASEQUERY_H

#include <QObject>
#include <QString>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QStringList>

class QDatabasequery : public QObject
{
    Q_OBJECT
public:
    explicit QDatabasequery(QObject *parent = 0);
    ~QDatabasequery();
     void SetTableName(QString table);
     bool opendatabase();

     void cloesdatabase();

     bool insert(QString &table, QStringList &names,QStringList &values);

     bool Updata(QString &table, QStringList &names,QStringList &values, QString &expression);

     bool del(QString &table, QString &srcDatacloum, QString &expression);

     //int GetTotalCount(QString &table);

     void GetValues(QString &table, QStringList &values, int index);
     int GetSize(QString &table);

     void GetoneValues(QString &table, QStringList &values, QString &srcDatacloum, QString &strData, int num);
     void GetSetionValues(QString &table, QStringList &values, int ilimit, int ioffset);
private:
     QSqlTableModel *model;
     QSqlDatabase _db;
     QString _tableName;

};

#endif // QDATABASEQUERY_H
