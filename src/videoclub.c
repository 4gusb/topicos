#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "videoclub.h"

#define MAX_LINEA 1024
#define ANIOACTUAL 2025
#define TODOOK 0
#define FECHAINVALIDA -1
#define FECHAVALIDA 1
#define ARCHNOEXISTE -1

//FALTAN: opcion de recuperar archivo
int generarBinario(const char * arch){
    char linea[MAX_LINEA];
    FILE * txt;
    t_fecha fechaProceso;
    t_miembro socio; 

    printf("Bienvenido.\nIngrese fecha de procesamiento.");
    ingresarFecha(&fechaProceso);   //ya incluye validarFecha
    FILE * txt = fopen(arch, "wb");
    if(!txt){
        printf("\nError al abrir el archivo.");
        return ARCHNOEXISTE;
    }
    
    while(fgets(linea, sizeof(linea), txt)){    //mientras haya lineas, sigue leyendo
        leerRegistro(linea, &socio);   //convierte linea de txt a registro socio
    }


    fclose(txt);

    leerRegistro(arch, &socio);



    return TODOOK;
}

int ingresarFecha(const t_fecha * fecha){
    int flagFecha;
    printf("\nDia: ");
    scanf("%d", &fecha->d);
    printf("\nMes: ");
    scanf("%d", &fecha->m);
    printf("\nAnio: ");
    scanf("%d", &fecha->a);
    flagFecha = validarFecha(fecha);
    if(flagFecha == FECHAINVALIDA){
        printf("\nLa fecha es invalida.");
        return FECHAINVALIDA;
    }
    return FECHAVALIDA;
}

int validarFecha(const t_fecha * fecha){
    int diasMeses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((fecha->a < 1900 || fecha->a > ANIOACTUAL) || (fecha->m < 1 || fecha->m >12))  return FECHAINVALIDA; //valida mes y anio
    if(esBisiesto(&(fecha->a)))
        diasMeses[1] = 29;  //si es bisiesto, el maximo de dias de febrero es 29
    if(fecha->d < 1 || fecha->d > diasMeses[(fecha->m)-1]) return FECHAINVALIDA;  //valida dia. (fecha->m)-1 para alinear el mes con el indice del vector
    else
        return FECHAVALIDA; 
}

bool esBisiesto(const int * anio){
    return (*anio % 4 == 0 && *anio % 100 != 0) || (*anio % 400 == 0);
}

int leerRegistro(const char *linea, const t_miembro * socio)
{
    sscanf(linea, "%ld,%59s,%d/%d/%d;%c;%d/%d/%d,%9s,%d/%d/%d,%c,%9s,%29s", 
        socio->dni, socio->nombre, socio->fNac, socio->sexo, socio->fAfiliacion, socio->categoria, socio->fechaUltCuota,
        socio->estado, socio->plan, socio->emailTutor);
    return 0;
}
