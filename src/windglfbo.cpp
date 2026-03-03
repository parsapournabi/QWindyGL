#include "windglfbo.h"

#include "windglrenderer.h"
#include "particlesparams.h"

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

ParticlesParams* WindGLFbo::particlesParams() const
{
    return m_particlesParams;
}

void WindGLFbo::setParticlesParams(ParticlesParams* particlesParams)
{
    if (particlesParams == m_particlesParams)
    {
        return;
    }

    m_particlesParams = particlesParams;
    emit particlesParamsChanged();
}
