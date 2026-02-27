#ifndef WINDGLFBO_H
#define WINDGLFBO_H

#include <QQuickFramebufferObject>

class ParticlesParams;
class WindGLRenderer;
class WindGLFbo : public QQuickFramebufferObject
{
        Q_OBJECT
        Q_PROPERTY(ParticlesParams* particlesParams READ particlesParams WRITE setParticlesParams NOTIFY particlesParamsChanged)
    public:
        explicit WindGLFbo(QQuickItem* parent = nullptr);
        ~WindGLFbo();

        Renderer* createRenderer() const override;

        /** Properties **/
        ParticlesParams* particlesParams() const;
        void setParticlesParams(ParticlesParams* particlesParams);

    signals:
        void particlesParamsChanged();

    private:
        /** Members **/
        ParticlesParams* m_particlesParams = nullptr;

        friend class WindGLRenderer;
};

#endif // WINDGLFBO_H
