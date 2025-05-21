#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

// === ESTRUTURAS ===
typedef struct {
    int dia; 
    int mes; 
    int ano;
} Data;

typedef struct {
    char nome[100];
    int idade;
    char RG[15];
    Data *data;
} RegistroPa;

typedef struct CelulaLista {
    RegistroPa *paciente;
    struct CelulaLista *proximo;
} CelulaLista;

typedef struct CelulaFila {
    RegistroPa *paciente;
    struct CelulaFila *proximo;
} CelulaFila;

typedef struct {
    CelulaLista *primeiro;
    int qtde;
} ListaPacientes;

typedef struct {
	CelulaFila *head;
	CelulaFila *tail;
	int qtde;
} FilaAtendimento;

typedef struct {
    RegistroPa* pacientes[MAX];
    int qtde;
} HeapPrioridade;

int filho_esq(int pai);
int filho_dir(int pai);
int pai(int filho);
void peneirar(HeapPrioridade* h, int pai);
void construir(HeapPrioridade* h);
CelulaLista *criar_celulaLista(RegistroPa *paciente);
CelulaFila *criar_celulaFila(RegistroPa *paciente);
ListaPacientes *criar_lista();
FilaAtendimento *cria_fila();
void Cadastro(ListaPacientes *listaPa);
void Atendimento(ListaPacientes *listaPa, FilaAtendimento *filaPa);
void Prioritario(ListaPacientes *listaPa, HeapPrioridade *h);
int comparar_pacientes(const void *a, const void *b);
void Pesquisa(ListaPacientes *listaPa);
void Desfazer();
void Carregar(ListaPacientes *listaPa, const char *nome_arquivo);
void Salvar(ListaPacientes *listaPa);
void Sobre();