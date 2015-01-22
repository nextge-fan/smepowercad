#include "cad_sanitary_shower.h"
#include "itemdb.h"

CAD_sanitary_shower::CAD_sanitary_shower() : CADitem(CADitemTypes::Sanitary_Shower)
{
    wizardParams.insert("Position x", QVariant::fromValue(0.0));
    wizardParams.insert("Position y", QVariant::fromValue(0.0));
    wizardParams.insert("Position z", QVariant::fromValue(0.0));
    wizardParams.insert("Angle x", QVariant::fromValue(0.0));
    wizardParams.insert("Angle y", QVariant::fromValue(0.0));
    wizardParams.insert("Angle z", QVariant::fromValue(0.0));

    processWizardInput();
    calculate();
}

CAD_sanitary_shower::~CAD_sanitary_shower()
{

}

QList<CADitemTypes::ItemType> CAD_sanitary_shower::flangable_items()
{
    QList<CADitemTypes::ItemType> flangable_items;
    flangable_items.append(CADitemTypes::Sanitary_ElectricWaterHeater);
    flangable_items.append(CADitemTypes::Sanitary_EmergencyEyeShower);
    flangable_items.append(CADitemTypes::Sanitary_EmergencyShower);
    flangable_items.append(CADitemTypes::Sanitary_Flange);
    flangable_items.append(CADitemTypes::Sanitary_LiftingUnit);
    flangable_items.append(CADitemTypes::Sanitary_Pipe);
    flangable_items.append(CADitemTypes::Sanitary_PipeEndCap);
    flangable_items.append(CADitemTypes::Sanitary_PipeReducer);
    flangable_items.append(CADitemTypes::Sanitary_PipeTeeConnector);
    flangable_items.append(CADitemTypes::Sanitary_PipeTurn);
    flangable_items.append(CADitemTypes::Sanitary_Shower);
    flangable_items.append(CADitemTypes::Sanitary_Sink);
    flangable_items.append(CADitemTypes::Sanitary_WashBasin);

    return flangable_items;
}

QImage CAD_sanitary_shower::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");

    ;

    image.load(imageFileName, "PNG");

    return image;
}

QString CAD_sanitary_shower::iconPath()
{
    return ":/icons/cad_sanitary/cad_sanitary_shower.svg";
}

QString CAD_sanitary_shower::domain()
{
    return "Sanitary";
}

QString CAD_sanitary_shower::description()
{
    return "Sanitary|Shower";
}

void CAD_sanitary_shower::calculate()
{
    matrix_rotation.setToIdentity();
    matrix_rotation.rotate(angle_x, 1.0, 0.0, 0.0);
    matrix_rotation.rotate(angle_y, 0.0, 1.0, 0.0);
    matrix_rotation.rotate(angle_z, 0.0, 0.0, 1.0);

    boundingBox.reset();

    this->snap_flanges.clear();
    this->snap_center.clear();
    this->snap_vertices.clear();

    this->snap_basepoint = (position);
}

void CAD_sanitary_shower::processWizardInput()
{
    position.setX(wizardParams.value("Position x").toDouble());
    position.setY(wizardParams.value("Position y").toDouble());
    position.setZ(wizardParams.value("Position z").toDouble());
    angle_x = wizardParams.value("Angle x").toDouble();
    angle_y = wizardParams.value("Angle y").toDouble();
    angle_z = wizardParams.value("Angle z").toDouble();

}
