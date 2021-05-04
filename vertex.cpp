#include <QVector2D>
#include <Qvector3D>

#include "iomanip"
#include "vertex.h"


Vertex::Vertex()
{

}

Vertex::Vertex(float x, float y, float z, float r, float g, float b)
{
    m_xyz[0] = x;
    m_xyz[1] = y;
    m_xyz[2] = z;
    m_normal[0] = r;
    m_normal[1] = g;
    m_normal[2] = b;
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b, float u, float v)
{
    m_xyz[0] = x;
    m_xyz[1] = y;
    m_xyz[2] = z;
    m_normal[0] = r;
    m_normal[1] = g;
    m_normal[2] = b;
    m_st[0] = u;
    m_st[1] = v;
}

Vertex::Vertex(QVector3D xyz, QVector3D normals, QVector2D uv)
{
    m_xyz[0] = xyz.x();
    m_xyz[1] = xyz.y();
    m_xyz[2] = xyz.z();
    m_normal[0] = normals.x();
    m_normal[1] = normals.y();
    m_normal[2] = normals.z();
    m_st[0] = uv.x();
    m_st[1] = uv.y();
}

std::ostream& operator<< (std::ostream& os, const Vertex& v) {
  os << std::fixed << std::setprecision(2) << std::setw(10);
  os << "(" << v.m_xyz[0] << ", " << v.m_xyz[1] << ", " << v.m_xyz[2] << ") ";
  os << "(" << v.m_normal[0] << ", " << v.m_normal[1] << ", " << v.m_normal[2] << ") ";
  os << "(" << v.m_st[0] << ", " << v.m_st[1] << ") ";
  return os;
}

std::istream& operator>> (std::istream& is, Vertex& v) {
// Trenger fire temporære variabler som kun skal lese inn parenteser og komma
  char dum, dum2, dum3, dum4;
  is >> dum >> v.m_xyz[0] >> dum2 >> v.m_xyz[1] >> dum3 >> v.m_xyz[2] >> dum4;
  is >> dum >> v.m_normal[0] >> dum2 >> v.m_normal[1] >> dum3 >> v.m_normal[2] >> dum4;
  is >> dum >> v.m_st[0] >> dum2 >> v.m_st[1] >> dum3;
  return is;
}
