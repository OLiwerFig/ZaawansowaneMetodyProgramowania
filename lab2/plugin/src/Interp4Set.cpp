#include <iostream>
#include "Interp4Set.hh"

using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

/*!
 *
 */
Interp4Set::Interp4Set() {
    _position[0] = _position[1] = _position[2] = 0; 
    _angles[0] = _angles[1] = _angles[2] = 0;
}

/*!
 *
 */
void Interp4Set::PrintCmd() const {
    cout << GetCmdName() << "Nazwa: " << _object_name 
    << "  X " << _position[0] << "  Y " << _position[1] 
    << "  Z " << _position[2] << " kat obrotu wokol x: " << _angles[0] 
    << "  y: " << _angles[1] << " z: " << _angles[2] << endl;  
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Set::ExecCmd(AbstractScene &rScn, 
                         const char *sMobObjName, 
                         AbstractComChannel &rComChann) 
{
   
  AbstractMobileObj* wObMob = rScn.FindMobileObj(sMobObjName);

    if( wObMob == nullptr )
    {
        std::cerr<<"Obiekt o nazwie: "<<sMobObjName<< " nie istnieje" <<endl;
        return false;
    }

    wObMob->SetPosition_m(Vector3D(_position[0], _position[1], _position[2]));
    wObMob->SetAng_Yaw_deg(_angles[0]);
    wObMob->SetAng_Roll_deg(_angles[1]);
    wObMob->SetAng_Roll_deg(_angles[2]);

  return true;
}

/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList) 
{
    if(!(Strm_CmdsList >> _object_name))
    {
        std::cerr << "Nie wczytano nazwy obiektu"<< endl;
        return false;
    }

    if(!(Strm_CmdsList >> _position[0]))
    {
        std::cerr << "Pozycja x nie zostala wczytana"<< endl;
        return false;
    }

    if(!(Strm_CmdsList >> _position[1]))
    {
        std::cerr << "Pozycja y nie zostala wczytana"<< endl;
        return false;
    }

    if(!(Strm_CmdsList >> _position[2]))
    {
        std::cerr << "Pozycja z nie zostala wczytana"<< endl;
        return false;
    }

    if(!(Strm_CmdsList >> _angles[0]))
    {
        std::cerr << "Kat wokol x nie zostal wczytany"<< endl;
        return false;
    }

    if(!(Strm_CmdsList >> _angles[1]))
    {
        std::cerr << "Kat wokol y nie zostal wczytany"<< endl;
        return false;
    }

    if(!(Strm_CmdsList >> _angles[2]))
    {
        std::cerr << "Kat wokol z nie zostal wczytany"<< endl;
        return false;
    }
    return true;
}

/*!
 *
 */
AbstractInterp4Command* Interp4Set::CreateCmd() 
{
    return new Interp4Set();
}

/*!
 *
 */
void Interp4Set::PrintSyntax() const 
{
    cout << "   Set Object_Name X Y Z AngleOX AngleOY AngleOZ" << endl;
}


/*!
 *
 */
void Interp4Set::PrintParams() const
{
    std::cout<<"Nazwa obiektu "<<_object_name <<" pozycja x: "<<_position[0]<<" y: "<<_position[1]<<" z: "<<_position[2]<<" kat obrotu wokol x: "<<_angles[0]<<" y: "<<_angles[1]<<" z: "<<_angles[1] <<endl;
}


