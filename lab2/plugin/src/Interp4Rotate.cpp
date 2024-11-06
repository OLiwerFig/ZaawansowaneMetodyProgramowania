#include <iostream>
#include "Interp4Rotate.hh"
#include <unistd.h>

using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}


/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void) {
    return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate() : _object_name(""), _axis_name(""), _angular_velocity(0), _rotate_angle(0) {}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const {
    cout << GetCmdName() << "  Nazwa_Obiektu: " << _object_name << "    Oś: " << _axis_name 
         << "    Prędkość: " << _angular_velocity << " stopni/s "
         << "    Kąt: " << _rotate_angle << " stopni" << endl;
}

/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const {
    return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Rotate::ExecCmd(AbstractScene &rScn, 
                            const char *sMobObjName, 
                            AbstractComChannel &rComChann) {
    AbstractMobileObj* wObMob = rScn.FindMobileObj(sMobObjName);

    if (wObMob == nullptr) {
        std::cerr << "Obiekt: " << sMobObjName << " nie istnieje"<< endl;
        return false;
    }

    double start_angle = 0;

    if (this->_axis_name == "OX") {
        start_angle = wObMob->GetAng_Pitch_deg();
    } else if (this->_axis_name == "OY") {
        start_angle = wObMob->GetAng_Roll_deg();
    } else if (this->_axis_name == "OZ") {
        start_angle = wObMob->GetAng_Yaw_deg();
    } else {
        std::cerr << "Wybrano nieprawidlową oś: " << this->_axis_name << endl;
        return false;
    }

    double delta_deg = 0;
    double dist_step_deg = static_cast<double>(_rotate_angle) / N;
    double time_step_us = (static_cast<double>(this->_rotate_angle) / this->_angular_velocity * 1000000) / N;

    for (int i = 0; i < N; ++i) {
        delta_deg += dist_step_deg;

        if (this->_axis_name == "OX") {
            wObMob->SetAng_Pitch_deg(delta_deg + start_angle);
        } else if (this->_axis_name == "OY") {
            wObMob->SetAng_Roll_deg(delta_deg + start_angle);
        } else if (this->_axis_name == "OZ") {
            wObMob->SetAng_Yaw_deg(delta_deg + start_angle);
        }

        usleep(time_step_us);
    }

return true;
}

/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList) {
    if(!(Strm_CmdsList >> _object_name))
    {
        std::cerr << "Nazwa obiektu nie zostala wczytana"<< endl;
        return false;
    }

    if(!(Strm_CmdsList >> _axis_name))
    {
        std::cerr << "Nazwa osi nie zostala wczytana"<< endl;
        return false;
    }

    if(!(Strm_CmdsList >> _angular_velocity))
    {
        std::cerr << "Predkosc kątowa nie zostala wczytana"<< endl;
        return false;
    }

    if(!(Strm_CmdsList >> _rotate_angle))
    {
        std::cerr << "Kat obrotu nie zostal wczytany"<< endl;
        return false;
    }
    return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}



/*!
 *
 */
void Interp4Rotate::PrintSyntax() const {
    cout << "   Rotate Object_Name Axis_Name Angular_Velocity[deg/s] Rotate_Angle[degrees]" << endl;
}

/*!
 *
 */
void Interp4Rotate::PrintParams() const
{
    std::cout<<"Nazwa obiektu "<<_object_name<<" Nazwa osi "<<_axis_name<<" Predkości obrotowa "<<_angular_velocity<<" kąt obrotu "<< _rotate_angle << endl;
} 






