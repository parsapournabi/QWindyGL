#ifndef PARTICLESPARAMS_H
#define PARTICLESPARAMS_H

#include <QObject>
#include <QVector2D>

// Suprer Fast Property definition
#define PARTICLE_PROP(type, name, cname, value) \
    private: \
    Q_PROPERTY(type name READ name WRITE set##cname NOTIFY name##Changed) \
    public: \
        type name() const { return m_##name; } \
        void set##cname(type v) { \
            if (m_##name == v) return; \
            m_##name = v; \
            name##HasChanged = true; \
            emit name##Changed(); \
        } \
        Q_SIGNAL void name##Changed(); \
        /* non-QObject classes Will recognize changes by this variable */ \
        bool name##HasChanged = false; \
    private: \
        type m_##name = value; \

class ParticlesParams : public QObject
{
        Q_OBJECT
        PARTICLE_PROP(float, numParticles, NumParticles, 0.0)
        PARTICLE_PROP(float, fadeOpacity, FadeOpacity, 0.0)
        PARTICLE_PROP(float, speedFactor, SpeedFactor, 0.0)
        PARTICLE_PROP(float, dropRate, DropRate, 0.0)
        PARTICLE_PROP(float, dropRateBump, DropRateBump, 0.0)
        PARTICLE_PROP(QVector2D, windMin, WindMin, QVector2D(-10.0, -10.0)) // UMin, VMin
        PARTICLE_PROP(QVector2D, windMax, WindMax, QVector2D(10.0, 10.0)) // UMax, VMax
        PARTICLE_PROP(int, windDataIndex, WindDataIndex, -1)
    public:
        explicit ParticlesParams(QObject* parent = nullptr)
            : QObject{parent}
        {

        }
};

#endif // PARTICLESPARAMS_H
