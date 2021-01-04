#include <stdio.h>
#include <stdlib.h>    
#include <unistd.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int optvalue = 0; /*miejsce do przechowywania informacji o opcjach wywolania*/
    int wart, procprog, promien;
    char* nazwa;
    while ((optvalue = getopt(argc, argv, "i:o:r:p:nkdm:h")))   /*petla wykonujaca sie dopoki nie wyczerpie*/
    {                                                           /*wszystkich opcji wywolania*/
        switch (optvalue) /*menu wywolujace odpowiednie funkcje dla odpowiednich opcji wywolania*/
        {
        case 'i':   /*wczytanie pliku > -i [nazwa pliku]*/
            printf ("%s \n", optarg);
            nazwa = optarg;
            printf ("wczytano %s \n", nazwa);
            break;
        case 'o':   /*zapis pliku > -o [nazwa pliku]*/
            printf ("%s \n", optarg);
            nazwa = optarg;
            printf ("zapisano %s \n", nazwa);
            break;
        case 'r':   /*rozmywanie obrazu > -r [1/2]*/
            promien = atoi(optarg);
            printf ("rozmycie %d \n", promien);
            break;
        case 'p':   /*progowanie obrazu > -p [0-100]*/
            procprog = atoi(optarg);
            printf ("progowanie %d \n", procprog);
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
