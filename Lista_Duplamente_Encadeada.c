#include <stdio.h>
#include <stdlib.h>

typedef struct SVaga{
    int id; 
    float comprimento; 
} Vaga; 

typedef struct SList{
    Vaga info; 
    struct SList *next;
    struct SList *prev;
} List;

typedef struct SSent{
    List *head; 
    List *tail; 
    int qtdElementos; 
}Sent;

Vaga create_vaga(int id, float comprimento){
    Vaga vaga; 
    vaga.id = id; 
    vaga.comprimento = comprimento;
    return vaga;
}

void initList(Sent *s){
    s->head = NULL; 
    s->tail = NULL; 
    s->qtdElementos = 0; 
}

void freeMemory(List *p){
    if(p->next == NULL) return; 
    freeMemory(p->next);
    free(p); 
}

void insertInList(Sent *s, Vaga vaga){
    List *ls; 
    ls = (List*)malloc(sizeof(List));
    ls->next = NULL; 
    ls->prev = NULL;
    ls->info = vaga; 

    if(s->head == NULL){
        s->head = ls;
        s->tail = ls;
        return;
    }

    List *aux; 
    aux = s->tail;

    aux->next = ls; 
    ls->prev = aux;
    s->tail = ls;
}

void listInListOrdemHead(Sent *s){
    for(List *aux = s->head; aux != NULL; aux = aux->next){
        printf("---------------------\n");
        printf("| id: %d            |\n", aux->info.id);
        printf("| Comprimento: %2.f  |\n", aux->info.comprimento);
        printf("--------------------\n");
    }
}

void listInListOrdemTail(Sent *s){
    for(List *aux = s->tail; aux != NULL; aux = aux->prev){
        printf("---------------------\n");
        printf("| id: %d            |\n", aux->info.id);
        printf("| Comprimento: %2.f  |\n", aux->info.comprimento);
        printf("--------------------\n");
    }
}

void menu_lista_dupla(){
    printf("-------   Menu  ------\n");
    printf("| 1 - Cadastrar vaga  |\n");
    printf("| 2 - Listar certo    |\n");
    printf("| 3 - Listar Inverso  |\n");
    printf("| 4 - Sair            |\n");
    printf("-----------------------\n");
}


int main(){
    int valor_menu = 0;
    int id; 
    float comprimento; 
    Sent s;
    initList(&s);
    do{
        menu_lista_dupla();
        scanf("%d", &valor_menu);
        switch (valor_menu){

        case 1:
            printf("Id: ");
            scanf("%d", &id);
            printf("Comprimento: ");
            scanf("%f", &comprimento);
            insertInList(&s, create_vaga(id, comprimento));
            break;
        case 2:
            listInListOrdemHead(&s);
            break;
        case 3: 
            listInListOrdemTail(&s);
            break;
        default:
            break;
        }

    }while(valor_menu != 4);

    freeMemory(s.head);

    return 0; 
}