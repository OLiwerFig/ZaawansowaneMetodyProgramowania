#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <map>
#include <memory>
#include <fstream>  // Dodaj ten nagłówek dla std::ifstream
#include <iostream>
#include <list>


#include "xmlinterp.hh"
#include "AbstractInterp4Command.hh"
#include "LibInterface.hh"


#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>



using namespace std;
using namespace xercesc;





/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */

bool ReadFile(const char* sFileName, Configuration &rConfig)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}















void _macro(std::string filename)
{
  std::string cmd = "cpp -P "+filename+" -o "+filename+".tmp";
  system(cmd.c_str());
}

int main( int argc, const char *argv[])
{



  std::string instructions_filename_pre_macro;
  std::string instructions_filename;
  std::string config_filename;

  Configuration   Config;


  if(argc < 2){
    std::cout << "Nie poprawna liczba parametrów wejsciowych" << std::endl;
    return 1;
  }

  instructions_filename_pre_macro = argv[1];
  config_filename = std::string(argv[2]);

 



  _macro(instructions_filename_pre_macro);

  instructions_filename = std::string(argv[1]) + ".tmp";


  if (!ReadFile(config_filename.c_str(), Config)) return 1;



  std::map<std::string, std::shared_ptr<LibInterface>> libsMap;


  libsMap["Move"] = std::make_shared<LibInterface>();
  if (!libsMap["Move"]->init("libs/libInterp4Move.so", "Move")) {
    std::cerr << "Błąd ładowania wtyczki libInterp4Move" << std::endl;
  }

  libsMap["Rotate"] = std::make_shared<LibInterface>();
  if (!libsMap["Rotate"]->init("libs/libInterp4Rotate.so", "Rotate")) {
    std::cerr << "Błąd ładowania wtyczki libInterp4Rotate" << std::endl;
  }

  libsMap["Set"] = std::make_shared<LibInterface>();
  if (!libsMap["Set"]->init( "libs/libInterp4Set.so", "Set")) {
    std::cerr << "Błąd ładowania wtyczki libInterp4Set" << std::endl;
  }

  libsMap["Pause"] = std::make_shared<LibInterface>();
  if (!libsMap["Pause"]->init( "libs/libInterp4Pause.so", "Pause")) {
      std::cerr << "Błąd ładowania wtyczki libInterp4Pause" << std::endl;
  }




  // Otwieranie strumienia pliku instructions_filename
  std::ifstream instructionsStream(instructions_filename);
  if (!instructionsStream.is_open()) {
    std::cerr << "Błąd otwierania pliku: " << instructions_filename << std::endl;
    return false;
  }


  std::string cmd;
  while (true) {
    
    if(! (instructionsStream >> cmd)){
      break;
    }

    if (libsMap.find(cmd) == libsMap.end()) {
      std::cerr << "!!! Nieznane polecenie: " << cmd << std::endl;
      return false;
    }
    
    AbstractInterp4Command *pCmd = libsMap[cmd]->createCmd();
    if (!pCmd) {
      std::cerr << "!!! Blad tworzenia polecenia: " << cmd << std::endl;
      return false;
    }

    if (!pCmd->ReadParams(instructionsStream)) {
      std::cerr << "!!! Blad wczytywania parametrow polecenia: " << cmd << std::endl;
      return false;
    }

    pCmd->PrintCmd();

    delete pCmd;
  }

  return 0;
}
