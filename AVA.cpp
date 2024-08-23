#include <stdio.h>
#include <vector>
#include <iostream>
#include <limits>
#include <string.h>
#include <ctype.h>

using namespace std;

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    char nome[50];
    char cpf[12]; // armazena apenas números (sem . e -)
    char sexo;    // utilizar M para masculino e F para Feminino
    Data nascimento;
} Pessoa;

vector<Pessoa> pessoas;

int menu()
{
    int op = 0;
    printf("1 - Cadastrar Pessoa\n");
    printf("2 - Resumir informações\n");
    printf("3 - Buscar por CPF\n");
    printf("4 - Buscar por nascimento\n");
    printf("5 - Contar por nascimento\n");

    printf("0 - Sair\n");

    printf("Opção: ");
    scanf("%d", &op);

    if (op < 0 || op > 5)
    {
        printf("Opção inválida, informe novamente.\n");
        menu();
    }

    return op;
}

void limparBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};

long long data(Data data)
{
    long long ano = data.ano * 365; // p/ simplificar
    long long mes = data.mes * 30;
    long long dia = data.dia;
    return ano + mes + dia;
}

void cadastrarPessoa()
{
    Pessoa pessoa;
    limparBuffer();
    printf("Informe o nome: ");
    fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
    printf("Informe o CPF (sem . e -): ");
    fgets(pessoa.cpf, sizeof(pessoa.cpf), stdin);

    printf("Data nascimento[DD/MM/AAAA]: ");
    scanf("%d/%d/%d", &pessoa.nascimento.dia, &pessoa.nascimento.mes, &pessoa.nascimento.ano);
    printf("Informe o genero(M/F): ");

    scanf(" %c", &pessoa.sexo);

    size_t lenNome = strlen(pessoa.nome);
    size_t lenCpf = strlen(pessoa.cpf);
    pessoa.nome[lenNome - 1] = '\0';
    pessoa.cpf[lenCpf - 1] = '\0';

        pessoas.push_back(pessoa);
    printf("Cadastro realizado com sucesso!\n");
}

void resumoCadastros()
{
    int contF = 0, contM = 0;
    for (int i = 0; i < pessoas.size(); i++)
    {
        if (pessoas[i].sexo == 'M' || pessoas[i].sexo == 'm')
        {
            contM++;
            continue;
        }
        contF++;
    }

    printf("%d pessoas estão cadastradas no sistema\n", pessoas.size());
    printf("%d Sexo masculino\n%d Sexo Feminino.\n", contM, contF);
}

void buscarPorCPF()
{
    limparBuffer();
    char cpf[12];
    int posPessoa = -1;
    Data nasc;
    printf("Informe o CPF (sem . e -): ");
    fgets(cpf, sizeof(cpf), stdin);
    size_t lenCpf = strlen(cpf);
    cpf[lenCpf - 1] = '\0';

    for (int i = 0; i < pessoas.size(); i++)
    {
        if (!strcmp(cpf, pessoas[i].cpf))
        {
            posPessoa = i;
            printf("Nome: %s\n", pessoas[i].nome);
            printf("CPF: %s\n", pessoas[i].cpf);
            printf("Genero: %c\n", pessoas[i].sexo);
            printf("Data Nascimento: %d/%d/%d\n", pessoas[i].nascimento.dia, pessoas[i].nascimento.mes, pessoas[i].nascimento.ano);
            break;
        }
    }

    if (posPessoa == -1)
    {

        printf("Pessoa não encontrada, tente novamente.\n");
    }
}

void buscarPorNascimento()
{
    Data nascimento;
    printf("Data nascimento[DD/MM/AAAA]: ");
    scanf("%d/%d/%d", &nascimento.dia, &nascimento.mes, &nascimento.ano);

    for (int i = 0; i < pessoas.size(); i++)
    {
        if (data(nascimento) == data(pessoas[i].nascimento))
        {
            printf("\n");
            printf("Nome: %s\n", pessoas[i].nome);
            printf("CPF: %s\n", pessoas[i].cpf);
            printf("Genero: %c\n", pessoas[i].sexo);
            printf("Data Nascimento: %d/%d/%d\n", pessoas[i].nascimento.dia, pessoas[i].nascimento.mes, pessoas[i].nascimento.ano);
            printf("\n");
        }
    }
}

void contarPorNascimento()
{
    Data dtns;

    Data inicial;
    int contador = 0;
    printf("Data inicial[DD/MM/AAAA]: ");
    scanf("%d/%d/%d", &inicial.dia, &inicial.mes, &inicial.ano);
    Data final;
    printf("Data final[DD/MM/AAAA]: ");
    scanf("%d/%d/%d", &final.dia, &final.mes, &final.ano);

    if (data(inicial) > data(final))
    {
        printf("Datas invalidas, tente novamente.\n");
        contarPorNascimento();
    }

    for (int i = 0; i < pessoas.size(); i++)
    {
        dtns = pessoas[i].nascimento;

        if (data(dtns) >= data(inicial) && data(dtns) <= data(final))
        {
            printf("\n");
            printf("Nome: %s\n", pessoas[i].nome);
            printf("CPF: %s\n", pessoas[i].cpf);
            printf("Genero: %c\n", pessoas[i].sexo);
            printf("Data Nascimento: %d/%d/%d\n", dtns.dia, dtns.mes, dtns.ano);
            printf("\n");
            contador++;
        }
    }

    printf("%d Pesssoa(s) nasceram no periodo informado\n");
}

int main()
{
    int op = 0;
    do
    {
        op = menu();

        switch (op)
        {
        case 1:
            cadastrarPessoa();
            break;
        case 2:
            resumoCadastros();
            break;
        case 3:
            buscarPorCPF();
            break;
        case 4:
            buscarPorNascimento();
            break;
        case 5:
            contarPorNascimento();
            break;
        default:
            printf("veio no default");
            break;
        }
    } while (op != 0);

    return 0;
}
