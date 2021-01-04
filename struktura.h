#ifndef STRUKTURA_H
#define STRUKTURA_H

#define MAX 999         /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024   /* Dlugosc buforow pomocniczych */
#define KRAWEDZ 0       /* Krawedz obrazu */
#define PGM 2           /* Definicja typu obrazu */
#define PPM 3           /* Definicja typu obrazu */
#define KANAL 0         /* Definicja domyslnego kanalu */
#define RED 1
#define GREEN 2
#define BLUE 3

/*Struktura dla obrazu P2 w Przetwarzaniu obrazów 1*/
/*
typedef struct {
    int wymx, wymy, szarosci;
    int obraz_pgm [][MAX];
} t_obraz;
*/

typedef struct {
    int wymx, wymy, szarosci;
    int typobrazu;
    int kanal;
    int **obraz_pgm;
    int **red;
    int **green;
    int **blue;
} t_obraz;


#endif