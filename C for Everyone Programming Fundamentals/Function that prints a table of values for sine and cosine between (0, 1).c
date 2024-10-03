#include<stdio.h>
#include<math.h> 
int main(void)
{ 
double interval;
int i;
printf("   Value  |    sin   |   cos\n"); /*Header*/
for(i = 0; i < 11; i++) /*Iteration adding to value*/
{
 interval = i/10.0; /*Value*/
 double y = sin (interval); /*sin of value*/
 double z = cos (interval); /*cos of value*/
 printf(" %lf | %lf | %lf \n", interval, y, z);
}



printf("\n+++++++\n");
return 0;
}
