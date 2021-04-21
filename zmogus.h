#ifndef ZMOGUSH
#define ZMOGUSH

class Zmogus {
protected:
    std::string vardas;
    std::string pavarde;
    
public:
    virtual ~Zmogus() = 0;
    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    void setVardas(std::string vardas) { Zmogus::vardas = vardas; }
    void setPavarde(std::string pavarde) { Zmogus::pavarde = pavarde; }
};

inline Zmogus::~Zmogus() {
}

#endif