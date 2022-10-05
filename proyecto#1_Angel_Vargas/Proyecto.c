/*
 * Nombre: Angel Gabriel Vargas Varela
 * Carnet: 2021080292
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Hash_Table.c"

/*
 * struct city: Un struct formado por tres elementos, uno tipo char* ciudad, un int interest y un product** product_table.
 */
typedef struct city {
	char* ciudad;
	int interest;
	product** product_table; 
} city;

/*
 * E: Se ingresa el valor de una ciudad de tipo product
 * S: Los valores para las tablas de cada uno de los productos de una ciudad.
 */
void city_values(product** valor){
	srand(rand()*time(NULL)*(rand()%rand()+rand()));
	for(int i=0; i<=3; i++){
		char* pn = material[rand()%7];
		product* produc = valor[hash(pn,31)];
		produc->price=(rand()%151) + 50;
		produc->status=rand()%2;
		produc->amount=(rand()%13) +3;
        
	}
}

/*
 * E: Recibe un parametro n de tipo char* que corresponde el nombre de la ciudad.
 * S: Inicializador del struct city, inicializa una variable tipo city y le asigna valores al azar a todas sus variables internas.
 */
city* ciudades(char* n) {
	city* c= calloc(1,sizeof(city));
	product** ht = hash_table(31);
	generate_product_table(ht, material);
	c->product_table = ht;
	city_values(c->product_table);
	c->ciudad = n;
	c->interest = (rand()%81)+20;
	return c;
}

/*
 * E: Un struct "city list node", que está formado por dos elementos, un struct city*, y un cln* sigt como en todo 
 * nodo de una lista.
 */
typedef struct city_node{
	city* country;
	struct city_node* sig;
}cln;
struct city_node* inic = NULL;

/*
 * E: Se genera un struct nodo de tipo cl
 * S: se ingresa un objeto de tipo cln con el nombre inicio, el cual marcara el inicio de la lista de las ciudades
 */
typedef struct cl{
	cln* inicio;
}cl;

/*
 * E: Se ingresa la ciudad
 * S: Se retorna la nueva ciudad
 */
cln* iniciar_cln(city* ct){
	cln* nn = calloc(1,sizeof(cln));
	nn->country = ct;
	return nn;
}

/*
 * E: Se inicializa un espacio de memoria
 * S:
 */


int insert_cl(cl* l,city* ct){
	if(l == NULL){
		printf("La lista no existe \n");
		return -1;
	}
	cln* nn = iniciar_cln(ct);
	if(l->inicio == NULL) {
		l->inicio = nn;
	}
	else{
		struct city_node* act = l->inicio;
		while (act->sig != NULL) {
		act = act->sig;
		}
		act->sig = nn;
	}
	return 0;
}

/*
 * E: Una ciudad de tipo city
 * S: Revisa el nivel de interes de la ciudad y de sus valores dentro de la tabla
 */
void check_city(city* ct){
	if(ct->interest <= 30 && ct->product_table != NULL){
		delete_product_table(ct->product_table);
		ct->product_table = NULL;
	}
	if(ct->interest > 30 && ct->product_table == NULL){
		product** ht = hash_table(31);
		generate_product_table(ht, material);
		city_values(ht);
		ct->product_table = ht;
	}
}

/*
 * E: La cantidad de ciudades con las que se va a jugar
 * S: La lista de las ciudad de manera al azar
 */
cl* generate_cities(int cantidad){
	if(cantidad > 10){
		cantidad = 10;
	}
	cl* lista_ciudades = init_cl();
	srand(rand()*time(NULL)*(rand()%rand()+rand()));
	char* ciudad_names[] = {"Alajuela", "Paris", "Londres", "Bogota", "Londres", "Roma", "Managua", "Moscu", "California", "Sydney"};
	for(int i=0;i<cantidad; i++){
		int var = rand()%10;
		char* name = ciudad_names[var];
		char* clearer = "x";
		if(name != clearer){
			city* c=ciudades(name);
			insert_cl(lista_ciudades, c);
			ciudad_names[var]="x";
		}
	}
	return lista_ciudades;
}


/*
 * E: Una ciudad de tipo city
 * S: Imprime la ciudad y su nivel de interes, además de que presenta de manera grafica si se puede comercializar o no
 */
int print_city(city* ciudad_comercio){
	printf("\n");
	printf("Ciudad: %s\n", ciudad_comercio->ciudad);
	printf("Interes: %d\n", ciudad_comercio->interest);
	if(ciudad_comercio->interest > 30){
		product** pt = ciudad_comercio->product_table;
		print_product_table(pt);
	}
	else {
		printf("No se puede comerciar, el nivel de interes no es el suficiente\n");
	}
	printf("\n");
	printf("\n");
	printf("\n");
	return 0;
}

int print_cl(cl* l){
	cln* act = l->inicio;
	while (act->sig!= NULL) {
		print_city(act->country);
		act = act->sig;
	}
	print_city(act->country);
	return 0;
}

typedef struct player{
	int points;
	product** inventory;
} player;


/*
 * E: Se agregan los recursos del jugador
 * S: se generan aleatoriamente el precio y la cantidad de los recursos
 */
void set_player_values(product** it){
	srand(rand()*time(NULL)*(rand()%rand()+rand()));
	for(int i=0; i<7; i++){
		char* pn = material[i];
		product* p = it[hash(pn,31)];
		p->price=(rand()%51) + 50;
		p->amount=(rand()%21) +10;
	}
}

/*
 * E: Se inician los valores y puntos del jugador
 * S: Se retornan los valores del inventario del jugador dentro de la tabla Hash
 */
player* iniciar_jugador(){
	player* py = calloc(1,sizeof(player));
	py->points = 2800;
	product** ht = hash_table(31);
	generate_product_table(ht, material);
	py->inventory=ht;
	set_player_values(py->inventory);
	return py;
}


/*
 * E: Se ingresa la cantidad de puntos que tendra el jugador
 * S: Se imprimen los puntos del jugador y su inventario
 */
void print_player(player* py){
    /*printf("%s : %i \n", jugadorRecursos1, recursosJugador1);
    printf("%s : %i \n", jugadorRecursos2, recursosJugador2);
    printf("%s : %i \n", jugadorRecursos3, recursosJugador3);*/
    printf("\n");
	printf("Recursos de jugador \n");
	printf("Cantidad de puntos: %d \n", py->points);
	print_inventory(py->inventory);
}

/*
 * E: Se ingresa la cantidad de recursos a comprar
 * S: Se actualizan los recursos del jugador
 */
int comprar(int cantidad, product* p, player* py){
	char* pn = p->key_name;
	int pr = p->price;
	int dinero = cantidad*pr;
	product* ip = py->inventory[hash(pn,31)];
	
	if (py->points < dinero){printf("El dinero es insuficiente para realizar la compra \n\n"); return 0;}
	 
	if (p->amount < cantidad){printf("La ciudad no posee esa cantidad de recursos \n\n"); return 0;}
	
	p->amount -= cantidad;
	ip->amount += cantidad;
	py->points -= dinero;
	return 1;
}

/*
 * E: Se agregan los recursos del jugador
 * S: Se actualizan los recursos del jugador
 */
 
int vender(int cantidad, product* p, player* py){
	char* pn = p->key_name;
	int pr = p->price;
	int dinero = cantidad*pr;
	product* ip = py->inventory[hash(pn,31)];
	
	if (ip->amount < cantidad){printf("No tienes los recursos suficientes para comerciar \n\n"); return 0;}
	
	p->amount += cantidad;
	ip->amount -= cantidad;
	py->points += dinero;
	return 1;
}

/*
 * E: Se ingresa la ciudad y los recursos del jugador
 * S: Se actualizan los recursos del jugador
 */
int comerciar(city* ct, player* py){
	if(ct->interest > 30){
		int ts = 0;
		char* entry="a";
		int key = hash(entry,31);
		while(ct->product_table[key] == NULL || ct->product_table[key]->price == 0){
		printf("Dijite un producto valido con el que desea comerciar: ");
		char nombre_ciudad[200];
		scanf("%s", nombre_ciudad);
		printf("\n");
		key = hash(nombre_ciudad, 31);
		//printf("Producto seleccionado: %d \n",key);
		}
		if(ct->product_table[key]->status == 0){
			printf("¿Cuantos recursos desea comprar? ");
			int cantidad;
			scanf("%d", &cantidad);
			printf("\n");
			ts = comprar(cantidad, ct->product_table[key], py);
			
		}
		if(ct->product_table[key]->status != 0){
			printf("¿Cuantos recursos desea vender? ");
			int cantidad;
			scanf("%d", &cantidad);
			printf("\n");
			ts = vender(cantidad, ct->product_table[key], py); 
		}
		return ts;
	}
	else{
		srand(rand()*time(NULL)*(rand()%rand()+rand()));
		ct->interest += rand()%11+15;
		return 1;
	}
}

/*
 * E: Se ingresa el turno
 * S: Se cambia de turno y se cambia el valor de interes de las ciudades
 */

void cambiar_ronda(cl* l){
	srand(rand()*time(NULL)*(rand()%rand()+rand()));
	int decay = rand()%5 +1;
	cln* act = l->inicio;
	while (act->sig!= NULL) {
		act->country->interest = act->country->interest - decay;
		if((act->country->interest)<0){
			act->country->interest = 0;
		}
		check_city(act->country);
		act = act->sig;
	}
		act->country->interest = act->country->interest - decay;
		if((act->country->interest)<0){
			act->country->interest = 0;
		}
		check_city(act->country);
		act = act->sig;
}

/*
 * E: Se ingresa un numero que indica la ciudad a elegir
 * S: Se retorna la ciudad con los valores actualizados
 */
city* select_city(cl* cities){
	cln* act = cities->inicio;
	city* ct= act->country;
	int lenght = 0;
	while (act->sig!= NULL) {
		lenght++;
		act = act->sig;
		}
		lenght++;
	int i = 1;
    printf("#--------------------------------------------------------------------------# \n");
	printf("Seleccione el numero de la ciudad con la que desea intercambiar recursos: \n");
    printf("#--------------------------------------------------------------------------# \n");
	int numero_ciudad;
	scanf("%d", &numero_ciudad);
	printf("\n");
	while(numero_ciudad>lenght) {
    printf("#--------------------------------------------------------------------------# \n");
	printf("Seleccione el numero de la ciudad con la que desea intercambiar recursos: \n");
    printf("#--------------------------------------------------------------------------# \n");
	scanf("%d", &numero_ciudad);
	printf("\n");	
	}
	act = cities->inicio;
	ct= act->country;
	while(i != numero_ciudad){
		act = act->sig;
		ct= act->country;
		i++;
	}
	return ct;
}

/*
 * E: Se ingresan los puntos del jugador
 * S: Se imprime si el jugador gano o perdio
 */
char* winner(int puntos){
	if(puntos >= 30000){
		return "Ganaste!! Obtuvistes más de 30000 puntos \n";
	}
	return "Perdiste! No reunistes suficientes puntos para ganar \n";
}

/*
 * E: Se ingresa la ciudad y los recursos del jugador
 * S: Se imprimen los turnos y el resultado de la partida
 */
void client_resources(cl* cities, player* py){
	int  ronda = 1;
	while(ronda <= 30){
		printf("*---------//*Turno #%d*//---------* \n", ronda);
		print_cl(cities);
		print_player(py);
		city* ct = select_city(cities);
		int ts = comerciar(ct,py);
		while(ts!=1){
			ts = comerciar(ct,py);
		}
		if(ts == 1){
			ronda++;
			cambiar_ronda(cities);
		}		
	}
	printf("---------//*Resultados*//--------- \n");
	print_cl(cities);
	print_player(py);
	int finalscore = py->points;
	char* won = winner(finalscore);
	printf("%s", won);
}

/*
 * E: Se utilizan programas anteriores
 * S: Se imprime toda la interfaz del juego y sus respectivas mecanicas
 */
int main(){
	int cantidad;
	printf("Seleccione la cantidad de ciudades con las que desea jugar (minimo 3, maximo 10): ");
	scanf("%d", &cantidad);
    if(cantidad < 3 || cantidad > 10){
        printf("La cantidad de ciudades que ha ingresado es invalido");
    }else{
	printf("\n");
	printf("*----------/* Comercio Canamo */------------* \n");
	printf("\n");
    printf("*----------/* Instrucciones de juego */------------* \n");
    printf("- En este juego de comercio, se tienen varias ciudades con recursos de manera aleatoria \n");
    printf("- El jugador cuenta con recursos y puntos para poder comercializar \n");
    printf("- Para ganar este juego se debe obtener un total de 30000 puntos al final de la partida \n");
    printf("- Si una ciudad cuenta con un interes menor a 30, la ciudad no puede comercializar \n");
    printf("- Algunas ciudades cuentan con recursos que se pueden comprar o vender, por lo que el jugador debe decidir si vender o gastar puntos \n");
    printf("- Para elegir una ciudad a comerciar, se debe ingresar un numero, el cual corresponde al orden de posicion de las ciudades  \n");
    printf("- Al elegir una ciudad, se debe ingresar el nombre del recurso que se desea comerciar  \n");
    printf("- El juego cuenta con 30 turnos y si se llega al turno 30, el juego finaliza y decide si el jugador gano o perdio \n");
    printf("\n");
	cl* cities = generate_cities(cantidad);
	player* py = iniciar_jugador();
	client_resources(cities,py);
	
	return 0;
    }
}
