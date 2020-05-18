/***********************************************************
 *  Name       : meina1.cpp                                *
 *  Verwendung : Loesung der ersten Praktikumsaufgabe,     *
 *               Nullstellen eines quadratischen Polynoms  *
 *  Autor      :                                           *
 *  Datum      :                                           *
 *  Sprache    : C++                                       *
 ***********************************************************/

// Einbinden der Praktikums-Umgebung. Falls Sie die Ein-/Ausgabe zuerst
// nicht ueber die Praktikumsumgebung machen wollen, sollten Sie auch noch
// #include <iostream> einbinden.

#include "unit.h"
#include <iostream>

// ===== Hauptprogramm =====

int main() {
    // Hier kommt nun Ihr Programm. Viel Erfolg!

	for (int i = 1; i <= num_examples; i++)
	{
		double a = 0,b = 0,c = 0;
		getExample(i, a, b, c);             
		//dann werden die i-te Koeff. in a,b,c eingespeichert

		double x1 = 0, x2 = 0, w = 0, s = 0;

		//ueberpruefe, ob das Polynom linear ist
		if (a == 0)
		{
			//ueberpruefe, ob Polynom konstant ist
			if (b == 0)
			{
				//ueberpruefe, ob Polynom konstant 0
				if (c == 0)
				{
					checkSolution(infinity);
				}
				//falls die konstante ungleich 0, ergibt sich keine nullstellen
				else
				{
					checkSolution(0);
				}
			}
			//falls polynom linear, gilt die nullstelle wie folgt:
			else
			{
				x1 = -c / b;
				checkSolution(1,false,x1);
			}

		}
		//falls a ungleich 0, ist das polynom quadratisch
		else
		{
			//falls b,c=0,gibt's nur eine nullstelle :0
			if (b == 0 && c == 0)
			{
				checkSolution(1,false,0);
			}
			//sonst
			else
			{
				// normiere das polynom
				if (a != 1)
				{
					b = b / a;
					c = c / a;
					a = 1;
				}
				//ueberpruefe, ob (b/2)^2 > DBL_MAX ist
				// falls nein, schreibe die wurzel nicht um
				if (fabs(b) < 2 * sqrt(DBL_MAX))
				{
					w = pow((b/2),2) - c;
					//ueberpruefe, ob die wurzeln komplex sind
					//falls ja, check die nullstellen wie folgt
					if (w < 0)
					{
						checkSolution(2, true, -b/2, sqrt(fabs(w)));
					}
                    //falls die nullstellen reell und identisch sind,
					else if(w == 0)
					{
						checkSolution(1, false, -b/2);
					}

					//falls die nullstellen reell sind, ueberpruefe zunaechst, ob b groesser als null ist
					//falls ja, berechne x2 zuerst, dann x1
					else
					{
						s = sqrt(w);
						if (b > 0)
						{
							x2 = -b / 2 - s;
							x1 = c / x2;
						}
						else
						{
							x1 = -b / 2 + s;
							x2 = c / x1;
						}
						// stelle das beitragsgroessere zuerst in der folgenden funktion ein
						if (fabs(x1) > fabs(x2))
						{
							checkSolution(2, false, x1,x2);

						}
						else
						{
							checkSolution(2, false, x2, x1);
						}
					}
				}
				//falls (b/2)^2 > DBL_MAX, klammere p zunaechst aus der wurzel aus
				else
				{
					w = double(1.0 / 4) - c / b / b;
					//ueberpruefe die realitaet oder komplexitaet der nullstellen
					if (w < 0)
					{
						checkSolution(2, true, -b/2, fabs(b)*sqrt(fabs(w)));
					}
					//falls die nullstellen reell:
					else if(w==0)
					{
						checkSolution(1, false, -b/2);
					}


						
			
					else
					{
						s = fabs(b) * sqrt(w);
						//falls b>0, berechne x2 zuerst
						if (b > 0)
						{
							x2 = -b / 2 - s;
							x1 = c / x2;
						}
						else
						{
							x1 = -b / 2 + s;
							x2 = c / x1;
						}
						// stelle das beitragsgroessere zuerst in der folgenden funktion ein
						if (fabs(x1) > fabs(x2))
						{
							checkSolution(2, false, x1, x2);

						}
						else
						{
							checkSolution(2, false, x2, x1);
						}
					}
				}

			}
		}
	}

    return 0;
}
