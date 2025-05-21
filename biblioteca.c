#include "biblioteca.h"

// === FUNCOES DE HEAP ===
int filho_esq(int pai) { return 2 * pai + 1; }
int filho_dir(int pai) { return 2 * pai + 2; }
int pai(int filho) { return (filho - 1) / 2; }

void peneirar(HeapPrioridade* h, int pai) {
    int maior = pai;
    int esq = filho_esq(pai);
    int dir = filho_dir(pai);

    if (esq < h->qtde && h->pacientes[esq]->idade > h->pacientes[maior]->idade)
        maior = esq;
    if (dir < h->qtde && h->pacientes[dir]->idade > h->pacientes[maior]->idade)
        maior = dir;

    if (maior != pai) {
        RegistroPa* temp = h->pacientes[pai];
        h->pacientes[pai] = h->pacientes[maior];
        h->pacientes[maior] = temp;
        peneirar(h, maior);
    }
}

void construir(HeapPrioridade* h) {
    for (int i = h->qtde / 2 - 1; i >= 0; i--) {
        peneirar(h, i);
    }
}

// === FUNCOES DE LISTA E FILA ===
CelulaLista *criar_celulaLista(RegistroPa *paciente){
    CelulaLista *nova = malloc(sizeof(CelulaLista));
    nova->proximo = NULL;
    nova->paciente = paciente;
    return nova;
}

CelulaFila *criar_celulaFila(RegistroPa *paciente){
    CelulaFila *nova = malloc(sizeof(CelulaFila));
    nova->proximo = NULL;
    nova->paciente = paciente;
    return nova;
}

ListaPacientes *criar_lista(){
    ListaPacientes *listaPa = malloc(sizeof(ListaPacientes));
    listaPa->primeiro = NULL;
    listaPa->qtde = 0;
    return listaPa;
}

FilaAtendimento *cria_fila(){
	FilaAtendimento *fila = malloc(sizeof(FilaAtendimento));
	fila->head = NULL;
	fila->tail = NULL;
	fila->qtde = 0;
	return fila;
}

void Cadastro(ListaPacientes *listaPa){
    int opcao;
     do {
        printf("\n==================================\n");
        printf("1. Cadastrar Paciente\n");
        printf("2. Consultar Paciente\n");
        printf("3. Lista completa\n");
        printf("4. Atualizar Paciente\n");
        printf("5. Remover Paciente\n");
        printf("0. Menu\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:{
                RegistroPa *paciente = malloc(sizeof(RegistroPa));
                paciente->data = malloc(sizeof(Data));
                printf("Cadastrar nome:  ");
                getchar();
                fgets(paciente->nome, sizeof(paciente->nome), stdin);
                paciente->nome[strcspn(paciente->nome, "\n")] = '\0';
                printf("Cadastrar idade:  ");
                scanf("%d", &paciente->idade);
                printf("Cadastrar RG:  ");
                getchar();
                fgets(paciente->RG, sizeof(paciente->RG), stdin);
                paciente->RG[strcspn(paciente->RG, "\n")] = '\0';
                printf("Cadastrar data:\n");
                printf("Dia: ");
                scanf("%d", &paciente->data->dia);
                printf("Mês: ");
                scanf("%d", &paciente->data->mes);
                printf("Ano: ");
                scanf("%d", &paciente->data->ano);

                CelulaLista *novoPaciente = criar_celulaLista(paciente);
                CelulaLista *atual = listaPa->primeiro;
                listaPa->primeiro = novoPaciente;
                novoPaciente->proximo = atual;
                listaPa->qtde++;
                break;
            }
            case 2: {
                int achou = 0;
                char RGConsultar[15];
                printf("RG: ");
                getchar();
                fgets(RGConsultar, sizeof(RGConsultar), stdin);
                RGConsultar[strcspn(RGConsultar, "\n")] = '\0';
                CelulaLista *atual = listaPa->primeiro;
                while(atual != NULL){
                    if(strcmp(atual->paciente->RG, RGConsultar) == 0){
                        achou = 1;
                        break;
                    }
                    atual = atual->proximo;
                }
                if(achou == 1){
                    printf("%s  %d anos  RG: %s cadastro realizado em: %d/%d/%d\n", atual->paciente->nome, atual->paciente->idade, atual->paciente->RG, atual->paciente->data->dia, atual->paciente->data->mes, atual->paciente->data->ano);
                    break;
                }
                printf("Não encontrado");
                break;
            }
            case 3: {
                CelulaLista *atual = listaPa->primeiro;
                while(atual != NULL){
                    printf("%s  %d anos  RG: %s cadastro realizado em: %d/%d/%d\n", atual->paciente->nome, atual->paciente->idade, atual->paciente->RG, atual->paciente->data->dia, atual->paciente->data->mes, atual->paciente->data->ano);
                    atual = atual->proximo;
                }
                break;
            }
            case 4: {
                int achou = 0;
                char RGMudar[15];
                printf("RG: ");
                getchar();
                fgets(RGMudar, sizeof(RGMudar), stdin);
                RGMudar[strcspn(RGMudar, "\n")] = '\0';
                CelulaLista *atual = listaPa->primeiro;
                while(atual != NULL){
                    if(strcmp(atual->paciente->RG, RGMudar) == 0){
                        achou = 1;
                        break;
                    }
                    atual = atual->proximo;
                }
                if(achou == 1){
                    printf("Atualizar idade: ");
                    scanf("%d", &atual->paciente->idade);
                    break;
                }
                printf("Não encontrado");
                break;
            }
            case 5: {
                int achou = 0;
                char RGRemover[15];
                printf("RG: ");
                getchar();
                fgets(RGRemover, sizeof(RGRemover), stdin);
                RGRemover[strcspn(RGRemover, "\n")] = '\0';
                CelulaLista *atual = listaPa->primeiro;
                CelulaLista *anterior = NULL; 
                while(atual != NULL){
                    if(strcmp(atual->paciente->RG, RGRemover) == 0){
                        achou = 1;
                        break;
                    }
                    anterior = atual;
                    atual = atual->proximo;
                }
                if(achou == 1){
                    if(anterior == NULL){
                        listaPa->primeiro = atual->proximo;
                        listaPa->qtde--;
                    }
                    else{
                        anterior->proximo = atual->proximo;
                        listaPa->qtde--;
                    }
                    break;
                }
                printf("Não encontrado");
                break;
            }
        }
     }while (opcao != 0);
};

void Atendimento(ListaPacientes *listaPa, FilaAtendimento *filaPa){
    int opcao;
     do {
        printf("\n==================================\n");
        printf("1. Adicionar paciente á fila\n");
        printf("2. Retirar paciente da fila\n");
        printf("3. Fila completa\n");
        printf("0. Menu\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:{
                int achou = 0;
                char NomeAdicionar[100];
                printf("Nome: ");
                getchar();
                fgets(NomeAdicionar, sizeof(NomeAdicionar), stdin);
                NomeAdicionar[strcspn(NomeAdicionar, "\n")] = '\0';
                CelulaLista *atual = listaPa->primeiro;
                while(atual != NULL){
                    if(strcmp(atual->paciente->nome, NomeAdicionar) == 0){
                        achou = 1;
                        break;
                    }
                    atual = atual->proximo;
                }
                if(achou == 1){
                    CelulaFila *novoPaciente = criar_celulaFila(atual->paciente);
                    if(filaPa->qtde == 0){
                        filaPa->head = novoPaciente;
                        filaPa->qtde++;
                        break;
                    }
                    else{
                        filaPa->tail->proximo = novoPaciente;
                        filaPa->qtde++;
                        break;
                    }
                }
                printf("Não encontrado");
                break;
            }
            case 2:{
                int achou = 0;
                char NomeRetirar[100];
                printf("Nome: ");
                getchar();
                fgets(NomeRetirar, sizeof(NomeRetirar), stdin);
                NomeRetirar[strcspn(NomeRetirar, "\n")] = '\0';
                CelulaFila *atual = filaPa->head;
                while(atual != NULL){
                    if(strcmp(atual->paciente->nome, NomeRetirar) == 0){
                        achou = 1;
                        break;
                    }
                    atual = atual->proximo;
                }
                if(achou == 1){
                    CelulaFila *auxiliar = filaPa->head;
                    if(filaPa->qtde == 1){
                        filaPa->head = NULL;
                        filaPa->tail = NULL;
                        filaPa->qtde--;
                        break;
                    }
                    else{
                        filaPa->head = filaPa->head->proximo;
                        filaPa->qtde--;
                        break;
                    }
                }
                printf("Não encontrado");
                break;
            }
            case 3:
            {
                int id = 1;
                CelulaFila *atual = filaPa->head;
                while(atual != NULL){
                    printf("%d -> %s  %d anos  RG: %s cadastro realizado em: %d/%d/%d\n", id, atual->paciente->nome, atual->paciente->idade, atual->paciente->RG, atual->paciente->data->dia, atual->paciente->data->mes, atual->paciente->data->ano);
                    atual = atual->proximo;
                    id++;
                }
            }
        }
     }while (opcao != 0);
};

// === FUNCAO DE ATENDIMENTO PRIORITARIO ===
void Prioritario(ListaPacientes *listaPa, HeapPrioridade *h) {
    int opcao;

    do {
        printf("\n========= Atendimento Prioritário =========\n");
        printf("1. Inserir paciente na fila prioritária\n");
        printf("2. Atender paciente prioritário\n");
        printf("3. Mostrar fila prioritária\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: {
                int achou = 0;
                char NomeInserir[15];
                printf("Nome ");
                fgets(NomeInserir, sizeof(NomeInserir), stdin);
                NomeInserir[strcspn(NomeInserir, "\n")] = '\0';

                CelulaLista *atual = listaPa->primeiro;
                while (atual != NULL) {
                    if (strcmp(atual->paciente->nome, NomeInserir) == 0) {
                        achou = 1;
                        break;
                    }
                    atual = atual->proximo;
                }
                if (achou == 1) {
                    if (h->qtde == MAX) {
                        printf("Fila prioritária cheia!\n");
                        return;
                    }
                    h->pacientes[h->qtde] = atual->paciente;
                    h->qtde++;
                    construir(h);
                }
                printf("Paciente não encontrado.\n");
                break;
            }
            case 2:{
                int achou = 0;
                char NomeAtender[15];
                printf("Nome ");
                fgets(NomeAtender, sizeof(NomeAtender), stdin);
                NomeAtender[strcspn(NomeAtender, "\n")] = '\0';

                CelulaLista *atual = listaPa->primeiro;
                while (atual != NULL) {
                    if (strcmp(atual->paciente->nome, NomeAtender) == 0) {
                        achou = 1;
                        break;
                    }
                    atual = atual->proximo;
                }
                if(achou == 1){
                    if (h->qtde == 0) {
                        printf("Fila prioritária vazia!\n");
                        return;
                    }
                    printf("Paciente atendido (prioritário): %s (%d anos)\n", h->pacientes[0]->nome, h->pacientes[0]->idade);
                    h->pacientes[0] = h->pacientes[h->qtde - 1];
                    h->qtde--;
                    construir(h);
                }
                printf("Paciente não encontrado.\n");
                break;
            }
            case 3:{
                printf("Fila Prioritária:\n");
                for (int i = 0; i < h->qtde; i++) {
                    printf("%d. %s (%d anos) - RG: %s\n", i + 1, h->pacientes[i]->nome, h->pacientes[i]->idade, h->pacientes[i]->RG);
                }
                break;
            }
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
        }
    } while (opcao != 0);
}

void Pesquisa(){

};
void Desfazer(){

};
void Carregar(){

};

void Salvar(ListaPacientes *listaPa) {
    if (listaPa->qtde == 0 || listaPa->primeiro == NULL) {
        printf("Nenhum paciente cadastrado para salvar.\n");
        return;
    }

    // Usa a data do primeiro paciente como base para nome do arquivo
    RegistroPa *p0 = listaPa->primeiro->paciente;
    char nome_arquivo[100];
    sprintf(nome_arquivo, "Dados.txt");

    FILE *arquivo = fopen(nome_arquivo, "a");
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo");
        return;
    }

    CelulaLista *atual = listaPa->primeiro;
    while (atual != NULL) {
        RegistroPa *p = atual->paciente;
        fprintf(arquivo, "%s;%d;%s;%02d/%02d/%04d\n",
                p->nome, p->idade, p->RG,
                p->data->dia, p->data->mes, p->data->ano);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Pacientes salvos com sucesso em '%s'.\n", nome_arquivo);
}

void Sobre(){

};