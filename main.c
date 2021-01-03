#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "operacje.h"
#include "filtry.h"
#include "struktura.h"



int main() {
  int tabelatemp[MAX][MAX]; /*tabela tymczasowa opisana w funkcji rozmywania*/
  int wart, procprog, promien; /*wart - zmienna dla menu uzytkownika*/
  int odczytano = 0;                        /*procprog - opisane w funkcji progowania*/
  FILE *plik;
  char nazwa[100];
  t_obraz obraz;
  


  do
{
    printf ("Menu: \n 1 - Wczytaj \n 2 - Zapisz \n 3 - Wyswietl \n 4 - Negatyw \n 5 - Progowanie \n"); 
    printf (" 6 - Konturowanie \n 7 - Rozmycie pionowe \n 8 - Rozmycie poziome \n 0 - Wyjscie \n Twój wybor: ");
    scanf ("%d", &wart);
    
    switch (wart)
    {
    case 1:             /*wczytywanie pliku*/
        printf("Wybrałeś opcję %d. \n", wart);
        printf("Podaj nazwe pliku:\n");
        scanf("%s",nazwa); /*Uzytkownik podaje nazwe pliku ktory chce wczytac*/
        plik=fopen(nazwa,"r"); /*plik odczytywany w trybie read only*/
        
        if (plik != NULL) /*sprawdzenie czy plik istnieje*/
        {
            odczytano = czytaj(plik, &obraz); /*wywolanie f. czytaj i przypisanie "odczytano" jej zwrotu*/
            fclose(plik);   /*zamkniecie pliku*/
            wyczysc();      /*wywolanie f. czyszczenia terminala*/
            printf("Plik odczytano poprawnie\n\n"); /*zwrot do terminala*/
        }
        else    /*sytuacja w ktorej podany plik nieistnieje*/
        {
            wyczysc();
            printf("Blad: Nie udalo sie wczytac podanego pliku\n\n");
        }
        
        break;
    case 2:
        printf("Wybrałeś opcję %d. \n", wart);
        if (odczytano != 0) /*sprawdzenie czy wczytano plik*/
        {
            printf("Podaj nazwe pod jaka ma zostac zapisany plik, pamietajac o koncowce (.pgm): ");
            scanf("%s",nazwa); /*pobranie nazwy pliku podanej przez uzytkownika*/
            plik=fopen(nazwa,"w"); /*plik otwarty w trybie write premitted*/
            zapisz(plik,&obraz); /*wywolanie funkcji zapisz*/
            fclose(plik);
            wyczysc();  /*wywolanie f. czyszczenia terminala*/
            printf("Poprawnie zapisano plik\n\n");
        }
        else
        {
            wyczysc();
            printf("Blad: Brak pliku do zapisania\n\n");
         }
        break;
    case 3:
        printf("Wybrałeś opcję %d. \n", wart);
        if (odczytano != 0){ /*sprawdzenie czy wczytano plik*/
        plik=fopen("temp.pgm","w"); /*otwarcie pliku tymczasowego do wyswietlenia*/
        zapisz(plik,&obraz); /*zapis pliku*/
        fclose(plik); /*zamykam go*/
        wyswietl("temp.pgm"); /*wywolanie f. wyswietlania*/
        wyczysc();  /*wywolanie f. czyszczenia terminala*/
        printf("Obraz wyswietlono poprawnie\n\n");
      }
      else{ /*sytuacja, gdy plik nie jest wczytany*/
        wyczysc();  /*wywolanie f. czyszczenia terminala*/
        printf("Blad: Brak pliku do wyswietlenia\n\n");
      }
        break;
    case 4:
        printf("Wybrałeś opcję %d. \n", wart);
        if (odczytano != 0){ /*sprawdzenie czy wczytano plik*/
        negatyw(&obraz); /*wywolanie f. negatywu*/
        wyczysc();        /*wywolanie f. czyszczenia terminala*/
        printf("Negatyw wykonano poprawnie\n\n");
      }
      else{ /*sytuacja, gdy plik nie jest wczytany*/
        wyczysc();
        printf("Blad: Brak pliku do wykonania negatywu\n\n");
        }
        break;
    case 5:
        printf("Wybrałeś opcję %d. \n", wart);
        if (odczytano != 0){ /*sprawdzenie czy wczytano plik*/
        printf("Podaj procent progowania: ");
        scanf("%d", &procprog); /*uzytkownik podaje procent progowania*/
        if (procprog>=0 || procprog<=100)
        {
            progowanie(&obraz,procprog); /*wywolanie f. progowania*/
            wyczysc();        /*wywolanie f. czyszczenia terminala*/
            printf("Progowanie wykonano poprawnie\n\n");
        }
        else
        {
            wyczysc();        /*wywolanie f. czyszczenia terminala*/
            printf("Blad: Procent progowania wykracza poza mozliwy zakres\n\n");
        }
      }
      else{ /*sytuacja, gdy plik nie jest wczytany*/
        wyczysc();
        printf("Blad: Brak pliku do wykonania progowania\n\n");
        }
        break;
    case 6:
        printf("Wybrałeś opcję %d. \n", wart);
        if (odczytano != 0){    /*sprawdzenie czy wczytano plik*/
        konturowanie(&obraz); /*wywolanie f. konturowania*/
        wyczysc();        /*wywolanie f. czyszczenia terminala*/
        printf("Konturowaie wykonano poprawnie\n\n");
      }
      else{ /*sytuacja, gdy plik nie jest wczytany*/
        wyczysc();
        printf("Blad: Brak pliku do wykonania konturowania\n\n");
        }
        break;
    case 7:
        printf("Wybrałeś opcję %d. \n", wart);
        if (odczytano != 0){    /*sprawdzenie czy wczytano plik*/
        printf("Podaj promien rozmycia (1 lub 2): ");
        scanf("%d", &promien); /*uzytkownik podaje promien rozmycia*/
        if (promien == 1 || promien == 2)
        {
            rozmywanie_pion(&obraz, promien, tabelatemp);
            wyczysc();        /*wywolanie f. czyszczenia terminala*/
            printf("Rozmycie wykonano poprawnie\n\n");
        }
        else
        {
            wyczysc();        /*wywolanie f. czyszczenia terminala*/
            printf("Blad: Podano niepoprawy promien rozmycia \n\n");
        }
      }
      else{ /*sytuacja, gdy plik nie jest wczytany*/
        wyczysc();
        printf("Blad: Brak pliku do wykonania rozmycia\n\n");
        }
        break;
    case 8:
        printf("Wybrałeś opcję %d. \n", wart);
        if (odczytano != 0){    /*sprawdzenie czy wczytano plik*/
        printf("Podaj promien rozmycia (1 lub 2): ");
        scanf("%d", &promien); /*uzytkownik podaje promien rozmycia*/
        if (promien == 1 || promien == 2)
        {
            rozmywanie_poziom(&obraz, promien, tabelatemp);
            wyczysc();        /*wywolanie f. czyszczenia terminala*/
            printf("Rozmycie wykonano poprawnie\n\n");
        }
        else
        {
            wyczysc();        /*wywolanie f. czyszczenia terminala*/
            printf("Blad: Podano niepoprawy promien rozmycia \n\n");
        }
      }
      else{ /*sytuacja, gdy plik nie jest wczytany*/
        wyczysc();
        printf("Blad: Brak pliku do wykonania rozmycia\n\n");
        }
        break;    
    case 0:
        puts ("Koniec działania programu");
        usun();
        return 0;
        break;

    default:
        puts ("Błędna wartość!");
        break;
    }

} while (wart != 0);
}