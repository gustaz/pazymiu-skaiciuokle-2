#ifndef STUDENTASH
#define STUDENTASH

#include "zmogus.h"
#include "ManoVector.h"

//! Studento klase. 
/*!
  Studento klase, laikanti visus su studentu susijusius duomenis. Paveldi is zmogaus klases.
*/

class Studentas : public Zmogus {
private:
    int egz; /*!< Studento gautas egzamino ivertis */
    ManoVector<int> nd; /*!< Studento namu darbu aibe */
    double vid; /*!< Studento aritmetinis vidurkis */
    double med; /*!< Studento pazymiu mediana */
public:
    //! Studento konstruktorius.
    /*!
      Konstruktorius su priskirtomis bazinemis reiksmemis.
    */
    Studentas() : egz(0), vid(0), med(0) { Zmogus::vardas = "", Zmogus::pavarde = ""; }

    Studentas(std::string vardas_, std::string pavarde_, int egz, ManoVector<int> nd, double vid, double med) : egz(egz), vid(vid), med(med) { vardas = vardas_; pavarde = pavarde_; }
    //! Copy konstruktorius.
    /*!
      Konstruktorius skirtas perduoti parametrus is vieno sios klases objekto kitam.
    */
    Studentas (const Studentas& a) : egz(a.getEgz()) , vid(a.getVid()), med(a.getMed())
    {
        vardas = a.getVardas();
        pavarde = a.getPavarde();
        
        nd.reserve(a.getNd().size());
        for(int i : a.getNd()) 
        {
            nd.push_back(i);
        }
    }
    //! Copy assignment operatorius.
    /*!
      Operatorius skirtas copy assignment operacijos igalinimui.
    */
    Studentas& operator=(const Studentas& a) 
    {
        if(&a == this) return *this;

        vardas = a.getVardas();
        pavarde = a.getPavarde();
        egz = a.getEgz();
        vid = a.getVid();
        med = a.getMed();
        nd.clear();
        nd.shrink_to_fit();
        nd.reserve(a.getNd().size());
        for(int i : a.getNd()) 
        {
            nd.push_back(i);
        }
        return *this;
    }
    //! Destruktorius.
    /*!
      Objekto destruktorius.
    */
    ~Studentas(){}
    //! Member funkcija egzamino iverciui gauti.
    /*!
      \return egz
    */
    inline int getEgz() const { return egz; }
    //! Member funkcija namu darbu aibei gauti.
    /*!
      \return pavarde
    */
    inline ManoVector<int> getNd() const { return nd; }
    //! Member funkcija aritmetiniui vidurkiui gauti.
    /*!
      \return vid
    */
    inline double getVid() const { return vid; }
    //! Member funkcija medianai gauti.
    /*!
      \return med
    */
    inline double getMed() const { return med; }
    //! Member funkcija egzaminui nustatyti
    /*!
      \param egz egzamino pazymys kuris bus nustatomas
    */
    inline void setEgz(int egz) { Studentas::egz = egz; }
    //! Member funkcija vienam pazymiui prie pazymiu aibes prideti
    /*!
      \param ndn namu darbo ivertinimas, kuris bus pridedamas
    */
    inline void addOneNd(int ndn) { nd.push_back(ndn); }
    //! Member funkcija nustatyti visiems namu darbams
    /*!
      \param nd kuri namu darbu aibe bus nustatoma 
    */
    inline void addNd(ManoVector<int> nd) { Studentas::nd = nd; }
    //! Member funkcija aritmetiniam vidurkiui nustatyti
    /*!
      \param vid kuris aritmetinis vidurkis bus nustatomas
    */
    inline void setVid(double vid) { Studentas::vid = vid; }
    //! Member funkcija medianai nustatyti
    /*!
      \param vid kuri mediana bus nustatoma
    */
    inline void setMed(double med) { Studentas::med = med; }
};

#endif