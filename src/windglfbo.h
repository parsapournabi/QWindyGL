#ifndef WINDGLFBO_H
#define WINDGLFBO_H

#include <QQuickFramebufferObject>
#include <QGeoRectangle>

#define PROPERTY(type, name, cname, value) \
    private: \
        Q_PROPERTY(type name READ name WRITE set##cname NOTIFY name##Changed) \
    public: \
        type name() const { return m_##name; } \
        void set##cname(type v) { \
                if (m_##name == v) return; \
                m_##name = v; \
                m_##name##HasChanged = true; \
                emit name##Changed(); \
            } \
        Q_SIGNAL void name##Changed(); \
    private: \
        type m_##name = value; \
        bool m_##name##HasChanged = false;

class ParticlesParams;
class WindGLRenderer;
class WindGLFbo : public QQuickFramebufferObject
{
        Q_OBJECT
        PROPERTY(ParticlesParams*, particlesParams, ParticlesParams, nullptr);
        PROPERTY(QGeoRectangle, projection, Projection, {})
    public:
        explicit WindGLFbo(QQuickItem* parent = nullptr);
        ~WindGLFbo();

        Renderer* createRenderer() const override;

    private:
        friend class WindGLRenderer;
};

#endif // WINDGLFBO_H
