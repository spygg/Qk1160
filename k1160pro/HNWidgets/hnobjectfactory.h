#ifndef HNOBJECTFACTORY_H
#define HNOBJECTFACTORY_H

#include <QByteArray>
#include <QMetaObject>
#include <QHash>

class HNObjectFactory
{
public:
    template<typename T>
    static void registerClass()
    {
        //将生成此类对象的具体（非模板）函数注册进Hash
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
    }

    static QObject* createObject( const QByteArray& className, QObject* parent = NULL )
    {
        //搜索生成此类对象的函数
        Constructor constructor = constructors().value( className );
        if ( constructor == NULL )
            return NULL;
        //生成对象
        return (*constructor)( parent );
    }

private:
    typedef QObject* (*Constructor)( QObject* parent );

    template<typename T>
    static QObject* constructorHelper( QObject* parent )
    {
        return new T( parent );
    }

    static QHash<QByteArray, Constructor>& constructors()
    {
        //保存生成类对象的具体（非模板）函数
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }
};

#endif // HNOBJECTFACTORY_H
