#include <cs50.h>
#include <math.h>
#include <stdio.h>

int get_cents(void) {
  int cents = -1;

  do {
    cents = get_int("How many cents are owed? ");
  } while (cents < 0);

  return cents;
}

int calculate_quarters(int cents) {

  int quarters_quantity = floor(cents / 25);

  return quarters_quantity;
};

int calculate_dimes(int cents) {

  int dimes_quantity = floor(cents / 10);

  return dimes_quantity;
}
int calculate_nickels(int cents) {

  int nickels_quantity = floor(cents / 5);

  return nickels_quantity;
}
int calculate_pennies(int cents) {

  int pennies_quantity = floor(cents / 1);

  return pennies_quantity;
}

int main(void) {
  // Ask how many cents the customer is owed
  int cents = get_cents();

  // Calculate the number of quarters to give the customer
  int quarters = calculate_quarters(cents);

  cents = cents - quarters * 25;

  // // Calculate the number of dimes to give the customer
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
  printf("The customer will receive an amont of %i coins.\n", coins);
}
