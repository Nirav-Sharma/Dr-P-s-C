#include <stdio.h>
#include <stdlib.h>
 
 
int main(){
    FILE *p; 
    p = fopen("Elephant seal weights.txt", "r");

    int Array[1000];
    int i;
    double sum=0.0;

    for (i = 0; i < 1000; i++)
    {
        fscanf(p, "%d", &Array[i] ); 
        sum = sum + Array[i];
    }
        printf("The average weight is %lf",sum/1000);

        fclose(p);
        return 0;
}
