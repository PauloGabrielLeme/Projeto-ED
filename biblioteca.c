#include "biblioteca.h"

// === FUNCOES DE HEAP ===
int filho_esq(int pai) { return 2 * pai + 1; }
int filho_dir(int pai) { return 2 * pai + 2; }
int pai(int filho) { return (filho - 1) / 2; }

VerticeArvore* inserir_arvore(VerticeArvore *raiz, RegistroPa *paciente, int criterio) {
    if (raiz == NULL) {
        VerticeArvore *novo = malloc(sizeof(VerticeArvore));
        novo->paciente = paciente;
        novo->esq = novo->dir = NULL;
        return novo;
    }

    int valorRaiz, valorNovo;
    switch (criterio) {
        case 1: // Ano
            valorRaiz = raiz->paciente->data->ano;
            valorNovo = paciente->data->ano;
            break;
        case 2: // Mês
            valorRaiz = raiz->paciente->data->mes;
            valorNovo = paciente->data->mes;
            break;
        case 3: // Dia
            valorRaiz = raiz->paciente->data->dia;
            valorNovo = paciente->data->dia;
            break;
        case 4: // Idade
            valorRaiz = raiz->paciente->idade;
            valorNovo = paciente->idade;
            break;
    }

    if (valorNovo < valorRaiz) {
        raiz->esq = inserir_arvore(raiz->esq, paciente, criterio);
    } else {
        raiz->dir = inserir_arvore(raiz->dir, paciente, criterio);
    }

    return raiz;
}

void em_ordem(VerticeArvore *raiz) {
    if (raiz == NULL) return;
    em_ordem(raiz->esq);
    RegistroPa *p = raiz->paciente;
    printf("%s - Idade: %d - RG: %s - Data: %02d/%02d/%04d\n", p->nome, p->idade, p->RG, p->data->dia, p->data->mes, p->data->ano);
    em_ordem(raiz->dir);
}

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
                        filaPa->head = filaPa->tail = novoPaciente;  // atualiza ambos head e tail
                        filaPa->qtde++;
                } else {
                        filaPa->tail->proximo = novoPaciente;        // liga o novo ao final da fila
                        filaPa->tail = novoPaciente;                 // atualiza o novo tail
                        filaPa->qtde++;
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
                    printf("%d %s  %d anos  RG: %s cadastro realizado em: %d/%d/%d\n", id, atual->paciente->nome, atual->paciente->idade, atual->paciente->RG, atual->paciente->data->dia, atual->paciente->data->mes, atual->paciente->data->ano);
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
                } else {
                    printf("Paciente não encontrado.\n");
                }
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

int comparar_pacientes(const void *a, const void *b) {
    RegistroPa *pa = *(RegistroPa**)a;
    RegistroPa *pb = *(RegistroPa**)b;

    if (pa->data->ano != pb->data->ano)
        return pa->data->ano - pb->data->ano;
    if (pa->data->mes != pb->data->mes)
        return pa->data->mes - pb->data->mes;
    if (pa->data->dia != pb->data->dia)
        return pa->data->dia - pb->data->dia;

    return strcmp(pa->RG, pb->RG);
}


void Pesquisa123(ListaPacientes *listaPa) {
    if (listaPa->qtde == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    int opcao = 0;
    char nomeBusca[100], rgBusca[20];
    int idadeBusca, diaBusca, mesBusca, anoBusca;

    printf("Selecione:\n");
    printf("1. Nome\n");
    printf("2. RG\n");
    printf("3. Idade\n");
    printf("4. Data\n");
    scanf("%d", &opcao);

    // Aloca vetor para ponteiros filtrados
    RegistroPa **resultados = malloc(listaPa->qtde * sizeof(RegistroPa*));
    if (!resultados) {
        printf("Erro de alocação.\n");
        return;
    }

    int encontrados = 0;
    CelulaLista *atual = listaPa->primeiro;

    // Lê o valor de busca com base na opção
    if (opcao == 1) {
        printf("Digite o nome: ");
        scanf(" %[^\n]", nomeBusca);

        while (atual != NULL) {
            if (strcmp(atual->paciente->nome, nomeBusca) == 0)
                resultados[encontrados++] = atual->paciente;
            atual = atual->proximo;
        }

    } else if (opcao == 2) {
        printf("Digite o RG: ");
        scanf("%s", rgBusca);

        while (atual != NULL) {
            if (strcmp(atual->paciente->RG, rgBusca) == 0)
                resultados[encontrados++] = atual->paciente;
            atual = atual->proximo;
        }

    } else if (opcao == 3) {
        printf("Digite a idade: ");
        scanf("%d", &idadeBusca);

        while (atual != NULL) {
            if (atual->paciente->idade == idadeBusca)
                resultados[encontrados++] = atual->paciente;
            atual = atual->proximo;
        }

    } else if (opcao == 4) {
        printf("Digite a data (dd mm aaaa): ");
        scanf("%d %d %d", &diaBusca, &mesBusca, &anoBusca);

        while (atual != NULL) {
            if (atual->paciente->data->dia == diaBusca &&
                atual->paciente->data->mes == mesBusca &&
                atual->paciente->data->ano == anoBusca) {
                resultados[encontrados++] = atual->paciente;
            }
            atual = atual->proximo;
        }

    } else {
        printf("Opção inválida.\n");
        free(resultados);
        return;
    }

    if (encontrados == 0) {
        printf("Nenhum paciente encontrado.\n");
        free(resultados);
        return;
    }

    // Ordena os resultados encontrados
    qsort(resultados, encontrados, sizeof(RegistroPa*), comparar_pacientes);

    // Exibe os pacientes encontrados
    printf("\n--- Pacientes encontrados ---\n");
    for (int j = 0; j < encontrados; j++) {
        printf("%s  %d anos  RG: %s  Cadastro: %02d/%02d/%04d\n",
               resultados[j]->nome, resultados[j]->idade, resultados[j]->RG,
               resultados[j]->data->dia, resultados[j]->data->mes, resultados[j]->data->ano);
    }

    free(resultados);
}
void Pesquisa(ListaPacientes *listaPa) {
    if (listaPa->qtde == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    printf("\n=== PESQUISA ===\n");
    printf("1. Ordenar por ano\n");
    printf("2. Ordenar por mês\n");
    printf("3. Ordenar por dia\n");
    printf("4. Ordenar por idade\n");
    printf("Escolha uma opção: ");

    int criterio;
    scanf("%d", &criterio);

    VerticeArvore *raiz = NULL;
    CelulaLista *atual = listaPa->primeiro;

    while (atual != NULL) {
        raiz = inserir_arvore(raiz, atual->paciente, criterio);
        atual = atual->proximo;
    }

    printf("\nPacientes ordenados:\n");
    em_ordem(raiz);
}

void Desfazer(FilaAtendimento* filaAtendimento) {
    if (filaAtendimento == NULL || filaAtendimento->head == NULL) {
        printf("Fila vazia. Nada a desfazer.\n");
        return;
    }

    char resposta;
    printf("Tem certeza que deseja desfazer o último atendimento? (s/n): ");
    scanf(" %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        // Remove da fila o primeiro paciente (head)
        CelulaFila* temp = filaAtendimento->head;
        filaAtendimento->head = temp->proximo;
        free(temp);
        filaAtendimento->qtde--;

        if (filaAtendimento->head == NULL) {
            filaAtendimento->tail = NULL;  // fila vazia após remoção
        }

        printf("Último atendimento removido da fila.\n");
    } else {
        printf("Operação cancelada.\n");
    }
}



void Carregar(ListaPacientes *listaPa, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char *linhas[MAX];
    int count = 0;
    char buffer[256];

    // Lê todas as linhas e armazena em memória
    while (fgets(buffer, sizeof(buffer), arquivo)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // remove newline
        linhas[count] = strdup(buffer);       // copia para o array
        count++;
        if (count >= MAX) break;
    }

    fclose(arquivo);

    // Agora percorre de trás pra frente
    for (int i = count - 1; i >= 0; i--) {
        RegistroPa *p = malloc(sizeof(RegistroPa));
        p->data = malloc(sizeof(Data));

        char *token = strtok(linhas[i], ";");
        if (token != NULL) strcpy(p->nome, token);

        token = strtok(NULL, ";");
        if (token != NULL) p->idade = atoi(token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(p->RG, token);

        token = strtok(NULL, "/");
        if (token != NULL) p->data->dia = atoi(token);
        token = strtok(NULL, "/");
        if (token != NULL) p->data->mes = atoi(token);
        token = strtok(NULL, "/");
        if (token != NULL) p->data->ano = atoi(token);

        // Insere o paciente na lista
        CelulaLista *nova = criar_celulaLista(p);
        nova->proximo = listaPa->primeiro;
        listaPa->primeiro = nova;
        listaPa->qtde++;

        free(linhas[i]); // libera memória da linha lida
    }
        printf("Pacientes carregados\n");
}


void Salvar(ListaPacientes *listaPa) {
    if (listaPa->qtde == 0 || listaPa->primeiro == NULL) {
        printf("Nenhum paciente cadastrado para salvar.\n");
        return;
    }

    RegistroPa *p0 = listaPa->primeiro->paciente;
    char nome_arquivo[100];
    sprintf(nome_arquivo, "Dados");

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo");
        return;
    }

    fseek(arquivo, 0, SEEK_SET); // vai para o início do arquivo

    CelulaLista *atual = listaPa->primeiro;
    while (atual != NULL) {
        RegistroPa *p = atual->paciente;
        fprintf(arquivo, "%s;%d;%s;%02d/%02d/%04d\n",
                p->nome, p->idade, p->RG,
                p->data->dia, p->data->mes, p->data->ano);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Pacientes salvos com sucesso\n");
}

void Sobre(){
    int e = 0;

    printf("\n");
    printf("Nome: LORENZO COLONNESE CHIGANCAS RA: 24.223.085-2\n");
    printf("Nome: PAULO GABRIEL GONÇALVES LEME RA: \n");
    printf("Ciclo: ALUNOS DO 4º CICLO\n");
    printf("Curso: CIÊNCIA DA COMPUTAÇÂO\n");
    printf("Diciplina: ESTRUTURA DE DADOS\n");
    printf("Data: 21/05/2025\n\n");

    printf("1. Imprimir de Novo\n");
    printf("0. Sair\n");

    scanf("%d",&e);

    if(e==1){
        Sobre();
    }

};
