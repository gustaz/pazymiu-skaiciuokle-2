#include "declarations.h"

void askForGeneration()
{
	char pasirinkimas;
	std::ofstream output;
	
	generateDirectories("data");
	generateDirectories("data/input");

	std::cout << "Ar norite generuoti 1 000 studentu faila? (T/N): ";
	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);
	if (tolower(pasirinkimas) == 't')
	{
		clockStart = std::chrono::steady_clock::now();
		generateFile(1000, output);
		std::cout << 1000 << " studentu failo generavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
		accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
	}

	std::cout << "Ar norite generuoti 10 000 studentu faila? (T/N): ";
	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);
	if (tolower(pasirinkimas) == 't')
	{
		clockStart = std::chrono::steady_clock::now();
		generateFile(10000, output);
		std::cout << 10000 << " studentu failo generavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
		accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
	}

	std::cout << "Ar norite generuoti 100 000 studentu faila? (T/N): ";
	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);
	if (tolower(pasirinkimas) == 't')
	{
		clockStart = std::chrono::steady_clock::now();
		generateFile(100000, output);
		std::cout << 100000 << " studentu failo generavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
		accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
	}

	std::cout << "Ar norite generuoti 1 000 000 studentu faila? (T/N): ";
	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);
	if (tolower(pasirinkimas) == 't')
	{
		clockStart = std::chrono::steady_clock::now();
		generateFile(1000000, output);
		std::cout << 1000000 << " studentu failo generavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
		accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
	}

	std::cout << "Ar norite generuoti 10 000 000 studentu faila? (T/N): ";
	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);
	if (tolower(pasirinkimas) == 't')
	{
		clockStart = std::chrono::steady_clock::now();
		generateFile(10000000, output);
	}
}

void generateDirectories(std::string directory)
{
	try 
	{
		int dir = _mkdir(directory.c_str());

		if (dir == 0)
			std::cout << "Sukurta direktorija " + directory << "." << std::endl;
		else
			if (dir != 0 && errno == EEXIST)
			{
				std::cout << "Direktorija " + directory + " jau egzistuoja. Nieko nedaroma." << std::endl;
			}
		else throw(1);
	}
	catch (int err)
	{
		std::cout << "Ivyko klaida aplankalu kurimo metu! Programa nutraukia veikla.";
		exit(1);
	}
}

void generateFile(int numberOfStudents, std::ofstream& output)
{
	std::string fileName = "studentai" + std::to_string(numberOfStudents) + ".txt";
	output.open("data/input/" + fileName);
	output << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" ;

	int noOfHomework = 20;

	for (int i = 0; i < noOfHomework; i++)
	{
		output << std::setw(7) << "ND" + std::to_string(i + 1);
	}
	output << std::setw(7) << "Egz." << std::endl;

	for (int i = 0; i < numberOfStudents; i++)
	{
		int grades = gradeGen();
		output << std::setw(20) << "Vardas" + std::to_string(i + 1) << std::setw(20) << "Pavarde" + std::to_string(i + 1);

		for (int i = 0; i < noOfHomework; i++)
		{
			output << std::setw(7) << gradeGen();
		}
		output << std::setw(7) << gradeGen();
		if(i != numberOfStudents - 1) output << std::endl;
	}
	output.close();
}

void generationSequence(int studentuFailuDydziai, std::ofstream& output, double& benchmarkTime)
{
	std::cout << std::endl << "Pradedamas darbas su "
		<< studentuFailuDydziai << " duomenimis." << std::endl;

	clockStart = std::chrono::steady_clock::now();
	std::cout << "Vykdomas failo generavimas." << std::endl;
	generateFile(studentuFailuDydziai, output);
	std::cout << studentuFailuDydziai << " studentu failo generavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
	benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
}

double findMedian(std::vector<int> grades, int n)
{
	if (n % 2 == 0) {

		nth_element(grades.begin(), grades.begin() + n / 2, grades.end());

		nth_element(grades.begin(), grades.begin() + (n - 1) / 2, grades.end());

		return (double)(grades[(n - 1) / 2] + grades[n / 2]) / 2.0;
	}
	else {
		nth_element(grades.begin(), grades.begin() + n / 2, grades.end());
		return (double)grades[n / 2];
	}
}

void checkInput(int& skaicius, bool limited)
	{
		while (std::cin.fail() || skaicius < 0 || skaicius > 10)
		{
			if (std::cin.fail())
				std::cout
				<< "Ivedete reiksme, netenkinancia salygos! (Gal netycia vietoje skaiciaus ivedete raide?)"
				<< std::endl;

			else if (skaicius <= 0)
				std::cout
				<< "Ivedete reiksme, netenkinancia salygos! (Skaicius negali buti mazesne uz 0!)"
				<< std::endl;
			else if (skaicius > 10)
			{
				if (!limited) break;

				std::cout
					<< "Ivedete reiksme, netenkinancia salygos! (Skaicius negali buti didesnis uz 10!)"
					<< std::endl;
			}
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Pakartokite ivedima: ";
			std::cin >> skaicius;
		}
	}

void checkInput(char& ivestis)
{
	while (std::cin.fail() || tolower(ivestis) != 't' && tolower(ivestis) != 'n')
	{
		if (std::cin.fail())
			std::cout
			<< "Ivedete reiksme, netenkinancia salygos! (Gal netycia vietoje raides ivedete skaiciu?)"
			<< std::endl;
		else if (tolower(ivestis) != 't' && tolower(ivestis) != 'n')
			std::cout
			<< "Atsakydami i programos uzduodamus klausimus rasykite raides T (-taip) arba N (-ne)!"
			<< std::endl;

		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Pakartokite ivedima: ";
		std::cin >> ivestis;
	}
}