#include <stdio.h>
#include <stdlib.h>

typedef struct SCarro{
    int id; 
    int ano;
} Carro;

typedef struct SLists{
    Carro info;
    struct SLists *Next;
} List;

typedef struct SSent{
    List *First;
    int qtdElementos;
} Sent;

Carro createCar(int id, int ano){
    Carro car; 
    car.id = id; 
    car.ano = ano;
    return car;
}

void freeMemory(List *p){
    if(p==NULL) return; 
    freeMemory(p->Next);
    free(p);
}

void initList(Sent *s){
    s->First = NULL; 
    s->qtdElementos = 0; 
}

void insertInlist(Sent *s, Carro carro){
    List *ls;
    ls = (List *)malloc(sizeof(List));
    ls->info = carro;
    ls->Next = NULL; 
    
    if(s->First == NULL){
        s->First = ls;
        s->qtdElementos++;
        return;
    }
    List *aux = s->First;
    while(aux->Next != NULL){
        aux = aux->Next;
    }

    ls->Next = aux->Next;
    aux->Next = ls;
    s->qtdElementos++;
}

void ListList(Sent *s){
    if(s->First == NULL){
        printf("Lista Vazia. ");
        return;
    }
    for(List *aux = s->First; aux != NULL; aux = aux->Next){
        printf("--------Carro--------\nId: %d \nano: %d \n", aux->info.id, aux->info.ano);
    }
}

void deleteElementList(Sent *s, int id){
    List *aux, *auxPrev = NULL;

    if(s->First == NULL){
        printf("Lista Vazia!");
        return;
    }
    if(s->First->info.id == id){
        aux = s->First;
        s->First = aux->Next;
        free(aux);
        s->qtdElementos--;
        printf("Deletado com sucesso!");
        return;
    }

    for(aux = s->First; aux != NULL; aux = aux->Next){
    
        if(aux->info.id == id){
            auxPrev->Next = aux->Next;
            free(aux);
            s->qtdElementos--;
            printf("Deletado com sucesso!");
            return;
        }
        auxPrev = aux;
    }
    printf("Id não encontrado");
}

void updateCar(Sent *s, int id, int ano){
    List *aux = NULL;

    if(s->First == NULL){
        printf("Lista Vazia!");
        return;
    }

    if(s->First->info.id == id){
        s->First->info.ano = ano;
        printf("Atualizado com sucesso!");
        return;
    }

    for(aux = s->First; aux != NULL; aux = aux->Next){
    
        if(aux->info.id == id){
            aux->info.ano = ano;
            printf("Atualizado com sucesso!");
            return;
        }
    }
    printf("Id não encontrado");
}

void menu_car(){
    printf("--- Estacionamento Car house ---\n");
    printf(" 1 - cadastrar carro \n");
    printf(" 2 - Listar carros\n");
    printf(" 3 - Deletar carro\n");
    printf(" 4 - Atualizar carro\n");
    printf(" 5 - Sair\n");
}

int main(){
    
    Sent s;
    initList(&s);

    int valor_menu = 0; 
    do{
        menu_car();
        int id, ano;
        scanf("%d", &valor_menu);
        switch (valor_menu){
        case 1:
            printf("ID:");
            scanf("%d", &id);
            printf("Ano:");
            scanf("%d", &ano);
            createCar(id, ano);
            insertInlist(&s, createCar(id, ano));
            break;
        case 2:
            ListList(&s);
            break;
        case 3:
            printf("id do carro que quer deletar: "); 
            scanf("%d", &id);
            deleteElementList(&s, id);
            break;
        case 4: 
            printf("id do carro que quer atualizar: ");
            scanf("%d", &id);
            printf("novo ano: ");
            scanf("%d", &ano);
            updateCar(&s, id, ano);
            break;
        case 5:
            break;
        default:
            break;
        }

    }while(valor_menu != 5);


    freeMemory(s.First);
    return 0; 
}