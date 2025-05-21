#include "biblioteca.h"

int main() {
    ListaPacientes *listaPa = criar_lista();
    FilaAtendimento *filaPa = cria_fila();
    HeapPrioridade *heap = malloc(sizeof(HeapPrioridade));
    heap->qtde = 0;

    int opcao;

    do {
        printf("\n==================================\n");
        printf("1. Cadastro de Pacientes\n");
        printf("2. Atendimento\n");
        printf("3. Atendimento Prioritário\n");
        printf("4. Pesquisa\n");
        printf("5. Desfazer Ações\n");
        printf("6. Carregar\n");
        printf("7. Salvar\n");
        printf("8. Sobre\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                Cadastro(listaPa);
                break;
            case 2:
                Atendimento(listaPa, filaPa);
                break;
            case 3:
                Prioritario(listaPa, heap);
                break;
            case 4:
                Pesquisa();
                break;
            case 5:
                Desfazer();
                break;
            case 6:
                Carregar();
                break;
            case 7:
                Salvar(listaPa);
                break;
            case 8:
                Sobre();    
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    printf("\n");

    return 0;
}
