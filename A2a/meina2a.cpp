#include <iostream>
#include "unit.h"
using std::cout;
using std::cin;
using std::endl;

//Gib die Laenge (laenge) des Feldes und das Feld (feld) selber ein
void Bubblesort(size_t laenge, unsigned int* feld)
{
	// i durchlaeuft das gesamte Feld
	for (size_t i = 0; i < laenge - 1; i++)
	{
		//jedes Element des auf i folgenden Teilfeldes wird rueckwaerts mit seinem vornen Nachbarn verglichen
		for (size_t j = laenge - 1; j > i; j--)
		{
			//falls das vorne groesser als das hintere, vertausche sie
			if (feld[j] < feld[j - 1])
			{
				swap(feld, j-1, j);
			}
		}
	}
}

void Auswahlsortieren(size_t laenge, unsigned int* feld)
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

void Einfuegesortieren(size_t laenge, unsigned int* feld)
{
	// i durchlaeuft das gesamte Feld
	for (size_t i = 0; i < laenge; i++)
	{
		// nun ist das Feld von 0 bis i-1 geordnet 
		// Es wird die richtige stelle im bereits sortiertem Feld [0,...,i-1] 
		//fuer feld[i] gesucht
		for (size_t j = 0; j < i; j++)
		{
			if (feld[j] > feld[i])
			{
				// der Rest des bereits sortierten Feldes muss hinter der stelle j 
				// um eins nach hinten verschoben werden
				for (int k = j; k < i; k++)
				{
					swap(feld, k, i);
				}
			}
		}
	}
}


// gib den zu betrachtenen Knoten und die Laenge (laenge) des Feldes, sowie das Feld ein
void heapify(size_t knoten, size_t laenge, unsigned int* feld)
{
	size_t groesste = knoten, links = 2 * knoten + 1, rechts = 2 * knoten + 2;

	// falls der linke Unterknoten kleiner ist als der Vaterknoten, 
	// so wird der linke Unterknoten als groesser vermerkt
	if (links<laenge && feld[links] >feld[groesste])
	{
		groesste = links;
	}

	// falls der rechte Unterknoten kleiner ist als der momentan als groesster Vermerkte,
	// so wird der rechte Unterknoten als groesser vermerkt
	if (rechts<laenge && feld[rechts] >feld[groesste])
	{
		groesste = rechts;
	}

	// ist der groesste Knoten nicht der Vaterknoten, so wird entsprechend vertauscht und 
	// die heapyfy Funktion auf den veraenderten Unterbaum angewendet
	if (groesste != knoten)
	{
		swap(feld, knoten, groesste);
		// rufe rekursiv nochmal heapify an geaenderte wurzel, 
		// um Heap-Bedingung nicht kaputt zu machen
		heapify(groesste, laenge, feld);
	}

}

void HeapsortAlgorithmus(size_t laenge, unsigned int* feld)
{
	// zuerst forme den Baum zu einem heap
	// dazu wird die heapify Funktion von unten nach oben auf jeden Knoten angewendet, welcher kein Blatt ist
	// fuer den feld mit Laenge (laenge) brauchen wir zuerst an laenge / 2 konten die heapify-Fkt. aufzurufen
	if (laenge >= 3)
	{
		for (size_t i = laenge / 2 - 1; i >= 0;i--)
		{
			heapify(i, laenge, feld);

			// fuer i = 0, i-- wird zu gross sein wegen seines Datentyps size_t
			if (i == 0)
			{
				break;
			}
		}

		// da nun der Baum ein Heap ist kann mit dem sortieren begonnen werden
		// der gesamten Laenge nach wird der erste Knoten (oberste) also groesste mit dem letzten Vertauscht und der Baum, exklusive dem letzten nun groessten Blatt wird erneut 
		// zum heap gemacht, dies wird solange wiederholt, bis alle Knoten in der richtigen reihenfolge stehen


		for (size_t i = laenge - 1; i >=0; i--)
		{
			swap(feld, i, 0);
			//hier muss hepify auf den teilfelder (feld[0],...feld[i-1]),der nur noch die ersten i elementen von felder enthaelt, angewendet werden
			heapify(0, i, feld);

			//gleiches argument fuer i = 0 wie oben
			if(i == 0)
			{
				break;
			}

		}
	}
	else
	{
		heapify(0, laenge, feld);
	}
	


}

void Quicksort(size_t AnfangsIndex, size_t LetzterIndex, unsigned int* feld)
{
	// Laufindizees werden gesetzt
	size_t i = AnfangsIndex, j = LetzterIndex - 1;
	// Pivotelement wird als letztes Element des zu betrachtenen Feldes gewaehlt
	unsigned int pivot = feld[LetzterIndex];

	// solange i j noch nicht "ueberholt" hat, d.h. i noch < j ist.
	do {
		//Feld wird solange von links durchlaufen, bis ein Eintrag grosser gelich dem Pivotelement gefunden wird
		while (feld[i] <= pivot && i < LetzterIndex - 1)
		{
			i++;
		}
		//Feld wird solange von rechts durchlaufen, bis ein Eintrag kleiner gelich dem Pivotelement gefunden wird
		while (feld[j] >= pivot && j > AnfangsIndex)
		{
			j--;
		}
		// falls i, j noch nicht "ueberholt" hat, werden die Elemente an den Stellen j und i vertauscht
		if (i < j)
		{
			swap(feld, i, j);
		}
	} while (i < j);

	// Pivotelement wird an richtigen Platz getauscht
	if (feld[i] > pivot)
	{
		swap(feld, i, LetzterIndex);
	}
	// Rekursion der Funktion fuer die entstandenen Teilfelder; Pivotelement wird nicht mehr beruehrt
	if (AnfangsIndex < j)
	{
		Quicksort(AnfangsIndex, j, feld);
	}
	if (i < LetzterIndex - 1)
	{
		Quicksort(i+1, LetzterIndex, feld);
	}
}


void Mergesort(size_t LinkerIndex, size_t RechterIndex, unsigned int* feld)
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
		int* flinks = new int[laenge1];
		int* frechts = new int[laenge2];

		// Kopieren der Daten in die Teilfelder
		for (size_t i = 0; i < laenge1; i++)
		{
			flinks[i] = feld[LinkerIndex + i];
		}
		for (size_t i = 0; i < laenge2; i++)
		{
			frechts[i] = feld[mitte +1 + i];
		}

		// die Elemente der aufgespaltenen beiden Felder, sollen nun sortiert wieder in das alte gespeichert werden

		// Laufindizis n, m ,p jeweils fuer linkes, rechtes und zusammengefuegtes Feld
		size_t n = 0, m = 0, p = LinkerIndex;

		while (n < laenge1 && m < laenge2)
		{
			if (flinks[n] <= frechts[m])
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

		// nun kann der Speicher fuer die Teilfelder wieder freigegeben werden
		delete[] frechts;
		delete[] flinks;
	}

	
}





size_t pivo_ende(size_t laenge, unsigned int* feld)
{
	// falls feld nur ein element enthaelt, braucht nicht zu vertauschen und das index = 0
	if (laenge <= 1)
		return 0;

	// aenhlich wie oben definiertes Quicksort
	unsigned int pivot = feld[laenge - 1];
	size_t i = 0;
	size_t j = laenge - 2;
	do {
		//Feld wird solange von links durchlaufen, bis ein Eintrag grosser gelich dem Pivotelement gefunden wird
		while (feld[i] <= pivot && i < laenge - 1)
		{
			i++;
		}
		//Feld wird solange von rechts durchlaufen, bis ein Eintrag kleiner gelich dem Pivotelement gefunden wird
		while (feld[j] >= pivot && j >= 0)
		{
			// fuer laenge = 2 gilt j = 0 und wir muessen beachten, dass j-- zu viel grosse ist, da j von typ size_t
			if (j == 0) break;
			j--;
		}
		// falls i, j noch nicht "ueberholt" hat, werden die Elemente an den Stellen j und i vertauscht
		if (i < j)
		{
			swap(feld, i, j);
		}
	} while (i < j);

	// Pivotelement wird an richtigen Platz getauscht
	if (feld[i] > pivot)
	{
		swap(feld, i, laenge - 1);
	}
	
	return i;
}

size_t pivo_anfang(size_t laenge, unsigned int* feld)
{
	// falls feld nur ein element enthaelt, braucht nicht zu vertauschen und das index = 0
	if (laenge <= 1)
		return 0;

	// nun ist feld[0] das pivotelement
	unsigned int pivot = feld[0];
	size_t i = 1;
	size_t j = laenge - 1;
	do {
		//Feld wird solange von links durchlaufen, bis ein Eintrag grosser gelich dem Pivotelement gefunden wird
		while (feld[i] <= pivot && i < laenge)
		{
			if (i == laenge - 1) break;
			i++;
		}
		//Feld wird solange von rechts durchlaufen, bis ein Eintrag kleiner gelich dem Pivotelement gefunden wird
		while (feld[j] >= pivot && j >= 1)
		{
			j--;
		}
		// falls i, j noch nicht "ueberholt" hat, werden die Elemente an den Stellen j und i vertauscht
		if (i < j)
		{
			swap(feld, i, j);
		}
	} while (i < j);

	// hier ist anders als der Fall pivo_ende. wir vergleichen feld[j] mit das pivotelement,
	// und wir muessen das kleinere der beiden zahlen an der stelle mit index 0 vertauschen
	if (feld[j] < pivot)
	{
		swap(feld, j, 0);
	}

	return j;
}

size_t pivo_mitte(size_t laenge, size_t index, unsigned int* feld)
{
	// falls feld nur ein element enthaelt, braucht nicht zu vertauschen und das index = 0
	if (laenge <= 1)
		return 0;

	// pivotelement ist nun feld[index]
	unsigned int pivot = feld[index];
	size_t i = 0;
	size_t j = laenge - 1;
	do {
		
		while (feld[i] <= pivot && i < laenge)
		{
			if (i == laenge - 1) break;
			i++;
		}
		
		while (feld[j] >= pivot && j >= 0)
		{
			// fuer laenge = 2 gilt j = 0 und wir muessen beachten, dass j-- zu viel grosse ist, da j von typ size_t
			if (j == 0) break;
			j--;
		}
		// falls i, j noch nicht "ueberholt" hat, werden die Elemente an den Stellen j und i vertauscht
		if (i < j)
		{
			swap(feld, i, j);
		}
	} while (i < j);

	// Pivotelement wird an richtigen Platz getauscht
	// falls i <= index, dh.j<=i<=index, muessen wir das grossere zws feld[i] und feld[index] vergleichen
	// und das groessere an feld[i] vertauschen.
	if (i<= index)
	{
		// fuer den fall i = index braucht keinem vertausch
		if (i < index)
		{
			swap(feld, i, index);
		}
		return i;
	}

	// falls j >= index, dh.i>=j>=index, muessen wir das kleinere zws feld[j] und feld[index] vergleichen
	// und das klenere an feld[j] vertauschen.
	else if (j >= index)
	{
		if (j != index)
		{
			swap(feld, j, index);
		}

		return j;
	}
	// falls das pivotelement an richtigem platz gestellt geworden hat, gib einfach index zurueck
	else
	{
		return index;
	}
}

void Quicksort_median3(size_t laenge, unsigned int* feld)
{
	// falls die laenge des feldes 0 oder 1 ist, braucht man nichts zu tun
	if (laenge <= 1)
		return;

	size_t AnfangsIndex = 0;
	size_t LetzterIndex = laenge - 1;
	size_t Mitte = laenge / 2;
	size_t median = 0;
	size_t index;  // index zeigt, woran das pivotelement vertauscht wird

	// suche jetzt das median der drei indizis
	// falls median das erste element ist, benutzte den algorithmus pivo_anfang, 
	// um den feld zu sortieren und gib index zurueck
	if (feld[AnfangsIndex] <= feld[LetzterIndex] && feld[AnfangsIndex] >= feld[Mitte])
	{
		median = AnfangsIndex;
		index = pivo_anfang(laenge, feld);
	}

	// falls median in mitte ist, benutze dann pivo_mitte
	else if (feld[Mitte] <= feld[LetzterIndex] && feld[Mitte] >= feld[AnfangsIndex])
	{
		median = Mitte;
		index = pivo_mitte(laenge, median, feld);
	}
	// falls median an ende, benutze pivo_ende
	else
	{
		median = LetzterIndex;
		index = pivo_ende(laenge, feld);
	}
	// dann benutze Quicksort_median3 rekursiv auf den Teilfeldern
	// es wird auf zwei teilfelder geteilt, wobei der vorne teilfeld alle elemente des feldes mit indizis kleiner als index nimmt,
	// und der hinte alle elemente des feldes mit indizis groesser als index bis ende nimmt
	Quicksort_median3(index, feld);
	Quicksort_median3(laenge - index - 1, feld + index + 1);

}

int main()
{
	size_t laenge = 2000;
	unsigned int* feld = new unsigned int[laenge];
	

	for (unsigned int i = 1; i < num_examples + 1; i++)
	{
		cout << "Bubblesort:\n";
		cout << endl;
		getExample(i, laenge, feld);
		Bubblesort(laenge, feld);
		checkSolution(feld);
		cout << endl << endl << endl;

		cout << "Auswahlesortieren:\n";
		cout << endl;
		getExample(i, laenge, feld);
		Auswahlsortieren(laenge, feld);
		checkSolution(feld);
		cout << endl << endl << endl;

		cout << "Einfuegesortieren:\n";
		cout << endl;
		getExample(i, laenge, feld);
		Einfuegesortieren(laenge, feld);
		checkSolution(feld);
		cout << endl << endl << endl;

		cout << "Heapsort:\n";
		cout << endl;
		getExample(i, laenge, feld);
		HeapsortAlgorithmus(laenge, feld);
		checkSolution(feld);
		cout << endl << endl << endl;

		cout << "Quicksort:\n";
		cout << endl;
		getExample(i, laenge, feld);
		Quicksort(0, laenge - 1, feld);
		checkSolution(feld);
		cout << endl << endl << endl;

		cout << "Mergesort:\n";
		cout << endl;
		getExample(i, laenge, feld);
		Mergesort(0, laenge - 1, feld);
		checkSolution(feld);
		cout << endl << endl << endl;

		cout << "Quicksort mit Median aus Drei:\n";
		cout << endl;
		getExample(i, laenge, feld);
		Quicksort_median3(laenge, feld);
		checkSolution(feld);
		cout << endl << endl << endl;
	}
	delete [] feld;

return 0;

}
