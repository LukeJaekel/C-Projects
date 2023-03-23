#include <cs50.h>
#include <stdio.h>

int main(void)
{

long number;
int second_to_last, count=0;

//Prompt user until a number is entered

do
{
    number = get_long("Enter Card Number: ");
}
while(number <= 0);

long CC = number;
long divide = 10;

//Calculation 1 (count every second number starting with second-to-last digit)

    int sum;

while(CC > 0)
{
    int lastdigit = CC % 10;
    sum = sum + lastdigit;
        CC = CC / 100;
}

//Calculation 2 (Multiply the count by 2)

CC = number / 10;
while(CC > 0)
{
    int lastdigit = CC % 10;
    int timestwo = lastdigit * 2;
    sum = sum + (timestwo % 10) + (timestwo / 10);
        CC = CC / 100;
}

CC = number;
while(CC != 0)
{
        CC = CC / 10;
    count++;
}

for(int i = 0; i < count - 2; i++)
{
    divide = divide * 10;
}

int firstdigit = number / divide;
int firsttwo = number / (divide / 10);

//Card Type Check

if(sum % 10 == 0)
{
    if(firstdigit == 4 && (count == 13 || count == 16))
    {
        printf("VISA\n");
    }
    else if((firsttwo == 34 || firsttwo == 37) && count == 15)
    {
        printf("AMEX\n");
    }
    else if(count == 16 && (firsttwo > 50 && firsttwo < 56))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
else
{
    printf("INVALID\n");
}

}


//American Express - Contain 15 digits and start with 34 or 37
//Mastercard - Contain 16 digits and start with 51, 52, 53, 54 or 55
//Visa - Contain 13 or 16 digits and start with 4
