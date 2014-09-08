#include "cad_basic_3Dface.h"
#include <QDebug>
#include <QPen>

CAD_basic_3Dface::CAD_basic_3Dface() : CADitem(CADitem::Basic_Face)
{
}

void CAD_basic_3Dface::calculate()
{
    qreal min_x;
    qreal min_y;
    qreal min_z;
    qreal max_x;
    qreal max_y;
    qreal max_z;

    int i = 0;

    foreach(Vertex vertex, vertices)
    {
        if (i == 0)
        {
            min_x = vertex.pos.x();
            min_y = vertex.pos.y();
            min_z = vertex.pos.z();
            max_x = vertex.pos.x();
            max_y = vertex.pos.y();
            max_z = vertex.pos.z();
            this->position = vertex.pos;
        }
        else
        {
            min_x = qMin(min_x, vertex.pos.x());
            min_y = qMin(min_y, vertex.pos.y());
            min_z = qMin(min_z, vertex.pos.z());
            max_x = qMax(max_x, vertex.pos.x());
            max_y = qMax(max_y, vertex.pos.y());
            max_z = qMax(max_z, vertex.pos.z());
        }
        this->snap_vertices.append(vertex.pos);
        i++;
    }

    this->boundingBox.p0 = QVector3D(min_x, min_y, min_z);
    this->boundingBox.a1 = QVector3D(max_x, 0.0, 0.0);
    this->boundingBox.a2 = QVector3D(0.0, max_y, 0.0);
    this->boundingBox.a3 = QVector3D(0.0, 0.0, max_z);

//    this->snap_center = ((M3dVector)(M3dVector(p1) *0.5 + M3dVector(p2) * 0,5)).toM3dPoint();
}