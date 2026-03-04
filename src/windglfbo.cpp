#include "windglfbo.h"

#include "windglrenderer.h"

#include <QTimer>

WindGLFbo::WindGLFbo(QQuickItem* parent)
    : QQuickFramebufferObject(parent)
{
    setMirrorVertically(true);

    QTimer* tmr = new QTimer(this);

    tmr->setInterval(5);
    connect(tmr, &QTimer::timeout, this, [ = ]()
    {
        update();
    });

    tmr->start();
}

WindGLFbo::~WindGLFbo()
{

}

QQuickFramebufferObject::Renderer* WindGLFbo::createRenderer() const
{
    return new WindGLRenderer();
}
