#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "struktura.h"


/************************************************************************************
 * Funkcja wykonujaca negatyw na wczytanym pliku       	       	       	       	    *
 *										                                            *
 * \param[in] t_obraz *obraz struktura przechowujaca dane o obrazie    		        *
 *                                  						                        *
 ************************************************************************************/

void negatyw(t_obraz *obraz)
{  
    int i, j;
    
    if (obraz->typobrazu == PGM)
    {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
            obraz->obraz_pgm [i][j] = obraz->szarosci - obraz->obraz_pgm [i][j]; /*odbicie wartosci koloru piksela na przeciwna strone tabeli*/
            }
        }
    }
    
    if (obraz->typobrazu == PPM)
    {
        if (obraz->kanal == KANAL || obraz->kanal == RED)
        {
            for (i=0; i<obraz->wymy; ++i)
            {
            for (j=0; j<obraz->wymx; ++j)
            {
            obraz->red [i][j] = obraz->szarosci - obraz->red [i][j]; /*odbicie wartosci koloru piksela na przeciwna strone tabeli*/
            }
            }
        }
        if (obraz->kanal == KANAL || obraz->kanal == GREEN)
        {
            for (i=0; i<obraz->wymy; ++i)
            {
            for (j=0; j<obraz->wymx; ++j)
            {
            obraz->green [i][j] = obraz->szarosci - obraz->green [i][j]; /*odbicie wartosci koloru piksela na przeciwna strone tabeli*/
            }
            }
        }
        if (obraz->kanal == KANAL || obraz->kanal == GREEN)
        {
            for (i=0; i<obraz->wymy; ++i)
            {
            for (j=0; j<obraz->wymx; ++j)
            {
            obraz->blue [i][j] = obraz->szarosci - obraz->blue [i][j]; /*odbicie wartosci koloru piksela na przeciwna strone tabeli*/
            }
            }
        }
    } 
}

/************************************************************************************
 * Funkcja wykonujaca progowanie na wczytanym pliku                                 *
 * dla zadanego przez uzytkownika procentu      	       	       	       	        *
 *										                                            *
 * \param[in] t_obraz *obraz struktura przechowujaca dane o obrazie    		        *
 * \param[in] procprog wprowadzony przez uzytkownika prog                           *
 ************************************************************************************/

void progowanie(t_obraz *obraz, int procprog) 
{                           /*procprog - wprowadzony w menu przez uzytkownika procent przy ktorym ma zostac wykonane progowanie*/
    int i, j, wartprog;     /*wartprog - liczbowa wartosc progu dla ktorej nastepuje "zalamanie" sie czerni z biela*/
                            /*jest to wybrany przez uzytkownika procent z maksymalnej wartosci szarosci*/
        wartprog = ((procprog*obraz->szarosci)/100);

        if (obraz->typobrazu == PGM)
        {
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

        if (obraz->typobrazu == PPM)
        {
        if (obraz->kanal == KANAL || obraz->kanal == RED)
        {
           for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (obraz->red [i][j] <= wartprog) //progowanie "w dol", do czerni
                {
                    obraz->red [i][j] = 0;
                }
                
                if (obraz->red [i][j] > wartprog) //progowanie "w gore", do bieli
                {
                    obraz->red [i][j] = obraz->szarosci;
                }
            }
        } 
        }
        if (obraz->kanal == KANAL || obraz->kanal == GREEN)
        {
           for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (obraz->green [i][j] <= wartprog) //progowanie "w dol", do czerni
                {
                    obraz->green [i][j] = 0;
                }
                
                if (obraz->green [i][j] > wartprog) //progowanie "w gore", do bieli
                {
                    obraz->green [i][j] = obraz->szarosci;
                }
            }
        }             
        }
        if (obraz->kanal == KANAL || obraz->kanal == BLUE)
        {
           for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (obraz->blue [i][j] <= wartprog) //progowanie "w dol", do czerni
                {
                    obraz->blue [i][j] = 0;
                }
                
                if (obraz->blue [i][j] > wartprog) //progowanie "w gore", do bieli
                {
                    obraz->blue [i][j] = obraz->szarosci;
                }
            }
        }             
        }
        }
        
}

/************************************************************************************
 * Funkcja wykonujaca konturowanie na wczytanym pliku       	       	       	    *
 *										                                            *
 * \param[in] t_obraz *obraz struktura przechowujaca dane o obrazie    		        *
 *                                  						                        *
 ************************************************************************************/

void konturowanie(t_obraz *obraz)
{
    int i, j;
    if (obraz->typobrazu == PGM)
    {
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

    if (obraz->typobrazu == PPM)
    {
        if (obraz->kanal == KANAL || obraz->kanal == RED)
        {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (i==(obraz->wymy-1))        /*wyjatek dla dolnych krawedzi obrazu*/
                {
                    if (j==(obraz->wymx-1))    /*wyjatek dla rogu obrazu*/
                    {
                        obraz->red [i][j] = 0;
                    }
                    else
                    {
                        obraz->red [i][j] = (abs(obraz->red [i][j+1]-obraz->red [i][j])); /*wyjatek dla dolnej krawedzi obrazu*/
                    }
                    
                }
                else
                {
                    if (j==(obraz->wymx-1))    /*wyjatek dla prawej krawedzi obrazu*/
                    {
                        obraz->red [i][j] = (abs(obraz->red [i+1][j]-obraz->red [i][j]));
                    }
                    else                /*standardowa sytuacja*/
                    {
                        obraz->red [i][j] = (abs(obraz->red [i+1][j]-obraz->red [i][j]) + abs(obraz->red [i][j+1]-obraz->red [i][j]));

                        if (obraz->red [i][j] > obraz->szarosci)    /*moze wystapic sytuacja w ktorej powyzszy wzor odda wart. wieksza niz  */
                        {                                   /*maksymalna mozliwa, ten if stanowi zabezpieczenie przed czyms takim   */
                            obraz->red [i][j] = obraz->szarosci; 
                        }
                        
                    }
                    /*konturowanie wedlug wzoru z pliku obrazy_filtry.pdf, abs (int) to wart. bezwzgledna z int*/
                } 
            }
        }
        }
        if (obraz->kanal == KANAL || obraz->kanal == GREEN)
        {
        for (i=0; i<obraz->wymy; ++i)    
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (i==(obraz->wymy-1))        /*wyjatek dla dolnych krawedzi obrazu*/
                {
                    if (j==(obraz->wymx-1))    /*wyjatek dla rogu obrazu*/
                    {
                        obraz->green [i][j] = 0;
                    }
                    else
                    {
                        obraz->green [i][j] = (abs(obraz->green [i][j+1]-obraz->green [i][j])); /*wyjatek dla dolnej krawedzi obrazu*/
                    }
                    
                }
                else
                {
                    if (j==(obraz->wymx-1))    /*wyjatek dla prawej krawedzi obrazu*/
                    {
                        obraz->green [i][j] = (abs(obraz->green [i+1][j]-obraz->green [i][j]));
                    }
                    else                /*standardowa sytuacja*/
                    {
                        obraz->green [i][j] = (abs(obraz->green [i+1][j]-obraz->green [i][j]) + abs(obraz->green [i][j+1]-obraz->green [i][j]));

                        if (obraz->green [i][j] > obraz->szarosci)    /*moze wystapic sytuacja w ktorej powyzszy wzor odda wart. wieksza niz  */
                        {                                   /*maksymalna mozliwa, ten if stanowi zabezpieczenie przed czyms takim   */
                            obraz->green [i][j] = obraz->szarosci; 
                        }
                        
                    }
                    /*konturowanie wedlug wzoru z pliku obrazy_filtry.pdf, abs (int) to wart. bezwzgledna z int*/
                } 
            }
        }    
        }
        if (obraz->kanal == KANAL || obraz->kanal == BLUE)
        {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (i==(obraz->wymy-1))        /*wyjatek dla dolnych krawedzi obrazu*/
                {
                    if (j==(obraz->wymx-1))    /*wyjatek dla rogu obrazu*/
                    {
                        obraz->blue [i][j] = 0;
                    }
                    else
                    {
                        obraz->blue [i][j] = (abs(obraz->blue [i][j+1]-obraz->blue [i][j])); /*wyjatek dla dolnej krawedzi obrazu*/
                    }
                    
                }
                else
                {
                    if (j==(obraz->wymx-1))    /*wyjatek dla prawej krawedzi obrazu*/
                    {
                        obraz->blue [i][j] = (abs(obraz->blue [i+1][j]-obraz->blue [i][j]));
                    }
                    else                /*standardowa sytuacja*/
                    {
                        obraz->blue [i][j] = (abs(obraz->blue [i+1][j]-obraz->blue [i][j]) + abs(obraz->blue [i][j+1]-obraz->blue [i][j]));

                        if (obraz->blue [i][j] > obraz->szarosci)    /*moze wystapic sytuacja w ktorej powyzszy wzor odda wart. wieksza niz  */
                        {                                   /*maksymalna mozliwa, ten if stanowi zabezpieczenie przed czyms takim   */
                            obraz->blue [i][j] = obraz->szarosci; 
                        }
                        
                    }
                    /*konturowanie wedlug wzoru z pliku obrazy_filtry.pdf, abs (int) to wart. bezwzgledna z int*/
                } 
            }
        }    
        }
    }
        
}

/************************************************************************************
 * Funkcja wykonujaca rozmywanie pionowe na wczytanym pliku                         *
 *										                                            *
 * PORZUCONA FUNCKJA, UZYWANE JEST TYLKO JEDNO ROZMYWANIE                           *
 *										                                            *
 * \param[in] t_obraz *obraz struktura przechowujaca dane o obrazie    		        *
 * \param[in] prog prog rozmycia wybrany przez uzytkownika (1 lub 2)                *
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
 *										                                            *
 * \param[in] t_obraz *obraz struktura przechowujaca dane o obrazie    		        *
 * \param[in] prog prog rozmycia wybrany przez uzytkownika (1 lub 2)                *
 ************************************************************************************/
void rozmywanie_poziom(t_obraz *obraz, int prog)
{
    int i, j;   /*rozmywanie jest wykonywane do tabeli tymczasowej (tabela_temp)*/
                /*po to by pobierane wartosci sie zgadzaly z oczekiwaniami      */
                /*gdyby nie ten zabieg funkcja pobieralaby wartosci juz rozmyte */
                /*dla ktorych w dalszej czesci obrazu moglyby pojawiac sie bledy*/

/*alokacja miejsca w pamieci dla tabeli tymczasowej*/
  obraz->tabela_temp = (int **) malloc((obraz->wymy) * sizeof(int*)); /*alokacja indeksów wierszy*/
  for (i = 0; i < (obraz->wymy); i++) /*alokacja odpowiedniej liczby kolumn dla wszystkich wierszy*/
  {
    obraz->tabela_temp[i] = (int *) malloc((obraz->wymx) * sizeof(int)); 
  }
    if (obraz->typobrazu == PGM)
    {
        if (prog == 1) //pierwszy prog rozmywania
    {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (j==KRAWEDZ)     //wyjatek dla gornej krawedzi obrazu, by funkcja nie pobierala czegos co nie istnieje
                {
                obraz->tabela_temp[i][j] = (obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j+1])/2;
                }
                if (j==(obraz->wymx-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j])/2;
                }
                else                //standardowa sytuacja
                {
                obraz->tabela_temp[i][j] = (obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j+1])/3;  
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
                obraz->tabela_temp[i][j] = (obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j+1]+obraz->obraz_pgm[i][j+2])/3;
                }
                if (j==(KRAWEDZ+1)) //wyjatek dla drugiego wiersza obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j+1]+obraz->obraz_pgm[i][j+2])/4;
                }
                if (j==(obraz->wymx-2))   //wyjatek dla przedostatniego wiersza obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->obraz_pgm[i][j-2]+obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j]+1)/4;
                }
                if (j==(obraz->wymx-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->obraz_pgm[i][j-2]+obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j])/3;
                }
                else                //standardowa sytuacja
                {
                obraz->tabela_temp[i][j] = (obraz->obraz_pgm[i][j-2]+obraz->obraz_pgm[i][j-1]+obraz->obraz_pgm[i][j]+obraz->obraz_pgm[i][j]+1+obraz->obraz_pgm[i][j+2])/5;  
                }         
            }
        }
    }

    for (i=0; i<obraz->wymy; ++i)
    {
        for (j=0; j<obraz->wymx; ++j)                 /*czesc funkcji odpowiedzialna za przepisanie              */
        {                                       /*wartosci z tabeli tymczasowej spowrotem do glownej tabeli*/
        obraz->obraz_pgm [i][j] = obraz->tabela_temp[i][j];   /*oraz wyczyszczenie tabeli tymczasowej                    */
        obraz->tabela_temp[i][j] = 0;
        }
    }        
    }

if (obraz->typobrazu == PPM)
    {
    if (obraz->kanal == KANAL || obraz->kanal == RED)
    {
              if (prog == 1) //pierwszy prog rozmywania
    {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (j==KRAWEDZ)     //wyjatek dla gornej krawedzi obrazu, by funkcja nie pobierala czegos co nie istnieje
                {
                obraz->tabela_temp[i][j] = (obraz->red[i][j]+obraz->red[i][j+1])/2;
                }
                if (j==(obraz->wymx-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->red[i][j-1]+obraz->red[i][j])/2;
                }
                else                //standardowa sytuacja
                {
                obraz->tabela_temp[i][j] = (obraz->red[i][j-1]+obraz->red[i][j]+obraz->red[i][j+1])/3;  
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
                obraz->tabela_temp[i][j] = (obraz->red[i][j]+obraz->red[i][j+1]+obraz->red[i][j+2])/3;
                }
                if (j==(KRAWEDZ+1)) //wyjatek dla drugiego wiersza obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->red[i][j-1]+obraz->red[i][j]+obraz->red[i][j+1]+obraz->red[i][j+2])/4;
                }
                if (j==(obraz->wymx-2))   //wyjatek dla przedostatniego wiersza obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->red[i][j-2]+obraz->red[i][j-1]+obraz->red[i][j]+obraz->red[i][j]+1)/4;
                }
                if (j==(obraz->wymx-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->red[i][j-2]+obraz->red[i][j-1]+obraz->red[i][j])/3;
                }
                else                //standardowa sytuacja
                {
                obraz->tabela_temp[i][j] = (obraz->red[i][j-2]+obraz->red[i][j-1]+obraz->red[i][j]+obraz->red[i][j]+1+obraz->red[i][j+2])/5;  
                }         
            }
        }
    }

    for (i=0; i<obraz->wymy; ++i)
    {
        for (j=0; j<obraz->wymx; ++j)                 /*czesc funkcji odpowiedzialna za przepisanie              */
        {                                       /*wartosci z tabeli tymczasowej spowrotem do glownej tabeli*/
        obraz->red [i][j] = obraz->tabela_temp[i][j];   /*oraz wyczyszczenie tabeli tymczasowej                    */
        obraz->tabela_temp[i][j] = 0;
        }
    }      
    }
    if (obraz->kanal == KANAL || obraz->kanal == GREEN)
    {
              if (prog == 1) //pierwszy prog rozmywania
    {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (j==KRAWEDZ)     //wyjatek dla gornej krawedzi obrazu, by funkcja nie pobierala czegos co nie istnieje
                {
                obraz->tabela_temp[i][j] = (obraz->green[i][j]+obraz->green[i][j+1])/2;
                }
                if (j==(obraz->wymx-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->green[i][j-1]+obraz->green[i][j])/2;
                }
                else                //standardowa sytuacja
                {
                obraz->tabela_temp[i][j] = (obraz->green[i][j-1]+obraz->green[i][j]+obraz->green[i][j+1])/3;  
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
                obraz->tabela_temp[i][j] = (obraz->green[i][j]+obraz->green[i][j+1]+obraz->green[i][j+2])/3;
                }
                if (j==(KRAWEDZ+1)) //wyjatek dla drugiego wiersza obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->green[i][j-1]+obraz->green[i][j]+obraz->green[i][j+1]+obraz->green[i][j+2])/4;
                }
                if (j==(obraz->wymx-2))   //wyjatek dla przedostatniego wiersza obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->green[i][j-2]+obraz->green[i][j-1]+obraz->green[i][j]+obraz->green[i][j]+1)/4;
                }
                if (j==(obraz->wymx-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->green[i][j-2]+obraz->green[i][j-1]+obraz->green[i][j])/3;
                }
                else                //standardowa sytuacja
                {
                obraz->tabela_temp[i][j] = (obraz->green[i][j-2]+obraz->green[i][j-1]+obraz->green[i][j]+obraz->green[i][j]+1+obraz->green[i][j+2])/5;  
                }         
            }
        }
    }

    for (i=0; i<obraz->wymy; ++i)
    {
        for (j=0; j<obraz->wymx; ++j)                 /*czesc funkcji odpowiedzialna za przepisanie              */
        {                                       /*wartosci z tabeli tymczasowej spowrotem do glownej tabeli*/
        obraz->green [i][j] = obraz->tabela_temp[i][j];   /*oraz wyczyszczenie tabeli tymczasowej                    */
        obraz->tabela_temp[i][j] = 0;
        }
    }            
    }
    if (obraz->kanal == KANAL || obraz->kanal == BLUE)
    {
              if (prog == 1) //pierwszy prog rozmywania
    {
        for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {
                if (j==KRAWEDZ)     //wyjatek dla gornej krawedzi obrazu, by funkcja nie pobierala czegos co nie istnieje
                {
                obraz->tabela_temp[i][j] = (obraz->blue[i][j]+obraz->blue[i][j+1])/2;
                }
                if (j==(obraz->wymx-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->blue[i][j-1]+obraz->blue[i][j])/2;
                }
                else                //standardowa sytuacja
                {
                obraz->tabela_temp[i][j] = (obraz->blue[i][j-1]+obraz->blue[i][j]+obraz->blue[i][j+1])/3;  
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
                obraz->tabela_temp[i][j] = (obraz->blue[i][j]+obraz->blue[i][j+1]+obraz->blue[i][j+2])/3;
                }
                if (j==(KRAWEDZ+1)) //wyjatek dla drugiego wiersza obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->blue[i][j-1]+obraz->blue[i][j]+obraz->blue[i][j+1]+obraz->blue[i][j+2])/4;
                }
                if (j==(obraz->wymx-2))   //wyjatek dla przedostatniego wiersza obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->blue[i][j-2]+obraz->blue[i][j-1]+obraz->blue[i][j]+obraz->blue[i][j]+1)/4;
                }
                if (j==(obraz->wymx-1))   //wyjatek dla dolnej krawedzi obrazu, jw.
                {
                obraz->tabela_temp[i][j] = (obraz->blue[i][j-2]+obraz->blue[i][j-1]+obraz->blue[i][j])/3;
                }
                else                //standardowa sytuacja
                {
                obraz->tabela_temp[i][j] = (obraz->blue[i][j-2]+obraz->blue[i][j-1]+obraz->blue[i][j]+obraz->blue[i][j]+1+obraz->blue[i][j+2])/5;  
                }         
            }
        }
    }

    for (i=0; i<obraz->wymy; ++i)
    {
        for (j=0; j<obraz->wymx; ++j)                 /*czesc funkcji odpowiedzialna za przepisanie              */
        {                                       /*wartosci z tabeli tymczasowej spowrotem do glownej tabeli*/
        obraz->blue [i][j] = obraz->tabela_temp[i][j];   /*oraz wyczyszczenie tabeli tymczasowej                    */
        obraz->tabela_temp[i][j] = 0;
        }
    }            
    }
    }


}

/************************************************************************************
 * Funkcja wykonujaca konwersje pliku PPM do PGM                                    *
 *										                                            *
 * \param[in] t_obraz *obraz struktura przechowujaca dane o obrazie    		        *
 ************************************************************************************/
void konwersja(t_obraz *obraz)
{
int i, j;

/*alokacja miejsca w pamieci dla obrazu*/
  obraz->obraz_pgm = (int **) malloc((obraz->wymy) * sizeof(int*)); /*alokacja indeksów wierszy*/
  for (i = 0; i < (obraz->wymy); i++) /*alokacja odpowiedniej liczby kolumn dla wszystkich wierszy*/
  {
    obraz->obraz_pgm[i] = (int *) malloc((obraz->wymx) * sizeof(int)); 
  }
  
    for (i=0; i<obraz->wymy; ++i)
        {
            for (j=0; j<obraz->wymx; ++j)
            {       /*konwersja obrazu to wyciagniecie sredniej arytmetycznej z kazdego kanalu kazdego piksela*/
               obraz->obraz_pgm[i][j] = ((obraz->red[i][j]) + (obraz->green[i][j]) + (obraz->blue[i][j]))/3;        
            }
        }
        obraz->typobrazu = PGM; /*zmiana typu pliku znajdujacego sie w pamieci*/
}