#include <iostream>
#include <vector>
#include <fstream>
#include "unit.h"
#include <string>
using std::string;


// eine neue tausche Funktion muss definiert werden
// sie bekommt einen Vektor uebergeben und die beiden Indizees deren Elemente vertauscht werden sollen
template<typename ElemT>
void swap(std::vector<ElemT>& feld, size_t index1, size_t index2)
{
	ElemT b = feld[index1];
	feld[index1] = feld[index2];
	feld[index2] = b;

}

template<typename ElemT>
void Bubblesort(size_t laenge, std::vector<ElemT>& feld)
{
	// i durchlaeuft das gesamte Feld
	for (size_t i = 0; i < laenge-1; i++)
	{
		//jedes Element des auf i folgenden Teilfeldes wird rueckwaerts mit seinem vornen Nachbarn verglichen
		for (size_t j = laenge-1; j > i; j--)
		{
			//falls das vorne groesser als das hintere, vertausche sie
			if (feld[j] < feld[j - 1])
			{
				swap(feld, j - 1, j);
			}
		}
	}
}

template<typename ElemT>
void Auswahlsortieren(size_t laenge, std::vector<ElemT>& feld)
{
	// i durchlaeuft das gesamte Feld
	size_t x = 0;
	for (size_t i = 0; i < laenge - 1; i++)
	{
		// das kleinste Element des auf den Index i-1 folgende Feldes wird gesucht, 
		// indem alle Eintraege dieses Teilfeldes mit dem Eintrag am Index i verglichen werden
		x = i;
		for (size_t j = i + 1; j < laenge; j++)
		{
			// Falls der Eintrag an j-ter Stelle kleiner ist als der Eintrag an der i-ten Stelle, 
			// so wird der Index des kleineren Eintrages als x vermerkt
			if (feld[j] < feld[x])
			{
				x = j;
			}
		}
		// waehlt das kleinste aus und vertausche an der i-ten stelle
		if (x != i)
		{
			swap(feld, x, i);
		}
		// nun ist das Feld von 0 bis i geordnet und der Vorgang wird wiederholt
	}
}


template<typename ElemT>
void Mergesort(size_t LinkerIndex, size_t RechterIndex, std::vector<ElemT>& feld)
{
	// rechter und Linker Index sind Elemente des Intervalles [0,Laenge des Feldes-1]
	size_t mitte;
	// Falls das Feld mehr als einen Eintrag hat
	if (LinkerIndex < RechterIndex)
	{

		mitte = (LinkerIndex + (RechterIndex - 1)) / 2;

		// Weitere Aufspaltung durch Rekursion
		Mergesort(LinkerIndex, mitte, feld);
		Mergesort(mitte + 1, RechterIndex, feld);

		// wenn dann ganz aufgespalten, kann mit neuzusammenfuegen bzw. sortieren begonnen werden

		// so sollen die zwischenzuspeichernden Teilfelder aussehen: linkes Feld: [linkerIndex, mitte]; 
		// rechtes Feld: [mitte+1, rechterIndex]
		size_t laenge1 = mitte - LinkerIndex + 1;
		size_t laenge2 = RechterIndex - mitte;

		// Teilfelder werden erzeugt
		std::vector<ElemT> flinks(laenge1);
		std::vector<ElemT> frechts(laenge2);

		// Kopieren der Daten in die Teilfelder
		for (size_t i = 0; i < laenge1; i++)
		{
			flinks[i] = feld[LinkerIndex + i];
		}
		for (size_t i = 0; i < laenge2; i++)
		{
			frechts[i] = feld[mitte + 1 + i];
		}

		// die Elemente der aufgespaltenen beiden Felder, sollen nun sortiert wieder in das alte gespeichert werden

		// Laufindizis n, m ,p jeweils fuer linkes, rechtes und zusammengefuegtes Feld
		size_t n = 0, m = 0, p = LinkerIndex;

		while (n < laenge1 && m < laenge2)
		{
			if (flinks[n] < frechts[m] || flinks[n] == frechts[m])
			{
				feld[p] = flinks[n];
				n++;
				p++;
			}
			else
			{
				feld[p] = frechts[m];
				m++;
				p++;
			}
		}

		// falls in einem der Teilfelder nun noch Elemente uebrig sind, werden diese nacheinander (sie sind ja bereits sortiert durch vorangegangene Rekursion) an das alte Feld angehangen
		while (n <= laenge1 - 1)
		{
			feld[p] = flinks[n];
			n++;
			p++;
		}
		while (m <= laenge2 - 1)
		{
			feld[p] = frechts[m];
			m++;
			p++;
		}


	}


}


template<typename ElemT>
void einlesen(std::ifstream& ifs, std::vector<ElemT>& feld)
{
	ElemT eintrag;

	while (!ifs.eof())
	{
		ifs >> eintrag;
		if (ifs.good())
		{
			feld.push_back(eintrag);
		}
	}
}



template<typename ElemT>
void ausgeben(std::ostream& os, const std::vector<ElemT>& feld)
{
	// jedes Element im Feld/Vektor wird einzeln eingelesen und hintereinander mit Ausgabeoperator der Wahl aus
	for (size_t i = 0;i <  feld.size() ; i++)
	{
		os << feld[i] << " ";
	}
}





int main()
{
	//Eingsbeoperatoren fuer verschiedene Dateien
	std::ifstream a("doubles.txt");
	std::ifstream b("strings.txt");
	std::ifstream c("studenten.txt");

	// Definition der zu verwendenen Vektoren
	std::vector<double> feld1;
	std::vector<string> feld2;
	std::vector<Student> feld3;

	// einlesen der Daten in die Vektoren
	einlesen(a, feld1);
	einlesen(b, feld2);
	einlesen(c, feld3);

	// Laenge der Vektoren wird fuer Sortieralgorithmen benoetigt
	size_t laenge1 = feld1.size();
	size_t laenge2 = feld2.size();
	size_t laenge3 = feld3.size();

	//Benutzer gibt an welcher Algorithmus verwendet werden soll
	std::cout << "Waehle einen Algorithmus:\n";
	char d;
	std::cin >> d;

	// Bubblesort
	if (d == 'B')
	{
		Bubblesort(laenge1, feld1);
		Bubblesort(laenge2, feld2);
		Bubblesort(laenge3, feld3);

		ausgeben(std::cout, feld1);
		std::cout << std::endl;
		ausgeben(std::cout, feld2);
		std::cout << std::endl;
		ausgeben(std::cout, feld3);
		std::cout << std::endl;

		checkSolution(feld1);
		checkSolution(feld1);
		checkSolution(feld1);
	}

	//Auswahlsortieren
	else if (d == 'A')
	{
		Auswahlsortieren(laenge1, feld1);
		Auswahlsortieren(laenge2, feld2);
		Auswahlsortieren(laenge3, feld3);

		ausgeben(std::cout, feld1);
		std::cout << std::endl;
		ausgeben(std::cout, feld2);
		std::cout << std::endl;
		ausgeben(std::cout, feld3);
		std::cout << std::endl;

		checkSolution(feld1);
		checkSolution(feld1);
		checkSolution(feld1);
	}

	//Mergesort
	else if (d == 'M')
	{
		Mergesort(0, laenge1 - 1, feld1);
		Mergesort(0, laenge2 - 1, feld2);
		Mergesort(0, laenge3 - 1, feld3);

		ausgeben(std::cout, feld1);
		std::cout << std::endl;
		ausgeben(std::cout, feld2);
		std::cout << std::endl;
		ausgeben(std::cout, feld3);
		std::cout << std::endl;

		checkSolution(feld1);
		checkSolution(feld1);
		checkSolution(feld1);
	}

	// Streams muessen geschlossen werden
	a.close();
	b.close();
	c.close();

	return 0;
}
