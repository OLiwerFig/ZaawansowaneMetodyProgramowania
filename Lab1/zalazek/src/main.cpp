#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"

using namespace std;


int main()
{
  void *pLibHnd_Rotate = dlopen("libInterpRotate.so",RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Rotate)(void);
  void *pFunRot;

  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: InterpRotate.so" << endl;
    return 1;
  }


  pFunRot = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!pFunRot) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFunRot);


  AbstractInterp4Command *pCmdRot = pCreateCmd_Rotate();

  cout << endl;
  cout << pCmdRot->GetCmdName() << endl;
  cout << endl;
  pCmdRot->PrintSyntax();
  cout << endl;
  pCmdRot->PrintCmd();
  cout << endl;
  
  delete pCmdRot;

  dlclose(pLibHnd_Rotate);

    void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);


  AbstractInterp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Move);

  
}
