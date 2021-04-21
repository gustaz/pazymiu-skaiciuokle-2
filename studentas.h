#ifndef STUDENTASH
#define STUDENTASH

#include "zmogus.h"
#include <vector>

class Studentas : public Zmogus {
private:
    int egz;
    std::vector<int> nd;
    double vid, med;
public:
    Studentas() : egz(0), vid(0), med(0) { Zmogus::vardas = "", Zmogus::pavarde = ""; }
    Studentas(std::string vardas_, std::string pavarde_, int egz, std::vector<int> nd, double vid, double med) : egz(egz), vid(vid), med(med) { vardas = vardas_; pavarde = pavarde_; }
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
    ~Studentas(){}
    
    Studentas(std::string vardas, std::string pavarde, int egz, std::vector<int> nd);
    inline int getEgz() const { return egz; }
    inline std::vector<int> getNd() const { return nd; }
    inline double getVid() const { return vid; }
    inline double getMed() const { return med; }
    inline void setEgz(int egz) { Studentas::egz = egz; }
    inline void addOneNd(int ndn) { nd.push_back(ndn); }
    inline void addNd(std::vector<int> nd) { Studentas::nd = nd; }
    inline void setVid(double vid) { Studentas::vid = vid; }
    inline void setMed(double med) { Studentas::med = med; }
};

#endif