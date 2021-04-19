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