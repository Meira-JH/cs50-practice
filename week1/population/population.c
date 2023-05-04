#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int calculate_years_for_growth(int start_size, int end_size) {

  int population_size = start_size;
  int year_count = 0;

  // double years_for_end_size = ((double)end_size - (double)start_size) /
  // (llamas_growth_per_year - llamas_loss_per_year);

  do {
    int llamas_growth_per_year = floor(population_size / 3);
    int llamas_loss_per_year = floor(population_size / 4);
    population_size =
        population_size + llamas_growth_per_year - llamas_loss_per_year;
    year_count++;
  } while (population_size < end_size);

  if (year_count < 1) {
    return 1;
  } else {
    return ceil(year_count);
  }
}

int main(void) {
  // TODO: Prompt for start size
  int population_start_size;
  do {
    population_start_size = get_int("Start size: ");

  } while (population_start_size < 9);

  // TODO: Prompt for end size
  int population_end_size;
  do {
    population_end_size = get_int("End size: ");

  } while (population_end_size < population_start_size);

  if (population_end_size == population_start_size) {
    printf("Years: 0 \n");
    exit(0);
  }

  printf("Years: %i \n", calculate_years_for_growth(population_start_size,
                                                    population_end_size));
}
