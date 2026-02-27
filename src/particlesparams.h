#ifndef PARTICLESPARAMS_H
#define PARTICLESPARAMS_H

#include <QObject>

// Suprer Fast Property definition
#define PARTICLE_PROP(type, name, cname, value) \
    private: \
    Q_PROPERTY(type name READ name WRITE set##cname NOTIFY name##Changed) \
    public: \
        type name() const { return m_##name; } \
        void set##cname(type v) { \
            if (v == m_##name) \
                return; \
            m_##name = v; \
            m_##name##HasChanged = true; \
            emit name##Changed(); \
        } \
        Q_SIGNAL void name##Changed(); \
    private: \
        type m_##name = value; \
        bool m_##name##HasChanged = false; // non-QObject classes Will recognize changes by this variable


class ParticlesParams : public QObject
{
        Q_OBJECT
        PARTICLE_PROP(float, numParticles, NumParticles, 0.0)
        PARTICLE_PROP(float, fadeOpacity, FadeOpacity, 0.0)
        PARTICLE_PROP(float, speedFactor, SpeedFactor, 0.0)
        PARTICLE_PROP(float, dropRate, DropRate, 0.0)
        PARTICLE_PROP(float, dropRateBump, DropRateBump, 0.0)
    public:
        explicit ParticlesParams(QObject* parent = nullptr)
            : QObject{parent}
        {

        }
};

#endif // PARTICLESPARAMS_H
