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

#include "cad_electrical_cabletray.h"

CAD_electrical_cabletray::CAD_electrical_cabletray() : CADitem(CADitemTypes::Electrical_Cabletray)
{
    wizardParams.insert("Position x", 0.0);
    wizardParams.insert("Position y", 0.0);
    wizardParams.insert("Position z", 0.0);
    wizardParams.insert("Angle x", 0.0);
    wizardParams.insert("Angle y", 0.0);
    wizardParams.insert("Angle z", 0.0);

    wizardParams.insert("a", 100.0);    // Höhe
    wizardParams.insert("b", 300.0);    // Breite
    wizardParams.insert("l", 1000.0);   // Länge
    wizardParams.insert("s", 10.0);     // Wandstärke

    floor = new CAD_basic_box();
    left = new CAD_basic_box();
    right = new CAD_basic_box();
    this->subItems.append(floor);
    this->subItems.append(left);
    this->subItems.append(right);

//    arrayBufVertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
//    arrayBufVertices->create();
//    arrayBufVertices->setUsagePattern(QOpenGLBuffer::StaticDraw);

//    indexBufFaces = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//    indexBufFaces->create();
//    indexBufFaces->setUsagePattern(QOpenGLBuffer::StaticDraw);

//    indexBufLines = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//    indexBufLines->create();
//    indexBufLines->setUsagePattern(QOpenGLBuffer::StaticDraw);
   
    processWizardInput();
    calculate();
}

CAD_electrical_cabletray::~CAD_electrical_cabletray()
{
//    arrayBufVertices->destroy();
//    indexBufFaces->destroy();
//    indexBufLines->destroy();
//    delete arrayBufVertices;
//    delete indexBufFaces;
//    delete indexBufLines;
}

QList<CADitemTypes::ItemType> CAD_electrical_cabletray::flangable_items(int flangeIndex)
{
    Q_UNUSED(flangeIndex);
    QList<CADitemTypes::ItemType> flangable_items;
    flangable_items.append(CADitemTypes::Electrical_Cabletray);
    flangable_items.append(CADitemTypes::Electrical_CabletrayCross);
    flangable_items.append(CADitemTypes::Electrical_CabletrayReducer);
    flangable_items.append(CADitemTypes::Electrical_CabletrayTeeConnector);
    flangable_items.append(CADitemTypes::Electrical_CabletrayTransition);
    flangable_items.append(CADitemTypes::Electrical_CabletrayTurn);
    flangable_items.append(CADitemTypes::Electrical_CabletrayVerticalLadder);
    return flangable_items;
}

QImage CAD_electrical_cabletray::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");        
    image.load(imageFileName, "PNG");
                       
    return image;
}

QString CAD_electrical_cabletray::iconPath()
{
    return ":/icons/cad_electrical/cad_electrical_cabletray.svg";
}

QString CAD_electrical_cabletray::domain()
{
    return "Electrical";
}

QString CAD_electrical_cabletray::description()
{
    return "Electrical|Cabletray";
}

void CAD_electrical_cabletray::calculate()
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

    QVector3D position_flr = position + matrix_rotation * QVector3D(l/2, 0.0, s/2);
    floor->wizardParams.insert("Position x", position_flr.x());
    floor->wizardParams.insert("Position y", position_flr.y());
    floor->wizardParams.insert("Position z", position_flr.z());
    floor->wizardParams.insert("Angle x", angle_x);
    floor->wizardParams.insert("Angle y", angle_y);
    floor->wizardParams.insert("Angle z", angle_z);

    floor->wizardParams.insert("l", l);
    floor->wizardParams.insert("b", b);
    floor->wizardParams.insert("a", s);
    floor->layer = this->layer;
    floor->processWizardInput();
    floor->calculate();

    QVector3D position_lft = position + matrix_rotation * QVector3D(l/2, -b/2 + s/2, (a+s)/2);
    left->wizardParams.insert("Position x", position_lft.x());
    left->wizardParams.insert("Position y", position_lft.y());
    left->wizardParams.insert("Position z", position_lft.z());
    left->wizardParams.insert("Angle x", angle_x);
    left->wizardParams.insert("Angle y", angle_y);
    left->wizardParams.insert("Angle z", angle_z);

    left->wizardParams.insert("l", l);
    left->wizardParams.insert("b", s);
    left->wizardParams.insert("a", a-s);
    left->layer = this->layer;
    left->processWizardInput();
    left->calculate();

    QVector3D position_rgt = position + matrix_rotation * QVector3D(l/2, +b/2 - s/2, (a+s)/2);
    right->wizardParams.insert("Position x", position_rgt.x());
    right->wizardParams.insert("Position y", position_rgt.y());
    right->wizardParams.insert("Position z", position_rgt.z());
    right->wizardParams.insert("Angle x", angle_x);
    right->wizardParams.insert("Angle y", angle_y);
    right->wizardParams.insert("Angle z", angle_z);

    right->wizardParams.insert("l", l);
    right->wizardParams.insert("b", s);
    right->wizardParams.insert("a", a-s);
    right->layer = this->layer;
    right->processWizardInput();
    right->calculate();

    this->snap_flanges.append(position);
    this->snap_flanges.append(position + matrix_rotation * QVector3D(l, 0.0, 0.0));

    this->snap_vertices.append(position + matrix_rotation * QVector3D(0.0, 0.5 * b, 0.0));
    this->snap_vertices.append(position + matrix_rotation * QVector3D(l,   0.5 * b, 0.0));
    this->snap_vertices.append(position + matrix_rotation * QVector3D(l,  -0.5 * b, 0.0));
    this->snap_vertices.append(position + matrix_rotation * QVector3D(0.0,-0.5 * b, 0.0));
    this->snap_vertices.append(position + matrix_rotation * QVector3D(0.0, 0.5 * b, a));
    this->snap_vertices.append(position + matrix_rotation * QVector3D(l,   0.5 * b, a));
    this->snap_vertices.append(position + matrix_rotation * QVector3D(l,  -0.5 * b, a));
    this->snap_vertices.append(position + matrix_rotation * QVector3D(0.0,-0.5 * b, a));

    this->boundingBox.enterVertices(floor->boundingBox.getVertices());
    this->boundingBox.enterVertices(left->boundingBox.getVertices());
    this->boundingBox.enterVertices(right->boundingBox.getVertices());
}

void CAD_electrical_cabletray::processWizardInput()
{
    position.setX(wizardParams.value("Position x").toDouble());
    position.setY(wizardParams.value("Position y").toDouble());
    position.setZ(wizardParams.value("Position z").toDouble());
    angle_x = wizardParams.value("Angle x").toDouble();
    angle_y = wizardParams.value("Angle y").toDouble();
    angle_z = wizardParams.value("Angle z").toDouble();

    a = wizardParams.value("a").toDouble();
    b = wizardParams.value("b").toDouble();
    l = wizardParams.value("l").toDouble();
    s = wizardParams.value("s").toDouble();
}

//void CAD_electrical_cabletray::paint(GLWidget *glwidget)
//{
//    QColor color_pen_tmp = getColorPen();
//    QColor color_brush_tmp = getColorBrush();

//    arrayBufVertices->bind();
//    glwidget->shaderProgram->enableAttributeArray(glwidget->shader_vertexLocation);
//    glwidget->shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(QVector3D));

//    if (glwidget->render_solid)
//    {
//        glwidget->setPaintingColor(color_brush_tmp);

//        indexBufFaces->bind();
//        glwidget->glDrawElements(GL_TRIANGLE_STRIP, indexBufFaces->size(), GL_UNSIGNED_SHORT, 0);

//        indexBufFaces->release();
//    }

//    if (glwidget->render_outline)
//    {
//        glwidget->setPaintingColor(color_pen_tmp);
                                      
//        indexBufLines->bind();
//        glwidget->glDrawElements(GL_LINES, indexBufLines->size(), GL_UNSIGNED_SHORT, 0);
//        indexBufLines->release();
//     }                          
                                                                                           
//     arrayBufVertices->release();
//}

QMatrix4x4 CAD_electrical_cabletray::rotationOfFlange(quint8 num)
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
