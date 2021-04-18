#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <functional>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <io.h>
#include <direct.h>
#include <list>
#include <deque>
#include <iterator>

#ifdef _WIN32
#define WINPAUSE system("pause")
#endif

static std::chrono::steady_clock::time_point clockStart;
extern double accumulatedTime;

struct Studentas 
{
	std::string vardas, pavarde;
	std::vector<int> nd;
	int egzaminas = 0;
	double galutinisVid = 0;
	double galutinisMed = 0;
};

struct compSurname
{
	inline bool operator() (const Studentas& struct1, const Studentas& struct2)
	{
		return (struct1.pavarde.compare(struct2.pavarde)) < 0;
	}
};

struct compGrade
{
	inline bool operator() (const Studentas& struct1, const Studentas& struct2)
	{
		return (struct1.galutinisVid < struct2.galutinisVid);
	}
};

struct isKietiakas
{
	inline bool operator() (const Studentas& struct1)
	{
		return (struct1.galutinisVid >= 5.00);
	}
};

inline bool fileExists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

auto static nowForSeed = std::chrono::high_resolution_clock::now();
auto static timeInMSForSeed = std::chrono::duration_cast<std::chrono::milliseconds>(nowForSeed.time_since_epoch()).count();

static std::mt19937::result_type seed = timeInMSForSeed;
auto static gradeGen = std::bind(std::uniform_int_distribution<int>(1, 10),
	std::mt19937(seed));

void checkInput(int& skaicius, bool limited);
void checkInput(char& ivestis);
void askForGeneration();
void generateFile(int numberOfStudents, std::ofstream& output);
void generateDirectories(std::string directory);
double findMedian(std::vector<int> grades, int n);

template <class T>
void readFromFile(T& studentai)
{
	Studentas student;

	std::ifstream input;

	int pasirinkimas;

	std::cout << "Pasirinkite, kuri faila norite skaityti: "
		<< std::endl << "(1) studentai1000.txt"
		<< std::endl << "(2) studentai10000.txt"
		<< std::endl << "(3) studentai100000.txt"
		<< std::endl << "(4) studentai1000000.txt"
		<< std::endl << "(5) studentai10000000.txt"
		<< std::endl << "(6) sortdemo.txt"
		<< std::endl << "(7) kursiokai.txt"
		<< std::endl;

	std::cout << "Jusu pasirinkimas: ";
	std::cin >> pasirinkimas;

	try
	{
		while (true)
		{
			switch (pasirinkimas)
			{
			case 1:
				input.open("data/input/studentai1000.txt");
				break;
			case 2:
				input.open("data/input/studentai10000.txt");
				break;
			case 3:
				input.open("data/input/studentai100000.txt");
				break;
			case 4:
				input.open("data/input/studentai1000000.txt");
				break;
			case 5:
				input.open("data/input/studentai10000000.txt");
				break;
			case 6:
				input.open("data/input/sortdemo.txt");
				break;
			case 7:
				input.open("data0/input/kursiokai.txt");
				break;
			default:
			{
				std::cout << "Ivedete klaidinga reiksme! Pasirinkite skaiciu nuo 1 iki 7: ";
				std::cin >> pasirinkimas;
				continue;
			}
			}
			break;
		}
		if (!input.good())
			throw 1;
	}
	catch (int err)
	{
		std::cout << "Pasirinktas failas nerastas! Programos veikla uzbaigiama.";
		exit(1);
	}

	clockStart = std::chrono::steady_clock::now();
	input.ignore(256, '\n');

	try
	{
		while (!input.eof())
		{

			std::string line, vardas, pavarde;

			input >> vardas >> pavarde;
			getline(input, line);

			std::stringstream stream(line);
			std::vector<int> values;

			int n;
			while (stream >> n)
			{
				values.push_back(n);
			}

			if (line.length() != 0)
			{
				values.pop_back();
				student.egzaminas = n;
				student.nd = values;
				student.vardas = vardas;
				student.pavarde = pavarde;
				studentai.push_back(student);
			}
		}
	}
	catch (std::bad_alloc& exception)
	{
		input.ignore(256, '\n');
		std::cout << "Programa aptiko klaidu faile! Tolimesnis sklandus veikimas negarantuojamas."
			<< std::endl;
	}

	input.close();

	std::cout << "Failo duomenys nuskaityti. "
		<< std::endl;
	std::cout << "Nuskaitymas uztruko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
	accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
}

template <class T>
void readFromFileAutomated(T& studentai, int studentuSkaicius, std::ifstream& input)
{
	Studentas student;
	std::string fileName = "studentai" + std::to_string(studentuSkaicius) + ".txt";
	input.open("data/input/" + fileName);
	input.ignore(256, '\n');
	
	try
	{
		while (!input.eof())
		{

			std::string line, vardas, pavarde;

			input >> vardas >> pavarde;
			getline(input, line);

			std::stringstream stream(line);
			std::vector<int> values;
			int n = 0;
			double avg = 0;
			while (stream >> n)
			{
				values.push_back(n);
				avg += n;
			}

			if (line.length() != 0)
			{
				avg -= n;
				values.pop_back();
				avg /= values.size();
				student.egzaminas = n;
				student.nd = values;
				student.galutinisVid = 0.4 * avg + 0.6 * student.egzaminas;
				student.galutinisMed = findMedian(student.nd, student.nd.size()) * 0.4 + student.egzaminas * 0.6;
				student.vardas = vardas;
				student.pavarde = pavarde;
				studentai.push_back(student);
			}
		}
	}
	catch (std::bad_alloc& exception)
	{
		input.ignore(256, '\n');
		std::cout << "Programa aptiko klaidu faile! Tolimesnis sklandus veikimas negarantuojamas."
			<< std::endl;
	}
	input.close();
}

template <class T>
void inputStudent(T& studentai)
{
	Studentas stud;
	char pasirinkimas;
	int n;

	std::cout << "Iveskite studento varda: ";
	getline(std::cin, stud.vardas);

	std::cout << "Iveskite studento pavarde: ";
	getline(std::cin, stud.pavarde);

	std::cout << "Pradedami ivesti studento " << stud.vardas << " " << stud.pavarde << " duomenys."
		<< std::endl
		<< "Ar zinomas tikslus atliktu namu darbu skaicius? (T/N): ";

	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);

	if (tolower(pasirinkimas) == 't')
	{
		std::cout << "Iveskite studento atliktu namu darbu skaiciu: ";
		std::cin >> n;
		checkInput(n, false);

		std::cout << "Dabar yra suteikiama galimybe pasirinkti ivedima."
			<< " Duomenys vedami arba ranka, arba generuojami atsitiktinai."
			<< std::endl
			<< "Ar norite duomenis generuoti atsitiktinai? (T/N): ";

		std::cin >> pasirinkimas;
		checkInput(pasirinkimas);

		if (tolower(pasirinkimas) == 't')
		{
			std::cout << "Pasirinkta duomenis generuoti atsitiktine tvarka.";

			for (int i = 0; i < n; i++)
				stud.nd.push_back(gradeGen());

			stud.egzaminas = gradeGen();

			std::cout << std::endl
				<< "Gauti pazymiai: ";
			for (int i = 0; i < stud.nd.size(); i++)
				std::cout << stud.nd[i] << " ";

			std::cout << std::endl
				<< "Gautas egzamino ivertinimas: "
				<< stud.egzaminas
				<< std::endl;
		}
		else if (tolower(pasirinkimas) == 'n')
		{
			std::cout << "Pasirinktas duomenu ivedimas ranka." <<
				std::endl;

			for (int i = 0; i < n; i++)
			{
				int ivestis;
				std::cout << "Iveskite " << i + 1 << "-aji pazymi: ";
				std::cin >> ivestis;
				checkInput(ivestis, true);
				stud.nd.push_back(ivestis);
			}
			std::cout << "Iveskite egzamino pazymi: ";
			std::cin >> stud.egzaminas;
			checkInput(stud.egzaminas, true);

			std::cout << "Baigtas duomenu ivedimas."
				<< std::endl;
		}
	}
	else if (tolower(pasirinkimas) == 'n')
	{
		std::cout << "Kadangi studento namu darbu skaicius nezinomas,"
			<< " atliekama ivestis rankiniu budu."
			<< std::endl;

		std::cout << "Noredami nutraukti pazymiu ivedima, pazymi suveskite 0."
			<< std::endl;

		while (true)
		{
			int ivestis;
			std::cout << "Iveskite " << stud.nd.size() + 1 << "-aji pazymi: ";
			std::cin >> ivestis;
			checkInput(ivestis, true);

			if (ivestis == 0 && stud.nd.size() > 0)
			{
				std::cout << "Iveskite egzamino pazymi: ";
				std::cin >> stud.egzaminas;
				checkInput(stud.egzaminas, true);
				break;
			}
			else if (ivestis == 0 && stud.nd.size() == 0)
				std::cout << "Studentas turi tureti bent viena pazymi!"
				<< std::endl;

			stud.nd.push_back(ivestis);
		}
	}
	studentai.push_back(stud);
}

template <class T>
void writeToConsoleAvg(T& studentai, std::ostream& out)
{
	out << std::left
		<< std::setw(20) << "Pavarde"
		<< std::setw(15) << "Vardas"
		<< std::setw(10) << "Galutinis " << "(Vid.)" << "\n"
		<< std::string(65, '-')
		<< "\n";

	for (auto const& i : studentai)
	{
		out << std::left
			<< std::setw(20) << i.pavarde
			<< std::setw(15) << i.vardas
			<< std::setw(15) << std::fixed << std::setprecision(2) << i.galutinisVid
			<< "\n";
	}
}

template <class T>
void writeToConsoleMed(T& studentai, std::ostream& out)
{
	out << std::left
		<< std::setw(20) << "Pavarde"
		<< std::setw(15) << "Vardas"
		<< std::setw(10) << "Galutinis " << "(Med.)" << "\n"
		<< std::string(65, '-')
		<< "\n";

	for (auto const& i : studentai)
	{
		out << std::left
			<< std::setw(20) << i.pavarde
			<< std::setw(15) << i.vardas
			<< std::setw(15) << std::fixed << std::setprecision(2) << i.galutinisMed
			<< "\n";
	}

}

template <class T>
void workFlow(T& studentai, int studentuFailuDydziai, std::ifstream& input, std::ofstream& output, char* type, double& benchmarkTime)
{
	std::cout << "Vykdomas failo nuskaitymas." << std::endl;
	clockStart = std::chrono::steady_clock::now();
	readFromFileAutomated(studentai, studentuFailuDydziai, input);
	benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
	std::cout << studentuFailuDydziai << " studentu failo nuskaitymas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
}

template <class T>
void thenPrint(T& studentai, T& vargsiukai, int studentuFailuDydziai, std::ofstream& output, double& benchmarkTime, char container[])
{
	clockStart = std::chrono::steady_clock::now();
	std::cout << "Vykdomas " << studentuFailuDydziai << " studentu duomenu isvedimas i faila." << std::endl;

	std::string containerName = container;
	output.open("data/output/kietiakai" + containerName + std::to_string(studentuFailuDydziai) + ".txt");
	writeToConsoleAvg(studentai, output);
	output.close();

	output.open("data/output/vargsiukai" + containerName + std::to_string(studentuFailuDydziai) + ".txt");
	writeToConsoleAvg(vargsiukai, output);
	output.close();

	std::cout << "Isvestis truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
	benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
	accumulatedTime += benchmarkTime;
	std::cout << studentuFailuDydziai << " isvedimas is viso truko: " << benchmarkTime << " s" << std::endl;
}
void generationSequence(int studentuFailuDydziai, std::ofstream& output, double& benchmarkTime);

#endif