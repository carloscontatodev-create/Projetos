#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char titulo[50];
    char autor[50];
    int lacamento;
} livro;

void registrarLivro(){
    livro livroNovo;
    printf ("Cadastrar Livro");

    FILE *arquivo fopen("estoque.txt", "a");
    if(arquivo == NULL){
        printf("Livro nao encontrado!");
        return;
    }

    printf("Digite o titulo do livro: \n");
    fgets (livroNovo.titulo, 50, stdin);
    livroNovo.titulo[strcspn(livroNovo.titulo, "\n")] = "\0";

    printf("Digite o autor do livro: \n");
    fgets (livroNovo.autor, 50, stdin);
    livroNovo.titulo[strcspn(livroNovo.autor, "\n")] = "\0";

    printf("Digite o lancamento do livro: \n");
    scanf ("%d", &livroNovo.lacamento);
    livroNovo.titulo[strcspn(livroNovo.lacamento, "\n")] = "\0";

    fprintf (arquivo, " %s;%s;%d", livroNovo.titulo, livroNovo.autor, livroNovo.lacamento);

    fclose(arquivo);
    printf("Registro Concluido!");
}

void pesquisarLivro(){
    
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL){
        printf("Livro nao encontrado no estoque!");
        return;
    }
    char buscarLivro [50];
    printf("Qual o nome do livro ?");
    fgets (buscarLivro, 50, stdin);
    buscarLivro[strspn(buscarLivro, "\n")] = '\0';

    livro livrotemp;
    int flag = 0;

    while (fscanf(arquivo, " %[^;]%[^;];%d\n", livrotemp.titulo, livrotemp.autor, livrotemp.lacamento) != EOF ){

        if (strcmp(livrotemp.titulo, buscarLivro) == 0){
            printf("Titulo: %s\n", livrotemp.titulo);
            printf("Autor: %s\n", livrotemp.autor);
            printf("Lancamento: %s\n", livrotemp.lacamento);

            flag = 1;
            break;
        }

        if (flag == 1){
            printf("O livro nao foi encontrado!\n");
        }
    }

    fclose(arquivo);
}

int main(){

    int opcao

    do{

        printf("1. Registrar livro.\n");
        printf("2. Pesquisar livro.\n");
        printf("3. Sair do menu.\n");

        scanf("%d", &opcao);
        getchar();

        if (opcao>3){
            printf("Por favor selecione uma opção valida.");
        }
        if (opcao == 1){
            registrarLivro();
            break;
        }
        if (opcao == 2){
            pesquisarLivro();
            break;
        }

    } while (opcao!=3)


    return 0;
}

void modificarLivro() {
    FILE *arquivoOriginal = fopen("estoque.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    // Se o arquivo original não existir, avisa e sai
    if (arquivoOriginal == NULL) {
        printf("\nERRO: Nenhum arquivo de estoque encontrado para modificar!\n");
        if (arquivoTemp != NULL) fclose(arquivoTemp);
        return;
    }

    char buscarLivro[50];
    char bufferTemporario[50];
    printf("\n--- MODIFICAR LIVRO ---\n");
    printf("Qual o nome do livro que deseja editar? ");
    fgets(buscarLivro, 50, stdin);
    buscarLivro[strcspn(buscarLivro, "\n")] = '\0';

    livro livrotemp;
    int flag = 0;

    // Lê o arquivo original linha por linha
    while (fscanf(arquivoOriginal, " %[^;];%[^;];%d\n", livrotemp.titulo, livrotemp.autor, &livrotemp.lancamento) != EOF) {
        
        if (strcmp(livrotemp.titulo, buscarLivro) == 0) {
            flag = 1;
            printf("\n=> Livro encontrado! Vamos atualizar os dados:\n");
            
            printf("Novo titulo: ");
            fgets(livrotemp.titulo, 50, stdin);
            livrotemp.titulo[strcspn(livrotemp.titulo, "\n")] = '\0';

            printf("Novo autor: ");
            fgets(livrotemp.autor, 50, stdin);
            livrotemp.autor[strcspn(livrotemp.autor, "\n")] = '\0';

            printf("Novo ano de lancamento: ");
            fgets(bufferTemporario, 50, stdin);
            livrotemp.lancamento = atoi(bufferTemporario); // Converte o texto para int
            
            // Grava os dados NOVOS no arquivo temporário
            fprintf(arquivoTemp, "%s;%s;%d\n", livrotemp.titulo, livrotemp.autor, livrotemp.lancamento);
            printf("\n=> Livro atualizado com sucesso!\n");
        } 
        else {
            // Se não for o livro buscado, apenas copia os dados ANTIGOS para o temporário
            fprintf(arquivoTemp, "%s;%s;%d\n", livrotemp.titulo, livrotemp.autor, livrotemp.lancamento);
        }
    }

    // Fecha os dois arquivos OBRIGATORIAMENTE antes de excluir ou renomear
    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    // Substitui o arquivo velho pelo novo atualizado
    if (flag == 1) {
        remove("estoque.txt");               // Deleta o arquivo antigo
        rename("temp.txt", "estoque.txt");   // Renomeia o temp para virar o oficial
    } else {
        printf("\nO livro '%s' nao foi encontrado!\n", buscarLivro);
        remove("temp.txt");                  // Como não achou nada, apaga o temp criado à toa
    }
}   