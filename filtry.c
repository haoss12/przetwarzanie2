#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "struktura.h"


/************************************************************************************
 * Funkcja wykonujaca negatyw na wczytanym pliku       	       	       	       	    *
 *										                                            *
 * \param[in] obraz_pgm tablica, w ktorej znajduje sie wczytany obraz      		    *
 * \param[in] wymx szerokosc obrazka						                        *
 * \param[in] wymy wysokosc obrazka						                            *
 * \param[in] szarosci liczba odcieni szarosci					                    *
 *                                  						                        *
 ************************************************************************************/

void negatyw(t_obraz *obraz)
{  
    int i, j;
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
            obraz->obraz_pgm [i][j] = obraz->szarosci - obraz->obraz_pgm [i][j]; /*odbicie wartosci koloru piksela na przeciwna strone tabeli*/
            }
        }
}

/************************************************************************************
 * Funkcja wykonujaca progowanie na wczytanym pliku                                 *
 * dla zadanego przez uzytkownika procentu      	       	       	       	        *
 *										                                            *
 * \param[in] obraz_pgm tablica, w ktorej znajduje sie wczytany obraz      		    *
 * \param[in] wymx szerokosc obrazka						                        *
 * \param[in] wymy wysokosc obrazka						                            *
 * \param[in] szarosci liczba odcieni szarosci					                    *
 * \param[in] procprog wprowadzony przez uzytkownika prog                           *
 ************************************************************************************/

void progowanie(t_obraz *obraz, int procprog) 
{                           /*procprog - wprowadzony w menu przez uzytkownika procent przy ktorym ma zostac wykonane progowanie*/
    int i, j, wartprog;     /*wartprog - liczbowa wartosc progu dla ktorej nastepuje "zalamanie" sie czerni z biela*/
                            /*jest to wybrany przez uzytkownika procent z maksymalnej wartosci szarosci*/
        wartprog = ((procprog*obraz->szarosci)/100);

        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (obraz->obraz_pgm [i][j] <= wartprog) //progowanie "w dol", do czerni
                {
                    obraz->obraz_pgm [i][j] = 0;
                }
                
                if (obraz->obraz_pgm [i][j] > wartprog) //progowanie "w gore", do bieli
                {
                    obraz->obraz_pgm [i][j] = obraz->szarosci;
                }
            }
        }
}

/************************************************************************************
 * Funkcja wykonujaca konturowanie na wczytanym pliku       	       	       	    *
 *										                                            *
 * \param[in] obraz_pgm tablica, w ktorej znajduje sie wczytany obraz      		    *
 * \param[in] wymx szerokosc obrazka						                        *
 * \param[in] wymy wysokosc obrazka						                            *
 * \param[in] szarosci liczba odcieni szarosci					                    *
 * 					                                                                *
 ************************************************************************************/

void konturowanie(t_obraz *obraz)
{
    int i, j;

        for (i=0; i<obraz->wymy; ++i)  
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (i==(obraz->wymy-1))        /*wyjatek dla dolnych krawedzi obrazu*/
                {
                    if (j==(obraz->wymx-1))    /*wyjatek dla rogu obrazu*/
                    {
                        obraz->obraz_pgm [i][j] = 0;
                    }
                    else
                    {
                        obraz->obraz_pgm [i][j] = (abs(obraz->obraz_pgm [i][j+1]-obraz->obraz_pgm [i][j])); /*wyjatek dla dolnej krawedzi obrazu*/
                    }
                    
                }
                else
                {
                    if (j==(obraz->wymx-1))    /*wyjatek dla prawej krawedzi obrazu*/
                    {
                        obraz->obraz_pgm [i][j] = (abs(obraz->obraz_pgm [i+1][j]-obraz->obraz_pgm [i][j]));
                    }
                    else                /*standardowa sytuacja*/
                    {
                        obraz->obraz_pgm [i][j] = (abs(obraz->obraz_pgm [i+1][j]-obraz->obraz_pgm [i][j]) + abs(obraz->obraz_pgm [i][j+1]-obraz->obraz_pgm [i][j]));

                        if (obraz->obraz_pgm [i][j] > obraz->szarosci)    /*moze wystapic sytuacja w ktorej powyzszy wzor odda wart. wieksza niz  */
                        {                                   /*maksymalna mozliwa, ten if stanowi zabezpieczenie przed czyms takim   */
                            obraz->obraz_pgm [i][j] = obraz->szarosci; 
                        }
                        
                    }
                    /*konturowanie wedlug wzoru z pliku obrazy_filtry.pdf, abs (int) to wart. bezwzgledna z int*/
                } 
            }
        }
}

/************************************************************************************
 * Funkcja wykonujaca rozmywanie pionowe na wczytanym pliku                         *
 *                                                 	       	       	       	        *
 * \param[in] obraz_pgm tablica, w ktorej znajduje sie wczytany obraz      		    *
 * \param[in] wymx szerokosc obrazka						                        *
 * \param[in] wymy wysokosc obrazka						                            *
 * \param[in] prog prog rozmycia wybrany przez uzytkownika (1 lub 2)                *
 * \param[in] tabela_temp tablica tymczasowa do wykonania operacji                  *
 ************************************************************************************/
void rozmywanie_pion(t_obraz *obraz, int prog, int tabela_temp [][MAX])
{
    int i, j;   /*rozmywanie jest wykonywane do tabeli tymczasowej (tabela_temp)*/
                /*po to by pobierane wartosci sie zgadzaly z oczekiwaniami      */
                /*gdyby nie ten zabieg funkcja pobieralaby wartosci juz rozmyte */
                /*dla ktorych w dalszej czesci obrazu moglyby pojawiac sie bledy*/

    if (prog == 1) //pierwszy prog rozmywania
    {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (i==KRAWEDZ)     //wyjatek dla gornej krawedzi obrazu, by funkcja nie pobierala czegos co nie istnieje
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i+1][j])/2;
                }
                if (i==(obraz->wymy-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i-1][j]+obraz->obraz_pgm[i][j])/2;
                }
                else                /*standardowa sytuacja*/
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i-1][j]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i+1][j])/3;    
                }         
            }
        }
    }

    if (prog == 2)  //drugi prog rozmywania
    {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {   
                if (i==KRAWEDZ)     //wyjatek dla gornej krawedzi obrazu, jw.
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i+1][j]+obraz->obraz_pgm[i+2][j])/3;
                }
                if (i==(KRAWEDZ+1)) //wyjatek dla drugiego wiersza obrazu, jw.
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i-1][j]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i+1][j]+obraz->obraz_pgm[i+2][j])/4;
                }
                if (i==(obraz->wymy-2))   //wyjatek dla przedostatniego wiersza obrazu, jw.
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i-2][j]+obraz->obraz_pgm[i-1][j]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i+1][j])/4;
                }
                if (i==(obraz->wymy-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i-2][j]+obraz->obraz_pgm[i-1][j]+obraz->obraz_pgm[i][j])/3;
                }
                else                //standardowa sytuacja
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i-2][j]+obraz->obraz_pgm[i-1][j]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i+1][j]+obraz->obraz_pgm[i+2][j])/5;  
                }         
            }
        }
    }

    for (i=0; i<obraz->wymy; ++i)
    {
        for (j=0; j<obraz->wymx; ++j)                 /*czesc funkcji odpowiedzialna za przepisanie              */
        {                                       /*wartosci z tabeli tymczasowej spowrotem do glownej tabeli*/
        obraz->obraz_pgm [i][j] = tabela_temp[i][j];   /*oraz wyczyszczenie tabeli tymczasowej                    */
        tabela_temp[i][j] = 0;
        }
    }

}

/************************************************************************************
 * Funkcja wykonujaca rozmywanie poziome na wczytanym pliku                         *
 *                                                 	       	       	       	        *
 * \param[in] obraz_pgm tablica, w ktorej znajduje sie wczytany obraz      		    *
 * \param[in] wymx szerokosc obrazka						                        *
 * \param[in] wymy wysokosc obrazka						                            *
 * \param[in] prog prog rozmycia wybrany przez uzytkownika (1 lub 2)                *
 * \param[in] tabela_temp tablica tymczasowa do wykonania operacji                  *
 ************************************************************************************/
void rozmywanie_poziom(t_obraz *obraz, int prog, int tabela_temp [][MAX])
{
    int i, j;   /*rozmywanie jest wykonywane do tabeli tymczasowej (tabela_temp)*/
                /*po to by pobierane wartosci sie zgadzaly z oczekiwaniami      */
                /*gdyby nie ten zabieg funkcja pobieralaby wartosci juz rozmyte */
                /*dla ktorych w dalszej czesci obrazu moglyby pojawiac sie bledy*/

        if (prog == 1) //pierwszy prog rozmywania
    {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (j==KRAWEDZ)     //wyjatek dla gornej krawedzi obrazu, by funkcja nie pobierala czegos co nie istnieje
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j+1])/2;
                }
                if (j==(obraz->wymx-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j])/2;
                }
                else                //standardowa sytuacja
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j+1])/3;  
                }         
            }
        }
    }

    if (prog == 2)  //drugi prog rozmywania
    {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {   
                if (j==KRAWEDZ)     //wyjatek dla gornej krawedzi obrazu, jw.
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j+1]+obraz->obraz_pgm[i][j+2])/3;
                }
                if (j==(KRAWEDZ+1)) //wyjatek dla drugiego wiersza obrazu, jw.
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j+1]+obraz->obraz_pgm[i][j+2])/4;
                }
                if (j==(obraz->wymx-2))   //wyjatek dla przedostatniego wiersza obrazu, jw.
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i][j-2]+obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j]+1)/4;
                }
                if (j==(obraz->wymx-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i][j-2]+obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j])/3;
                }
                else                //standardowa sytuacja
                {
                tabela_temp[i][j] = (obraz->obraz_pgm[i][j-2]+obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j]+1+obraz->obraz_pgm[i][j+2])/5;  
                }         
            }
        }
    }

    for (i=0; i<obraz->wymy; ++i)
    {
        for (j=0; j<obraz->wymx; ++j)                 /*czesc funkcji odpowiedzialna za przepisanie              */
        {                                       /*wartosci z tabeli tymczasowej spowrotem do glownej tabeli*/
        obraz->obraz_pgm [i][j] = tabela_temp[i][j];   /*oraz wyczyszczenie tabeli tymczasowej                    */
        tabela_temp[i][j] = 0;
        }
    }
}