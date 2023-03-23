#include <cs50.h>
#include <stdio.h>

int main(void)
{

int height, counter, j, k=0;

do
{
    height = get_int("Height: ");
}
while ((height >= 9) || (height <=0));
    {
    }
    for(counter = 1; counter <= height; counter++)
    {
    for(j = 1; j <= height - counter; j++)
    {
        printf(" ");
        }

    for(k = 1; k <= counter; k++)
    {
        printf("#");
    }

    printf("  ");
    for(j = 1; j <= counter; j++)
    {
        printf("#");
    }
    printf("\n");
    }

}
