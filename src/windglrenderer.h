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
        bool canRender() const;
        WindGLRendererParams* rendererParams() noexcept;
        const WindGLRendererParams* rendererParams() const noexcept;

    protected:
        void render() override;
        QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;
        void synchronize(QQuickFramebufferObject*) override;

        void initGL();
        void initShaders();
        void initBuffers();
        void initDebug();

        void draw();
        void drawScreen();
        void drawTexture(QOpenGLTexture* texture, float opacity);
        void drawParticles();
        void updateParticles();

        void createProgram(QOpenGLShaderProgram*& program, const char* vertex, const char* fragment);
        void createBuffer(QOpenGLBuffer*& buffer, const void* data, int size);
        void createTexture(QOpenGLTexture*& texture, QOpenGLTexture::Filter filter, const QImage& img);
        void createTexture(QOpenGLTexture*& texture, QOpenGLTexture::Filter filter, const void* data, int width, int height);
        void recreateWindowTextures();
        void bindTexture(QOpenGLTexture* texture, int unit);
        void bindAttribute(QOpenGLBuffer* buffer, int attribute, int size);
        void bindFramebuffer(GLuint fbo, QOpenGLTexture* texture);
        void bindFramebuffer(GLuint fbo, GLuint texture);
        void unbindFramebuffer();

        /** Dependent functions **/
        void applyColorRampTexture();
        void applyParticleStateTextures(int nums);
        void applyWindTexture(const QImage& windData);

        /** Destructure functions **/
        void destroyAll();
        void destroyProgram(QOpenGLShaderProgram*& program);
        void destroyBuffer(QOpenGLBuffer*& buffer);
        void destroyTexture(QOpenGLTexture*& texture);
        void destroyFramebuffer(GLuint* fboId);
        void destroyFramebuffer(QOpenGLFramebufferObject*& fbo);

        /** Members **/
        QOpenGLShaderProgram* drawProgram = nullptr;
        QOpenGLShaderProgram* screenProgram = nullptr;
        QOpenGLShaderProgram* updateProgram = nullptr;

        QOpenGLBuffer* quadBuffer = nullptr;
        QOpenGLBuffer* particleIndexBuffer = nullptr;

        QOpenGLTexture* screenTexture = nullptr;
        QOpenGLTexture* backgroundTexture = nullptr;
        QOpenGLTexture* windTexture = nullptr;
        QOpenGLTexture* colorRampTexture = nullptr;
        QOpenGLTexture* particleStateTexture0 = nullptr;
        QOpenGLTexture* particleStateTexture1 = nullptr;

        GLuint frameBuffer = -1; // don't need to use QOpenGLFramebufferObject

        QScopedPointer<WindGLRendererParams> m_params;
};

#endif // WINDGLRENDERER_H
