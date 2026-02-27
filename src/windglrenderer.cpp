#include "windglrenderer.h"

#include "windglfbo.h"
#include <QOpenGLFramebufferObjectFormat>

struct WindGLRendererParams
{
    bool initialized = false;
};

WindGLRenderer::WindGLRenderer()
    : m_params(new WindGLRendererParams)
{
    initGL();
    initShaders();
    initBuffers();

    rendererParams()->initialized = true;
}

WindGLRenderer::~WindGLRenderer()
{

}

WindGLRendererParams* WindGLRenderer::rendererParams() noexcept
{
    return m_params.get();
}

const WindGLRendererParams* WindGLRenderer::rendererParams() const noexcept
{
    return m_params.get();
}

void WindGLRenderer::render()
{
    auto params = rendererParams();
    if (!params->initialized)
    {
        return;
    }
}

QOpenGLFramebufferObject* WindGLRenderer::createFramebufferObject(const QSize& size)
{
    QOpenGLFramebufferObjectFormat fmt;
    fmt.setSamples(4);
    fmt.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, fmt);
}

void WindGLRenderer::synchronize(QQuickFramebufferObject*)
{

}

void WindGLRenderer::initGL()
{
    initializeOpenGLFunctions();
}

void WindGLRenderer::initShaders()
{

}

void WindGLRenderer::initBuffers()
{

}
