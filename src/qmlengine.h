#ifndef QMLENGINE_H
#define QMLENGINE_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

class QmlEngine : public QQmlApplicationEngine
{
        Q_OBJECT
    public:
        using QQmlApplicationEngine::QQmlApplicationEngine;

        Q_INVOKABLE void clearCache()
        {
            qDebug() << "Clearing Component cache...";
            return clearComponentCache();
        }

};

#endif // QMLENGINE_H
