#ifndef STRUKTURA_H
#define STRUKTURA_H

#define MAX 999         /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024   /* Dlugosc buforow pomocniczych */
#define KRAWEDZ 0       /* Krawedz obrazu */

/*Struktura dla obrazu P2 w Przetwarzaniu obrazów 1*/
/*
typedef struct {
    int wymx, wymy, szarosci;
    int obraz_pgm [][MAX];
} t_obraz;
*/

typedef struct {
    int wymx, wymy, szarosci;
    int **obraz_pgm;
} t_obraz;


#endif