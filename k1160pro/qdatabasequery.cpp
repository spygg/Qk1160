#include <QtSql/QSqlQuery>
#include <QObject>
#include <QTextStream>
#include "qdatabasequery.h"
#include "QUuid"


QDatabasequery::QDatabasequery(QObject *parent) :
    QObject(parent)
{
    QUuid uuid = QUuid::createUuid();
    //qDebug() << uuid.toString();
    _db = QSqlDatabase::addDatabase("QSQLITE", uuid.toString());
}

QDatabasequery::~QDatabasequery()
{
    _db.close();
}

void QDatabasequery::SetTableName(QString table)
{
    _tableName = table + ".db";
}


/*
    打开数据库.
    外部使用方式为打开使用和关闭，所以此处使用默认连接不会出现问题
        优化方法
        具名连接，打开数据库，连接不变。
*/
bool QDatabasequery::opendatabase()
{
    //_db = QSqlDatabase::addDatabase("QSQLITE"）;

    if(_db.isOpen())
        _db.close();

    _db.setDatabaseName(_tableName);

    return _db.open();
}

void QDatabasequery::cloesdatabase()
{
    _db.close();
}

/*
    插入函数.
    构造SQL插入语句.
*/
#include "HNDefine.h"

bool QDatabasequery::insert(QString &table, QStringList &names, QStringList &values)
{
    int length = names.count();
    int count = values.count();
    if (length != count)
    {
        return false;
    }

    QSqlQuery query(_db);

    QString sql = QString("insert into ") + table + QString("(");

    pline() << names;
    pline() << values;

    int i;
    for (i=0; i < length; i++)
    {
        sql = sql + names.value(i);
        if (i < length - 1)
        {
            sql+=QString(",");
        }
        else
        {

            sql = sql + QString(")");
        }
    }

    sql = sql + QString("values (");

    for (i = 0; i < count; i++)
    {
        sql = sql + QString("'") + values.value(i) + QString("'");
        if (i < count-1)
        {
            sql = sql + QString(",");
        }
        else
            sql = sql + QString(")");
    }


    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << sql << endl;
    bool ret = query.exec(sql);
    cout << ret << endl;
    return ret;
}

/*
    修改函数.
    构造SQL修改语句.
*/
bool QDatabasequery::Updata(QString &table, QStringList &names, QStringList &values, QString &expression)
{
    if (names.size() != values.size())
    {
        return false;
    }

    //UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值
    QSqlQuery query(_db);
    QString sql = QString("update ")+table+QString(" set ");
    for (int i = 0; i < names.size(); i++)
    {
        sql = sql + names.value(i);
        sql = sql + QString(" = '");
        sql = sql + values.value(i);
        sql = sql + QString("'");
        if (i != names.size()-1)
        {
            sql = sql + QString(" ,");
        }
    }

    sql = sql + QString(" where ") + expression;
    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << sql << endl;
    bool ret = query.exec(sql);
    cout << ret << endl;
}

/*
    删除函数.
    构造SQL删除语句.
*/
bool QDatabasequery::del(QString &table, QString &srcDatacloum, QString &expression)
{
    //DELETE FROM 表名称 WHERE 列名称 = 值
    QSqlQuery query(_db);
    QString sql = QString("delete from ") + table + QString(" where ") + srcDatacloum + QString("='") + expression + QString("'");

    if (query.exec(sql))
    {
        return true;
    }
    else
    {
        return false;
    }
}


void QDatabasequery::GetValues(QString &table, QStringList &values, int index)
{
    QSqlQuery query(_db);
    QString sql = QString("select * from ") + table;
    query.exec(sql);
    while (query.next())
    {
        values << query.value(index).toString();
    }
}

int QDatabasequery::GetSize(QString &table)
{
    QSqlQuery query(_db);
    QString sql = QString("select count(*) from ") + table;
    query.exec(sql);
    if(query.next())
        return query.value(0).toInt();
}

void QDatabasequery::GetoneValues(QString &table, QStringList &values, QString &srcDatacloum, QString &strData, int num)
{
    QSqlQuery query(_db);
    //QString sql = "select * from method where mingcheng='qq'";//QString("select * from ") + table + QString(" where ") + srcDatacloum + QString("='") + strData + QString("'");
    QString sql = QString("select * from ") + table + QString(" where ") + srcDatacloum + QString("='") + strData + QString("'");


    if(true == query.exec(sql))
    {
        query.next();

        for(int i = 0; i < num; i++)
        {
            values.append(query.value(i).toString());
        }

    }

}

void QDatabasequery::GetSetionValues(QString &table, QStringList &values, int ilimit, int ioffset)
{
    QSqlQuery query(_db);
    QString sql = QString("select * from ") + table + QString(" limit ") + ilimit + QString(" offset ") + ioffset;

    if(true == query.exec(sql))
    {
        query.next();
        //values.append(query);

    }
}
