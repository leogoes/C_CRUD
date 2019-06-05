#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados {

            char nome [20];
            char endereco[20];
            char data_nascimento[20];
            char cidade[20];
            char estado[20];
            char cep[20];

            };

void inclui();
void lista();
int pesquisaNome();
int pesquisaPrimeiraLetra();
int pesquisaAniversario();
int pesquisaCEP();
void altera();
void exclui();

int main()
{
        struct dados info;
        struct dados *p;
        int op;
        int i;
        int tam;    //n. de bytes da estrutura

        p = & info;
        tam = sizeof(info);

        for(i=0;i<sizeof(info);i++) {   //zera a estrutura de dados
            info.nome[i]=0;
           }
        while(1){
        printf(" 1 -Inclua dados  \n");
        printf(" 2 -Lista dados  \n");
        printf(" 3 -Pesquisa por nome  \n");
        printf(" 4 -Pesquisa pela 1 letra do nome  \n");
        printf(" 5 -Pesquisa os aniversariantes \n");
        printf(" 6 -Pesquisa por CEP  \n");
        printf(" 7 -Altera dados  \n");
        printf(" 8 -Exclui dados  \n");
        printf(" 9 -Saida\n");
        scanf("%d", &op);
        getchar();


    switch(op)
                {
                case 1 : inclui(p, tam);   //passa como parametro o ponteiro para a estrutura e o n. de bytes da desta
                break;

                case 2: lista(p, tam);
                break;

                case 3: pesquisaNome(p, tam);
                break;

                case 4: pesquisaPrimeiraLetra(p, tam);
                break;

                case 5: pesquisaAniversario(p, tam);
                break;

                case 6: pesquisaCEP(p, tam);
                break;

                case 7: altera(p, tam);
                break;

                case 8: exclui(p, tam);
                break;

                case 9: exit(0);
                break;

                default: printf("\n opcao invalida\n");
                }
    };

}

void inclui(struct dados *ps, int tam)
{
    FILE *p, *p1;
    int cont = 0;
    int i;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);

    for(i=0;i<tam;i++){ //zera os dados da estrutura
        ps -> nome[i]=0;
    }

    p = fopen("arquivo.txt", "a");

    if( p == NULL){
        printf("\nERRO");
        exit(1);
    }
    //Recebe dados do usuario
    printf("Insira um valor para o nome: ");
    gets(ps->nome);
    printf("Insira um valor para o endereco: ");
    gets(ps->endereco);
    printf("Insira um valor para a data de nascimento: dd/mm/aa ");
    gets(ps->data_nascimento);
    printf("Insira um valor para a cidade: ");
    gets(ps->cidade);
    printf("Insira um valor para o estado: ");
    gets(ps->estado);
    printf("Insira um valor para o CEP: ");
    gets(ps->cep);


   //aqui os dados sao recebidos via teclado
    fwrite(ps, tam,1,p);
    fclose(p);

    cont++;

    p1 = fopen("contador.txt", "w");
    fprintf(p1,"%d",cont);
    fclose(p1);
}

void lista(struct dados *ps, int tam)
{
    FILE *p, *p1;
    FILE *a;
    struct dados info;
    int i;
    int cont,comp;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    printf("%d\n",cont);
    fclose(p1);

    p = fopen("arquivo.txt", "r"); /*r" --> Abre o arquivo apenas para leitura.*/

    if( p== NULL)
        {
        puts("\nERRO\n");
        exit(1);
    }

    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);

    printf("                        \n\n");
    printf("Lista de Usuarios       \n\n");
    printf("***********************\n\n");
    printf("Usuarios inseridos: %d \n\n", cont);
    for(i=0;i<cont; i++){
        comp = i*tam;   //calcula o n. de bytes para posicionar o ponteiro do arquivo

    fseek(p,comp,0);    //posiciona o ponteiro no inicio do registro dentro do arquivo
    fread(ps,sizeof(info),1,p);   //le o registro
    if(ps -> nome[0] != '*'){     //verifica se esta apagado
       printf("\tDados do usuario: \n");
        printf("\tNome:");
        puts(ps->nome);
        printf("\tEndereco:");
        puts(ps->endereco);
        printf("\tData de Nascimento:");
        puts(ps->data_nascimento);
        printf("\tCidade:");
        puts(ps->cidade);
        printf("\tEstado:");
        puts(ps->estado);
        printf("\tCEP:");
        puts(ps->cep);
        printf("\n********************************\n\n");
        }
    }
        fclose(p);
}

int pesquisa(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char nome1[20];
    int i=0,y, x;
    int cont;

    printf("Informe um nome para pesquisa: ");
    gets(nome1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; nome1[x] != '\0';x++){
            if(nome1[x] != ps -> nome[x]){
                break;
            }
        }

    if(nome1[x] == '\0' && ps -> nome[x] == '\0')
    {
        printf("n. do reg.: %d\n",y);
        return y;
    }
    }
    printf("reg. nao existe\n");
    return -1;
}



int pesquisaCEP(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char cep1[20];
    int i=0,y, x;
    int cont;

    printf("Informe um CEP para pesquisa: ");
    gets(cep1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; cep1[x] != '\0';x++){
            printf("FOR");
            if(cep1[x] != ps -> cep[x]){
                printf("FOR1");
                break;
            }
        }

        if(cep1[x] == '\0' && ps -> cep[x] == '\0')
        {
            printf("n. do reg.: %d\n",y);
            printf("\n********************************\n\n");
            printf("\tDados do usuario: \n");
            printf("\tNome:");
            puts(ps->nome);
            printf("\tEndereco:");
            puts(ps->endereco);
            printf("\tData de Nascimento:");
            puts(ps->data_nascimento);
            printf("\tCidade:");
            puts(ps->cidade);
            printf("\tEstado:");
            puts(ps->estado);
            printf("\tCEP:");
            puts(ps->cep);
            printf("\n********************************\n\n");
            return y;
        }
    }
    printf("reg. nao existe\n");
    return -1;
}

int pesquisaNome(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char nome1[20];
    int i=0,y, x;
    int cont;

    printf("Informe um nome para pesquisa: ");
    gets(nome1);
    printf("%s",nome1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; nome1[x] != '\0';x++){
            if(nome1[x] != ps -> nome[x]){
                break;
            }
        }

    if(nome1[x] == '\0' && ps -> nome[x] == '\0')
    {
        printf("n. do reg.: %d\n",y);
        printf("\n********************************\n\n");
        printf("\tDados do usuario: \n");
        printf("\tNome:");
        puts(ps->nome);
        printf("\tEndereco:");
        puts(ps->endereco);
        printf("\tData de Nascimento:");
        puts(ps->data_nascimento);
        printf("\tCidade:");
        puts(ps->cidade);
        printf("\tEstado:");
        puts(ps->estado);
        printf("\tCEP:");
        puts(ps->cep);
        printf("\n********************************\n\n");
        return y;
    }
    }
    printf("%s",nome1);
    printf("%s",ps->nome);
    printf("reg. nao existe\n");
    return -1;
}

int pesquisaAniversario(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char mes1[3];
    int i=0,y, x;
    int cont;
    int count = 0;

    printf("Informe um Mes para pesquisa: ");
    gets(mes1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

    for(y=0;y<cont;y++)
    {

        fread(ps,tam,1,p);

        for(x = 0; x < 3; x++){
            if(mes1[x] == ps -> data_nascimento[x+3])
            {
                count++;

                if(cont = 3){
                printf("x + 3: %d\n", x+3);
                printf("x: %d\n", x);
                printf("n. do reg.: %d\n",y);
                printf("\n********************************\n\n");
                printf("\tDados do usuario: \n");
                printf("\tNome:");
                puts(ps->nome);
                printf("\tEndereco:");
                puts(ps->endereco);
                printf("\tData de Nascimento:");
                puts(ps->data_nascimento);
                printf("\tCidade:");
                puts(ps->cidade);
                printf("\tEstado:");
                puts(ps->estado);
                printf("\tCEP:");
                puts(ps->cep);
                printf("\n********************************\n\n");
                return y;
                }

            }
        }
    }
    printf("reg. nao existe\n");
    return -1;
}

int pesquisaPrimeiraLetra(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char nome1;
    int i=0,y, x;
    int cont;

    printf("Informe uma Letra para pesquisa: ");
    scanf("%c", &nome1);
    getchar();
    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

    for(y = 0; y < cont; y++) //Pesquisa por todos os registros no arquivo
    {
        fread(ps,tam,1,p);

    if(nome1 ==  ps -> nome[0] )
    {
        printf("n. do reg.: %d\n",y);
        printf("\n********************************\n\n");
        printf("\tDados do usuario: \n");
        printf("\tNome:");
        puts(ps->nome);
        printf("\tEndereco:");
        puts(ps->endereco);
        printf("\tData de Nascimento:");
        puts(ps->data_nascimento);
        printf("\tCidade:");
        puts(ps->cidade);
        printf("\tEstado:");
        puts(ps->estado);
        printf("\tCEP:");
        puts(ps->cep);
        printf("\n********************************\n\n");

    }
    else
        {
            printf("reg. nao existe\n");
            return -1;
        }

    }
        return y;
    }


void altera(struct dados *ps, int tam)
{
    FILE *p;
    int n_reg;
    int n_bytes;

    n_reg = pesquisaNome(ps, tam);     //pesquisa o registro no arquivo por Nome
    printf("altera reg n.: %d\n",n_reg);
    if(n_reg == -1){
 	     return;
    }
    n_bytes = tam * n_reg;

    p = fopen("arquivo.txt", "r+");

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser alterado
    fread(ps, tam, 1, p );  //le registro do arquivo

    printf("recebe os dados para alteracao: ");
    //recebe via teclado todos os dados do registro
    inclui(ps, tam);
    fseek(p,n_bytes,0);    //posiciona o ponteiro do arquivo no inicio do regisro a ser alterado
    fwrite(ps, tam,1,p);  //escreve o registro no arquivo

    fclose(p);
}

void exclui(struct dados *ps, int tam)
{
    FILE *p;
    int n_reg;
    int n_bytes;
    n_reg = pesquisaNome(ps, tam);  //pesquisa o registro no arquivo
    if(n_reg == -1){
 	     return;
    }
    p = fopen("arquivo.txt", "r+");
    n_bytes = tam * n_reg;

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser apagado
    fread(ps, tam, 1, p );   //le o registro do arquivo
    printf("nome para apagar e' %s\n",ps -> nome);
    //apaga o registro do arquivo
    ps -> nome[0] = '*';     //Insere um * no inicio da string

    fseek(p,n_bytes,0);  //posiciona o ponteiro do arquivo no inicio do regisro a ser apagado
    fwrite(ps,tam,1,p);  //escreve o registro

    fclose(p);

}


