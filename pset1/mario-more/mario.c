#include <cs50.h>
#include <stdio.h>


void makePyramid(int n);

int main(void)
{
    int rows;
    do
    {
        rows = get_int("How many rows do you want the pyramid to be? ");
    }
    while(rows < 1 || rows > 8);

    makePyramid(rows);
}

void makePyramid(int n)
{
    for(int rows = 0; rows < n; rows++)
    {
        for(int space = n; space > rows + 1; space--)
        {
            printf(" ");
        }

        for(int cols = 0; cols < rows + 1; cols++)
        {
            printf("#");
        }

        printf("  ");

        for(int cols = 0; cols < rows + 1; cols++)
        {
            printf("#");
        }
        printf("\n");
    }
}

