#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char usuario[50];
    char senha[50];
} Login;

typedef struct {
    char bairro[50];
    char rua[50];
    char numero[50];
} Endereco;

void cadastro();
int logar();
void consulta();
void cadEndereco();

int main() {
    setlocale(LC_ALL, "portuguese");
    system("clear");

    Login cads;
    int login, escolha;

    printf("(1) Cadastro\n(2) Login\n");
    scanf("%d", &login);
    getchar();

    switch (login) {
        case 1:
            cadastro();
            break;
        case 2: {
            int autentificador = 0;
            while (autentificador != 1) {
                if (logar() == 1) {
                    autentificador = 1;
                } else {
                    system("clear");
                    printf("Login ou senha incorretos, tente novamente.\n");
                }
            }
            break;
        }
        default:
            printf("Opção inválida!\n");
            return 1;
    }

    system("clear");

    printf("Escolha uma opção:\n(1) Cadastrar endereço\n(2) Fazer chamado\n(3) Ver chamados\n");
    scanf("%d", &escolha);
    getchar();

    switch (escolha) {
        case 1:
            system("clear");
            cadEndereco();
            break;
        case 2:
            printf("Opção não implementada.\n");
            break;
        case 3:
            system("clear");
            consulta();
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    return 0;
}

void cadastro() {
    FILE *file = fopen("usuarioCads.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Login cads;

    printf("Digite o usuário: ");
    fgets(cads.usuario, sizeof(cads.usuario), stdin);

    printf("Digite a senha: ");
    fgets(cads.senha, sizeof(cads.senha), stdin);

    cads.usuario[strcspn(cads.usuario, "\n")] = '\0';
    cads.senha[strcspn(cads.senha, "\n")] = '\0';

    fprintf(file, "%s %s\n", cads.usuario, cads.senha);

    fclose(file);
}

int logar() {
    FILE *file = fopen("usuarioCads.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    Login cads;

    char usuarioInsert[50], senhaInsert[50];

    printf("Digite o usuário: ");
    fgets(usuarioInsert, sizeof(usuarioInsert), stdin);

    printf("Digite a senha: ");
    fgets(senhaInsert, sizeof(senhaInsert), stdin);

    usuarioInsert[strcspn(usuarioInsert, "\n")] = '\0';
    senhaInsert[strcspn(senhaInsert, "\n")] = '\0';

    while (fscanf(file, "%s %s", cads.usuario, cads.senha) != EOF) {
        if (strcmp(usuarioInsert, cads.usuario) == 0 && strcmp(senhaInsert, cads.senha) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void consulta() {
    FILE *file = fopen("enderCads.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[200];
    printf("Pontos de coleta disponíveis:\n");
    while (fgets(linha, sizeof(linha), file) != NULL) {
        printf("%s", linha);
    }
    printf("\n");

    fclose(file);
}

void cadEndereco() {
    FILE *file = fopen("enderCads.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Endereco end;

    printf("Digite o bairro: ");
    fgets(end.bairro, sizeof(end.bairro), stdin);

    printf("Digite a rua: ");
    fgets(end.rua, sizeof(end.rua), stdin);

    printf("Digite o número: ");
    fgets(end.numero, sizeof(end.numero), stdin);

    end.bairro[strcspn(end.bairro, "\n")] = '\0';
    end.rua[strcspn(end.rua, "\n")] = '\0';
    end.numero[strcspn(end.numero, "\n")] = '\0';

    fprintf(file, "%s, %s, %s\n", end.bairro, end.rua, end.numero);

    fclose(file);
}