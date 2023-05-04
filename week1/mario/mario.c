#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_blank_spaces(n) {
  // print spaces
  int blank_spaces_count = n;

  if (n == 1) {
    return;
  } else {
    do {
      printf(" ");
      blank_spaces_count--;
    } while (blank_spaces_count > 1);
  }
}

void print_blocks(n) {
  // print blocks
  int blocks_count = n;
  do {
    printf("#");
    blocks_count--;
  } while (blocks_count > 0);
}

void print_pyramid(height) {
  int lines_to_print = height;
  int printing_line = 1;

  // loop to print pyramid
  do {
    print_blank_spaces(lines_to_print);
    print_blocks(printing_line);
    print_blank_spaces(3);
    print_blocks(printing_line);
    printf("\n");

    lines_to_print--;
    printing_line++;

  } while (lines_to_print > 0);
}

int getHeight() {
  int height;
  do {
    height = get_int("Height: ");
  } while (height > 8 || height <= 0);

  return height;
}

int main(void) {
  int height_of_pyramid = getHeight();

  print_pyramid(height_of_pyramid);

  exit(0);
}
