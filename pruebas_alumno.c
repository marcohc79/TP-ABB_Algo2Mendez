#include "pa2m.h"
#include "src/abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparador_letras(void *_char1, void *_char2)
{
	char *char1 = _char1;
	char *char2 = _char2;
	return (*char1) - (*char2);
}

int comparador_discos(void *_anio1, void *_anio2)
{
	int *anio1 = _anio1;
	int *anio2 = _anio2;
	return (*anio1) - (*anio2);
}

struct disco {
	int lanzmiento;
	char nombre[80];
};
typedef struct disco disco_t;

disco_t *crear_disco(int anio, char *name)
{
	disco_t *disco = calloc(1, sizeof(disco_t));
	if (!disco)
		return NULL;
	disco->lanzmiento = anio;
	strcpy(disco->nombre, name);
	return disco;
}

void free_discos(void *disco)
{
	free(disco);
}

void destructor_discos(void *_disco)
{
	disco_t *disco = _disco;
	if (disco)
		free_discos(disco);
}

bool mostrar_elemento(void *elemento, void *extra)
{
	extra = extra;
	if (elemento)
		printf("%d ", ((disco_t *)elemento)->lanzmiento);
	return true;
}

void pruebas_crear_arbol_vacio()
{
	abb_t *arbol;
	pa2m_afirmar((arbol = abb_crear(NULL)) == NULL, "Comparador nulo.");
	pa2m_afirmar(abb_vacio(arbol) == true, "Arbol nulo esta vacio.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "Arbol nulo tiene tamanio 0.");
	pa2m_afirmar((arbol = abb_crear(comparador_letras)) != NULL,
		     "Se crea un arbol con comparador.");
	pa2m_afirmar(abb_vacio(arbol) == true, "Arbol creado esta vacio.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "Arbol creado tiene tamanio 0.");
	abb_destruir(arbol);
}

void pruebas_insertar_en_arbol()
{
	abb_t *arbol = abb_crear(comparador_letras);
	char letras[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	for (size_t i = 0; i < sizeof(letras); i++) {
		pa2m_afirmar(abb_insertar(arbol, &letras[i]) != NULL,
			     "Letra insertada.");
	}
	pa2m_afirmar(abb_vacio(arbol) == false, "Arbol no es vacio.");
	pa2m_afirmar(abb_tamanio(arbol) == 10,
		     "Tamanio correcto luego de insertar.");
	abb_destruir(arbol);
}

void pruebas_eliminar_elementos_arbol()
{
	abb_t *arbol = abb_crear(comparador_letras);
	char letras[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	char a = 'A';
	char b = 'B';
	char c = 'C';
	char d = 'D';
	char e = 'E';
	char f = 'F';
	char g = 'G';
	char h = 'H';
	char i = 'I';
	char j = 'J';
	char z = 'Z';

	for (size_t i = 0; i < sizeof(letras); i++) {
		abb_insertar(arbol, &letras[i]);
	}

	pa2m_afirmar(abb_tamanio(arbol) == 10,
		     "Tamanio correcto antes de eliminar.");
	pa2m_afirmar(abb_quitar(arbol, &z) == NULL,
		     "No se encuentra en el arbol.");

	pa2m_afirmar(abb_quitar(arbol, &a) == letras + 0,
		     "Se elimina raiz principal.");
	pa2m_afirmar(abb_tamanio(arbol) == 9,
		     "Tamanio correcto luego de eliminar.");

	pa2m_afirmar(abb_quitar(arbol, &e) == letras + 4,
		     "Se elimina raiz principal.");
	pa2m_afirmar(abb_tamanio(arbol) == 8,
		     "Tamanio correcto luego de eliminar.");

	pa2m_afirmar(abb_quitar(arbol, &b) == letras + 1,
		     "Se elimina raiz principal.");
	pa2m_afirmar(abb_tamanio(arbol) == 7,
		     "Tamanio correcto luego de eliminar.");

	pa2m_afirmar(abb_quitar(arbol, &i) == letras + 8,
		     "Se elimina raiz principal.");
	pa2m_afirmar(abb_tamanio(arbol) == 6,
		     "Tamanio correcto luego de eliminar.");

	pa2m_afirmar(abb_quitar(arbol, &d) == letras + 3,
		     "Se elimina raiz principal.");
	pa2m_afirmar(abb_tamanio(arbol) == 5,
		     "Tamanio correcto luego de eliminar.");

	pa2m_afirmar(abb_quitar(arbol, &h) == letras + 7,
		     "Se elimina raiz principal.");
	pa2m_afirmar(abb_tamanio(arbol) == 4,
		     "Tamanio correcto luego de eliminar.");

	pa2m_afirmar(abb_quitar(arbol, &f) == letras + 5,
		     "Se elimina raiz principal.");
	pa2m_afirmar(abb_tamanio(arbol) == 3,
		     "Tamanio correcto luego de eliminar.");

	pa2m_afirmar(abb_quitar(arbol, &c) == letras + 2,
		     "Se elimina raiz principal.");
	pa2m_afirmar(abb_tamanio(arbol) == 2,
		     "Tamanio correcto luego de eliminar.");

	pa2m_afirmar(abb_quitar(arbol, &j) == letras + 9,
		     "Se elimina raiz principal.");
	pa2m_afirmar(abb_tamanio(arbol) == 1,
		     "Tamanio correcto luego de eliminar.");

	pa2m_afirmar(abb_quitar(arbol, &g) == letras + 6,
		     "Se elimina raiz principal.");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "Tamanio correcto luego de eliminar.");

	pa2m_afirmar(abb_quitar(arbol, &a) == NULL,
		     "No se puede quitar elementos en arbol nulo.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "Tamanio 0.");
	pa2m_afirmar(abb_vacio(arbol) == true, "Arbol vacio.");

	pa2m_afirmar(abb_quitar(abb_insertar(arbol, letras + 0), &a) ==
			     letras + 0,
		     "Se insertar y quira elemento.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "Tamanio 0.");

	abb_destruir(arbol);
}

void pruebas_busqueda_elementos_arbol()
{
	abb_t *arbol = abb_crear(comparador_letras);
	char letras[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	char e = 'E';
	char h = 'H';
	char i = 'I';
	char z = 'Z';

	for (size_t i = 0; i < sizeof(letras); i++) {
		abb_insertar(arbol, &letras[i]);
	}

	pa2m_afirmar(abb_buscar(arbol, &z) == NULL,
		     "No se encuentra el elemento.");
	pa2m_afirmar(abb_buscar(arbol, &h) == letras + 7,
		     "Elemento encontrado.");
	abb_quitar(arbol, &i);
	pa2m_afirmar(abb_buscar(arbol, &i) == NULL,
		     "No se encuentra el elemento eliminado.");
	pa2m_afirmar(abb_quitar(arbol, abb_buscar(arbol, &e)) == letras + 4,
		     "Se busca y elimina el elemento.");
	pa2m_afirmar(abb_tamanio(arbol) == 8, "Tamanio correcto.");

	abb_destruir(arbol);
}

void pruebas_recorrido_arbol()
{
	abb_t *arbol = abb_crear(comparador_discos);
	disco_t *disco1 = crear_disco(2006, "Light Grenades");
	disco_t *disco2 = crear_disco(1997, "S.C.I.E.N.C.E.");
	disco_t *disco3 = crear_disco(2004, "A Crow Left of the Murder...");
	disco_t *disco4 = crear_disco(2001, "Morning View");
	disco_t *disco5 = crear_disco(1995, "Fungus Amongus");
	disco_t *disco6 = crear_disco(2009, "Monuments and Melodies");
	disco_t *disco7 = crear_disco(2011, "If Not Now, When?");
	disco_t *disco8 = crear_disco(1999, "Make Yourself");

	abb_insertar(arbol, disco1);
	abb_insertar(arbol, disco2);
	abb_insertar(arbol, disco3);
	abb_insertar(arbol, disco4);
	abb_insertar(arbol, disco5);
	abb_insertar(arbol, disco6);
	abb_insertar(arbol, disco7);
	abb_insertar(arbol, disco8);

	disco_t *discos_preorden[8];
	disco_t *discos_inorden[8];
	disco_t *discos_postorden[8];

	int fechas_pre[8] = { 2006, 1997, 1995, 2004, 2001, 1999, 2009, 2011 };
	int fechas_ind[8] = { 1995, 1997, 1999, 2001, 2004, 2006, 2009, 2011 };
	int fechas_pos[8] = { 1995, 1999, 2001, 2004, 1997, 2011, 2009, 2006 };

	size_t cantidad_pre =
		abb_recorrer(arbol, PREORDEN, (void **)discos_preorden, 8);
	size_t cantidad_ind =
		abb_recorrer(arbol, INORDEN, (void **)discos_inorden, 8);
	size_t cantidad_pos =
		abb_recorrer(arbol, POSTORDEN, (void **)discos_postorden, 8);

	printf("Recorrido preorden.\n");
	for (size_t i = 0; i < cantidad_pre; i++) {
		pa2m_afirmar(discos_preorden[i]->lanzmiento == fechas_pre[i],
			     "Preorden OK");
	}
	printf("\n");

	printf("Recorrido inorden.\n");
	for (size_t i = 0; i < cantidad_ind; i++) {
		pa2m_afirmar(discos_inorden[i]->lanzmiento == fechas_ind[i],
			     "Preorden OK");
	}
	printf("\n");

	printf("Recorrido postorden.\n");
	for (size_t i = 0; i < cantidad_pos; i++) {
		pa2m_afirmar(discos_postorden[i]->lanzmiento == fechas_pos[i],
			     "Preorden OK");
	}

	abb_destruir_todo(arbol, destructor_discos);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== ABB ========================");
	pa2m_nuevo_grupo("CREAR ARBOL");
	pruebas_crear_arbol_vacio();

	pa2m_nuevo_grupo("INSERTAR EN EL ARBOL");
	pruebas_insertar_en_arbol();

	pa2m_nuevo_grupo("ELIMINAR ELEMENTOS DEL ARBOL");
	pruebas_eliminar_elementos_arbol();

	pa2m_nuevo_grupo("BUSCAR ELEMENTOS DEL ARBOL");
	pruebas_busqueda_elementos_arbol();

	pa2m_nuevo_grupo("RECORRIDOS DEL ARBOL");
	pruebas_recorrido_arbol();

	return pa2m_mostrar_reporte();
}
