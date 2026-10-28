#include <stdio.h>
#include <string.h>

#define MAX_NOME 100
#define ARQUIVO "Aluno.csv"

typedef struct
{
    int matricula;
    char nome[MAX_NOME];
    int idade;
} Aluno;

void limpar_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

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

void gestaoAluno()
{

    Aluno aluno;
    FILE *arq = fopen(ARQUIVO, "a");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo %s.\n", ARQUIVO);
        return;
    }

    printf("Matricula: ");
    scanf("%d", &aluno.matricula);
    limpar_buffer();

    printf("Nome: ");
    fgets(aluno.nome, MAX_NOME, stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &aluno.idade);
    limpar_buffer();

    fprintf(arq, "%d;%s;%d\n", aluno.matricula, aluno.nome, aluno.idade);
    fclose(arq);

    printf("Aluno cadastrado com sucesso!\n");
}

void listar(void)
{
    Aluno aluno;
    char linha[200];
    int total = 0;
    FILE *arq = fopen(ARQUIVO, "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo %s.\n", ARQUIVO);
        return;
    }

    fgets(linha, sizeof(linha), arq);

    printf("\n%-10s %-35s %s\n", "MATRICULA", "NOME", "IDADE");
    printf("----------------------------------------------------\n");

    while (fscanf(arq, "%d;%[^;];%d\n", &aluno.matricula, aluno.nome, &aluno.idade) == 3)
    {
        printf("%-10d %-35s %d\n", aluno.matricula, aluno.nome, aluno.idade);
        total++;
    }

    if (total == 0)
        printf("Nenhum aluno cadastrado.\n");

    fclose(arq);
}

void gestaoLivros()
{
    int opcao;
    struct Livro
    {
        char nome[50];
        char sinopse[501];
        char dataLancamento[15];
    };

    struct Livro titulos[100];
    int quantidade = 0;

    do
    {

        printf("********************\n");
        printf("GESTÃO DE LIVROS\n");
        printf("********************\n");
        printf("1 - ADICIONAR LIVROS\n");
        printf("2 - REMOVER LIVROS\n");
        printf("3 - LISTAR LIVROS\n");
        printf("0 - SAIR\n");

        printf("Digite uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1:
            break;
        case 2:

            break;

        case 3:
            if (quantidade <= 0)
            {
                printf("Nenhum livro cadastrado!\n");
                return gestaoLivros();
            }
            printf("\n-------------------------\n\nLIVROS\n\n-------------------------\n");

            for (int i = 0; i < quantidade; i++)
            {
                printf("\nID: %d\nNOME: %s\nSINOPSE: %s\nDATA LANÇAMENTO: %s\n",
                       i,
                       titulos[i].nome,
                       titulos[i].sinopse,
                       titulos[i].dataLancamento);
            }
            break;
        }

    } while (opcao != 0);

    return;
}

void gestaoAutores()
{
    int opcao;
    struct Pessoa
    {
        char nome[100];
        char bio[100];
        int idade;
    };
    struct Pessoa autores[100];

    do
    {

        printf("********************\n");
        printf("GESTÃO DE AUTORES\n");
        printf("********************\n");
        printf("1 - ADICIONAR AUTOR");
        printf("2 - REMOVER AUTOR");
        printf("3 - LISTAR AUTORES");
        printf("0 - SAIR");

        printf("Digite uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            break;
        case 2:

            break;

        case 3:

            break;
        }

    } while (opcao != 0);

    return;
}

void gestaoUsuarios()
{
    int opcao;
    struct User
    {
        char nome[100];
        int idade;
        int codigo;
    };

    struct User usuarios[100];

    do
    {

        printf("********************\n");
        printf("GESTÃO DE USUARIOS\n");
        printf("********************\n");
        printf("1 - CADASTRAR CONTA");
        printf("2 - EXCLUIR CONTA");
        printf("0 - SAIR");

        printf("Digite uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            break;

        case 2:

            break;
        }

    } while (opcao != 0);
    return;
}

void relatorios()
{
    int opcao;
    struct Relatorios
    {
        int livros_emprestados;
        int user_cadastrado;
        int total_livros;
        int total_autor;
    };

    struct Relatorios info;

    do
    {

        printf("********************\n");
        printf("RELATORIOS\n");
        printf("********************\n");
        printf("1 - LISTAS LIVROS EMPRESTADOS");
        printf("2 - USUARIOS CADASTRADOS");
        printf("3 - TOTAL DE LIVROS");
        printf("4 - TOTAL DE AUTORES");
        printf("0 - SAIR");

        printf("Digite uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            break;

        case 2:

            break;

        case 3:

            break;

        case 4:

            break;
        }

    } while (opcao != 0);
    return;
}

void gestaoEmprestimos()
{
    int opcao;
    struct Emprestimos
    {
    };
    do
    {

        printf("********************\n");
        printf("GESTÃO DE EMPRESTIMOS\n");
        printf("********************\n");
        printf("1 - ");

        printf("Digite uma opção: ");
        scanf("%d", &opcao);

    } while (opcao != 0);
    return;
}

int main()
{
    int opcao;

    do
    {

        printf("---------------------------\n");
        printf("BIBLIOTECA ONLINE\n");
        printf("---------------------------\n");

        printf("****************\n");
        printf("MENU DE OPÇÕES\n");
        printf("****************\n");
        printf("1 - GESTAO DE LIVROS\n");
        printf("2 - GESTAO DE AUTORES\n");
        printf("3 - GESTAO DE USUARIOS\n");
        printf("4 - RELATORIOS\n");
        printf("5 - GESTAO DE EMPRESTIMOS\n");
        printf("6 - GESTAO DE ALUNOS\n");
        printf("0 - SAIR\n\n");
        printf("Digite uma opção: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            gestaoLivros();
            break;
        case 2:
            gestaoAutores();
            break;
        case 3:
            gestaoUsuarios();
            break;
        case 4:
            relatorios();
            break;
        case 5:
            gestaoEmprestimos();
            break;
        case 6:
            gestaoAluno();
            break;
        case 7:
            listar();
            break;
        default:

            break;
        }
    } while (opcao != 0);

    return 0;
}