#include <stdio.h>
#include <stdlib.h> //usando system
#include <ctype.h> //usando toupper
#include <string.h> //usando strcmp
#include <locale.h>

struct TpFarma{
    char Nome[21];
    float Preco;
    int QEstoque;
};

typedef struct TpFarma TpFARMA;
TpFARMA RgFarma;

FILE *ArqFarma;

long int Tamanho = 21*sizeof(char)+sizeof(float)+sizeof(int);

void Incluir(){
    char R;
    ArqFarma = fopen("Farmacos.dat", "a+b");
    do{
        printf("*** Inclus�o ***\n\n");
        int ver = 0;
        do{
            ver = 0;
            char Nome[21];
            printf("Nome: ");
            scanf(" %[^\n]s", Nome);
            fseek(ArqFarma, 0, 0);
            while(fread(&RgFarma, Tamanho, 1, ArqFarma)){
                if(strcmp(RgFarma.Nome, Nome) == 0 && RgFarma.Preco > 0){
                    printf("Farmaco j� existente!\n");
                    ver = 1;
                    break;
                }else{
                    strcpy(RgFarma.Nome, Nome);
                }
            }

        }while(ver);

        do{
            printf("Pre�o: ");
            scanf("%f", &RgFarma.Preco);
            if(RgFarma.Preco < 0)
                printf("Pre�o Inv�lido!\n");
        } while(RgFarma.Preco < 0);

        do{
            printf("Estoque: ");
            scanf("%d", &RgFarma.QEstoque);
            if (RgFarma.QEstoque < 0)
                printf("Estoque Inv�lido!\n");
        } while(RgFarma.QEstoque < 0);

        fseek(ArqFarma, 0, 2);
        fwrite(&RgFarma, Tamanho, 1, ArqFarma);

        printf("\nNoma inclus�o? S/N ");
        scanf(" %c", &R);
        R = toupper(R);
    }while(R != 'N');
    fclose(ArqFarma);
    return 0;
};
void Excluir(){};

long int TArquivo(){
    fseek(ArqFarma, 0, 2);
    long int R = ftell(ArqFarma)/Tamanho;
    return R;
}

void Alterar(){
    ArqFarma = fopen("Farmacos.dat", "r+b");
    if(TArquivo() != 0){
        printf("*** Alterar ***\n\n");
        fseek(ArqFarma, 0, 0);
        printf("Qual farmaco? ");
        char Farmaco[21];
        scanf("%s", Farmaco);
        int Achou = 0;
        do{
            fread(&RgFarma, Tamanho, 1, ArqFarma);
            if(strcmp(RgFarma.Nome, Farmaco) == 0 && RgFarma.Preco > 0){
                Achou = 1;
                printf("Nome: %s\n", RgFarma.Nome);
                printf("Valor: %.2f\n", RgFarma.Preco);
                printf("Estoque: %d\n", RgFarma.QEstoque);
            }
        }while(!feof(ArqFarma) && (Achou == 0));

        if(Achou == 0)
            printf("Registro inexistente!");
        else{
            do{
                printf("Qual o novo pre�o? \n");
                scanf("%f", &RgFarma.Preco);
                if(RgFarma.Preco < 0)
                    printf("Pre�o inv�lido!\n");
            }while(RgFarma.Preco < 0);

        }
    }
};
void Consultar(){};
void LTodos(){};

int main()
{
    setlocale(LC_ALL, "Portuguese");
    ArqFarma = fopen("Farmacos.dat", "a+b");
    char opcao;
    do{
        printf("\n\n> > > Pague Pouco < < <\n\n");
        printf("O que deseja fazer? \n\n");
        printf("I - Incluir \n");
        printf("E - Excluir \n");
        printf("A - Alterar \n");
        printf("C - Consultar \n");
        printf("T - Listar Todos \n");
        printf("S - Sair \n\n");
        scanf(" %c", &opcao);
        opcao = toupper(opcao);
        switch (opcao){
            case 'I': Incluir(); break;
            case 'E': Excluir(); break;
            case 'A': Alterar(); break;
            case 'C': Consultar(); break;
            case 'T': LTodos(); break;
            default: printf("Op��o Inv�lida!!"); break;
        }
    }while( opcao != 'S');
    fclose(ArqFarma);
    return 0;
}
