#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product {
	char* key_name;
	int price;
	int status;
	int amount;
} product;

product* iniciar_productos(char* name) {
	product* produc = calloc(1,sizeof(product));
	produc -> key_name = name;
	produc -> price = 0;
	produc -> status = 0;
	produc -> amount = 0;
	return produc;
}


int hash(char* key_name, int htl){
	int lenght = strlen(key_name);
	int key = 0;
	for(int i=1; i < lenght; i++){
		int character_value = key_name[i]-'0';
		key += character_value;
	}
	key = (key/lenght)%htl;
	return key;
}

product** hash_table(int lenght) {
	product** ht= calloc(lenght,sizeof(product*));
	return ht;
}

char* material[] = {"Semillas" , "agua", "Canabis", "fertilizante", "zacate", "fibra", "proteina"};

void generate_product_table(product** ht, char* pnl[]){
	for(int i=0; i < 7; i++){
		char* pn = pnl[i];
		int key = hash(pn, 31);
		product* p = iniciar_productos(pn);
		ht[key] = p;
	}
	char* pn = pnl[6];
	int key = hash(pn, 31);
	product* p = iniciar_productos(pn);
	ht[key] = p;
}

void delete_product_table(product** ht){
 	for(int i=0; i < 7; i++){
		char* pn = material[i];
		int key = hash(pn, 31);
		//printf("key to delete: %d \n", key);
		free(ht[key]);
		ht[key] = NULL;
	}
	free(ht);
	ht= NULL;
}

void print_product_table(product** ht){
	for(int i=0; i < 7; i++){
		char* pn = material[i];
		int key = hash(pn,31);
		product* p = ht[key];
		if(p->price > 0){
			printf("*--------------------------------------------* \n");
			printf("Producto: %s \n", p -> key_name);
			printf("Precio: %d \n", p -> price);
			if(p -> status == 0){
			printf("Se vende este producto \n");
			}
			else{
			printf("Se puede comprar este producto \n");
			}
			printf("Cantidad disponible: %d \n", p -> amount);
			printf("*--------------------------------------------* \n");
		}
	}
}


void print_inventory(product** ht){
	printf("*--------------------------------------------*\n");
	for(int i=0; i < 7; i++){
		char* pn = material[i];
		int key = hash(pn,31);
		product* p = ht[key];
		if(p->price > 0){
			printf("Cantidad de %s: %d \n", p -> key_name, p->amount);
		}
	}
	printf("*--------------------------------------------*\n \n");
}

product** redimensionar_hash_table(product** ht, int nl){
	product** nht = hash_table(nl);
	for(int i=0; i<(sizeof(ht)/sizeof(product)); i++){
		if(ht[i] != NULL){
			product* val = ht[i];
			int key = hash(val->key_name, nl);
			nht[key] = val;
		}
	}
	if(ht[sizeof(ht)/sizeof(product)] != NULL){
			product* val = ht[sizeof(ht)/sizeof(product)];
			int key = hash(val->key_name, nl);
			nht[key] = val;
		}
	return nht;
}

/*int main(){
	product** ht = init_hash_table(31);
	generate_product_table(ht, pnl);
	print_product_table(ht);
	delete_product_table(ht);
	ht = init_hash_table(31);
	generate_product_table(ht, pnl);
	print_product_table(ht);
	return 0;
}*/
