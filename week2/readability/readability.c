#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int isLetter(char character) {
  if (character < 91 && character > 64) {
    return 1;
  }

  return 0;
}

int isDotExclamationOrQuestion(char character) {
  if (character == 63 || character == 33 || character == 46) {
    return 1;
  }

  return 0;
}

int computeColemanLiau(int words, int letters, int sentences) {
  float colemanLiau = 0.0588 * (float)letters / (float)words * 100 -
                      0.296 * (float)sentences / (float)words * 100 - 15.8;

  if (ceilf(colemanLiau) < 1) {
    return printf("Before Grade 1\n");
  }
  if (ceilf(colemanLiau) > 16) {
    return printf("Grade 16+\n");
  }

  return printf("Grade %i\n", (int)round(colemanLiau));
  ;
}

int main(void) {

  int words = 0;
  int letters = 0;
  int sentences = 0;
  string inputText = get_string("Text: ");
  int inputLength = strlen(inputText);

  if (!inputText || inputLength < 2) {
    inputText = get_string("Text: ");
  }

  for (int i = 0, isLastPunctuation = 0, isLastSpace = 0; i < inputLength;
       i++) {
    char normalizedCharAscii = (int)toupper(inputText[i]);

    if (isDotExclamationOrQuestion(inputText[i])) {
      sentences += 1;
      words += 1;
      isLastPunctuation = 1;
      isLastSpace = 0;
    }

    if (!isLastPunctuation && !isLastSpace && inputText[i] == 32) // SPACE ASCII
    {
      words += 1;
      isLastSpace = 1;
    }

    if (inputText[i] == 44) // COMMA ASCII
    {
      words += 1;
      isLastPunctuation = 1;
      isLastSpace = 0;
    }

    if (isLetter(normalizedCharAscii)) {
      letters += 1;
      isLastPunctuation = 0;
      isLastSpace = 0;
    }
  }

  computeColemanLiau(words, letters, sentences);
}
