#include <stdio.h>
#include <stdlib.h>    
#include <unistd.h>
#include <getopt.h>
#include "struktura.h"

int main(int argc, char **argv)
{
    int optvalue = 0; /*miejsce do przechowywania informacji o opcjach wywolania*/
    int wart, procprog, promien;
    char* nazwa;
    FILE *plik;
    int odczytano = 0; 
    t_obraz obraz;

    while ((optvalue = getopt(argc, argv, "i:o:r:p:nkdm:h")))   /*petla wykonujaca sie dopoki nie wyczerpie*/
    {                                                           /*wszystkich opcji wywolania*/
        switch (optvalue) /*menu wywolujace odpowiednie funkcje dla odpowiednich opcji wywolania*/
        {
        case 'i':   /*wczytanie pliku > -i [nazwa pliku]*/
            printf ("%s \n", optarg);
            nazwa = optarg;
            printf ("wczytano %s \n", nazwa);
            if (strcmp(nazwa, "-")==0)
            {
            odczytano = czytaj(stdin, &obraz); /*wywolanie f. czytaj dla standardowego wejscia i przypisanie "odczytano" jej zwrotu*/ 
            }
            else
            {
            plik=fopen(nazwa,"r"); /*plik o podanej nazwie odczytywany w trybie read only*/

            if (plik != NULL) /*sprawdzenie czy plik istnieje*/
            {
                odczytano = czytaj(plik, &obraz); /*wywolanie f. czytaj i przypisanie "odczytano" jej zwrotu*/
                fclose(plik);   /*zamkniecie pliku*/
            }
            else    /*sytuacja w ktorej podany plik nie istnieje*/
            {
                printf("Blad: Nie udalo sie wczytac podanego pliku\n");
            }
            }
            break;
        case 'o':   /*zapis pliku > -o [nazwa pliku]*/
            printf ("%s \n", optarg);
            nazwa = optarg;
            printf ("zapisano %s \n", nazwa);
            if (odczytano != 0) /*sprawdzenie czy wczytano plik*/
            {
                if (strcmp(nazwa, "-")==0)
                {
                zapisz (stdout, &obraz); /*wywolanie f. zapisz dla standardowego wyjscia*/ 
                }
                else
                {
                plik=fopen(nazwa,"w");  /*plik otwarty w trybie write premitted*/
                zapisz(plik,&obraz);    /*wywolanie funkcji zapisz*/
                fclose(plik);
                }
            }
            else
            {
                printf("Blad: Brak pliku do zapisania\n\n");
            }
            break;
        case 'r':   /*rozmywanie obrazu > -r [1/2]*/
            promien = atoi(optarg); /*wczytanie promieniu rozmycia z argumentu opcji*/
            printf ("rozmycie %d \n", promien);
            if (odczytano != 0){    /*sprawdzenie czy wczytano plik*/
            if (promien == 1 || promien == 2) /*sprawdzenie poprawnosci promienia rozmycia*/
            {
            rozmywanie_poziom(&obraz, promien, tabelatemp);
            }
            else
            {
            printf("Blad: Podano niepoprawy promien rozmycia \n\n");
            }
            }
            else{   /*sytuacja, gdy plik nie jest wczytany*/
            printf("Blad: Brak pliku do wykonania rozmycia\n\n");
            }                
            break;
        case 'p':   /*progowanie obrazu > -p [0-100]*/
            procprog = atoi(optarg); /*wczytanie procentu progowania z argumentu opcji*/
            printf ("progowanie %d \n", procprog);
            if (odczytano != 0){ /*sprawdzenie czy wczytano plik*/
            if (procprog>=0 || procprog<=100)
            {
            progowanie(&obraz,procprog); /*wywolanie f. progowania*/
            }
            else
            {
            printf("Blad: Procent progowania wykracza poza mozliwy zakres\n\n");
            }
            }
            else{ /*sytuacja, gdy plik nie jest wczytany*/
            printf("Blad: Brak pliku do wykonania progowania\n\n");
            }
            break;
        case 'n':   /*negatyw obrazu > -n*/
            printf ("negatyw \n");
            break;
        case 'k':   /*konturowanie obrazu > -k*/
            printf ("kontur \n");
            break;
        case 'd':   /*wyswietlenie obrazu > -d*/
            printf ("wyswietl \n");
            break;
        case 'm':   /*wybor kanalu do pracy > -m [r/g/b]*/
            printf ("kanal  %s\n", optarg);
            break;
        case 'h':   /*pomoc dla uzytkownika > -h*/
            printf("nei pomoge Ci synu \n");
        break;
        default:
            return 1;
            break;
        }
    }
    
    return 0;
}
