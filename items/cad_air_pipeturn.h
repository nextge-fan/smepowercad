#ifndef CAD_AIR_PIPETURN_H
#define CAD_AIR_PIPETURN_H

#include "caditem.h"

class CAD_air_pipeTurn : public CADitem
{
public:
    CAD_air_pipeTurn();
    virtual void calculate();
};

#endif // CAD_AIR_PIPETURN_H