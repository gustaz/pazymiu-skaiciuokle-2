#ifndef STUDENTASH
#define STUDENTASH

#include <vector>

class Studentas {
private:
    std::string vardas, pavarde;
    int egz;
    std::vector<int> nd;
    double vid, med;
public:
    Studentas() : vardas(""), pavarde(""), egz(0), vid(0), med(0) { }
    Studentas(std::string vardas, std::string pavarde, int egz, std::vector<int> nd, double vid, double med) : vardas(vardas), pavarde(pavarde), egz(egz), vid(vid), med(med) { }
    Studentas (const Studentas& a) : vardas(a.getVardas()), pavarde(a.getPavarde()), egz(a.getEgz()) , vid(a.getVid()), med(a.getMed())
    {
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
    inline std::string getVardas() const { return vardas; }
    inline std::string getPavarde() const { return pavarde; }
    inline int getEgz() const { return egz; }
    inline std::vector<int> getNd() const { return nd; }
    inline double getVid() const { return vid; }
    inline double getMed() const { return med; }
    inline void setVardas(std::string vardas) { Studentas::vardas = vardas; }
    inline void setPavarde(std::string pavarde) { Studentas::pavarde = pavarde; }
    inline void setEgz(int egz) { Studentas::egz = egz; }
    inline void addOneNd(int ndn) { nd.push_back(ndn); }
    inline void addNd(std::vector<int> nd) { Studentas::nd = nd; }
    inline void setVid(double vid) { Studentas::vid = vid; }
    inline void setMed(double med) { Studentas::med = med; }
};

#endif