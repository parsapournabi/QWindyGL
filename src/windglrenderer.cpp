#include "windglrenderer.h"

#include "windglfbo.h"
#include "particlesparams.h"
#include "utils.h"

#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLDebugLogger>
#include <QRandomGenerator>
#include <QtMath>

#define R_PARAM_RO() \
    const auto& params = rendererParams(); \
    const auto& particlesParams = params->particlesParams;

struct WindGLRendererParams
{
    ParticlesParams* particlesParams = nullptr;
    QSize windDataRes{0, 0};
    QSize windowSize{0, 0};
    quint16 particleStateResolution = 0;
    bool initialized = false;
};

WindGLRenderer::WindGLRenderer()
    : m_params(new WindGLRendererParams)
{
    initGL();
    initShaders();
    initBuffers();
    // initDebug();

    rendererParams()->initialized = true;
}

WindGLRenderer::~WindGLRenderer()
{
    destroyAll();
}

bool WindGLRenderer::canRender() const
{
    return m_params->initialized &&
           m_params->particlesParams &&
           m_params->particlesParams->windDataIndex() > -1;
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
    if (!canRender())
    {
        return;
    }
    draw();

    /** Force 60 FPS **/
    // update();
}

QOpenGLFramebufferObject* WindGLRenderer::createFramebufferObject(const QSize& size)
{
    QOpenGLFramebufferObjectFormat fmt;
    fmt.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    fmt.setSamples(4);

    // Resizing windows textures...
    rendererParams()->windowSize = size;
    recreateWindowTextures();

    return new QOpenGLFramebufferObject(size, fmt);
}

void WindGLRenderer::synchronize(QQuickFramebufferObject* fbo)
{
    auto windGLFbo = qobject_cast<WindGLFbo*>(fbo);
    if (!windGLFbo)
    {
        qCritical() << "Cannot cast QQuickFramebufferObject -> WindGLFbo class";
        return;
    }

    if (!m_params->particlesParams)
    {
        m_params->particlesParams = windGLFbo->m_particlesParams;
    }

    if (m_params->particlesParams)
    {
        if (m_params->particlesParams->windDataIndexHasChanged)
        {
            m_params->particlesParams->windDataIndexHasChanged = false;

            applyWindTexture(Utils::getWindData(m_params->particlesParams->windDataIndex()));
        }

        if (m_params->particlesParams->numParticlesHasChanged)
        {
            m_params->particlesParams->numParticlesHasChanged = false;

            applyParticleStateTextures(m_params->particlesParams->numParticles());
        }
    }
}

void WindGLRenderer::initGL()
{
    initializeOpenGLFunctions();
}

void WindGLRenderer::initShaders()
{
    const char* drawVert = ":/shaders/draw.vert";
    const char* drawFrag = ":/shaders/draw.frag";
    const char* quadVert = ":/shaders/quad.vert";
    const char* screenFrag = ":/shaders/screen.frag";
    const char* updateFrag = ":/shaders/update.frag";

    createProgram(drawProgram, drawVert, drawFrag);
    createProgram(screenProgram, quadVert, screenFrag);
    createProgram(updateProgram, quadVert, updateFrag);
}

void WindGLRenderer::initBuffers()
{
    // QuadBuffer
    float quads[12] =
    {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };
    createBuffer(quadBuffer, quads, sizeof(quads));

    glGenFramebuffers(1, &frameBuffer);

    applyColorRampTexture();
}

void WindGLRenderer::initDebug()
{
    QOpenGLContext* ctx = QOpenGLContext::currentContext();
    ctx->hasExtension(QByteArrayLiteral("GL_KHR_debug"));

    QOpenGLDebugLogger* logger = new QOpenGLDebugLogger();
    logger->initialize();
    QObject::connect(logger, &QOpenGLDebugLogger::messageLogged,
                     logger, [ = ](const QOpenGLDebugMessage & debugMsg)
    {

        qCritical() << "--------------------------";
        qCritical() << "OpenGL: " << __FILE__ << "at line: " << __LINE__;
        qCritical() << "Debug message (" << debugMsg.id() << "): " << debugMsg.message();
        qCritical() << "--------------------------";

    });
    logger->startLogging();
}

void WindGLRenderer::draw()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);

    drawScreen();
    updateParticles();
}

void WindGLRenderer::drawScreen()
{
    R_PARAM_RO();

    int w = params->windowSize.width();
    int h = params->windowSize.height();

    bindFramebuffer(frameBuffer, screenTexture);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(.0, .0, w, h);

    drawTexture(backgroundTexture, particlesParams->fadeOpacity());
    drawParticles();

    unbindFramebuffer(); // Releasing FBO

    // Binding framebufferObject() (Main one)
    framebufferObject()->bind();

    // enable blending to support drawing on top of an existing background (e.g. a map)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    drawTexture(screenTexture, 1.0);
    glDisable(GL_BLEND);

    // save the current screen as the background for the next frame
    qSwap(backgroundTexture, screenTexture);

    framebufferObject()->release();
}

void WindGLRenderer::drawTexture(QOpenGLTexture* texture, float opacity)
{
    R_PARAM_RO();

    auto program = screenProgram;

    program->bind();

    bindAttribute(quadBuffer, program->attributeLocation("a_pos"), 2);

    bindTexture(texture, 0);
    program->setUniformValue("u_screen", 0);

    program->setUniformValue("u_opacity", opacity);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    program->release();
}

void WindGLRenderer::drawParticles()
{
    R_PARAM_RO();

    auto program = drawProgram;

    program->bind();

    bindAttribute(particleIndexBuffer, program->attributeLocation("a_index"), 1);

    bindTexture(particleStateTexture0, 2);
    program->setUniformValue("u_particles", 2);

    bindTexture(windTexture, 1);
    program->setUniformValue("u_wind", 1);

    bindTexture(colorRampTexture, 0);
    program->setUniformValue("u_color_ramp", 0);

    program->setUniformValue("u_particles_res", (float) params->particleStateResolution);
    program->setUniformValue("u_color_ramp_active", (float) particlesParams->colorRampActive());
    program->setUniformValue("u_wind_min", particlesParams->windMin());
    program->setUniformValue("u_wind_max", particlesParams->windMax());

    glDrawArrays(GL_POINTS, 0, params->particleStateResolution * params->particleStateResolution);

    program->release();
}

void WindGLRenderer::updateParticles()
{
    R_PARAM_RO();

    bindFramebuffer(frameBuffer, particleStateTexture1);
    glViewport(0, 0, params->particleStateResolution, params->particleStateResolution);

    auto program = updateProgram;

    program->bind();

    bindAttribute(quadBuffer, program->attributeLocation("a_pos"), 2);

    bindTexture(particleStateTexture0, 1);
    program->setUniformValue("u_particles", 1);

    bindTexture(windTexture, 0);
    program->setUniformValue("u_wind", 0);

    program->setUniformValue("u_rand_seed", (float) QRandomGenerator::global()->generateDouble());
    program->setUniformValue("u_wind_res", QVector2D(params->windDataRes.width(), params->windDataRes.height()));
    program->setUniformValue("u_wind_min", particlesParams->windMin());
    program->setUniformValue("u_wind_max", particlesParams->windMax());
    program->setUniformValue("u_speed_factor", particlesParams->speedFactor());
    program->setUniformValue("u_drop_rate", particlesParams->dropRate());
    program->setUniformValue("u_drop_rate_bump", particlesParams->dropRateBump());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    program->release();

    qSwap(particleStateTexture0, particleStateTexture1);
}

void WindGLRenderer::createProgram(QOpenGLShaderProgram*& program, const char* vertex, const char* fragment)
{
    if (program || (program && program->isLinked()))
    {
        qCritical() << "program is already created!" << program;
        return;
    }

    program = new QOpenGLShaderProgram();
    bool vert = program->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, vertex);

    if (!vert)
    {
        qCritical() << "Failed to link vertex shader: " << vertex;
    }

    bool frag = program->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, fragment);
    if (!frag)
    {
        qCritical() << "Failed to link fragment shader: " << frag;
    }

    if (!program->link() || !vert || !frag)
    {
        exit(EXIT_FAILURE);
    }
}

void WindGLRenderer::createBuffer(QOpenGLBuffer*& buffer, const void* data, int size)
{
    // Destroy if exists
    destroyBuffer(buffer);

    buffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    buffer->create();
    buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer->bind();
    buffer->allocate(data, size);
    buffer->release();
}

void WindGLRenderer::createTexture(QOpenGLTexture*& texture, QOpenGLTexture::Filter filter, const QImage& img)
{
    // Destroy if exists
    destroyTexture(texture);

    texture = new QOpenGLTexture(img);
    texture->setMinMagFilters(filter, filter);
}

void WindGLRenderer::createTexture(QOpenGLTexture*& texture, QOpenGLTexture::Filter filter, const void* data, int width, int height)
{
    // Destroy if exists
    destroyTexture(texture);

    using T = QOpenGLTexture;
    texture = new QOpenGLTexture(T::Target::Target2D);
    texture->setSize(width, height);
    texture->setFormat(T::TextureFormat::RGBA8_UNorm);
    texture->setMinMagFilters(filter, filter);
    texture->setWrapMode(T::WrapMode::ClampToEdge);
    texture->allocateStorage();
    texture->setData(T::PixelFormat::RGBA, T::PixelType::UInt8, data);
}

void WindGLRenderer::recreateWindowTextures()
{
    R_PARAM_RO();

    int w = params->windowSize.width();
    int h = params->windowSize.height();

    QByteArray emptyPixels(w * h * 4, 0);

    // screen textures to hold the drawn screen for the previous and the current frame
    createTexture(backgroundTexture, QOpenGLTexture::Nearest, emptyPixels, w, h);
    createTexture(screenTexture, QOpenGLTexture::Nearest, emptyPixels, w, h);
}

void WindGLRenderer::bindTexture(QOpenGLTexture* texture, int unit)
{
    texture->bind(unit);
}

void WindGLRenderer::bindAttribute(QOpenGLBuffer* buffer, int attribute, int size)
{
    buffer->bind();

    glEnableVertexAttribArray(attribute);
    glVertexAttribPointer(attribute, size, GL_FLOAT, GL_FALSE, 0, 0);
}

void WindGLRenderer::bindFramebuffer(GLuint fbo, QOpenGLTexture* texture)
{
    if (texture)
    {
        return bindFramebuffer(fbo, texture->textureId());
    }
}

void WindGLRenderer::bindFramebuffer(GLuint fbo, GLuint texture)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
}

void WindGLRenderer::unbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void WindGLRenderer::applyColorRampTexture()
{
    createTexture(colorRampTexture, QOpenGLTexture::Linear, Utils::getColorRamp().mirrored());
}

void WindGLRenderer::applyParticleStateTextures(int nums)
{
    auto* params = rendererParams();
    auto particleRes = params->particleStateResolution = qCeil(qSqrt(nums));
    int total = particleRes * particleRes;

    QByteArray particleState(total * 4, 0); // total * RGBA
    for (int i(0); i < particleState.size(); ++i)
    {
        // One byte which will be normalized 0.0~1.0
        particleState[i] = QRandomGenerator::global()->bounded(256);
    }

    /** Two textures with same initialized value **/
    createTexture(particleStateTexture0, QOpenGLTexture::Nearest,
                  particleState, particleRes, particleRes);

    createTexture(particleStateTexture1, QOpenGLTexture::Nearest,
                  particleState, particleRes, particleRes);

    /**
        GLSL 130 doesn't support gl_VertexID in some graphic cards,
        so it is required to create it manually.
    **/
    QVector<float> particleIndices(total);
    for (int i(0); i < particleIndices.size(); ++i)
    {
        particleIndices[i] = (float) i;
    }
    createBuffer(particleIndexBuffer,
                 particleIndices.data(),
                 particleIndices.size() * sizeof(decltype(particleIndices)::value_type));
}

void WindGLRenderer::applyWindTexture(const QImage& windData)
{
    m_params->windDataRes = windData.size();
    createTexture(windTexture, QOpenGLTexture::Linear, windData);
}

void WindGLRenderer::destroyAll()
{
    destroyBuffer(quadBuffer);
    destroyBuffer(particleIndexBuffer);

    destroyTexture(windTexture);
    destroyTexture(particleStateTexture0);
    destroyTexture(particleStateTexture1);
    destroyTexture(colorRampTexture);
    destroyTexture(backgroundTexture);
    destroyTexture(screenTexture);

    destroyProgram(drawProgram);
    destroyProgram(screenProgram);
    destroyProgram(updateProgram);

    destroyFramebuffer(&frameBuffer);
}

void WindGLRenderer::destroyProgram(QOpenGLShaderProgram*& program)
{
    if (program)
    {
        qDebug() << "Deleting program..." << program->programId();
        program->release();
        program->removeAllShaders();
        delete program;
        program = nullptr;
    }
}

void WindGLRenderer::destroyBuffer(QOpenGLBuffer*& buffer)
{
    if (buffer)
    {
        qDebug() << "Deleting buffer..." << buffer->bufferId();
        buffer->release();
        delete buffer;
        buffer = nullptr;
    }
}

void WindGLRenderer::destroyTexture(QOpenGLTexture*& texture)
{
    if (texture)
    {
        qDebug() << "Deleting texture..." << texture->textureId();
        texture->release();
        delete texture;
        texture = nullptr;
    }
}

void WindGLRenderer::destroyFramebuffer(GLuint* fboId)
{
    if (*fboId > -1)
    {
        qDebug() << "Deleting framebuffer..." << *fboId;
        glDeleteFramebuffers(1, fboId);
        *fboId = -1;
    }
}

void WindGLRenderer::destroyFramebuffer(QOpenGLFramebufferObject*& fbo)
{
    if (fbo)
    {
        qDebug() << "Deleting framebuffer..." << fbo;
        fbo->release();
        delete fbo;
        fbo = nullptr;
    }
}
