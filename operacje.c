#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										                                            *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			            *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		            *
 * \param[out] wymx szerokosc obrazka						                        *
 * \param[out] wymy wysokosc obrazka						                        *
 * \param[out] szarosci liczba odcieni szarosci					                    *
 * \return liczba wczytanych pikseli						                        *
 ************************************************************************************/

int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci)
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

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

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

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",wymx,wymy,szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<*wymy;i++) {
    for (j=0;j<*wymx;j++) {
      if (fscanf(plik_we,"%d",&(obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return *wymx**wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

/************************************************************************************
 * Funckja zapisujaca plik pod wybrana przez uzytkownika nazwa 	       	       	    *
 *										                                            *
 * \param[out] plik_wy uchwyt do pliku do zapisu obrazu w PGM			            *
 * \param[in] obraz_pgm tablica, w ktorej znajduje sie obraz do zapisu	            *
 * \param[in] wymx szerokosc obrazka						                        *
 * \param[in] wymy wysokosc obrazka				    		                        *
 * \param[in] szarosci liczba odcieni szarosci					                    *
 * \return (0) dla bledu, 1 dla poprawnej sytuacji			                        *
 ************************************************************************************/
int zapisz(FILE *plik_wy, int obraz_pgm [][MAX], int *wymx, int *wymy, int szarosci)
{
    int i, j;

    if (plik_wy == NULL)
    {
        fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
        return(0);
    }
    
    fprintf(plik_wy, "P2\n");
    fprintf(plik_wy, "%d %d %d", *wymx, *wymy, szarosci);
    fprintf(plik_wy, "\n");
    for (i=0; i<*wymy; ++i){
        for (j=0; j<*wymx; ++j){
            fprintf(plik_wy, "%d ", (obraz_pgm [i][j]));
        }
        fprintf(plik_wy, "\n");
    }

    return 1;
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