#include "struktura.h"

#ifndef OPERACJE_H
#define OPERACJE_H

int czytaj(FILE *plik_we, t_obraz *obraz);
int zapisz(FILE *plik_wy, t_obraz *obraz);
void wyswietl(char *n_pliku);
void wyczysc();
void usun();

#endif 