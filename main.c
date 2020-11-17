#include <stdio.h>//padrão
#include <conio.h>//padrão
#include <string.h>//uso string
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <direct.h>


int lista;
// Arquivos com todos os pacientes lista_pacientes1.txt
FILE *Ponteiro;
// Arquivos com todos os pacientes com conformidades lista_pacientes2.txt
FILE *Ponteiro2;

typedef struct{
    char login[30]; // vetor login da struct pessoa
    char senha[30]; // vetor senha da struct pessoa
} pessoa; pessoa p[1]; 

void main(){
   setlocale(LC_ALL, "Portuguese");


    char login[30]; // armazenar a senha 
    char senha[30]; //  armazenar a senha  pelo usuário

    strcpy(p[0].login, "admin"); // Definindo o login "admin" na struct
    strcpy(p[0].senha, "admin"); // Definindo a senha "admin"  na struct

    printf("\nlogin:");
    scanf("%s", login); // armazenando os dados inseridos pelo usuário para o vetor login que está dentro da função main

    printf("\nsenha:");
    scanf("%s", senha); // armazenando os dados inseridos pelo usuário para o vetor senha que está dentro da função main

    if ((strcmp(login,p[0].login)==0) && (strcmp(senha,p[0].senha)==0)){ // A função strcmp é responsável por comparar string com string
        printf("Usuário logado"); // se os vetores de dentro da struct tiver os mesmos dados do vetor interno da função main, usuário será logado.
    }else{
        printf("Login e/ou senha incorretos"); // senão, login ou senha incorreta.
    }

    printf("\n**Login Confirmado**\n");
    getch();

    char nome[50],
        cpf[50],
        endereco_rua[50],
        endereco_numero[50],
        endereco_bairro[50],
        endereco_cep[50],
        telefone[50],
        strIdade[4],
        dataDiagnostico[50],
        comorbidades[50];
    int idade, nitems,conformidade;

    do
	{
	    printInfoBase();
        printf("\n--> Cadastros de Pacientes com Covid-19 <--\n");
        printf("\n--> 1-Cadastrar de paciente <--\n");
        printf("\n--> 2-Listar pacientes fora do grupo de risco <--\n");
        printf("\n--> 3-Listar pacientes considerados do grupo risco <--\n");
        printf("\n--> 0-Encerrar <--\n");
        scanf("%d", &lista);
        fflush(stdin);

        switch(lista){
            case 0:;
                printInfoBase();
                printf("\n\n\nSaindo do sistema.");
                getch();
                break;
            case 1:;
                bool continuaValido = true;

                struct tm *data_hora_atual;
                time_t segundos;
                time(&segundos);
                data_hora_atual = localtime(&segundos);
                data_hora_atual = localtime(&segundos);
                int diaA = data_hora_atual->tm_mday;
                int mesA = data_hora_atual->tm_mon+1;
                int anoA = data_hora_atual->tm_year+1900;

                printInfoBase();
                Ponteiro=fopen("lista_pacientes1.txt","a");
                printf("\nDigite o nome completo do paciente: ");
                fgets(nome,50,stdin);
                fputs(nome,Ponteiro);


                if(strlen(nome) == 0){
                    continuaValido = false;
                }

                if (continuaValido){
                    printf("\nDigite o CPF do paciente: ");
                    fgets(cpf,50,stdin);
                    fputs(cpf,Ponteiro);

                }

                printf("\n Digite a rua : ");
                fgets(endereco_rua,50,stdin);
                printf("\nDigite o numero: ");
                fgets(endereco_numero,50,stdin);
                printf("\nDigite o bairro: ");
                fgets(endereco_bairro,50,stdin);
                printf("\nDigite o CEP ");
                fgets(endereco_cep,50,stdin);
                printf("\nDigite o telefone: ");
                fgets(telefone,50,stdin);
                printf("\nDigite data de diagnostico ex:(dd/mm/aaaa)\n");
                fgets(dataDiagnostico,50,stdin);


                int diaN, mesN, anoN, idade;

                printf("\nDigite a data de nascimento ex:(dd/mm/aaaa)\n");
                scanf("%d/%d/%d", &diaN, &mesN, &anoN);

                if ((mesN > mesA) || ((mesN = mesA) && (diaN > diaA))){
                   idade = anoA - anoN ;
                   printf("Paciente tem %d", idade);
                }
                else {
                    idade = anoA - anoN;
                    printf("Paciente tem %d", idade);
                }


                printf("\nVoc� tem algum dessas comorbidade(diabetes, obesidade, hipertensão,tuberculose, outros)(Sim 1/Nao 2): ");
                scanf("%d",&conformidade);

                if(conformidade == 1) {
                    printf("\nInforme a Comorbidade: ");
                    scanf("[^\n]s",&comorbidades);
                }

                if((conformidade == 1)||(idade >= 65)){
                   Ponteiro2=fopen("lista_pacientes2.txt","a");
                   fprintf(Ponteiro2,"Nome: %s",nome);
                   fprintf(Ponteiro2,"CPF: %s",cpf);
                   fprintf(Ponteiro2,"CEP: %s",endereco_cep);
                   fprintf(Ponteiro2,"Telefone: %s",telefone);
                   fprintf(Ponteiro2,"Idade: %d\n",idade);
                   fprintf(Ponteiro2,"Comorbidade: %s \n\n",comorbidades);


                    fclose(Ponteiro2);

                    printInfoBase();
                    printf("\nPaciente Cadastrado com Sucesso");
                    getch();
                }
                else if ((conformidade == 2)||(idade < 65)){
                   Ponteiro=fopen("lista_pacientes1.txt","a");
                   fprintf(Ponteiro,"Nome: %s",nome);
                   fprintf(Ponteiro,"CPF: %s",cpf);
                   fprintf(Ponteiro,"CEP: %s",endereco_cep);
                   fprintf(Ponteiro,"Telefone: %s",telefone);
                   fprintf(Ponteiro,"Idade: %d\n",idade);
                   fclose(Ponteiro);

                    printInfoBase();
                    printf("\nPaciente Cadastrado com Sucesso");
                    getch();
                } else {
                     printInfoBase();
                    printf("\nfalha no cadastro!!");
                    getch();
                }

                break;

            case 2:;
                printInfoBase();

                char ch;
                Ponteiro = fopen("lista_pacientes1.txt", "r");
                if(Ponteiro == NULL)
                {   printInfoBase();
                    printf("N�o foi poss�vel abrir o arquivo.\n");
                    exit(EXIT_FAILURE);
                } else do {
                   ch = fgetc(Ponteiro);
                    putchar(ch);


                } while(ch != EOF); //end of file

                fclose(Ponteiro);


                printf("\n\n\n------------------------------------------------");
                printf("\nFim da lista de pacientes.");
                getch();
                break;


              case 3:;
                printInfoBase();

                char ch1;
                Ponteiro2 = fopen("lista_pacientes2.txt", "r");
                if(Ponteiro2 == NULL)
                {   printInfoBase();
                    printf("N�o foi poss�vel abrir o arquivo.\n");
                    printf("Por favor verifique as permiss�es de acesso ou se os arquivos existem.\n");
                    exit(EXIT_FAILURE);
                } else do {
                   ch1 = fgetc(Ponteiro2);
                    putchar(ch1);


                } while(ch1 != EOF); //end of file

                fclose(Ponteiro2);


                printf("\n\n\n--------------------------------------------------------------------------------------");
                printf("\nFim da lista de pacientes de risco.");
                getch();
                break;

            default:;
                printInfoBase();
                printf("Op��o inv�lida\n");
                getch();
                break;
            }
    } while(lista != 0);

    system('cls');
}

void printInfoBase(){
    system("cls");
    printf("\n|-----------------------------------------------------------|");
    printf("\n|                                                           |");
    printf("\n|             GERENCIAMENTO PACIENTE COVID                  |");
    printf("\n|___________________________________________________________|");
}
