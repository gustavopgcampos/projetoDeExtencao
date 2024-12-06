#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char userInsert[50], senhaInsert[50];

typedef struct {
    char bairro[50];
    char rua[50];
    char numero[50];
    char enderecoConcat[100];
} Endereco;

typedef struct {
    char user[50];
    char senha[50];
    int userNumber;
} Login;

int loginColetor(char user[], char senha[]) {
    FILE *file;
    file = fopen("cadastroColetor.txt", "rb");

    if(file == NULL){
        printf("Erro ao abrir o arquivo.");
    }

    Login rbn;

    userInsert[strcspn(userInsert, "\n")] = '\0';
    senhaInsert[strcspn(senhaInsert, "\n")] = '\0';

    while (fscanf(file, "%s %s", rbn.user, rbn.senha) != EOF) {
        if (strcmp(userInsert, rbn.user) == 0 && strcmp(senhaInsert, rbn.senha) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    return 0;
}

int conferir_usuario(const char *usuario,int qual){
    
    Login conf;
    FILE *file;

    file = fopen("cadastroColetor.txt","r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo");
    }

     while (fscanf(file, "%s %s", conf.user, conf.senha) != EOF) {
        if (strcmp(usuario, conf.user) == 1) {
            printf("Nome de usuário já existente.\nAperte qualquer tecla para cadastrar novamente");
            fclose(file);
            return 0;
        }
        else{
            return 1;
        }
    }
}

int cadastroColetor() {
    FILE *file;
    file = fopen("cadastroColetor.txt", "ab");
    if(file == NULL){
        printf("Erro ao abrir ao arquivo");
    }


    Login cad;

    printf("Digite seu nome de usuário: ");
    fgets(cad.user, 50, stdin);

    printf("Digite sua senha: ");
    fgets(cad.senha, 50, stdin);

    cad.user[strcspn(cad.user, "\n")] = '\0';
    cad.senha[strcspn(cad.senha, "\n")] = '\0';

   

    fprintf(file, "%s %s\n", cad.user, cad.senha);
        
    
    fclose(file);
}

void change() {
    FILE *file;
    file = fopen("enderCads.txt", "r+b");
    Endereco end;

    int index = 1;
}

void cadastroUsuario() {
    int random, min = 0, max = 100;

    FILE *file;
    file = fopen("userCads.txt", "ab");


    Login cads;

    printf("Digite seu nome de usuário: ");
    fgets(cads.user, 50, stdin);

    printf("Digite sua senha: ");
    fgets(cads.senha, 50, stdin);

    srand(time(NULL));
    random = (min + (rand() % (max - min + 1)));

    cads.userNumber = random;

    cads.user[strcspn(cads.user, "\n")] = '\0';
    cads.senha[strcspn(cads.senha, "\n")] = '\0';

    fprintf(file, "%s %s \n", cads.user, cads.senha);

    fclose(file);
}

int logarUsuario(char user[], char password[]) {
    FILE *file;
    file = fopen("userCads.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    Login rbn;

    char username[50], pass[50];

    printf("Digite seu nome de usuário: ");
    fgets(userInsert, 50, stdin);

    printf("Digite sua senha: ");
    fgets(senhaInsert, 50, stdin);

    userInsert[strcspn(userInsert, "\n")] = '\0';
    senhaInsert[strcspn(senhaInsert, "\n")] = '\0';

    while (fscanf(file, "%s %s", rbn.user, rbn.senha) != EOF) {
        if (strcmp(userInsert, rbn.user) == 0 && strcmp(senhaInsert, rbn.senha) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    return 0;
}

void verChamados() {
    FILE *file;
    file = fopen("enderCads.txt", "r");

    char linhas[200];
    printf("Pontos de coletas disponíveis:\n");
    while (fgets(linhas, sizeof(linhas), file) != NULL) {
        printf("%s", linhas);
    }

    printf("\n");

    fclose(file);
}

void cadastroEndereco() {
    
    FILE *file;
    file = fopen("enderCads.txt", "a");

    Endereco rbn;

    printf("Digite o seu bairro: ");
    fgets(rbn.bairro, 50, stdin);

    printf("Digite a sua rua: ");
    fgets(rbn.rua, 50, stdin);

    printf("Digite o número do endereço: ");
    fgets(rbn.numero, 50, stdin);

    rbn.bairro[strcspn(rbn.bairro, "\n")] = '\0';
    rbn.rua[strcspn(rbn.rua, "\n")] = '\0';
    rbn.numero[strcspn(rbn.numero, "\n")] = '\0';

    

    fprintf(file, "%s, %s, %s\n", rbn.bairro,rbn.rua,rbn.numero);

    fclose(file);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    system("cls");
    Login cads;
    
    int escolha=10, acesso=0;
    
    printf("\n+-------------------------------+");
    printf("\n|(1) Registrar usuário comum    |");
    printf("\n|(2) Registrar coletor          |");
    printf("\n|(3) Login                      |");
    printf("\n|(0) Sair                       |");
    printf("\n+-------------------------------+");
    printf("\n Opção: ");
    scanf("%d", &escolha);
    printf("+----------------------------+\n");
    
    if(escolha != 1 && escolha != 2 && escolha != 3 && escolha != 0) {
        printf("Opção inválida!");
        return 0;
    }

    getchar();

    switch (escolha) {
        case 0:
            printf("\nSaindo...");
            return 0;
            break;
        case 1:
            cadastroUsuario();

            break;

        case 3: {
            int autenticador = 0;

            while (autenticador != 1) {
                if (logarUsuario(cads.user, cads.senha) == 0) {
                    if (loginColetor(cads.user, cads.senha) == 1) {
                        autenticador = 1;
                        acesso = 1;

                    } else {
                        system("clear");
                        printf("Senha incorreta, tente novamente.\n");
                    }
                }else{
                    autenticador = 1;
                }
            }

            
            break;
        }

        case 2:
            cadastroColetor();
            acesso = 1;
            break;    
            
    }

    if(acesso == 1){

            system("cls");

            printf("\n+----------------------------+");
            printf("\n|(1) Ver chamados            |");
            printf("\n|(2) Reservar chamados       |");
            printf("\n|(0) Sair                    |");
            printf("\n+----------------------------+");
            printf("\n Opção: ");
            scanf("%d", &escolha);
            getchar();

            switch (escolha) {
                case 1:
                    system("cls");
                    verChamados();
                    break;

                case 2:
                    printf("Não implementado\n");
                    break;

                default:
                    printf("Não implementado\n");
                    break;
            }
    }else{
            system("cls");
            while(escolha != 0) {
                
                printf("\n+----------------------------+");
                printf("\n|(1) Registrar endereço      |");
                printf("\n|(2) Fazer chamado           |");
                printf("\n|(3) Ver chamados            |");
                printf("\n|(4) Mudar endereços         |");
                printf("\n|(0) Sair                    |");
                printf("\n+----------------------------+");
                printf("\n Opção: ");
                scanf("%d", &escolha);
                getchar();
                
                switch (escolha) {
                case 0:
                    printf("\nSaindo...");
                    return 0;
                    break;
                case 1:
                    system("cls");
                    cadastroEndereco();
                    break;

                case 2:
                    printf("Não implementado\n");
                    break;

                case 3:
                    system("cls");
                    verChamados();
                    break;

                case 4:
                    printf("Não implementado\n");
                    break;

                default:
                    printf("Opção inválida\n");
                    break;
            }
            }
        }
    }