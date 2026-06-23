#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nomeContato[100];
    char email[100];
    char telefone[20];
    char tipoContato[100];
} ListaTelefonica;

void cadastrarContato(){
    ListaTelefonica novoContato;
    printf("\n");
    printf("** Cadastre um novo contato **\n");
    printf("\n");

    FILE *arquivo = fopen("arquivo.txt", "a");
    if (arquivo == NULL){
        printf("Contato não encontrado!\n");
        printf("\n");
        return;
    }

    printf("Digite o nome do contato: \n");
    fgets (novoContato.nomeContato, 100, stdin);
    novoContato.nomeContato[strcspn(novoContato.nomeContato, "\n")] = '\0';

    printf("Digite o email do contato: \n");
    fgets (novoContato.email, 100, stdin);
    novoContato.email[strcspn(novoContato.email, "\n")] = '\0';

    printf("Digite o telefone do contato: \n");
    fgets (novoContato.telefone, 20, stdin);
    novoContato.telefone[strcspn(novoContato.telefone, "\n")] = '\0';

    printf("Pessoal.\nTrabalho.\nFamilia.\nCliente.\nOutro.\nDigite o tipo do contato: \n");
    fgets(novoContato.tipoContato, 100, stdin);
    novoContato.tipoContato[strcspn(novoContato.tipoContato, "\n")] = '\0';

    fprintf (arquivo, "%s;%s;%s;%s\n", novoContato.nomeContato, novoContato.email, novoContato.telefone, novoContato.tipoContato);

    fclose (arquivo);
    printf("Cadastro efetivado com sucesso! \n");
    printf("\n");
}

void pesquisarCOntato(){
    char buscarContato[50];
    FILE *arquivo = fopen("arquivo.txt", "r");
    if (arquivo == NULL){
        printf("Contato nao encontrado!\n");
        return;
    }
    printf("Digite o nome do contato: \n");
    fgets(buscarContato, 50, stdin);
    buscarContato [strcspn(buscarContato, "\n")] = '\0'; 

    ListaTelefonica contatotemp;
    int bandeira = 0;

    while (fscanf(arquivo, " %[^;];%[^;];%[^;];%[^\n]\n", contatotemp.nomeContato, contatotemp.email, contatotemp.telefone, contatotemp.tipoContato) != EOF){

        if (strcmp(contatotemp.nomeContato, buscarContato) == 0){
            printf("Nome do Contato: %s\n", contatotemp.nomeContato);
            printf("Email do Contato: %s\n", contatotemp.email);
            printf("Telefone do Contato: %s\n", contatotemp.telefone);
            printf("Tipo do contato: %s\n", contatotemp.tipoContato);
            bandeira = 1;
            break;
        }
    }
    if (bandeira == 0){
        printf("Contato nao encontrado!");
        printf("\n");
    }

    fclose(arquivo);
}

void editarContato(){
    FILE *arquivo = fopen("arquivo.txt", "r");
    FILE *arquivoTemp = fopen("arquivotemp.txt", "w");

    if (arquivo == NULL){
        printf("Contato nao encontrado!");
        printf("\n");
        if (arquivoTemp == NULL) fclose(arquivo);
        return;
    }

    char buscarContato[50];

    printf("Editar contato.\n");
    printf("Qual o nome do contato que deseja modificar: \n");
    fgets(buscarContato, 50, stdin);
    buscarContato[strcspn(buscarContato, "\n")] = '\0';

    ListaTelefonica contatotemp;
    int bandeira = 0;

    // CORREÇÃO: Mudança para %[^;] no telefone
    while (fscanf(arquivo, " %[^;];%[^;];%[^;];%[^\n]\n", contatotemp.nomeContato, contatotemp.email, contatotemp.telefone, contatotemp.tipoContato) != EOF){

        if (strcmp(contatotemp.nomeContato, buscarContato) == 0){
            bandeira = 1;

            printf("Digite o novo nome do contato: \n");
            fgets(contatotemp.nomeContato, 50, stdin);
            contatotemp.nomeContato[strcspn(contatotemp.nomeContato, "\n")] = '\0';

            printf("Digite o novo email: \n");
            fgets(contatotemp.email, 50, stdin);
            contatotemp.email[strcspn(contatotemp.email, "\n")] = '\0';

            printf("Digite o novo telefone do contato: \n");
            fgets(contatotemp.telefone, 20, stdin);
            contatotemp.telefone[strcspn(contatotemp.telefone, "\n")] = '\0';

            printf("Pessoal.\nTrabalho.\nFamilia.\nCliente.\nOutro.\nDigite o tipo do contato: \n");
            printf("\n");
