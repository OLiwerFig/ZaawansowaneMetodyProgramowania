#include "LibInterface.hh"


LibInterface::LibInterface() {
}



bool LibInterface::init(const std::string & library_name, const std::string & cmd_name ){

     _LibHandler = dlopen(library_name.c_str(), RTLD_LAZY);
    if (!_LibHandler) {
        return false;
    }
    _CmdName = cmd_name;
    _CreateCmd = (AbstractInterp4Command * (*)())dlsym(_LibHandler, "CreateCmd");
    if (!_CreateCmd) {
        return false;
    }

    return true;

}

LibInterface::~LibInterface()
{
    dlclose(_LibHandler);
    
}