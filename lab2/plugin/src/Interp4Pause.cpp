#include <iostream>
#include <unistd.h>
#include "Interp4Pause.hh"

using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}


/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


/*!
 *
 */
Interp4Pause::Interp4Pause() : _time_ms(0) {}


/*!
 *
 */
void Interp4Pause::PrintCmd() const 
{
    cout << GetCmdName() << " " << _time_ms << endl;

}

/*!
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Pause::ExecCmd(AbstractScene &rScn, 
                           const char *sMobObjName, 
                           AbstractComChannel &rComChann) 
{
    usleep(_time_ms*1000);
    return true;
}


/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList) 
{

  if(!(Strm_CmdsList >> _time_ms))
    {
        std::cerr << "Wystapil blad przy wczytywaniu czasu"<< endl;
        return false;
    }

    return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Pause::CreateCmd() {
    return new Interp4Pause();
}

/*!
 *
 */
void Interp4Pause::PrintSyntax() const {
    cout << " Pause Time_in_ms" << endl;
}



/*!
 *
 */
void Interp4Pause::PrintParams() const
{
    std::cerr<<"Czas pauzy: "<<_time_ms <<" ms"<<endl;   
}
