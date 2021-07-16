#include "juegos.h"
#include "cliente.h"

#ifndef DATAWAREHOUSE_H_INCLUDED
#define DATAWAREHOUSE_H_INCLUDED



#endif // DATAWAREHOUSE_H_INCLUDED

/** \brief Hardcodea los juegos
 * \param Estructura array juegos []
 * \param tam tama�o juegos
 * \param cantidad de hardcodeos
 * \return retorna total
 */
int hardcodearJuegos(eJuego juegos[], int tam, int cant);


/** \brief Hardcodea las categorias
 * \param Estructura array categorias []
 * \param tamcat tama�o categorias
 * \param cantidad de hardcodeos
 * \return retorna total
 */
int hardcodearCategorias(eCategoria categoria[], int tamcat, int cant);



/** \brief Hardcodea las localidades
 * \param Estructura array localidades []
 * \param tamcat tama�o localidades
 * \param cantidad de hardcodeos
 * \return retorna total
 */
int hardcodearLocalidades(eLocalidad localidad[], int taml, int cant);

