#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nomeContato[100];
    char email[100];
    int telefone;
    char tipoContato[100];
} ListaTelefonica;

void cadastrarContato(){
    ListaTelefonica novoContato;
    printf("** Cadastre um novo contato **\n");

    FILE *arquivo = fopen("arquivo.txt", "a");
    if (arquivo == NULL){
        printf("Contato não encontrado!\n");
        return;
    }

    printf("Digite o nome do contato: \n");
    fgets (novoContato.nomeContato, 100, stdin);
    novoContato.nomeContato[strcspn(novoContato.nomeContato, "\n")] = '\0';

    printf("Digite o email do contato: \n");
    fgets (novoContato.email, 100, stdin);
    novoContato.email[strcspn(novoContato.email, "\n")] = '\0';

    printf("Digite o telefone do contato: \n");
    scanf("%d", &novoContato.telefone);
    while (getchar() != '\n');

    printf("Pessoal.\nTrabalho.\nFamilia.\nCliente.\nOutro.\nDigite o tipo do contato: \n");
    fgets(novoContato.tipoContato, 100, stdin);
    novoContato.tipoContato[strcspn(novoContato.tipoContato, "\n")] = '\0';

    fprintf (arquivo, "%s;%s;%d;%s\n", novoContato.nomeContato, novoContato.email, novoContato.telefone, novoContato.tipoContato);

    fclose (arquivo);
    printf("Cadastro efetivado com sucesso! \n");
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

    while (fscanf(arquivo, " %[^;];%[^;];%d;%[^\n]\n", contatotemp.nomeContato, contatotemp.email, &contatotemp.telefone, contatotemp.tipoContato) != EOF){

        if (strcmp(contatotemp.nomeContato, buscarContato) == 0){
            printf("Nome do Contato: %s\n", contatotemp.nomeContato);
            printf("Email do Contato: %s\n", contatotemp.email);
            printf("Telefone do Contato: %d\n", contatotemp.telefone);
            printf("Tipo do contato: %s\n", contatotemp.tipoContato);
            bandeira = 1;
            break;
        }
    }
    if (bandeira == 0){
        printf("Contato nao encontrado!");
    }

    fclose(arquivo);

}

void editarContato(){
    FILE *arquivo = fopen("arquivo.txt", "r");
    FILE *arquivoTemp = fopen("arquivotemp.txt", "w");

    if (arquivo == NULL){
        printf("Contato nao encontrado!");
        if (arquivoTemp == NULL) fclose(arquivo);
        return;
    }

    char buscarContato[50];

    printf("Editar contato.\n");
    printf("Qual o nome do contato que deseja modifciar: \n");
    fgets(buscarContato, 50, stdin);
    buscarContato[strcspn(buscarContato, "\n")] = '\0';

    ListaTelefonica contatotemp;
    int bandeira = 0;

    while (fscanf(arquivo, " %[^;];%[^;];%d;%[^\n]\n", contatotemp.nomeContato, contatotemp.email, &contatotemp.telefone, contatotemp.tipoContato) != EOF){

        if (strcmp(contatotemp.nomeContato, buscarContato) == 0){
            bandeira = 1;

            printf("Digite o novo nome do contato: \n");
            fgets(contatotemp.nomeContato, 50, stdin);
            contatotemp.nomeContato[strcspn(contatotemp.nomeContato, "\n")] = '\0';

            printf("Digite o novo email: \n");
            fgets(contatotemp.email, 50, stdin);
            contatotemp.email[strcspn(contatotemp.email, "\n")] = '\0';

            printf("Digite o novo telefone do contato: \n");
            scanf("%d", &contatotemp.telefone);
            while (getchar() != '\n');

            printf("Digite o novo tipo de contato: \n");
            fgets(contatotemp.tipoContato, 50, stdin);
            contatotemp.tipoContato[strcspn(contatotemp.tipoContato, "\n")] = '\0';

            fprintf(arquivoTemp, "%s;%s;%d;%s\n", contatotemp.nomeContato, contatotemp.email, contatotemp.telefone, contatotemp.tipoContato);
            printf("Contato atualizado com sucesso!\n");
        }
        else{
            fprintf(arquivoTemp, "%s;%s;%d;%s\n", contatotemp.nomeContato, contatotemp.email, contatotemp.telefone, contatotemp.tipoContato);
        }
    }

        fclose(arquivo);
        fclose(arquivoTemp);

    if (bandeira == 1){
        remove ("arquivo.txt");
        rename ("arquivotemp.txt", "arquivo.txt");
    }
    else {
        printf("Contato nao encontrado!\n");
        remove ("arquivotemp.txt");
    }
}

void apagarContato(){
    FILE *arquivo = fopen("arquivo.txt", "r");
    FILE *arquivoTemp = fopen("arquivotemp.txt", "w");

    if (arquivo == NULL){
        printf("Contato nao encontrado!");
        if (arquivoTemp == NULL) fclose(arquivo);
        return;
    }

    char buscarContato[50];

    printf("Apagar Contato\n");
    printf("Qual o nome do contato que deseja deletar: \n");
    fgets(buscarContato, 50, stdin);
    buscarContato[strcspn(buscarContato, "\n")] = '\0';

    ListaTelefonica contatotemp;
    int bandeira = 0;

    while (fscanf(arquivo, " %[^;];%[^;];%d;%[^\n]\n", contatotemp.nomeContato, contatotemp.email, &contatotemp.telefone, contatotemp.tipoContato) != EOF){

        if (strcmp(contatotemp.nomeContato, buscarContato) == 0){
            bandeira = 1;
            printf("O contato foi apagado com sucesso!\n");
        }
        else{
            fprintf(arquivoTemp, "%s;%s;%d;%s\n", contatotemp.nomeContato, contatotemp.email, contatotemp.telefone, contatotemp.tipoContato);
        }
    }

        fclose(arquivo);
        fclose(arquivoTemp);

    if (bandeira == 1){
        remove ("arquivo.txt");
        rename ("arquivotemp.txt", "arquivo.txt");
    }
    else {
        printf("Contato nao encontrado!\n");
        remove ("arquivotemp.txt");
    }
}

void listarContatos(){

    FILE *arquivo = fopen("arquivo.txt", "r");
    if (arquivo == NULL){
        printf("Contato nao encontrado!\n");
        return;
    }

    ListaTelefonica contatotemp;
    int contador = 0;

    printf("** Lista de Contatos **\n");
    while (fscanf(arquivo, " %[^;];%[^;];%d;%[^\n]\n", contatotemp.nomeContato, contatotemp.email, &contatotemp.telefone, contatotemp.tipoContato) != EOF) {

        printf("Nome do contato: %s\n", contatotemp.nomeContato);
        printf("Email do contato: %s\n", contatotemp.email);
        printf("Telefone do contato: %d\n", contatotemp.telefone);
        printf("Tipo do contato: %s\n", contatotemp.tipoContato);
        printf("\n");

        contador++;
    }

    if(contador==0){
        printf("A lista esta vazio no momento!\n");
    }
    else{
        printf("Há um total de %d contatos salvos.\n", contador);
    }

    fclose(arquivo);

}

int main(){

    int opcao;

    printf("--- Bem vindo a Lista Telefonica ---\n");
    printf("Digite a opcao desejada.\n");


    do{
    printf("1. Cadastrar contato.\n2. Alterar contato.\n3. Apagar contato.\n4.Procurar contato.\n5. Listar contatos.\n6. Sair\n");
    scanf("%d", &opcao);
    while (getchar() != '\n');
    if (opcao == 1){cadastrarContato();}
    if (opcao == 2){editarContato();}
    if (opcao == 3){apagarContato();}
    if (opcao == 4){pesquisarCOntato();}
    if (opcao == 5){listarContatos();}
    if (opcao == 6){printf("Obrigado!\n");}
    } while (opcao != 6);

    system("pause");
    return 0;
}
