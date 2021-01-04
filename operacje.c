#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "struktura.h"
#define MAXLINIA 30     /*maksymalna dlugosc linii w standardzie pgm/ppm*/

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										                                                              *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			                *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		              *
 * \param[out] wymx szerokosc obrazka						                                    *
 * \param[out] wymy wysokosc obrazka						                                    *
 * \param[out] szarosci liczba odcieni szarosci					                            *
 * \return liczba wczytanych pikseli						                                    *
 ************************************************************************************/

int czytaj(FILE *plik_we, t_obraz *obraz)
{
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 lub P3 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  
  
  if ( (buf[0]=='P') && (buf[1]=='2')) {  /* Czy jest magiczne "P2"? */
    obraz->typobrazu = PGM;
    
    /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  if (obraz->obraz_pgm != NULL)     /*zwalnianie pamieci, jesli byla wczesniej zaalokowana*/
  {                                 /*taka sytuacja moze nastapic gdy wczytujemy obraz do pamieci*/
    for(i=0; i<obraz->wymy; i++){   /*kolejny, n-ty raz*/
          free(obraz->obraz_pgm[i]);    /*zwolnienie poszczegolnych wierszy*/
        }
        free(obraz->obraz_pgm);         /*zwolnienie indeksow*/
  }

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d", &obraz->wymx, &obraz->wymy, &obraz->szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  

  /*alokacja miejsca w pamieci dla obrazu*/
  obraz->obraz_pgm = (int **) malloc((obraz->wymy) * sizeof(int*)); /*alokacja indeksów wierszy*/
  for (i = 0; i < (obraz->wymy); i++) /*alokacja odpowiedniej liczby kolumn dla wszystkich wierszy*/
  {
    obraz->obraz_pgm[i] = (int *) malloc((obraz->wymx) * sizeof(int)); 
  }
  

  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      if (fscanf(plik_we,"%d", (&obraz->obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return (obraz->wymx)*(obraz->wymy);   /* Czytanie zakonczone sukcesem    */
  }
  
  if ( (buf[0]=='P') && (buf[1]=='3')) {  /* Czy jest magiczne "P3"? */
    obraz->typobrazu = PPM;
    obraz->kanal = KANAL;
    
    /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  if (obraz->red != NULL)     /*zwalnianie pamieci, jesli byla wczesniej zaalokowana*/
  {                                 /*taka sytuacja moze nastapic gdy wczytujemy obraz do pamieci*/
    for(i=0; i<obraz->wymy; i++){   /*kolejny, n-ty raz*/
          free(obraz->red[i]);    /*zwolnienie poszczegolnych wierszy*/
        }
        free(obraz->red);         /*zwolnienie indeksow*/
  }
  if (obraz->green != NULL)     /*zwalnianie pamieci, jesli byla wczesniej zaalokowana*/
  {                                 /*taka sytuacja moze nastapic gdy wczytujemy obraz do pamieci*/
    for(i=0; i<obraz->wymy; i++){   /*kolejny, n-ty raz*/
          free(obraz->green[i]);    /*zwolnienie poszczegolnych wierszy*/
        }
        free(obraz->green);         /*zwolnienie indeksow*/
  }
  if (obraz->blue != NULL)     /*zwalnianie pamieci, jesli byla wczesniej zaalokowana*/
  {                                 /*taka sytuacja moze nastapic gdy wczytujemy obraz do pamieci*/
    for(i=0; i<obraz->wymy; i++){   /*kolejny, n-ty raz*/
          free(obraz->blue[i]);    /*zwolnienie poszczegolnych wierszy*/
        }
        free(obraz->blue);         /*zwolnienie indeksow*/
  }

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d", &obraz->wymx, &obraz->wymy, &obraz->szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  

  /*alokacja miejsca w pamieci dla obrazu*/
  obraz->red = (int **) malloc((obraz->wymy) * sizeof(int*)); /*alokacja indeksów wierszy*/
  for (i = 0; i < (obraz->wymy); i++) /*alokacja odpowiedniej liczby kolumn dla wszystkich wierszy*/
  {
    obraz->red[i] = (int *) malloc((obraz->wymx) * sizeof(int)); 
  }
  obraz->green = (int **) malloc((obraz->wymy) * sizeof(int*)); /*alokacja indeksów wierszy*/
  for (i = 0; i < (obraz->wymy); i++) /*alokacja odpowiedniej liczby kolumn dla wszystkich wierszy*/
  {
    obraz->green[i] = (int *) malloc((obraz->wymx) * sizeof(int)); 
  }
  obraz->blue = (int **) malloc((obraz->wymy) * sizeof(int*)); /*alokacja indeksów wierszy*/
  for (i = 0; i < (obraz->wymy); i++) /*alokacja odpowiedniej liczby kolumn dla wszystkich wierszy*/
  {
    obraz->blue[i] = (int *) malloc((obraz->wymx) * sizeof(int)); 
  }
  

  /* Pobranie obrazu i zapisanie w poszczegolnych tablicach*/
  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      if (fscanf(plik_we,"%d %d %d", (&obraz->red[i][j]),(&obraz->green[i][j]),(&obraz->blue[i][j]))!=3) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return (obraz->wymx)*(obraz->wymy);   /* Czytanie zakonczone sukcesem    */
  }
  
  else
  {
    fprintf(stderr,"Blad: To nie jest plik PGM lub PPM\n");
    return(0);
  }
  
}                       /* Zwroc liczbe wczytanych pikseli */

/************************************************************************************
 * Funckja zapisujaca plik pod wybrana przez uzytkownika nazwa 	       	       	    *
 *										                                                              *
 * \param[out] plik_wy uchwyt do pliku do zapisu obrazu w PGM			                  *
 * \param[in] obraz_pgm tablica, w ktorej znajduje sie obraz do zapisu	            *
 * \param[in] wymx szerokosc obrazka						                                    *
 * \param[in] wymy wysokosc obrazka				    		                                  *
 * \param[in] szarosci liczba odcieni szarosci					                            *
 * \return (0) dla bledu, 1 dla poprawnej sytuacji			                            *
 ************************************************************************************/
int zapisz(FILE *plik_wy, t_obraz *obraz)
{
    int i, j;

    if (plik_wy == NULL)
    {
        fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
        return(0);
    }
    if (obraz->typobrazu == PGM)
    {
    fprintf(plik_wy, "P2\n");
    fprintf(plik_wy, "%d %d %d", obraz->wymx, obraz->wymy, obraz->szarosci);
    fprintf(plik_wy, "\n");
    for (i=0; i<obraz->wymy; ++i){
        for (j=0; j<obraz->wymx; ++j){
            fprintf(plik_wy, "%d ", (obraz->obraz_pgm [i][j]));
            if (j%MAXLINIA == 0 && j != 0)
            {
              fprintf(plik_wy, "\n");
            }
            
        }
    }

    return 1;
    }
    if (obraz->typobrazu == PPM)
    {
    fprintf(plik_wy, "P3\n");
    fprintf(plik_wy, "%d %d %d", obraz->wymx, obraz->wymy, obraz->szarosci);
    fprintf(plik_wy, "\n");
    for (i=0; i<obraz->wymy; ++i){
        for (j=0; j<obraz->wymx; ++j){
            fprintf(plik_wy, "%d %d %d ", (obraz->red [i][j]), (obraz->green [i][j]), (obraz->blue [i][j]));
            if (j%MAXLINIA == 0 && j != 0)
            {
              fprintf(plik_wy, "\n");
            }
            
        }
    }

    return 1;
    }
    
}

/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku)
{
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

/*Funkcja czyszczaca terminal dla wiekszej czytelnosci menu*/
void wyczysc()
{
  char polecenie[DL_LINII];     /*bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"clear ");   /*konstrukcja polecenia postaci */
  system(polecenie);            /*wykonanie polecenia           */
}

/*Funkjca usuwajaca plik tymczasowy stworzony na potrzeby wyswietlania*/
void usun()
{    
  char polecenie[DL_LINII];     /*bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"rm ");      /*konstrukcja polecenia postaci */
  strcat(polecenie,"temp.pgm ");    /* rm "nazwa_pliku" &       */
  strcat(polecenie," &");
  system(polecenie);            /*wykonanie polecenia           */
}