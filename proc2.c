#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int sum(int *v1, int *v2, int len)
{
    int soma[len];
    printf("Calculando a soma dos numeros: \n\n");

    for (int i=0;i<len;i++){
        soma[i] = v1[i] + v2[i];
        printf("\t\t%d + %d = %d\n", v1[i], v2[i], soma[i]);
        sleep(2);
    }
    printf("\tVetor final: \t\t");
    for (int i=0;i<len;i++){
        printf("%d ", soma[i]);
    }
    printf("\n\n");
    return 0;
}

int subtraction(int *v1, int *v2, int len)
{
    int soma[len];
    printf("Calculando a subtracao dos numeros: \n\n");

    for (int i=0;i<len;i++){
        soma[i] = v1[i] - v2[i];
        printf("\t\t%d - %d = %d\n", v1[i], v2[i], soma[i]);
        sleep(2);
    }
    printf("\tVetor final: \t\t");
    for (int i=0;i<len;i++){
        printf("%d ", soma[i]);
    }
    printf("\n\n");
    return 0;
}

int multiplying(int *v1, int *v2, int len)
{
    int soma[len];
    printf("Calculando a multiplicacao dos numeros: \n\n");

    for (int i=0;i<len;i++){
        soma[i] = v1[i] * v2[i];
        printf("\t\t%d x %d = %d\n", v1[i], v2[i], soma[i]);
        sleep(2);
    }
    printf("\tVetor final: \t\t");
    for (int i=0;i<len;i++){
        printf("%d ", soma[i]);
    }
    printf("\n\n");
    return 0;
}

int getVec(int *arr1, int *arr2, int len)
{   
    //int arr1[len], arr2[len];
    printf("O seu vetor vai ter %d posicoes\n", len);

    for (int i=0;i<len;i++){
        arr1[i] = rand() % 1000;
        arr2[i] = rand() % 1000;

    }
    printf("Seu vetor 1 eh:\t\t");
    for (int i=0;i<len;i++){
        printf("%d ", arr1[i]);

    }
    printf("\n");
    printf("Seu vetor 2 eh:\t\t");
    for (int i=0;i<len;i++){
        printf("%d ", arr2[i]);

    }
    printf("\n");

    return 0;
}

int copyArray(int *arr_copy, int arr_orig[], int len) {
    for (int i=0; i<len; i++){
        arr_copy[i] = arr_orig[i]; 
    }
}


int main() {
    // var type pid_t
    pid_t newPid, me, parent, x;
    int status;
    int n;
    newPid = fork();

    me = getpid();
    parent = getppid();
    
    // esse print sera mostrado duas vezes pq o filho comeca na linha acima
    printf("Meu pid: %d, \tpid pai: %d, \tpid novo: %d\n\n", me, parent, newPid);

    if (newPid != 0) 
    {
        if (newPid % 2 == 0)
        {
            printf("Esperando filho pid: %d\n", newPid);
            x = waitpid(newPid, &status, 0);
            printf("\n\n-->\t\tFilho %d terminou\n", x);    
        } else {
            printf("\n\n-->\t\tPai %d terminou\n\n", me);
        }
        
    }
    else
    {
        printf("Sou o filho\n");
        printf("Digite o range dos vetores: ");
        scanf("%d", &n);
        // cria os vetores de n posicoes
        int arr1[n], arr2[n];
        getVec(arr1, arr2, n);
        
        if (parent % 2 == 0 && me % 2 == 0)
        {
            printf("\nPai e filho pares\n");
            multiplying(arr1,arr2,n);
        } else if (parent % 2 != 0 && me % 2 != 0)
        {
            printf("\nPai e filho impares --> diminuir\n");
            subtraction(arr1,arr2,n);
        } else if (parent % 2 != 0 && me % 2 == 0)
        {
            printf("\nPai impar e filho par --> somar\n");
            sum(arr1,arr2,n);
        } else if (parent % 2 == 0 && me % 2 != 0)
        {
            int arr1_sub[n], arr1_sum[n]; // eh pra somar o resultado ou valor inicial?
            int arr2_sub[n], arr2_sum[n];
            copyArray(arr1_sub, arr1, n);
            copyArray(arr1_sum, arr1, n);
            copyArray(arr2_sub, arr2, n);
            copyArray(arr2_sum, arr2, n);

            printf("\nPai par e filho impar --> multiplicar, diminuir e somar\n");
            multiplying(arr1,arr2,n);
            subtraction(arr1_sub,arr2,n);
            sum(arr1_sum,arr2,n);
        }
        

        sleep(5);

    }

    
    return 0;
}