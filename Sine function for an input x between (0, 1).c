#include<stdio.h>
#include<math.h>

int main (void)
{
    double x, y;
    printf("\nEnter a value between 0 and 1: ");
    scanf("%lf", &x);
    
    if(x > 0 && x < 1) {
    y = sin(x);
    printf("\nSine of %lf is: %.6lf", x, y);
    }
    else {printf("\nInput should be between 0 and 1.");}
    return 0;
}
