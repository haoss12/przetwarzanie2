#include <stdio.h>
#include <stdlib.h>    
#include <unistd.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int optvalue = 0, liczba, i, liczbaa;

    while ((optvalue = getopt(argc, argv, "xh:y")))
    {
        switch (optvalue)
        {
        case 'x':
            if (optarg != NULL)
            {
                liczba = atoi(optarg);
            }
            for (i = 0; i < liczba; i++)
            {
                printf ("%d", i);
            }
            printf ("\n");
            break;
        case 'y':
            printf ("pozdro 600 na rejonei \n");
        break;
        case 'h':
            printf("nei pomoge Ci synu \n");
            if (optarg != NULL)
            {
                liczbaa = atoi(optarg);
            }
            printf ("%d \n", liczbaa);
        break;
        default:
            return 1;
            break;
        }
    }
    
    return 0;
}
