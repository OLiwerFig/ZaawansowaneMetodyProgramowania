#ifndef VECTOR3D_HH
#define VECTOR3D_HH

#include "geomVector.hh"

/*!
 * \file
 * \brief Deklaracja instacji szablonu geom::Vector
 */

 /*!
  * \brief Instacja szablonu geom::Vector<typename,int> dla przestrzeni 3D.
  */
//  typedef geom::Vector<double,3>  Vector3D;

class Vector3D : public geom::Vector<double,3>
{
    public:

    Vector3D(double x,double y,double z)
    {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
    }

};

#endif
