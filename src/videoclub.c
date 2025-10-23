#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/Users/agustinabregant/topicos/include/videoclub.h"

#define MAXLINEA 1024
#define ANIOACTUAL 2025
#define MESACTUAL 9
#define DIAACTUAL 26
#define TODOOK 0
#define FECHAINVALIDA -1
#define ERROR -1

//FALTAN: opcion de recuperar archivo
int generarBinario(char * arch){
    int validarFechaProceso, validaciones;
    char linea[MAXLINEA], * mensajeValidaciones[10]; //nombreArch[50]; //no es claro si hay que guardar en el arch errores solo el primer error que salta, o todos los que saltan para ese registro. en caso der solo uno, solo guardaria un string, o [1]
    FILE * miembros_txt; //* errores_txt, * miembros_dat;//
    t_fecha fechaProceso;
    t_miembro socio; 

    //Ingreso de fecha de proceso
    printf("Bienvenido.\nIngrese fecha de procesamiento.");
    validarFechaProceso = ingresarFecha(&fechaProceso);   //ingresarFecha() ya incluye validarFecha
    if(validarFechaProceso == FECHAINVALIDA) //muy repetitivo, habria q optimizarlo
        return FECHAINVALIDA;

    //APERTURA DE ARCHIVOS

    //Archivo miembros txt
    miembros_txt = fopen(arch, "r");
    if(!miembros_txt){
        printf("\nError al abrir el archivo.");
        return ERROR;
    }
    else
        printf("\nArchivo leido correctamente.");
    
    /* 
    //Archivo errores txt
    sprintf(nombreArch, "error-VC-%d%d%d.txt", fechaProceso.a, fechaProceso.m, fechaProceso.d);
    errores_txt = fopen(nombreArch, "wT");
    if(!errores_txt){
        printf("\nError al crear el archivo.");
        return ERROR;
    }
    else
        printf("\nArchivo creado correctamente."); 
    
    //Archivo miembros binario
    sprintf(nombreArch, "miembros-VC-%d%d%d.dat", fechaProceso.a, fechaProceso.m, fechaProceso.d);
    miembros_dat = fopen(nombreArch, "wb");    
    if(!miembros_dat){
        printf("\nError al crear el archivo.");
        return ERROR;
    }
    else
        printf("\nArchivo creado correctamente."); 
    */

    //LECTURA MIEMBROS TXT

    while(fgets(linea, sizeof(linea), miembros_txt)){    //mientras haya lineas, sigue leyendo
        leerRegistro(linea, &socio);   //convierte linea de txt a registro socio
        //valida campos
        validaciones = validacionesCampos(&socio, mensajeValidaciones);
        //if((validaciones = ERROR))
            //printf("\n %s", &(mensajeValidaciones[0])); //muestra el msj correspondiente a la 1era validacion que
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
    if(flagFecha == ERROR){
        printf("\nLa fecha es invalida.");
        return ERROR;
    }
    return TODOOK;
}

int cmpFecha(const t_fecha * f1, const t_fecha * f2){
    //devuelve 0 si las fechas son iguales, -1 si la primera fecha es menor, 1 si la primera fecha es mayor
    if (f1->a != f2->a)
        return (f1->a < f2->a) ? -1 : 1;    //chequea que el anio sea el actual o menor
    if (f1->m != f2->m)
        return (f1->m < f2->m) ? -1 : 1;    //chequea que el mes sea el actual o menor
    if (f1->d != f2->d)
        return (f1->d < f2->d) ? -1 : 1;    //chequea que el dia sea el actual o menor

    return 0;
}



int validarFecha(const t_fecha * fecha){
    int diasMeses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    //determina si es bisiesto y, en caso de serlo, febrero (segundo elemento del vector) tiene 29 dias
    if(esBisiesto(&(fecha->a)))
        diasMeses[1] = 29;  

    //valida anio (cual es el anio minimo permitido, 1000?)
    if ((fecha->a < 1000 || fecha->a > ANIOACTUAL))  
        return ERROR; 

    //valida mes
    if ((fecha->m < 1 || fecha->m >12 || fecha->m > MESACTUAL)) 
        return ERROR; 

    //valida dia ( (fecha->m)-1 para alinear el mes con el indice del vector )
    if(fecha->d < 1 || fecha->d > DIAACTUAL || fecha->d > diasMeses[(fecha->m)-1]) 
        return ERROR;   
    
        printf("\nFecha correcta");
    return TODOOK; 
}

bool esBisiesto(const int * anio){
    return (*anio % 4 == 0 && *anio % 100 != 0) || (*anio % 400 == 0);
}


//FALTA: podrian agregarse validaciones por si algun valor no se lee bien (ej. fecha no numerica)
int leerRegistro(char *linea, t_miembro * socio)
{
    sscanf(linea, "\n%ld,%59[^,], %d/%d/%d, %c, %d/%d/%d, %9[^,], %d/%d/%d, %c, %9[^,], %29[^,]", 
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

    printf("\nDNI:%ld \nNombre: %s \nFnac: %d/%d/%d \nSexo:%c \nfAfiliciacion: %d/%d/%d \nCategoria: %s \nfUltCuota: %d/%d/%d \nEstado: %c \nPlan: %s \nEmailTutor:%s",
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

int cmpDNI(long * dni, const int limite){
    //devuelve 0 si dni y limite son iguales, -1 si dni es menor, 1 si dni es mayor
    if (*dni != limite)
        return (*dni < limite) ? -1 : 1;    
    return 0;
}

int cmpChar(char * charAComparar, char comparador){
    return(*charAComparar == comparador) ? TODOOK : ERROR;
}

int cmpString(char * stringAComparar, char * comparador){
    return(strcmp(stringAComparar, comparador));
}

int validarEmail(char * email, char * categoria){
    if(strcmp(categoria, "MENOR") == 0){
        if(email[0] == '\0'){   //chequea que el mail no este vacio (si el primer caracter es \0)
            return ERROR;
        }    
    }
    return TODOOK;
}

int validarCategoria(char * categoria, t_fecha * fnac){
    int edad = ANIOACTUAL - fnac->a;
    if (MESACTUAL < fnac->m || (MESACTUAL == fnac->m && DIAACTUAL < fnac->d))
        edad--;

    if (edad < 18)
        return (strcmp(categoria, "MENOR") == 0 ? TODOOK : ERROR);
    else
        return (strcmp(categoria, "ADULTO") == 0 ? TODOOK : ERROR);
}


int validacionesCampos(t_miembro * socio, char * mensajeValidaciones[]){
    printf("\nEntro a validaciones");
    int i=0;

    //Validacion DNI
    if(cmpDNI(&(socio->dni), 1000000) == -1 || cmpDNI(&(socio->dni), 100000000) == 1){
        printf("\nDNI Incorrecto");
        mensajeValidaciones[i] = "DNI invalido.";
        i++;
    }
    else
        printf("\nDNI Correcto");

    //Validacion Sexo
    if(cmpChar(&(socio->sexo), 'F') == ERROR && cmpChar(&(socio->sexo), 'M') == ERROR){
        printf("\nSexo Incorrecto");
        mensajeValidaciones[i] = "Sexo invalido.";
        i++;
    }
    else
        printf("\nSexo Correcto");
    
    //Validacion Plan
    if(cmpString(socio->plan, "BASIC") != TODOOK &&
        cmpString(socio->plan, "PREMIUM") != TODOOK &&
        cmpString(socio->plan, "VIP") != TODOOK &&
        cmpString(socio->plan, "FAMILY") != TODOOK)
        {
            printf("\nPlan Incorrecto");
            mensajeValidaciones[i] = "Plan invalido.";
            i++;
        }
    else
        printf("\nPlan Correcto");
    

    //Validacion Email
    if(validarEmail(socio->emailTutor, socio->categoria) == ERROR){
        printf("\nNo existe tutor para el menor");
        mensajeValidaciones[i] = "Menor sin tutor.";
        i++;
    }
    else
        printf("\nEmail correcto");


    //Validacion Categoria
    if(validarCategoria(socio->categoria, &socio->fNac) == ERROR){
        printf("\nLa categoria es incorrecta");
        mensajeValidaciones[i] = "La categoria es incorrecta";
        i++;
    }
    else
        printf("\nCategoria correcta");



    return TODOOK;
}

