#include <stdio.h>
#include <math.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);
float cents;

int main(void)
{
    // Ask how many cents the customer is owed
    get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    do
    {
        printf("\nQauntos centavos?");
        scanf("%f", &cents);
    } while (cents < 0);
    return cents;
}

int calculate_quarters(int cents)
{
    resumindo(25,cents);
}

int calculate_dimes(int cents)
{
    resumindo(10,cents);
}

int calculate_nickels(int cents)
{
    resumindo(5,cents);
}

int calculate_pennies(int cents)
{
    resumindo(1,cents);
}

int resumindo(int type, int cents){
    if(cents/type>1){
        return floor(cents/type);
    }
    else if(cents/type==1){
        return 1;
    }
    else{
        return 0;
    }
}