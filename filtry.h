#include "struktura.h"

#ifndef FILTRY_H
#define FILTRY_H

void negatyw(t_obraz *obraz);
void progowanie(t_obraz *obraz, int procprog);
void konturowanie(t_obraz *obraz);
void rozmywanie_pion(t_obraz *obraz, int prog, int tabela_temp [][MAX]);
void rozmywanie_poziom(t_obraz *obraz, int prog);
void konwersja(t_obraz *obraz);

#endif 
