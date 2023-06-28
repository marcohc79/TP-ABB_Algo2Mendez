# TDA ABB

## Repositorio de Marco Huamani - 95392 - mhcaballero79@gmail.com 

- Para compilar: <br>
Utilizaremos el archivo `makefile` ubicado en el directorio del proyecto y solo basta con ejecutar 
el siguente comando desde la terminal.:

```bash
make
```

---
##  Funcionamiento

Se implementá un Árbol Binario de Búsqueda (ABB) con sus operaciones básicas, las mismas serán detallas
en el raptado teórico:

+ Crear.
+ Destruir.
+ Insertar.
+ Buscar.
+ Eliminar.
+ ¿Está vacío?

Dichas operaciones fueron implementadas utilizando recursividad ya que el nivel de abstracción de un 
ABB nos lo permite. En otras palabras podemos pensar que cada nodo tiene un sub-árbol o un árbol que
contiene nodos y esos nodos contienen hijos nodos. A todo esto, utilizar recursividad pone en prueba
todos los conceptos vistos en clase.

---

## Respuestas a las preguntas teóricas

A continuación abordaremos los conceptos de **Árbol**, **Árbol Binario**, y **Árbol Binario de Búsqueda**.
Además, en el apartado de **Árbol Binario de Búsqueda (ABB)** explicaremos algunas funciones del archivo
*abb.c* para la implementación de *abb.h*.

### Árbol

Es una estructura de datos jerárquicos que consta de nodos interconectados por enlaces o ramas. Cada nodo
del árbol puede tener varios nodos secundarios, también conocidos como hijos, y solo puede tener un nodo 
primario, también conocido como padre, excepto la raíz del árbol, que no tiene padre. <br>
En un árbol, la raíz es el nodo superior y los nodos hojas son los nodos finales que no tienen hijos. Cada
nodo puede tener cero o más nodos hijos. Veamos la siguiente imagen. 
<br>

<div align="center">
    <img width="65%" src="img/Arbol.svg">
</div>

<br>

### Árbol Binario

Un árbol binario es una estructura de datos en la cual cada nodo puede tener uno o dos hijos. Los cuales 
podemos llamarlo hijo izquierdo e hijo derecho. Además cuenta con ciertas operaciones básicas para insertar,
remover, buscar datos. <br>
El gran problema que cuenta esta estructura es que no hay ninguna restricción sobre los valores que pueden 
ser almacenados en los nodos, y por lo tanto no hay garantía de que el árbol tenga una estructura ordenada
que permita realizar búsquedas eficientes.
<br>

<div align="center">
    <img width="50%" src="img/AB.svg">
</div>

<br>

### Árbol Binario de Búsqueda

Un árbol binario de búsqueda (ABB) es un tipo especial de árbol binario en el que cada nodo tiene un valor 
asociado y se cumple que:

+ El valor de cada nodo en el subárbol izquierdo es menor que el valor del nodo raíz.
+ El valor de cada nodo en el subárbol derecho es mayor que el valor del nodo raíz.

Debido a estas propiedades, los ABB son útiles al momento de realizar búsquedas y/o almacenar datos
de forma ordena. También al momento de recorrerlos se desprenden varias formas de hacerlo, pero de todas ellas 
destacan las siguientes:

+ Recorrido en **preorden**: el recorrido comienza por el nodo raíz, luego se visita el subárbol izquierdo y, 
finalmente, se visita el subárbol derecho. El orden de procesamiento en este recorrido es: raíz, izquierda,
derecha.
+ Recorrido en **inorden**: el recorrido comienza por el subárbol izquierdo, luego se visita el nodo raíz y, 
finalmente, se visita el subárbol derecho. El orden de procesamiento en este recorrido es: izquierda, raíz,
derecha. El recorrido en inorden de un árbol binario de búsqueda produce una secuencia ordenada de valores.
+ Recorrido en **postorden**: el recorrido comienza por el subárbol izquierdo, luego se visita el subárbol 
derecho y, finalmente, se visita la raíz. El orden de procesamiento en este recorrido es: izquierda, 
derecha, raíz.

<div align="center">
    <img width="50%" src="img/ABB.svg">
</div>

<br>

A continuación detallaremos las operaciones e implementación de **insertar** y **eliminar** un **nodo** en el TP. 
La lógica también puede ser utilizada para **buscar**.
<br>

#### Insertar

Tenemos el árbol y elemento que se quiere insertar. Para ello contamos previamente de una función *comparador*
y como su nombre lo dice, compara los elementos del árbol. Posterior a esto vemos crear la estructura *nodo*,
la cual cuenta con con *elemento* y dos apuntadores para *hijo derecha* e *hijo izquierda* respectivamente. <br>
Luego vemos si nuestra estructura está vacío y de ser así dicho *nodo* pasará a ser **raíz** del ABB. De no
ser así entonces comenzará a ir comparando nodo a nodo siguiendo las propiedades anteriormente descriptas hasta
encontrar un espacio disponible.

<div align="center">
    <img width="50%" src="img/abb_insertar.svg">
</div>

<br>

Tal cual se ve en la imagen, el número 20 se irá comparando primero con 12 y este al ser menor irá al subárbol
derecho y así sucesivamente hasta encontrar espacio disponible en el *hijo derecho* del numero **17**.

<br>

#### Eliminar

Ahora veamos como eliminar un nodo, para esto se recibe el ABB y el elemento a eliminar. No va ser necesario
crear un nodo ya que nos basta con encontrar el *elemento* para buscarlo nos apoyaremos en la **función de comparación**
que viene con la estructura del ABB. <br>
Tenemos 3 situaciones, cuando el nodo tiene 2, 1 o 0 hijos.

Comencemos con el caso que tenga 2 hijos el nodo a eliminar. 

<br>

<div align="center">
    <img width="50%" src="img/abb_eliminar.svg">
</div>

<br>

Siguiendo el ejemplo de la imagen, se quiere eliminar el número 15 y vemos que dicho nodo tiene 
dos hijos. 
En este caso debemos buscar el predecesor inorden (se crea una función para esto), esto es ir al subárbol
izquierdo, del nodo a eliminar, y luego buscar el elemento más a la derecha este subárbol. Esto se logra
cuando encontramos un nodo donde su **hijo derecho** a punta a NULL. Nos guardamos dicho valor y retornamos 
todo lo que apunta su **hijo izquierdo** previamente a esto se libera la memoria de este nodo. Finalmente
intercambiamos los valores, tal cual se puede ver en la imagen.

<br>

Vemos el caso que se tenga 1 o mas hijos. <br>

Al igual que anteriormente iremos comparando los valores respetando la función *comparador* provista por
la estructura. En este ejemplo vemos que el número a eliminar es menor a la raíz por ende nos movemos a la
izquierda de este, esto lo haremos repetidas veces hasta encontrar el valor deseado. <br>
Una vez encontrado, se retornará el hijo derecho o izquierdo de acuerdo a lo que corresponda. En nuestro 
ejemplo al tener **hijo izquierdo** esto será retornado, tal cual se puede ver en la siguiente imagen.

<div align="center">
    <img width="50%" src="img/abb_eliminar_op2.svg">
</div>

<br>

##### Complejidad de las operaciones.

A continuación se analiza la complejidad de operaciones en el peor de los casos.

| Operación  | Complejidad | Justificación |
|------------|-------------|---------------|
| Crear      | O(1) | Son acciones únicas que no se repiten. |
| Insertar*   | O(n) | En caso que el árbol se haya deformado hacia una lista, se deberá recorrer todos los elementos. |
| Borrar*     | O(n) | En caso que el árbol se haya deformado hacia una lista, se deberá recorrer todos los elementos.|
| Buscar*     | O(n) | En caso que el árbol se haya deformado hacia una lista, se deberá recorrer todos los elementos.|
| Vacío      | O(1) | Solo se fija si existe un atributo de la estructura. |
| Recorrido (Pre, In, Post) | O(n) | Recorrer todos los elementos del árbol. |
| Destruir   | O(n) | Recorre todos los elementos del árbol. |

*En el cuadro colocamos la peor complejidad, pero en el caso donde el ABB se mantenga equilibrado
dichas operaciones pasan a ser **O(log n)** ya que en cada iteración vamos descartando una **"mitad"**.
