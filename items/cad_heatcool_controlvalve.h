#ifndef CAD_HEATCOOL_CONTROLVALVE_H
#define CAD_HEATCOOL_CONTROLVALVE_H

#include "caditem.h"

class CAD_heatcool_controlvalve : public CADitem
{
public:
    CAD_heatcool_controlvalve();
    virtual ~CAD_heatcool_controlvalve();
    virtual QList<CADitemTypes::ItemType> flangable_items();
    virtual QImage wizardImage();
    virtual QString iconPath();
    virtual QString domain();
    virtual QString description();
    virtual void calculate();
    virtual void processWizardInput();
};

#endif // CAD_HEATCOOL_CONTROLVALVE_H
