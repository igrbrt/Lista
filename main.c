/* 
 * File:   main.c
 * Author: igor
 *
 * Created on 21 de Novembro de 2010, 17:30
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Pessoa{
    char nome[30];
    char endereco[50];
    char telefone[10];
}Pessoa;

typedef struct No{
    Pessoa conteudo;
    struct No *prox;
}No;

// prototipo das funcoes
void inserir(No**,Pessoa*);
char* apagar(No**);
void mostrar(No**);
void cadastrar(Pessoa**);
int verifica(No**);


int main() {
    No *Inicio = NULL;
    char* info=NULL;
    Pessoa *pessoa = NULL;
    int op;
    do{
        puts("\t\t == Lista Simplismente Encadeada ==\n\n");
        printf("(1) - Inserir\n(2) - Remover\n(3) - Imprimir\n(4) - Sair\n-->");
        scanf("%d",&op);
        __fpurge(stdin);
        switch(op){
            case 1:cadastrar(&pessoa);
                   inserir(&Inicio,pessoa);
                   break;
            case 2:if(verifica(&Inicio) == 0)
                        break;
                   mostrar(&Inicio);
                   info = apagar(&Inicio);
                   if(info==NULL)
                       break;
                   else
                       printf("\nRemovido: %s \n",info);
                   break;
            case 3:if(verifica(&Inicio) == 0)
                        break;
                   mostrar(&Inicio);printf("\n");
                   break;
            case 4:puts("\nFechando...");
                   break;
            default:puts("\nCalma, Usuario amigo!");
        }
        sleep(2);
        system("clear");
    }while(op!=4);
    return (0);
}


void inserir(No **inicio,Pessoa *nova){
    No *aux,*aux2;
    No* novo = (No*)malloc(sizeof(No));  // no a ser inserido na lista
    novo->conteudo = *nova;
    if(*inicio == NULL){    // aloca o primeiro elemento se a lista tiver vazia
        *inicio = (No*)malloc(sizeof(No));
        *inicio=novo;           // atribui o novo novo pro inicio da lista
    }
    else{
        if( strcmp(novo->conteudo.nome,(*inicio)->conteudo.nome) <0 ){ //insere antes do primeiro
            novo->prox=*inicio;
            *inicio=novo;
        }
        else{
            aux2=(*inicio)->prox;
            aux=(*inicio);
            while(aux->prox != NULL && strcmp(novo->conteudo.nome,aux2->conteudo.nome) >0 ){ //procura posicao a ser inserido na lista
                aux=aux->prox;
                aux2=aux2->prox;
            }
            aux->prox=novo;  // avanca para o proximo no
            novo->prox=aux2;
        }
    }
}

char* apagar(No **inicio){
    No* aux = *inicio;
    No* aux2 = *inicio;
    char info[30];
    char retorno[30];  // nome a ser retornado
    printf("\nPessoa a ser removido:");
    __fpurge(stdin);
    fgets(info,30,stdin);
    if(strcmp(info,(*inicio)->conteudo.nome) == 0){  //inicio da lista
        strcpy(retorno,((*inicio)->conteudo.nome)); // copia conteudo a ser removido
        *inicio = aux->prox;  // atualiza inicio
        free(aux);
        return retorno;
    }
    else{
        aux = (*inicio)->prox;
        while(aux != NULL){
            if(aux->prox == NULL && strcmp(aux->conteudo.nome,info) == 0){  // final da lista
                strcpy(retorno,aux->conteudo.nome);     // copia conteudo a ser removido
                aux2->prox = NULL;
                free(aux);
                return retorno;
            }
            if(strcmp(info,aux->conteudo.nome) == 0){  //meio da lista
                strcpy(retorno,aux->conteudo.nome);     // copia conteudo a ser removido
                aux2->prox = aux->prox;
                free(aux);
                return retorno;
            }
            aux2 = aux;  // se nao encontrou ainda o elemento avanca pro proximo no
            aux = aux->prox;
        }
    }
    printf("\nElemento Nao Existe!\n");
    return NULL;
}

void mostrar(No **aux){  // imprime toda a lista
    printf("Nome: %sTelefone: %s\nEndereco: %s\n",(*aux)->conteudo.nome,(*aux)->conteudo.telefone,(*aux)->conteudo.endereco);
    printf("---------------------------------------------------\n");
    if((*aux)->prox != NULL)
        mostrar(&(*aux)->prox);
}

void cadastrar(Pessoa **Nova){  // cadastra pessoa a ser inserida
    if ( *Nova == NULL)         //quando ainda nao foi inserido ninguem
        (*Nova) = (Pessoa*)malloc(sizeof(Pessoa)); // ele aloca uma pessoa para receber os dados
    printf("\nNome: ");
    fgets((*Nova)->nome,30,stdin);  __fpurge(stdin);
    printf("\nTelefone [ex: 6384515637]: ");
    fgets((*Nova)->telefone,10,stdin); __fpurge(stdin);
    printf("\nEndereco: ");
    fgets((*Nova)->endereco,50,stdin); __fpurge(stdin);
    puts("\nCadastrado!");
}

int verifica(No **inicio){  // verifica se lista esta vazia
    if((*inicio) == NULL){
        puts("\nLista Vazia !");
        return 0;
    }
    return 1;
}