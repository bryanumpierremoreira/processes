#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int collatz(int x)
{
    
    printf("x = %d: %d, ", x, x);
    
    while (x != 1) {
        if (x % 2 == 0) {
            x = x / 2;
            
        } else {
            x = (3 * x) + 1;
        }
        printf("%d, ", x);
    }
    printf("\n\n");
    sleep(5);
    
    return 0;
}

int dez(int me, int *valor_collatz)
{
    char texto[256];
    char dezena[256];

    int size_me = sizeof(me);
    sprintf(texto,"%d", me);

    dezena[0] = texto[size_me-2];
    dezena[1] = texto[size_me-1];
    printf("\ncentena funcao: %s\n", dezena);
    int valor;
    int *ptr = &valor;
    valor = atoi(dezena);
    printf("\nvalor inteiro: %d\n\n",valor);

    valor_collatz = ptr;
    return 0;
}

int main()
{
    pid_t newPid, me, parent, x;
    int status;
    int n = 0;
    int valor_collatz = 0;
    char texto[256];

    printf("Digite o range de processos filhos: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("loop: %d\n", i);
        newPid = fork();
    }
    

    me = getpid();
    int size_me = sizeof(me);
    parent = getppid();
    
    // esse print sera mostrado N vezes pq o filho comeca no trecho acima
    printf("\nMeu pid: %d, \tpid pai: %d, \tpid novo: %d\n\n", me, parent, newPid);

    printf("size_of pid: %d eh: %d\n", me, size_me+1);
    //passa o int pra str na variavel texto
    sprintf(texto,"%d", me);
    printf("\ntexto: %s\n\n", texto);
    

    printf("\n");
    if (newPid != 0)
    {
        printf("Esperando filho pid: %d\n", newPid);
        x = waitpid(newPid, &status, -1);
        printf("\n\n-->\t\tFilho %d terminou\n\n", x);
    }
    else
    {
        printf("Sou o filho\n");
        printf("Vou pegar a centena e dezena do id do processo filho\n");
        char dezena[256];

        dezena[0] = texto[size_me-2];
        dezena[1] = texto[size_me-1];
        printf("\ncentena: %s\n", dezena);
        int valor;

        valor = atoi(dezena);
        //printf("\n%d\n\n\n",valor);
        if (valor !=0)
        {
            collatz(valor);
        }
        
        

    }
    
    return 0;
}