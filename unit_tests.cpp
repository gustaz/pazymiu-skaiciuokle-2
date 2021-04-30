#define CATCH_CONFIG_MAIN
#include "declarations.h"

//! Unit testai studento klasei patikrinti.
TEST_CASE("Studento klases patikrinimas", "[Studentas]") 
{

    Studentas studentas;

    REQUIRE(studentas.getNd().size() == 0);
    SECTION("Nustatomas vardas ir pavarde") 
    {
        studentas.setVardas("Bandymas");
        studentas.setPavarde("BBandymas");

        REQUIRE(studentas.getVardas() == "Bandymas");
        REQUIRE(studentas.getPavarde() == "BBandymas");
    }
    SECTION("Pridedamas vienas namu darbas") 
    {
        studentas.addOneNd(10);

        REQUIRE(studentas.getNd().size() == 1);
        REQUIRE(studentas.getNd().at(0) == 10);
    }
    SECTION("Paimama namu darbu aibe") 
    {
        std::vector<int> ndList{10, 5, 7, 4, 10};
        studentas.addNd(ndList);

        REQUIRE(studentas.getNd().size() == 5);
        REQUIRE(studentas.getNd() == ndList);
    }
}