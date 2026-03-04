#ifndef WINDGLFBO_H
#define WINDGLFBO_H

#include <QQuickFramebufferObject>

#define PROPERTY(type, name, cname, value) \
    private: \
        Q_PROPERTY(type name READ name WRITE set##cname NOTIFY name##Changed) \
    public: \
        type name() const { return m_##name; } \
        void set##cname(type v) { \
                if (m_##name == v) return; \
                m_##name = v; \
                emit name##Changed(); \
            } \
        Q_SIGNAL void name##Changed(); \
    private: \
        type m_##name = value;

class ParticlesParams;
class WindGLRenderer;
class WindGLFbo : public QQuickFramebufferObject
{
        Q_OBJECT
        PROPERTY(ParticlesParams*, particlesParams, ParticlesParams, nullptr);
    public:
        explicit WindGLFbo(QQuickItem* parent = nullptr);
        ~WindGLFbo();

        Renderer* createRenderer() const override;

    private:
        friend class WindGLRenderer;
};

#endif // WINDGLFBO_H
