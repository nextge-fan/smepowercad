/**********************************************************************
** smepowercad
** Copyright (C) 2015 Smart Micro Engineering GmbH
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

#include "cad_air_ductfiredamper.h"

CAD_air_ductFireDamper::CAD_air_ductFireDamper() : CADitem(CADitemTypes::Air_DuctFireDamper)
{
    wizardParams.insert("Position x", 0.0);
    wizardParams.insert("Position y", 0.0);
    wizardParams.insert("Position z", 0.0);
    wizardParams.insert("Angle x", 0.0);
    wizardParams.insert("Angle y", 0.0);
    wizardParams.insert("Angle z", 0.0);

    wizardParams.insert("a",  200.0);
    wizardParams.insert("b",  300.0);
    wizardParams.insert("l", 1000.0);
    wizardParams.insert("l2", 100.0);
    wizardParams.insert("l3", 700.0);
    wizardParams.insert("g",  350.0);
    wizardParams.insert("h",  250.0);
    wizardParams.insert("fe",  10.0);
    wizardParams.insert("ff",  10.0);
    wizardParams.insert("s",    1.0);

    this->flange_duct_left = new CAD_basic_duct();
    this->flange_duct_middle = new CAD_basic_box();
    this->flange_duct_right = new CAD_basic_duct();
    this->main_duct = new CAD_basic_duct();
    this->function = new CAD_basic_box();
    this->subItems.append(flange_duct_left);
    this->subItems.append(flange_duct_middle);
    this->subItems.append(flange_duct_right);
    this->subItems.append(main_duct);
    this->subItems.append(function);

    processWizardInput();
    calculate();
}

CAD_air_ductFireDamper::~CAD_air_ductFireDamper()
{

}

QList<CADitemTypes::ItemType> CAD_air_ductFireDamper::flangable_items(int flangeIndex)
{
    Q_UNUSED(flangeIndex);
    QList<CADitemTypes::ItemType> flangable_items;
    flangable_items.append(CADitemTypes::Air_Duct);
    flangable_items.append(CADitemTypes::Air_DuctTeeConnector);
    flangable_items.append(CADitemTypes::Air_DuctTransitionRectRect);
    flangable_items.append(CADitemTypes::Air_DuctTransitionRectRound);
    flangable_items.append(CADitemTypes::Air_DuctTurn);
    flangable_items.append(CADitemTypes::Air_DuctVolumetricFlowController);
    flangable_items.append(CADitemTypes::Air_DuctYpiece);
    flangable_items.append(CADitemTypes::Air_Filter);
    flangable_items.append(CADitemTypes::Air_HeatExchangerAirAir);
    flangable_items.append(CADitemTypes::Air_HeatExchangerWaterAir);
    flangable_items.append(CADitemTypes::Air_MultiLeafDamper);
    return flangable_items;
}

QImage CAD_air_ductFireDamper::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");
    image.load(imageFileName, "PNG");

    return image;
}

QString CAD_air_ductFireDamper::iconPath()
{
    return ":/icons/cad_air/cad_air_ductfiredamper.svg";
}

QString CAD_air_ductFireDamper::domain()
{
    return "Air";
}

QString CAD_air_ductFireDamper::description()
{
    return "Air|Duct fire damper";
}

void CAD_air_ductFireDamper::calculate()
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

    QVector3D position_fl = position + matrix_rotation * QVector3D(-l3, 0.0, 0.0);
    flange_duct_left->wizardParams.insert("Position x", (position_fl.x()));
    flange_duct_left->wizardParams.insert("Position y", (position_fl.y()));
    flange_duct_left->wizardParams.insert("Position z", (position_fl.z()));
    flange_duct_left->wizardParams.insert("Angle x", (angle_x));
    flange_duct_left->wizardParams.insert("Angle y", (angle_y));
    flange_duct_left->wizardParams.insert("Angle z", (angle_z));
    flange_duct_left->wizardParams.insert("l", (fe));
    flange_duct_left->wizardParams.insert("b", (b + 2 * ff));
    flange_duct_left->wizardParams.insert("a", (a + 2 * ff));
    flange_duct_left->wizardParams.insert("s", (ff));
    flange_duct_left->processWizardInput();
    flange_duct_left->calculate();

    QVector3D position_md = position + matrix_rotation * QVector3D(l2 / 2, 0.0, 0.0);
    flange_duct_middle->wizardParams.insert("Position x", (position_md.x()));
    flange_duct_middle->wizardParams.insert("Position y", (position_md.y()));
    flange_duct_middle->wizardParams.insert("Position z", (position_md.z()));
    flange_duct_middle->wizardParams.insert("Angle x", (angle_x));
    flange_duct_middle->wizardParams.insert("Angle y", (angle_y));
    flange_duct_middle->wizardParams.insert("Angle z", (angle_z));
    flange_duct_middle->wizardParams.insert("l", (l2));
    flange_duct_middle->wizardParams.insert("b", (g));
    flange_duct_middle->wizardParams.insert("a", (h));
    flange_duct_middle->processWizardInput();
    flange_duct_middle->calculate();

    QVector3D position_fr = position + matrix_rotation * QVector3D(l - l3 - fe, 0.0, 0.0);
    flange_duct_right->wizardParams.insert("Position x", (position_fr.x()));
    flange_duct_right->wizardParams.insert("Position y", (position_fr.y()));
    flange_duct_right->wizardParams.insert("Position z", (position_fr.z()));
    flange_duct_right->wizardParams.insert("Angle x", (angle_x));
    flange_duct_right->wizardParams.insert("Angle y", (angle_y));
    flange_duct_right->wizardParams.insert("Angle z", (angle_z));
    flange_duct_right->wizardParams.insert("l", (fe));
    flange_duct_right->wizardParams.insert("b", (b + 2 * ff));
    flange_duct_right->wizardParams.insert("a", (a + 2 * ff));
    flange_duct_right->wizardParams.insert("s", (ff));
    flange_duct_right->processWizardInput();
    flange_duct_right->calculate();

    QVector3D position_main = position + matrix_rotation * QVector3D(-l3, 0.0, 0.0);
    main_duct->wizardParams.insert("Position x", (position_main.x()));
    main_duct->wizardParams.insert("Position y", (position_main.y()));
    main_duct->wizardParams.insert("Position z", (position_main.z()));
    main_duct->wizardParams.insert("Angle x", (angle_x));
    main_duct->wizardParams.insert("Angle y", (angle_y));
    main_duct->wizardParams.insert("Angle z", (angle_z));
    main_duct->wizardParams.insert("l", (l));
    main_duct->wizardParams.insert("b", (b));
    main_duct->wizardParams.insert("a", (a));
    main_duct->wizardParams.insert("s", (s));
    main_duct->processWizardInput();
    main_duct->calculate();

    QVector3D position_f = position + matrix_rotation * QVector3D(-l3 / 2, 0.6 * b, 0.0);
    function->wizardParams.insert("Position x", (position_f.x()));
    function->wizardParams.insert("Position y", (position_f.y()));
    function->wizardParams.insert("Position z", (position_f.z()));
    function->wizardParams.insert("Angle x", (angle_x));
    function->wizardParams.insert("Angle y", (angle_y));
    function->wizardParams.insert("Angle z", (angle_z));
    function->wizardParams.insert("l", (0.3 * l3));
    function->wizardParams.insert("b", (0.2 * b));
    function->wizardParams.insert("a", (0.5 * a));
    function->processWizardInput();
    function->calculate();

    boundingBox.enterVertex(flange_duct_left->pos_top_1);
//    boundingBox.enterVertex(flange_duct_left->pos_top_2);
//    boundingBox.enterVertex(flange_duct_left->pos_top_3);
    boundingBox.enterVertex(flange_duct_left->pos_top_4);
    boundingBox.enterVertex(flange_duct_left->pos_bot_1);
//    boundingBox.enterVertex(flange_duct_left->pos_bot_2);
//    boundingBox.enterVertex(flange_duct_left->pos_bot_3);
    boundingBox.enterVertex(flange_duct_left->pos_bot_4);

//    boundingBox.enterVertex(flange_duct_right->pos_top_1);
    boundingBox.enterVertex(flange_duct_right->pos_top_2);
    boundingBox.enterVertex(flange_duct_right->pos_top_3);
//    boundingBox.enterVertex(flange_duct_right->pos_top_4);
//    boundingBox.enterVertex(flange_duct_right->pos_bot_1);
    boundingBox.enterVertex(flange_duct_right->pos_bot_2);
    boundingBox.enterVertex(flange_duct_right->pos_bot_3);
//    boundingBox.enterVertex(flange_duct_right->pos_bot_4);

    this->snap_flanges.append(position);
    this->snap_vertices.append(main_duct->snap_vertices);
    this->snap_flanges.append(main_duct->snap_flanges);

}

void CAD_air_ductFireDamper::processWizardInput()
{
    position.setX(wizardParams.value("Position x").toDouble());
    position.setY(wizardParams.value("Position y").toDouble());
    position.setZ(wizardParams.value("Position z").toDouble());
    angle_x = wizardParams.value("Angle x").toDouble();
    angle_y = wizardParams.value("Angle y").toDouble();
    angle_z = wizardParams.value("Angle z").toDouble();


    a = wizardParams.value("a").toDouble();
    h = wizardParams.value("h").toDouble();
    b = wizardParams.value("b").toDouble();
    g = wizardParams.value("g").toDouble();
    fe = wizardParams.value("fe").toDouble();
    ff = wizardParams.value("ff").toDouble();
    l = wizardParams.value("l").toDouble();
    l2 = wizardParams.value("l2").toDouble();
    l3 = wizardParams.value("l3").toDouble();
    s = wizardParams.value("s").toDouble();

}

QMatrix4x4 CAD_air_ductFireDamper::rotationOfFlange(quint8 num)
{
    if(num == 1)
    {
        QMatrix4x4 m;
        m.setToIdentity();
        m.rotate(180.0, 0.0, 0.0, 1.0);
        return matrix_rotation * m;
    }
    else if(num == 2)
    {
        return matrix_rotation;
    }
    else
        return matrix_rotation;
}
