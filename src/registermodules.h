#ifndef REGISTERMODULES_H
#define REGISTERMODULES_H

#include <QtQml/qqml.h>

#include "particlesparams.h"

#define TO_STR(x) #x

// Automatically registering classes when QCoreApplication executed
inline static void registerModules()
{
    qmlRegisterType<ParticlesParams>(TO_STR(WindGL), 1, 0, TO_STR(ParticlesParams));
}

#endif // REGISTERMODULES_H
