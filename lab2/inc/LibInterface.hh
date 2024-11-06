#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH



#include "AbstractInterp4Command.hh"
#include <dlfcn.h>
#include <string>


class LibInterface
{
private:
    void * _LibHandler;
    std::string _CmdName;
    AbstractInterp4Command * (*_CreateCmd)(void);

public:
    LibInterface();
    ~LibInterface();
    
    bool init(const std::string & library_name, const std::string & cmd_name );
    const std::string & getCmdName() { return _CmdName; };
    AbstractInterp4Command * createCmd() { return _CreateCmd(); };
    
};



#endif