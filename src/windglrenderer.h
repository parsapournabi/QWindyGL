#ifndef WINDGLRENDERER_H
#define WINDGLRENDERER_H

#include <QQuickFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

struct WindGLRendererParams;
class WindGLRenderer : public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions
{
    public:
        WindGLRenderer();
        ~WindGLRenderer();

        /** Getters & Setters **/
        WindGLRendererParams* rendererParams() noexcept;
        const WindGLRendererParams* rendererParams() const noexcept;

    protected:
        void render() override;
        QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;
        void synchronize(QQuickFramebufferObject*) override;

        void initGL();
        void initShaders();
        void initBuffers();

        /** Members **/
        QScopedPointer<WindGLRendererParams> m_params;
};

#endif // WINDGLRENDERER_H
