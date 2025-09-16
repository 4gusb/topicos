#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "videoclub.h"

#define MAXLINEA 1024
#define ANIOACTUAL 2025
#define TODOOK 0
#define FECHAINVALIDA -1
#define FECHAVALIDA 1
#define ARCHNOEXISTE -1

//FALTAN: opcion de recuperar archivo
int generarBinario(char * arch){
    int validaciones;
    char linea[MAXLINEA], nombreArch[50];
    FILE * miembros_txt, * errores_txt, * miembros_dat;
    t_fecha fechaProceso;
    t_miembro socio; 

    //Ingreso de fecha de proceso
    printf("Bienvenido.\nIngrese fecha de procesamiento.");
    ingresarFecha(&fechaProceso);   //ya incluye validarFecha


    //APERTURA DE ARCHIVOS

    //Archivo miembros txt
    miembros_txt = fopen(arch, "r");
    if(!miembros_txt){
        printf("\nError al abrir el archivo.");
        return ARCHNOEXISTE;
    }
    else
        printf("\nArchivo leido correctamente.");
    /* 
    //Archivo errores txt
    sprintf(nombreArch, "error-VC-%d%d%d.txt", fechaProceso.a, fechaProceso.m, fechaProceso.d);
    errores_txt = fopen(nombreArch, "wT");
    if(!errores_txt){
        printf("\nError al crear el archivo.");
        return ARCHNOEXISTE;
    }
    else
        printf("\nArchivo creado correctamente."); 
    
    //Archivo miembros binario
    sprintf(nombreArch, "miembros-VC-%d%d%d.dat", fechaProceso.a, fechaProceso.m, fechaProceso.d);
    miembros_dat = fopen(nombreArch, "wb");    
    if(!miembros_dat){
        printf("\nError al crear el archivo.");
        return ARCHNOEXISTE;
    }
    else
        printf("\nArchivo creado correctamente."); 
    */

    //LECTURA MIEMBROS TXT

    while(fgets(linea, sizeof(linea), miembros_txt)){    //mientras haya lineas, sigue leyendo
        leerRegistro(linea, &socio);   //convierte linea de txt a registro socio
        //valida
        //si no hubo errores, escribe el wb
        //si hubo errores, escribe el txt errores
        socio = (t_miembro){0};     //limpia la struct temporal cada vez que lee una nueva linea
    }
    
    fclose(miembros_txt);
    //fclose(errores_txt);
    //fclose(miembros_dat);
    return TODOOK;
}

int ingresarFecha(t_fecha * fecha){
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


//FALTA: podrian agregarse validaciones por si algun valor no se lee bien (ej. fecha no numerica)
int leerRegistro(char *linea, t_miembro * socio)
{
    sscanf(linea, "\n%ld,%59[^,],%d/%d/%d, %c,%d/%d/%d,%9[^,],%d/%d/%d, %c,%9[^,],%29[^,]", 
        &socio->dni,
        socio->nombre,
        &socio->fNac.d,
        &socio->fNac.m, 
        &socio->fNac.a,
        &socio->sexo,
        &socio->fAfiliacion.d,
        &socio->fAfiliacion.m,
        &socio->fAfiliacion.a,
        socio->categoria,
        &socio->fechaUltCuota.d,
        &socio->fechaUltCuota.m,
        &socio->fechaUltCuota.a,
        &socio->estado,
        socio->plan,
        socio->emailTutor);

    printf("\nDNI:%ld, \nNombre: %s, \nFnac: %d/%d/%d, \nSexo:%c, \nfAfiliciacion:%d/%d/%d, \nCategoria: %s, \nfUltCuota: %d/%d/%d, \nEstado: %c, \nPlan: %s, \nEmailTutor:%s",
        socio->dni,
        socio->nombre,
        socio->fNac.d,
        socio->fNac.m, 
        socio->fNac.a,
        socio->sexo,
        socio->fAfiliacion.d,
        socio->fAfiliacion.m,
        socio->fAfiliacion.a,
        socio->categoria,
        socio->fechaUltCuota.d,
        socio->fechaUltCuota.m,
        socio->fechaUltCuota.a,
        socio->estado,
        socio->plan,
        socio->emailTutor);

    return 0;
}
