/*
==ORDEM DAS FUNÇÕES==
registrarUsuarioComum()
registrarColetor()
loginUsuario() -> login apenas para o usuário
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int autenticado = 1;

typedef struct{ //estrutra para o endereço disponível
    char rua[50];
    char bairro[50];
    int numero;
} Endereco;

typedef struct{  //estrutura para usuario e senha(usuário normal)
    char nome[50];
    char senha[50];
} Login;

typedef struct{  //estrutura para o coletor
    char nomeColetor[50];
    char senhaColetor[50];
} LoginColetor;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void registrarUsuarioComum() { //funcao para cadastrar o usuário comum
    FILE *file;  //UC = usuário comum
    file = fopen("cadastroUsuarioComum.txt", "ab");

    if (file == NULL) {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    Login cadastro;

    printf("Digite aqui seu nome: ");
    fgets(cadastro.nome, 50, stdin);
    cadastro.nome[strcspn(cadastro.nome, "\n")] = '\0';

    printf("Digite aqui sua senha: ");
    fgets(cadastro.senha, 50, stdin);
    cadastro.senha[strcspn(cadastro.senha, "\n")] = '\0';

    fprintf(file, "%s %s\n", cadastro.nome, cadastro.senha);

    fclose(file);
}


void registrarColetor() { //funcao que registra o coletor
    FILE *file;
    file = fopen("cadastroColetor.txt", "w");

    if (file == NULL) {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    LoginColetor cadastroColetor;

    printf("Digite aqui seu nome: ");
    fgets(cadastroColetor.nomeColetor, 50, stdin);
    cadastroColetor.nomeColetor[strcspn(cadastroColetor.nomeColetor, "\n")] = '\0';

    printf("Digite aqui sua senha: ");
    fgets(cadastroColetor.senhaColetor, 50, stdin);
    cadastroColetor.senhaColetor[strcspn(cadastroColetor.senhaColetor, "\n")] = '\0';

    fprintf(file, "%s %s\n", cadastroColetor.nomeColetor, cadastroColetor.senhaColetor);

    fclose(file);
}

int loginUsuario(Login * usuario) {
    
    FILE *file;
    file = fopen("cadastroUsuarioComum.txt", "r");

    if (file == NULL) {
        printf("\nNão há nennhum usuário cadastrado no momento!");
        autenticado = 0;
        return 0;
    }

    char userInsert[50], senhaInsert[50];
    printf("\nBem vindo a aba de login!\n");
    printf("Digite seu nome de usuário: ");
    fgets(userInsert, 50, stdin);
    userInsert[strcspn(userInsert, "\n")] = '\0';

    printf("Digite sua senha de acesso: ");
    fgets(senhaInsert, 50, stdin);
    senhaInsert[strcspn(senhaInsert, "\n")] = '\0';

    int usuarioExiste = 0;

    while (fscanf(file, "%s %s\n", usuario->nome, usuario->senha) != EOF) {
        if (strcmp(userInsert, usuario->nome) == 0) {
            usuarioExiste = 1;
            if (strcmp(senhaInsert, usuario->senha) == 0) {
                fclose(file);
                system("cls");
                autenticado = 1;
                printf("Login bem-sucedido! Bem-vindo, %s.", usuario->nome);
                return 1;
            }
        }
    }

    fclose(file);

    if (usuarioExiste) {
        autenticado = 0;
        printf("Senha incorreta. Tente novamente.\n");
        loginUsuario(&usuario);
    }else{
        autenticado = 0;
        printf("Usuário não encontrado. Verifique seu nome de usuário.\n");
        loginUsuario(&usuario);
    }

    return 0;
}

void cadastrarEndereco() {
    FILE *file;
    file = fopen("enderecosCadastrados.txt", "a");

    if(file == NULL) {
        printf("\nNão há nenhum endereço cadastrado.");
    }

    Endereco endereco;


    printf("Digite aqui sua rua: ");
    fgets(endereco.rua, 50, stdin);
    endereco.rua[strcspn(endereco.rua, "\n")] = '\0';

    printf("Digite aqui seu bairro: ");
    fgets(endereco.bairro, 50, stdin);
    endereco.bairro[strcspn(endereco.bairro, "\n")] = '\0';

    printf("Digite aqui o número: ");
    scanf("%d", &endereco.numero);

    fprintf(file, "%s %s %d\n", endereco.rua, endereco.bairro, endereco.numero);

    fclose(file);
}

void verChamados() {
    FILE *file;
    char caracter;
    file = fopen("enderecosCadastrados.txt", "r");

    if(file == NULL) {
        printf("\nNão há endereços cadastrados!");
    }else {
        printf("\nPontos de coleta que estão disponíveis no momento: \n");
        while ((caracter = fgetc(file)) != EOF) {
            putchar(caracter);  
        }
    }

    fclose(file);
}

void excluirEnderecos(){ //funcao que exclui um endereço determinado pelo seu número
    FILE *fileOG;
    FILE *fileTEMP;
    Endereco end;
    int num;

    fileOG = fopen("enderecosCadastrados.txt", "rb");
    fileTEMP = fopen("enderecosTemporarios.txt", "ab");

    if(fileOG == NULL || fileTEMP == NULL) {
        printf("\nProblemas na abertura do arquivo!");
    }else{
        printf("Digite o número da casa a ser excluido: ");
        scanf("%d", &num);

        while(fread(&end, sizeof(Endereco), 1, fileOG) == 1){  //le o arquivo até encontrar o numero digitado, se encontrar move para o outro arquivo
            if(strcmp(num, end.numero) != 0) {
                fwrite(&end, sizeof(Endereco), 1, fileTEMP);
            }
        }
    }

    fclose(fileOG);
    fclose(fileTEMP);
    remove("enderecosCadastrados.txt");
    rename("enderecosTemporarios.txt", "enderecosCadastrados.txt");
    printf("\nEndereço excluido com sucesso!");
}

int main() {
    int escolha;

    Login usuario;

        printf("\n+-------------------------------+");
        printf("\n|(1) Registrar usuário comum    |");
        printf("\n|(2) Registrar coletor          |");
        printf("\n|(3) Login                      |");
        printf("\n|(0) Sair                       |");
        printf("\n+-------------------------------+");
        printf("\n Opção: ");
        scanf("%d", &escolha);
        limparBuffer();
        printf("+----------------------------+\n");

        switch(escolha){
            case 0:
                printf("\nSaindo...");
                return 0;
                break;
            case 1:
                registrarUsuarioComum();
                printf("\nUsuário registrado com sucesso!");
                system("cls");
                loginUsuario(&usuario);
                break;
            case 2:
                registrarColetor();
                printf("\nUsuário registrado com sucesso!");
                break;
            case 3:
                loginUsuario(&usuario);
                break;
            default:
                printf("\nOpção inválida!");
                return 0;
                break;
        }

        if(autenticado == 1) {
            while(escolha != 0){
                printf("\n+----------------------------+");
                printf("\n|(1) Registrar endereço      |");
                printf("\n|(2) Fazer chamado           |"); //?
                printf("\n|(3) Ver chamados            |");
                printf("\n|(4) Excluir endereço        |");
                printf("\n|(0) Sair                    |");
                printf("\n+----------------------------+");
                printf("\n Opção: ");
                scanf("%d", &escolha);
                limparBuffer();

                switch(escolha) {
                    case 0:
                        printf("Saindo...");
                        return 0;
                        break;
                    case 1:
                        system("cls");
                        cadastrarEndereco();
                        break;
                    case 2:

                        break;
                    case 3:
                        system("cls");
                        verChamados();
                        break;
                    case 4:
                        excluirEnderecos();
                        break;
                }
            }
        }

    return 0;
}