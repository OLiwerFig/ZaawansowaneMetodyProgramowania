#ifndef  COMMAND4SET_HH
#define  COMMAND4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"


/*!
 * \file
 * \brief Definicja klasy Interp4Pause
 *
 * Plik zawiera definicję klasy Interp4Pause ...
 */

/*!
 * \brief Modeluje polecenie pauzy
 *
 *  Klasa modeluje komende pauzy
 */
class Interp4Set: public AbstractInterp4Command {
    std::string _object_name;
    double _position[3]; //x,y,z
   // int _positions[3]; 
    int _angles[3];  //OX, OY, OZ
 public:
  /*!
   * \brief
   */
  Interp4Set();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const override;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const override;
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() const override;

  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const override;

  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   *
   * Wykonuje polecenie oraz wizualizuje jego realizację.
   * \param[in,out]  rScn - scena zawierającą obiekty mobilne,
   * \param[in]      sMobObjName - wskaźnik na nazwę lokalizującą i identyfikującą obiekt,
   * \param[in,out]  rComChann - kanał komunikacyjny z serwerem graficznym.
   * \retval true - operacja powiodła się,
   * \retval false - w przypadku przeciwnym.
   */
  virtual bool ExecCmd( AbstractScene      &rScn, 
                        const char         *sMobObjName,
                        AbstractComChannel &rComChann ) override;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList) override;

  
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static AbstractInterp4Command* CreateCmd();

 };

#endif
