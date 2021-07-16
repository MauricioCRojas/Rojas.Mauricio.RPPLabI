#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "informes.h"
#include "juegos.h"
#include "cliente.h"
#include "alquiler.h"
#include "validaciones.h"



//1
int mostrarJuegosMesa (eJuego juegos[], int tam, eCategoria categoria[], int tamcat)
{
    int todoOk=0;
    if (juegos!=NULL && tam>0 && categoria!=NULL && tamcat>0)
    {
        int contJuegosMesa=0;
        for(int i=0; i<tam; i++)
        {
            if (categoria[0].id==juegos[i].idCategoria)
            {
                contJuegosMesa++;
                printf("%10s\n", juegos[i].descripcion);
                todoOk=1;
            }
        }
        printf("La cantidad de juegos de mesa es: %d\n", contJuegosMesa);
    }
    return todoOk;
}



//2
int mostrarAlquileresXCliente (eCliente clientes[], int tamc, eAlquiler alquiler[],
                               int tama, eJuego juegos[], int tam, eLocalidad localidad[], int taml)
{
    int todoOk=0;
    if(clientes!=NULL && tamc>0 && alquiler!=NULL && tama>0 && juegos !=NULL && tam>0 && localidad !=NULL && taml>0)
    {
        int idCliente=0;
        int flag=0;
        int reintentos=0;

        printf("         Alquileres Clientes\n\n");

        mostrarClientes (clientes, tamc, localidad, taml);

        getNumero(&idCliente,"Ingrese ID cliente: ","Error.\n",0,1000,3);

        while(buscarCliente(clientes, tamc, idCliente)==-1)
        {
            getNumero(&idCliente,"ID incorrecto o sin clientes por el momento - Reingrese ID: ","Error.\n",0,1000,3);
            reintentos++;
            if(reintentos==3)
            {
                break;
            }
        }


        for (int i=0; i<tama; i++)
        {
            if(alquiler[i].codCliente==idCliente && alquiler[i].isEmpty==0)
            {
                char descripcion[20];
                char descripcion2[20];
                float precioJuego;

                cargarDescripcionCliente(alquiler[i].codCliente, clientes, tamc, descripcion);
                cargarDescripcionJuego(alquiler[i].codJuego, juegos, tam, descripcion2);
                cargarPrecioJuego(alquiler[i].codJuego, juegos, tam, &precioJuego);

                printf("    %d                %10s      %10s           %.2f      %d/%d/%d\n", alquiler[i].codAlq, descripcion,
                       descripcion2, precioJuego, alquiler[i].fechaAlquiler.dia, alquiler[i].fechaAlquiler.mes, alquiler[i].fechaAlquiler.anio);
                flag=1;
                todoOk=1;
            }

        }
        if(flag==0)
        {
            printf("El cliente de idCliente %d no registra alquiler\n", idCliente);
        }
    }
    return todoOk;
}


//3
int mostrarImportesXCliente (eCliente clientes[], int tamc, eAlquiler alquiler[],
                             int tama, eJuego juegos[], int tam, eLocalidad localidad[], int taml)
{
    int todoOk=0;
    if(clientes!=NULL && tamc>0 && alquiler!=NULL && tama>0 && juegos !=NULL && tam>0 && localidad !=NULL && taml>0)
    {
        float importeTotal=0;
        int idCliente;
        int flag=0;
        int reintentos=0;

        printf("         Importes Clientes\n\n");

        mostrarClientes (clientes, tamc, localidad, taml);
        printf("Ingrese idCliente: ");
        scanf("%d", &idCliente);

        while(buscarCliente(clientes, tamc, idCliente)==-1)
        {
            getNumero(&idCliente,"ID incorrecto o sin clientes por el momento - Reingrese ID: ","Error.\n",0,1000,3);
            reintentos++;
            if(reintentos==3)
            {
                break;
            }
        }

        for (int i=0; i<tama; i++)
        {
            if(alquiler[i].codCliente==idCliente && alquiler[i].isEmpty==0)
            {
                for(int j = 0; j < tam; j++)
                {
                    if(alquiler[i].codJuego == juegos[j].codigo)
                    {
                        importeTotal+= juegos[j].importe;
                        flag=1;
                        todoOk=1;
                    }
                }
            }
        }
        if(flag==0)
        {
            printf("El cliente de idCliente %d no registra alquiler\n", idCliente);
        }
        else
        {
            printf("El importe total del cliente ID %d es de %.2f\n",idCliente, importeTotal);
        }
    }
    return todoOk;
}






//4
int mostrarClienteSinAlquilar(eAlquiler alquileres[], int tamA, eCliente clientes[], int tamC, eLocalidad localidades[], int tamL)
{
    int todoOk = 0;
    int cantAlq[tamC];
    for(int i = 0; i < tamC; i ++)
    {
        cantAlq[i] = 0;
    }
    if(alquileres != NULL && tamA > 0 && clientes != NULL && tamC > 0)
    {

        for(int i = 0; i < tamC; i++)
        {
            for(int j = 0; j < tamA; j++)
            {
                if(alquileres[j].isEmpty == 0 && alquileres[j].codCliente == clientes[i].codigo && clientes[i].isEmpty == 0)
                {
                    cantAlq[i] += 1;
                }
            }
        }
        printf("Clientes que no alquilaron\n");
        printf("Codigo      Nombre       Apellido        Sexo   Telefono    Localidad \n");
        char descripcion[21];
        for(int i = 0; i < tamC; i ++)
        {
            if( !(cantAlq[i] > 0) && clientes[i].isEmpty == 0)
            {
                cargarDescripcionLocalidad(clientes[i].idLocalidad, localidades, tamL, descripcion);
                printf(" %d    %10s    %10s          %c   %10d    %10s \n", clientes[i].codigo, clientes[i].nombre, clientes[i].apellido, clientes[i].sexo,clientes[i].telefono, descripcion);
                todoOk = 1;
            }
        }


    }
    return todoOk;

}



int mostrarJuegosSinAlquilar(eAlquiler alquileres[], int tamA,eJuego juegos[], int tam, eCategoria categorias[], int tamC)
{
    int todoOk = 0;
    int cantAlq[tam];
    char descripcion[21];
    for(int i = 0; i < tam; i ++)
    {
        cantAlq[i] = 0;
    }
    if(alquileres != NULL && tamA > 0 && juegos != NULL && tam > 0)
    {

        for(int i = 0; i < tam; i++)
        {
            for(int j = 0; j < tamA; j++)
            {
                if(alquileres[j].isEmpty == 0 && alquileres[j].codJuego == juegos[i].codigo)
                {
                    cantAlq[i] += 1;
                }
            }
        }
        printf("Juegos no alquilados\n");
        printf("Codigo    Descripcion             Importe      Categoria \n");

        for(int i = 0; i < tam; i ++)
        {
            if( !(cantAlq[i] > 0) )
            {
                cargarDescripcionCategoria(juegos[i].idCategoria,categorias,tamC,descripcion);
                printf(" %d      %10s               %.2f      %10s \n", juegos[i].codigo, juegos[i].descripcion,juegos[i].importe,descripcion);
                todoOk = 1;
            }
        }
        if(todoOk == 0)
        {
            printf("Se alquilaron todos los juegos\n");
        }

    }
    return todoOk;

}

int telefonosPorFecha(eAlquiler alquileres[], int tamA, eCliente clientes[], int tamC)
{
    int todoOk = 0;
    eFecha auxFecha;
    if(clientes != NULL && tamC > 0 && alquileres != NULL && tamA > 0)
    {
        printf("Mostrar telefonos de alquileres en fecha:\n");

        getNumero(&auxFecha.dia,"Ingrese dia de alquiler 1 a 31: ","Error.\n",1,31,3);
        getNumero(&auxFecha.mes,"Ingrese mes de alquiler 1 a 12: ","Error.\n",1,12,3);
        getNumero(&auxFecha.anio,"Ingrese anio de alquiler: ","Error.\n",2020,2021,3);


        printf("  Nombre  Apellido  Telefono   \n");
        for(int i = 0; i < tamA; i ++)
        {
            if( alquileres[i].isEmpty == 0 && (alquileres[i].fechaAlquiler.dia == auxFecha.dia &&
                                               alquileres[i].fechaAlquiler.mes == auxFecha.mes && alquileres[i].fechaAlquiler.anio == auxFecha.anio) )
            {
                for(int j = 0; j < tamC; j ++)
                {
                    if(alquileres[i].codCliente == clientes[j].codigo)
                    {
                        printf("%10s  %10s  %d   \n",clientes[j].nombre,clientes[j].apellido,clientes[j].telefono);
                        todoOk = 1;
                    }
                }
            }
        }
    }
    return todoOk;
}


int mostrarJuegosMujeres(eAlquiler alquileres[], int tamA, eCliente clientes[], int tamC, eJuego juegos[], int tamJ, eCategoria categorias[], int tamCAT)
{
    int todoOk = 0;
    char descripcion[21];
    if(alquileres != NULL && tamA > 0 && clientes != NULL && tamC > 0 && juegos != NULL  && tamJ > 0 && categorias != NULL && tamCAT > 0)
    {
        printf("Juegos alquilados por mujeres:\n");
        printf("Codigo    Descripcion          Importe  Categoria \n");

        for(int i = 0; i < tamC; i++)
        {
            if(clientes[i].isEmpty == 0 && clientes[i].sexo == 'f')
            {
                for(int j= 0; j < tamA; j++)
                {
                    if(alquileres[j].isEmpty == 0 && alquileres[j].codCliente == clientes[i].codigo)
                    {
                        for(int k = 0; k < tamJ; k++)
                        {
                            if(alquileres[j].codJuego == juegos[k].codigo)
                            {
                                cargarDescripcionCategoria(juegos[i].idCategoria,categorias,tamC,descripcion);
                                printf("%d      %10s             %.2f %10s \n", juegos[i].codigo, juegos[i].descripcion,juegos[i].importe,descripcion);
                                todoOk = 1;
                            }
                        }
                    }
                }
            }
        }
        if(todoOk == 0)
        {
            printf("No hay juegos alquilados por mujeres\n");
        }
    }
    return todoOk;

}


int juegoFavoritoHombres(eAlquiler alquileres[], int tamA,eCliente clientes[], int tamCl, eJuego juegos[],
                         int tamJ, eCategoria categorias[], int tamC)
{
    int todoOk = 0;
    int cantAlq[tamJ];

    char descripcion[21];
    for(int i = 0; i < tamJ; i ++)
    {
        cantAlq[i] = 0;
    }
    if(alquileres != NULL && tamA > 0 && juegos != NULL && tamJ > 0 && categorias != NULL && tamC > 0 && clientes != NULL && tamCl > 0)
    {

        for(int i = 0; i < tamCl; i++)
        {
            if(clientes[i].isEmpty == 0 && clientes[i].sexo == 'm')
            {
                for(int j = 0; j < tamA; j++)
                {
                    if(alquileres[j].isEmpty == 0 && alquileres[j].codCliente == clientes[i].codigo)
                    {
                        for(int k = 0; k < tamJ; k++)
                        {
                            if(alquileres[j].codJuego == juegos[k].codigo)
                            {
                                cantAlq[k] += 1;
                                todoOk = 1;
                            }
                        }
                    }
                }
            }
        }

        printf("Juegos favorito de los hombres\n");
        printf("Codigo      Descripcion       Importe    Categoria \n");

        int juegoPref = cantAlq[0];
        for(int i = 1; i < tamJ; i++)
        {
            if(cantAlq[i] > juegoPref)
            {
                juegoPref = cantAlq[i];
            }
        }

        for (int i = 0; i < tamJ; i++)
        {
            if (cantAlq[i] == juegoPref && todoOk > 0)
            {
                cargarDescripcionCategoria(juegos[i].idCategoria,categorias,tamC,descripcion);
                printf("%d       %10s           %.2f  %10s \n", juegos[i].codigo, juegos[i].descripcion,juegos[i].importe,descripcion);
                todoOk = 1;
            }
        }

        if(todoOk == 0)
        {
            printf("No hay alquiler de hombres\n");
        }

    }
    return todoOk;

}

int validarJuego(int id, eJuego juegos[], int tam)
{
    int retorno = 0;
    if(juegos != NULL && tam > 0)
    {
        for(int i = 0; i < tam ; i++)
        {
            if(juegos[i].codigo == id)
            {
                retorno = 1;
            }
        }
    }
    return retorno;
}


int mostrarClientesJuego(eAlquiler alquileres[], int tamA,eCliente clientes[], int tamC, eJuego juegos[], int tamJ,eCategoria categorias[], int tamCat, eLocalidad localidades[], int tamL)
{
    int codJuego;
    int todoOk = 0;

    if(alquileres != NULL && tamA > 0 && clientes != NULL && tamC > 0 && juegos != NULL  && tamJ > 0 && localidades != NULL && tamL > 0)
    {
        printf("Clientes que alquilaron cierto juego:\n");
        mostrarJuegos(juegos, tamJ,categorias,tamC);

        printf("Ingrese Codigo de Juego: ");
        scanf(" %d", &codJuego);
        while( !validarJuego(codJuego,juegos,tamJ) )
        {
            printf("Juego invalido. Reingrese codigo de juego: ");
            scanf(" %d", &codJuego);
        }
        printf("Codigo  Nombre      Apellido  Sexo  Telefono    Localidad\n");
        char descripLocal[21];
        for(int i = 0; i < tamA; i++)
        {
            if( alquileres[i].isEmpty == 0 && alquileres[i].codJuego == codJuego)
            {
                for(int j = 0; j < tamC; j++)
                {
                    if(clientes[j].isEmpty == 0 && alquileres[i].codCliente == clientes[j].codigo)
                    {
                        cargarDescripcionLocalidad(clientes[j].idLocalidad,localidades,tamL,descripLocal);
                        printf("%d   %10s  %10s   %c    %d  %10s \n", clientes[j].codigo, clientes[j].nombre, clientes[j].apellido,
                               clientes[j].sexo,clientes[j].telefono, descripLocal);
                        todoOk = 1;
                    }
                }
            }
        }
        if(todoOk == 0)
        {
            printf("Este juego no ha sido alquilado\n");
        }
    }
    return todoOk;
}

//10
int mostrarRecaudacionPorFecha(eCliente clientes[], eAlquiler alquiler[], eJuego juegos[],int tama,int tamc, int tam)
{
    int todoOk = 0;
    float auxImporte = 0;
    eFecha auxFecha;

    if(clientes!=NULL && tamc>0 && alquiler!=NULL && tama>0 && juegos !=NULL && tam>0)
    {

        getNumero(&auxFecha.dia,"Ingrese dia de alquiler 1 a 31: ","Error.\n",1,31,3);
        getNumero(&auxFecha.mes,"Ingrese mes de alquiler 1 a 12: ","Error.\n",1,12,3);
        getNumero(&auxFecha.anio,"Ingrese anio de alquiler: ","Error.\n",2020,2021,3);


        for(int i = 0; i< tama; i++)
        {
            if(alquiler[i].fechaAlquiler.dia == auxFecha.dia &&
                    alquiler[i].fechaAlquiler.mes == auxFecha.mes &&
                    alquiler[i].fechaAlquiler.anio == auxFecha.anio)
            {
                for(int j = 0; j<tam ; j++)
                {
                    if(juegos[j].codigo == alquiler[i].codJuego && alquiler[i].isEmpty == 0)
                    {
                        auxImporte += juegos[j].importe;
                        todoOk = 1;
                    }
                }
            }
        }

        printf("La recaudacion de la fecha %d/%d/%d fue de %.2f \n", auxFecha.dia, auxFecha.mes, auxFecha.anio, auxImporte);
    }

    return todoOk;
}


//Muestra clientes de Avellaneda
int mostrarClientesAvellaneda (eCliente clientes[], int tama, eLocalidad localidad[], int taml)
{
    int todoOk=0;
    if (clientes!=NULL && tama>0 && localidad!=NULL && taml>0)
    {
        int contClientLocald=0;
        for(int i=0; i<tama; i++)
        {
            todoOk=1;
            if(strcmp(clientes[i].localidad, "Avellaneda")==0)
            {
                contClientLocald++;
                printf("%10s\n", clientes[i].nombre);
            }
        }
        printf("La cantidad de clientes de Avellaneda es: %d\n", contClientLocald);
    }
    return todoOk;
}


int mostrarJuegosAlquiladosEnJunin(eCliente clientes[], int tama, eLocalidad localidad[], int taml, eJuego juegos[], int tam,
                                   eAlquiler alquiler[], int tamc)
{

    int todoOk=0;
    int contJug=0;

    if (clientes!=NULL && tama>0 && localidad!=NULL && taml>0 && tam>0 && juegos!=NULL)
    {
        for(int i=0; i<tamc; i++)
        {
            if(strcmp(clientes[i].localidad, "Junin")==0)

            {
                for(int j=0; j<tama; j++)
                {
                    if(alquiler[j].codCliente==clientes[i].codigo && !alquiler[j].isEmpty)
                    {
                        todoOk=1;
                        contJug++;
                    }
                }

            }
        }
        printf("La cantidad de juegos alquilados en Junin es de: %d\n", contJug);

    }
    return todoOk;
}


int mostrarTejosBanfield (eJuego juegos[], int tam, eCategoria categoria[], int tamcat, eCliente clientes[], int tamc, eAlquiler alquiler[], int tama)
{
    int todoOk=0;
    if (juegos!=NULL && tam>0 && categoria!=NULL && tamcat>0)
    {
        int contTejoBanf=0;
        for(int i=0; i<tama; i++)
        {

            for(int j=0; j<tamc; j++)
            {
                if(strcmp(clientes[j].localidad, "Banfield")==0 && alquiler[i].codJuego==14)
                {
                    contTejoBanf++;
                    todoOk=1;
                }

            }


        }
        printf("La cantidad de tejos alquilados en Banfield es: %d\n", contTejoBanf);
    }
    return todoOk;
}

int hombresAlquilaronAjedrez (eCliente clientes [], int tamc, eAlquiler alquiler[], int tama)
{

    int todoOk=0;
    if (clientes!=NULL && tamc>0 && alquiler!=NULL && tama>0)
    {
        int contHombresAjedrez=0;
        for(int i=0; i<tama; i++)
        {

            for(int j=0; j<tamc; j++)
            {
                if(clientes[j].sexo == 'm' && alquiler[i].codJuego==13)
                {
                    contHombresAjedrez++;
                    todoOk=1;
                }

            }


        }
        printf("La cantidad de hombres que alquilaron ajedrez es: %d\n", contHombresAjedrez);
    }
    return todoOk;
}


int clientesCuyoNombreEmpiezanConAYSonDePergamino(eCliente clientes[], int tamc)
{
    int todoOk=0;
    int contadorClientes = 0;
    if(clientes!=NULL && tamc>0)
    {

        for(int i =0 ; i<tamc; i++)
        {
            if((clientes[i].nombre[0] == 'a' || clientes[i].nombre[0] == 'A')&&strcmp(clientes[i].localidad, "Pergamino")==0)
            {
                contadorClientes++;
                todoOk=1;
            }
        }
    }
    printf("La cantidad de clientes cuyo nombre empieza con A y son de Pergamino es : %d.\n", contadorClientes);
    return todoOk;
}
