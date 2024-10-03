#include<stdio.h>

int main(void)
{ 
    float PI = 3.14159;
    int radius;
    printf("Enter radius:");
    scanf("%d", &radius);
    float volume =  4 *PI *radius*radius*radius/3;
    printf("volume is : %f \n\n", volume);
return 0;
}