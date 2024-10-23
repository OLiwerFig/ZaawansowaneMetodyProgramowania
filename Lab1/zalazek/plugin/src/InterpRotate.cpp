#include <iostream>
#include "InterpRotate.hh"


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
AbstractInterp4Command* CreateCmd(void)
{
  return InterpRotate::CreateCmd();
}


/*!
 *
 */
InterpRotate::InterpRotate(): _Speed_mmS(0),
                                angle(0)
{}


/*!
 *
 */
void InterpRotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << "         " << GetCmdName() << "         " << _Speed_mmS  << " 10 2" << "         " << angle << "  na 360" << endl;    
}


/*!
 *
 */
const char* InterpRotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool InterpRotate::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool InterpRotate::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
AbstractInterp4Command* InterpRotate::CreateCmd()
{
  return new InterpRotate();
}


/*!
 *
 */
void InterpRotate::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  KątObrotu[m]" << endl;
}
