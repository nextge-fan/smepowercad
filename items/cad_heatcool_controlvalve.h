#ifndef CAD_HEATCOOL_CONTROLVALVE_H
#define CAD_HEATCOOL_CONTROLVALVE_H

#include "caditem.h"

class CAD_heatcool_controlvalve : public CADitem
{
public:
    CAD_heatcool_controlvalve();
    virtual void calculate();
};

#endif // CAD_HEATCOOL_CONTROLVALVE_H
