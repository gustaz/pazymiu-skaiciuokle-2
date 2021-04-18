#include "declarations.h"

double accumulatedTime = 0;

int main(int argc, char* argv[])
{

	std::chrono::steady_clock::time_point programStart = std::chrono::steady_clock::now();
	std::cin.sync_with_stdio(false);
	std::cout.sync_with_stdio(false);

	std::cout << "Atsakydami i programos uzduodamus klausimus rasykite raides T (-taip) arba N (-ne)."
		<< std::endl;

	char pasirinkimas;
	bool isValid = false;
	if (argc > 1)
	{
		
		for (int i = 1; i < argc; i++)
			if (strcmp(argv[i], "vector") == 0 || strcmp(argv[i], "deque") == 0 || strcmp(argv[i], "list") == 0)
				isValid = true;

		if (isValid)
		{
			std::vector<int> studentuFailuDydziai = { 1000, 10000, 100000, 1000000, 10000000 };
			//std::vector<int> studentuFailuDydziai = { 1000, 10000, 100000 };
			std::ofstream output;
			std::ifstream input;

			generateDirectories("data");
			generateDirectories("data/input");
			generateDirectories("data/output");

			bool toGenerate = false;

			for (int j = 0; j < studentuFailuDydziai.size(); j++)
			{
				std::string fileName = "data/input/studentai" + std::to_string(studentuFailuDydziai.at(j)) + ".txt";
				bool fileNotFound = fileExists(fileName);

				if (!fileNotFound)
					toGenerate = true;
			}
			
			for (int i = 1; i < argc; i++)
			{
				if (toGenerate || strcmp(argv[i], "generate") == 0)
				{
					std::cout << "Programa nerado ivesties arba buvo iskviesta generavimo funkcija. Vykdomas ivesties generavimas.";
					for (int i = 0; i < studentuFailuDydziai.size(); i++)
						generationSequence(studentuFailuDydziai[i], output, accumulatedTime);
				}
			}

			for (int i = 1; i < argc; i++)
			{
				if (strcmp(argv[i], "generate") == 0) i++;
				for (int j = 0; j < studentuFailuDydziai.size(); j++)
				{
					std::cout << "Pradedamas darbas su " << studentuFailuDydziai[j] << " " << argv[i] << " konteineriu" << std::endl;
					double benchmarkTime = 0;
					if (strcmp(argv[i], "vector") == 0)
					{
						std::vector<Studentas> studentai;

						workFlow(studentai, studentuFailuDydziai[j], input, output, argv[i], benchmarkTime);

						std::cout << "Vykdomas studentu rusiavimas pagal galutini ivertinima." << std::endl;
						clockStart = std::chrono::steady_clock::now();

						auto it = std::partition(studentai.begin(), studentai.end(), isKietiakas());
						std::vector<Studentas> vargsiukai(std::make_move_iterator(it), std::make_move_iterator(studentai.end()));
						studentai.erase(it, studentai.end());

						sort(studentai.begin(), studentai.end(), compSurname());
						sort(vargsiukai.begin(), vargsiukai.end(), compSurname());

						std::cout << "Studentu rusiavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
						benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

						thenPrint(studentai, vargsiukai, studentuFailuDydziai[j], output, benchmarkTime, argv[i]);
					}
					else if (strcmp(argv[i], "deque") == 0)
					{
						std::deque<Studentas> studentai;

						workFlow(studentai, studentuFailuDydziai[j], input, output, argv[i], benchmarkTime);

						std::cout << "Vykdomas studentu rusiavimas pagal galutini ivertinima." << std::endl;
						clockStart = std::chrono::steady_clock::now();

						auto it = std::partition(studentai.begin(), studentai.end(), isKietiakas());
						std::deque<Studentas> vargsiukai(std::make_move_iterator(it), std::make_move_iterator(studentai.end()));
						studentai.erase(it, studentai.end());

						sort(studentai.begin(), studentai.end(), compSurname());
						sort(vargsiukai.begin(), vargsiukai.end(), compSurname());

						std::cout << "Studentu rusiavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
						benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
						thenPrint(studentai, vargsiukai, studentuFailuDydziai[j], output, benchmarkTime, argv[i]);
					}
					else if (strcmp(argv[i], "list") == 0)
					{
						std::list<Studentas> studentai;

						workFlow(studentai, studentuFailuDydziai[j], input, output, argv[i], benchmarkTime);

						std::cout << "Vykdomas studentu rusiavimas pagal galutini ivertinima." << std::endl;
						clockStart = std::chrono::steady_clock::now();
						
						auto it = std::partition(studentai.begin(), studentai.end(), isKietiakas());
						std::list<Studentas> vargsiukai (std::make_move_iterator(it), std::make_move_iterator(studentai.end()));
						studentai.erase(it, studentai.end());

						studentai.sort(compSurname());
						vargsiukai.sort(compSurname());

						std::cout << "Studentu rusiavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
						benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

						thenPrint(studentai, vargsiukai, studentuFailuDydziai[j], output, benchmarkTime, argv[i]);
					}
                    std::cout << std::endl;
				}
			}
		}
	}
	if(argc <= 1 || !isValid)
	{
		std::cout << "Nepasirinkti (teisingi) vykdymo argumentai programos paleidimo metu, todel pereinama prie iprastos veiklos. " << std::endl;
		std::vector<Studentas> studentai;
		std::cout << "Ar norite vykdyti failu generacija? (T/N): ";
		std::cin >> pasirinkimas;
		checkInput(pasirinkimas);

		if (tolower(pasirinkimas) == 't')
		{
			askForGeneration();
		}
		else std::cout << "Pasirinkta failu negeneruoti. " << std::endl;

		std::cout << "Ar norite nuskaityti duomenis is failo? (T/N): ";
		std::cin >> pasirinkimas;
		checkInput(pasirinkimas);

		bool nuskaitytiDuomenys = false;
		bool skaitytiToliau = false;

		if (tolower(pasirinkimas) == 't')
		{
			readFromFile(studentai);
			nuskaitytiDuomenys = true;

		}
		if (nuskaitytiDuomenys)
		{
			std::cout << "Ar norite duomenis taip pat ivesti ranka? (T/N): ";
			std::cin >> pasirinkimas;
			checkInput(pasirinkimas);

			if (tolower(pasirinkimas) == 't')
				skaitytiToliau = true;
		}
		else
			std::cout << "Nepasirinkta duomenis skaityti is failo. Pereinama prie ivedimo rankiniu budu. "
			<< std::endl;

		while (skaitytiToliau || !nuskaitytiDuomenys)
		{
			std::cin.ignore();
			inputStudent(studentai);

			std::cout << "Ar norite prideti dar viena studenta? (T/N): ";
			std::cin >> pasirinkimas;

			checkInput(pasirinkimas);

			if (tolower(pasirinkimas) == 'n')
				break;
		}

		std::cout << "Vykdomas galutiniu ivertinimu skaiciavimas." << std::endl;
		clockStart = std::chrono::steady_clock::now();
		for (int i = 0; i < studentai.size(); i++)
		{
			double avg = 0;
			for (int j = 0; j < studentai[i].nd.size(); j++)
			{
				avg += studentai[i].nd[j];
			}
			avg /= studentai[i].nd.size();
			studentai[i].galutinisVid = 0.4 * avg + 0.6 * studentai[i].egzaminas;

			studentai[i].galutinisMed = findMedian(studentai[i].nd, studentai[i].nd.size()) * 0.4 + studentai[i].egzaminas * 0.6;
		}
		std::cout << "Galutiniu ivertinimu skaiciavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
		accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

		bool outputDone = false;
		std::cout << "Dabar yra suteikiama galimybe pasirinkti isvedima."
			<< std::endl;

		std::cout << "Ar norite, jog rezultatas butu skirstomas pagal galutini vidurki? "
			<< "Jei pasirinksite ne, jis bus neskirstomas. (T/N): ";

		std::cin >> pasirinkimas;
		checkInput(pasirinkimas);

		if (tolower(pasirinkimas) == 't')
		{
			std::vector<Studentas> kietiakai;
			std::vector<Studentas> vargsiukai;
			outputDone = true;

			std::cout << "Pasirinkote surusiavima ir isvesti i faila."
				<< std::endl << "Ar norite, jog rezultatas isvedamas butu pagal galutini ivertinima? "
				<< "Pasirinkus ne, bus skaiciuojama pagal mediana. (T/N): ";

			std::cin >> pasirinkimas;
			checkInput(pasirinkimas);

			generateDirectories("data");
			generateDirectories("data/output");

			if (tolower(pasirinkimas) == 't')
			{
				clockStart = std::chrono::steady_clock::now();
				for (int i = 0; i < studentai.size(); i++)
				{
					if (studentai[i].galutinisVid >= 5.00)
						kietiakai.push_back(studentai[i]);
					else
						vargsiukai.push_back(studentai[i]);
				}
				std::cout << "Rusiavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
				clockStart = std::chrono::steady_clock::now();
				std::ofstream output;

				output.open("data/output/kietiakai.txt");
				writeToConsoleAvg(kietiakai, output);
				output.close();

				output.open("data/output/vargsiukai.txt");
				writeToConsoleAvg(vargsiukai, output);
				output.close();

				std::cout << "Isvestis truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
			}

			if (tolower(pasirinkimas) == 'n')
			{
				clockStart = std::chrono::steady_clock::now();
				for (int i = 0; i < studentai.size(); i++)
				{
					if (studentai[i].galutinisMed >= 5)
						kietiakai.push_back(studentai[i]);
					else
						vargsiukai.push_back(studentai[i]);
				}
				std::cout << "Rusiavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

				clockStart = std::chrono::steady_clock::now();
				std::ofstream output;

				output.open("data/output/kietiakai.txt");
				writeToConsoleAvg(kietiakai, output);
				output.close();

				output.open("data/output/vargsiukai.txt");
				writeToConsoleAvg(vargsiukai, output);
				output.close();

				std::cout << "Isvestis truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
			}
		}

		if (tolower(pasirinkimas) == 'n' && !outputDone)
		{
			std::sort(studentai.begin(), studentai.end(), compSurname());
			std::cout << "Pasirinkote paprasta isvesti i komandine eilute."
				<< std::endl << "Ar norite, jog rezultate butu rodomas vidurkis? "
				<< "Pasirinkus ne, bus rodoma mediana. (T/N): ";

			std::cin >> pasirinkimas;
			checkInput(pasirinkimas);

			if (tolower(pasirinkimas) == 't')
			{
				clockStart = std::chrono::steady_clock::now();
				writeToConsoleAvg(studentai, std::cout);
				std::cout << "Israsymas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
			}
			if (tolower(pasirinkimas) == 'n')
			{
				clockStart = std::chrono::steady_clock::now();
				writeToConsoleMed(studentai, std::cout);
				std::cout << "Israsymas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
			}
		}
	}
	std::cout << std::endl << "Galutinis vykdymas truko: " << accumulatedTime << " s." << std::endl;
	std::cout << "Galutinis programos gyvavimo laikas: " << std::chrono::duration<double>(std::chrono::steady_clock::now() - programStart).count() << " s.";
}