/* ============================================================
   CADASTRO DE ALUNOS - Manipulacao de arquivo CSV em C
   Arquivo de dados: alunos.csv (separador ';')
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "alunos.csv" /* arquivo principal                */
#define ARQ_TEMP "temp.csv"  /* arquivo auxiliar                 */
#define MAX_NOME 80          /* tamanho maximo do nome           */

/* Estrutura que representa um aluno */
typedef struct
{
    int matricula;
    char nome[MAX_NOME];
    int idade;
} Aluno;

/* Prototipos das funcoes */
void limpar_tela(void);
void limpar_buffer(void);
void garantir_arquivo(void);
void cadastrar(void);
void consultar(void);
void listar(void);
void excluir(void);
void atualizar(void);

void limpar_tela(void)
{
    printf("\033[2J\033[H"); /* limpa a tela e posiciona o cursor no topo */
}

/* ------------------------------------------------------------
   limpar_buffer: esvazia o buffer de entrada ate encontrar
   uma quebra de linha ou o fim do arquivo.
   ------------------------------------------------------------ */
void limpar_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ------------------------------------------------------------
   garantir_arquivo: cria o CSV com o cabecalho, se nao existir.
   ------------------------------------------------------------ */
void garantir_arquivo(void)
{
    FILE *arq = fopen(ARQUIVO, "r");

    if (arq == NULL)
    {
        arq = fopen(ARQUIVO, "w");
        if (arq != NULL)
        {
            fprintf(arq, "matricula;nome;idade\n");
            fclose(arq);
        }
    }
    else
    {
        fclose(arq);
    }
}

/* ------------------------------------------------------------
   cadastrar: le matricula, nome e idade e acrescenta o
   registro no final do arquivo.
   ------------------------------------------------------------ */
void cadastrar(void)
{
    Aluno a;
    FILE *arq = fopen(ARQUIVO, "a"); /* modo append */

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo %s.\n", ARQUIVO);
        return;
    }

    printf("Matricula: ");
    scanf("%d", &a.matricula);
    limpar_buffer();

    printf("Nome: ");
    fgets(a.nome, MAX_NOME, stdin);
    a.nome[strcspn(a.nome, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &a.idade);
    limpar_buffer();

    fprintf(arq, "%d;%s;%d\n", a.matricula, a.nome, a.idade);
    fclose(arq);

    printf("Aluno cadastrado com sucesso!\n");
}

/* ------------------------------------------------------------
   consultar: solicita a matricula e exibe os dados do aluno.
   ------------------------------------------------------------ */
void consultar(void)
{
    int mat, achou = 0;
    Aluno a;
    char linha[200];
    FILE *arq = fopen(ARQUIVO, "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo %s.\n", ARQUIVO);
        return;
    }

    printf("Matricula a consultar: ");
    scanf("%d", &mat);
    limpar_buffer();

    fgets(linha, sizeof(linha), arq); /* pula o cabecalho */

    while (fscanf(arq, "%d;%[^;];%d\n", &a.matricula, a.nome, &a.idade) == 3)
    {
        if (a.matricula == mat)
        {
            printf("\nAluno encontrado:\n");
            printf("Matricula: %d\n", a.matricula);
            printf("Nome:      %s\n", a.nome);
            printf("Idade:     %d\n", a.idade);
            achou = 1;
            break;
        }
    }

    if (!achou)
        printf("Aluno com matricula %d nao encontrado.\n", mat);

    fclose(arq);
}

/* ------------------------------------------------------------
   listar: exibe todos os alunos cadastrados.
   ------------------------------------------------------------ */
void listar(void)
{
    Aluno a;
    char linha[200];
    int total = 0;
    FILE *arq = fopen(ARQUIVO, "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo %s.\n", ARQUIVO);
        return;
    }

    fgets(linha, sizeof(linha), arq); /* pula o cabecalho */

    printf("\n%-10s %-35s %s\n", "MATRICULA", "NOME", "IDADE");
    printf("----------------------------------------------------\n");

    while (fscanf(arq, "%d;%[^;];%d\n", &a.matricula, a.nome, &a.idade) == 3)
    {
        printf("%-10d %-35s %d\n", a.matricula, a.nome, a.idade);
        total++;
    }

    if (total == 0)
        printf("Nenhum aluno cadastrado.\n");

    fclose(arq);
}

/* ------------------------------------------------------------
   excluir: copia para um arquivo temporario todos os registros,
   exceto o da matricula informada, e substitui o original.
   ------------------------------------------------------------ */
void excluir(void)
{
    int mat, excluido = 0;
    Aluno a;
    char linha[200];
    FILE *arq = fopen(ARQUIVO, "r");
    FILE *temp = fopen(ARQ_TEMP, "w");

    if (arq == NULL || temp == NULL)
    {
        printf("Erro ao abrir os arquivos.\n");
        if (arq)
            fclose(arq);
        if (temp)
            fclose(temp);
        return;
    }

    printf("Matricula a excluir: ");
    scanf("%d", &mat);
    limpar_buffer();

    fgets(linha, sizeof(linha), arq);
    fputs(linha, temp);

    while (fscanf(arq, "%d;%[^;];%d\n", &a.matricula, a.nome, &a.idade) == 3)
    {
        if (a.matricula != mat)
        {
            fprintf(temp, "%d;%s;%d\n", a.matricula, a.nome, a.idade);
        }
        else
        {
            excluido = 1;
        }
    }

    fclose(arq);
    fclose(temp);

    if (excluido)
    {
        remove(ARQUIVO);
        rename(ARQ_TEMP, ARQUIVO);
        printf("Aluno excluido com sucesso!\n");
    }
    else
    {
        remove(ARQ_TEMP);
        printf("Aluno com matricula %d nao encontrado.\n", mat);
    }
}

/* ------------------------------------------------------------
   atualizar: localiza o aluno pela matricula e permite alterar
   nome e idade.
   ------------------------------------------------------------ */
void atualizar(void)
{
    int mat, atualizado = 0;
    Aluno a;
    char linha[200];
    FILE *arq = fopen(ARQUIVO, "r");
    FILE *temp = fopen(ARQ_TEMP, "w");

    if (arq == NULL || temp == NULL)
    {
        printf("Erro ao abrir os arquivos.\n");
        if (arq)
            fclose(arq);
        if (temp)
            fclose(temp);
        return;
    }

    printf("Matricula a atualizar: ");
    scanf("%d", &mat);
    limpar_buffer();

    fgets(linha, sizeof(linha), arq);
    fputs(linha, temp);

    while (fscanf(arq, "%d;%[^;];%d\n", &a.matricula, a.nome, &a.idade) == 3)
    {
        if (a.matricula == mat)
        {
            printf("Aluno encontrado: %s\n", a.nome);

            printf("Novo nome: ");
            fgets(a.nome, MAX_NOME, stdin);
            a.nome[strcspn(a.nome, "\n")] = '\0';

            printf("Nova idade: ");
            scanf("%d", &a.idade);
            limpar_buffer();

            fprintf(temp, "%d;%s;%d\n", a.matricula, a.nome, a.idade);
            atualizado = 1;
        }
        else
        {
            fprintf(temp, "%d;%s;%d\n", a.matricula, a.nome, a.idade);
        }
    }

    fclose(arq);
    fclose(temp);

    if (atualizado)
    {
        remove(ARQUIVO);
        rename(ARQ_TEMP, ARQUIVO);
        printf("Cadastro atualizado com sucesso!\n");
    }
    else
    {
        remove(ARQ_TEMP);
        printf("Aluno com matricula %d nao encontrado.\n", mat);
    }
}

/* ------------------------------------------------------------
   main: menu com WHILE + SWITCH-CASE
   ------------------------------------------------------------ */
int main(void)
{
    int opcao;

    garantir_arquivo();

    while (1)
    {
        printf("\n+++++++++++++ CADASTRO DE ALUNOS\n");
        printf("1-Cadastrar ALUNOS\n");
        printf("2-Consultar ALUNOS\n");
        printf("3-Listar ALUNOS\n");
        printf("4-Excluir ALUNOS\n");
        printf("5-Atualizar cadastro de ALUNOS\n");
        printf("6-Sair\n");
        printf("Selecione uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            limpar_buffer();
            printf("Entrada invalida! Digite um numero.\n");
            continue;
        }
        limpar_buffer();

        switch (opcao)
        {
        case 1:
            cadastrar();
            break;
        case 2:
            consultar();
            break;
        case 3:
            listar();
            break;
        case 4:
            excluir();
            break;
        case 5:
            atualizar();
            break;
        case 6:
            printf("Encerrando o programa...\n");
            return 0;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}