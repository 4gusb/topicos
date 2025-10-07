#include <stdio.h>
#include "videoclub.h"
#define ERROR -1


int main(int argc, char *argv[]) {
    char * arch = (argc >= 2) ? argv[1] : "data/miembros-VC.txt";  //si no se paso un archivo por main, busca este file por default
    generarBinario(arch);
    return 0;
}