#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dataNode{ //dados da lista
	int id;
} DataNode;

typedef struct node{
	DataNode data;
	struct node* next;	
 } Node;

typedef struct list{
	int size;
	Node* head;	
} List;

//inicio das funções
bool isEmpty(List* list);

List* createList(){ // cria lista
	List* list = (List*) malloc(sizeof(List));
	list -> size = 0;
	list -> head = NULL;
	
	return list;
}

void push(List* list, DataNode data){ //insere dado na lista
	Node* node = (Node*) malloc(sizeof(Node));
	
	node->data = data;
	node->next = list -> head;
	list->head = node;
	list->size++;
}

void printList(List* list){ //imprime lista toda
	
	if(isEmpty(list)){
		printf("Lista vazia.\n");
		return;
	}
	
	printf("Cabeca: ");
	Node* pointer = list->head;
	while(pointer != NULL){
		printf("(%d) -> ", pointer->data.id);
		pointer = pointer->next;
	}
	printf("(NIL)");
	printf("\n");
}

void pop(List* list){ //remove elemento da cabeça da lista
	if(!isEmpty(list)){
		Node* pointer = list->head;
		printf("O numero %d removido com SUCESSO.\n", pointer->data);
		list->head = pointer->next;
		free(pointer);
		list->size--;
		return;
	}
	printf("Lista vazia.\n");
}

bool isEmpty(List* list){ //auxilia a função pop
	return (list->size == 0);
}

Node* atPos(List* list, int index){ //passaremos um indice e retorna o Nó referente ao indice, se o indice for invalido retorna ponteiro NULL
	if(index >= 0 && index < list->size){
		Node* node = list->head;
		
		for(int i = 0; i < index; i++){
			node = node->next;
		}
		return node;
	}
	
	printf("Indice invalido.");
	return NULL;
}

int indexOf(List* list, Node* node){ //oposto so atPos, retorna o indice de um nó
	if(node != NULL){
		Node* pointer = list->head;
		
		int index = 0;
		
		while(pointer != node && pointer != NULL){
			pointer = pointer->next;
			index++;
		}
		
		if(pointer != NULL){
			return index;
		}	
	}
	
	printf("Nó nao pertencente a lista.\n");
	return -1;
}

void erase(List* list, int index){//exclui o nó no indice que passamos, desde que esse indice exista
	if(index == 0){
		pop(list);
	}else{
		Node* current = atPos(list, index);
		
		if(current != NULL){
			Node* previous = atPos(list, index - 1);
			previous->next = current->next;
			
			free(current);
			list->size--;
		}
	}
}

void insert(List* list, DataNode data, int index){ //insere um nó no indice que queremos
	if(index == 0){
		push(list, data);
	}else{
		Node* current = atPos(list, index);
		if(current != NULL){
			Node* previous = atPos(list, index - 1);
			
			Node* newNode = (Node*) malloc(sizeof(Node));
			newNode->data = data;
			
			previous->next = newNode;
			newNode->next = current;
			list->size++;
		}	
		
	}
}

void xchgNodes(List* list, Node* nodeA, Node* nodeB){ //faz a troca entre 2 nós
	if(nodeA == nodeB){
		return;
	}
	
	int indexA = indexOf(list, nodeA);
	int indexB = indexOf(list, nodeB);
	
	if(indexA == -1 || indexB == -1){
		return;
	}
	
	if(indexA > indexB){
		nodeA = nodeB;
		nodeB = atPos(list, indexA);
		
		indexA = indexB;
		indexB = indexOf(list, nodeB);
	}
	
	Node* pb = atPos(list, indexB - 1);
	if(nodeA == list->head){
		list->head = nodeB;
	}else{
		Node* pa = atPos(list, indexA - 1);
		pa->next = nodeB;
	}
	
	pb->next = nodeA;
	Node* pointer = nodeA->next;
	nodeA->next = nodeB->next;
	nodeB->next = pointer;		
}

Node* min(List* list, int index){ //retorna o menor valor da lista a partir de um indice especifico
	Node* pointer = atPos(list, index);
	
	if(pointer != NULL){
		Node* minNode = pointer;
		
		while(pointer != NULL ){
			if(pointer->data.id < minNode->data.id){
				minNode = pointer;
			}
			pointer = pointer->next;
		}
		return minNode;
	}
	
	return NULL;
}

Node* max(List* list, int index){ //retorna o maior valor da lista a partir de um indice especifico
	Node* pointer = atPos(list, index);
	
	if(pointer != NULL){
		Node* maxNode = pointer;
		
		while(pointer != NULL ){
			if(pointer->data.id > maxNode->data.id){
				maxNode = pointer;
			}
			pointer = pointer->next;
		}
		return maxNode;
	}
	return NULL;
}

void incSort(List* list){ //ordenando em ordem crescente
	for(int i = 0; i < list->size - 1; i++){
		xchgNodes(list, atPos(list, i), min(list, i));
	}
}

void decSort(List* list){ //ordenando em ordem decrescente
	for(int i = 0; i < list->size - 1; i++){
		xchgNodes(list, atPos(list, i), max(list, i));
	}
}

//menu do programa
int showMenu(){
	int opcao;
    
    printf("*-------------------------------------------------- LISTA ENCADEADA ---------------------------------------------------*");
    printf("[1] Inserir dados na Lista.\n[2] Imprimir Lista.\n[3] Remover dados da Lista.\n[4] Ordenar a Lista(CRESCENTE).\n[5] Ordenar a Lista(DECRESCENTE).\n[0] Sair.\n");
    for(int i = 0; i < 120; i++) printf("-");
	printf("Opcao: ");
	scanf("%d", &opcao);

    return opcao;
}

//programa principal
int main(void){
	int opcao = 0;
	List* l = createList();
	DataNode data;
    
    opcao = showMenu();    
	system("cls");
    while(opcao != 0){
        switch(opcao){
            case 1 : {
                system("cls");
                int num = 0;
				printf("Qual numero deseja inserir?\nR: ");
                scanf("%d", &num);
				data.id = num;
				push(l, data);
                break;
            }
            case 2 : {
            	system("cls");
                printList(l);
                break;
            }
            case 3 : {
            	system("cls");
                pop(l);
                break;
            }
            case 4 : {
            	system("cls");
                incSort(l);
                break;
            }
            case 5 : {
            	system("cls");
                decSort(l);
                break;
            }
            default :{
            	system("cls");
				printf("Opcao invalida, tente novamente!\n");
				break;
			}
        }
        opcao = showMenu();
        system("cls");
    }
}

