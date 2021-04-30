#ifndef ZMOGUSH
#define ZMOGUSH

//! Bazine zmogaus klase. 
/*!
  Abstrakti klase skirta is kurios paveldi studentas klase.
*/

class Zmogus {
protected:
    std::string vardas; /*!< Zmogaus vardas */
    std::string pavarde; /*!< Zmogaus pavarde */

public:
    //! Virtualus destruktorius.
    /*!
      Sis destruktorius klase pavercia abstrakcia.
    */
    virtual ~Zmogus() = 0;
    //! Member funkcija vardui gauti.
    /*!
      \return Vardas
    */
    std::string getVardas() const { return vardas; }
    //! Member funkcija pavardei gauti.
    /*!
      \return Pavarde
    */
    std::string getPavarde() const { return pavarde; }
    //! Member funkcija vardui nustatyti.
    /*!
      \param vardas kuris vardas bus nustatomas
    */
    void setVardas(std::string vardas) { Zmogus::vardas = vardas; }
    //! Member funkcija pavardei nustatyti.
    /*!
      \param pavarde kuri pavarde bus nustatomas
    */
    void setPavarde(std::string pavarde) { Zmogus::pavarde = pavarde; }
};
//! Destruktoriaus deklaracija.
/*!
  Virtualaus destruktoriaus deklaracija reikalinga klases parametrizacijai.
*/
inline Zmogus::~Zmogus() {
}

#endif