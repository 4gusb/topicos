#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef VIDEOCLUB_H   
#define VIDEOCLUB_H 

//ESTRUCTURAS

typedef struct {
    int d, m, a;   // dia, mes, año
} t_fecha;

typedef struct {
    long dni;              // DNI  
    char nombre[60];       // Apellido y Nombres
    t_fecha fNac;          // Fecha de Nacimiento
    char sexo;             // 'F' o 'M'
    t_fecha fAfiliacion;   // Fecha de afiliacion
    char categoria[10];    // "MENOR" o "ADULTO"
    t_fecha fechaUltCuota; // Fecha de última cuota paga
    char estado;           // 'A' (Alta) o 'B' (Baja)
    char plan[10];         // BASIC, PREMIUM, VIP, FAMILY
    char emailTutor[30];   // obligatorio si es menor
} t_miembro;


//FUNCIONES

int generarBinario(char * arch);   // solo declaración
int ingresarFecha(t_fecha * fecha);
int validarFecha(const t_fecha * fecha);
bool esBisiesto(const int * anio);
int leerRegistro(char * linea, t_miembro * socio);

#endif
