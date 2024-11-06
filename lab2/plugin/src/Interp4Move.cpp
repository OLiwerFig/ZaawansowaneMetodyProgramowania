#include <iostream>
#include <unistd.h>
#include "Interp4Move.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}


/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _speed_mmS(0), _distance_mm(0){}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() << "  Nazwa: "<<_object_name << "  Prędkość: " << _speed_mmS  << "  Dystans: " <<_distance_mm << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd(AbstractScene &rScn, 
                          const char *sMobObjName, 
                          AbstractComChannel &rComChann)
{

    AbstractMobileObj* wObMob = rScn.FindMobileObj(sMobObjName);
    if (wObMob == nullptr) {
        std::cerr << "Nie mogę znaleźć obiektu: " << sMobObjName << std::endl;
        return false;
    }


    Vector3D startPos = wObMob->GetPositoin_m();
    double startRoll = wObMob->GetAng_Roll_deg() * M_PI / 180;
    double startPitch = wObMob->GetAng_Pitch_deg() * M_PI / 180;
    double startYaw = wObMob->GetAng_Yaw_deg() * M_PI / 180;

    
    double dist_step_m = static_cast<double>(_distance_mm) / N;
    double time_step_us = (static_cast<double>(_distance_mm) / _speed_mmS* 1000000) / N;

    double cosPitch = cos(startPitch);
    double sinPitch = sin(startPitch);
    double cosYaw = cos(startYaw);
    double sinYaw = sin(startYaw);
    double cosRoll = cos(startRoll);
    double sinRoll = sin(startRoll);

    Vector3D deltaPos = startPos;


    for (int i = 0; i < N; ++i) {
        deltaPos[0] += dist_step_m * cosPitch * cosYaw;
        deltaPos[1] += dist_step_m * (cosRoll * sinYaw + cosYaw * sinPitch * sinRoll);
        deltaPos[2] += dist_step_m * (sinRoll * sinYaw - cosRoll * cosYaw * sinPitch);
        
        wObMob->SetPosition_m(deltaPos);
        usleep(time_step_us);
    }

    return true;
}



/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> _object_name))
    {
        std::cout << "Nazwa obiektu nie zostala wczytana"<< std::endl;
        return false;
    }

    if(!(Strm_CmdsList >> _speed_mmS))
    {
        std::cout << "Predkosc nie zostala wczytana"<< std::endl;
        return false;
    }

    if(!(Strm_CmdsList >> _distance_mm))
    {
        std::cout << "Dystans nie zostal wczytany"<< std::endl;
        return false;
    }

  return true;
}



/*!
 *
 */
AbstractInterp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}



/*!
 *
 */
void Interp4Move::PrintParams() const
{
    std::cout<<"   Nazwa obiektu "<< _object_name<<" prędkość[m/s] "<< _speed_mmS <<" dystans "<<_distance_mm << endl;
} 


