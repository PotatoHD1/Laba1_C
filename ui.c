//
// Created by korna on 09.03.2021.
//
#include "void_string.c"
#include "ascii_string.c"
#include "unicode_string.c"
#include "utf8_string.c"
#include "tests.c"
#include <stdio.h>
#include <stdlib.h>
const char *MSGS[] = {"0. Quit",
                      "1. Input ASCII string",
                      "2. Input UNICODE string",
                      "3. Input UTF-8 string",
                      "4. Print string",
                      "5. Find b in a",
                      "6. Run tests",
                      "7. Clear error log"};
const char *MSGS1[] = {"0. Quit", "1. String a", "2. String b"};
const char *MSGS2[] = {"0. Quit", "1. With case", "2. Without case"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int Dialog(const char *msgs[], int n) {
  char *error = "";
  int choice = -1;
  do {
    printf("%s", error);
    error = "You're wrong. Try again!\n";
    for (int i = 0; i < n; ++i) {
      printf("%s\n", msgs[i]);
    }
    printf("Make your choice: \n");
    scanf("%d", &choice);
  } while (choice < 0 || choice >= n);
  return choice;
}
char *get_str() {
  printf("Input string:\n");
  scanf("\n");
  int *len = calloc(1, sizeof(int));
  char buf[81] = {0};
  char *res = NULL;
  int n = 0;
  do {
    n = scanf("%80[^\n]", buf);
    if (n < 0) {
      if (!res) {
        return NULL;
      }
    } else if (n > 0) {
      int chunk_len = strlen(buf);
      int str_len = *len + chunk_len;
      res = realloc(res, str_len + 1);
      memcpy(res + *len, buf, chunk_len);
      *len = str_len;
    } else {
      scanf("%*c");
    }
  } while (n > 0);
  if (*len > 0) {
    res[*len] = '\0';
  } else {
    res = calloc(1, sizeof(char));
  }
  free(len);
  return res;
}
void StartUI() {
  char **errorlog = calloc(1, sizeof(char *));
  *errorlog = calloc(1, 1);
  int res = 1;
  voidString *a = NULL;
  voidString *b = NULL;
  typeMetadata *ascii = CreateASCIIMeta(errorlog);
  typeMetadata *utf8 = CreateUTF8Meta(errorlog);
  typeMetadata *unicode = CreateUNICODEMeta(errorlog);
  while (res != 0) {
    res = Dialog(MSGS, MSGS_SIZE);
    switch (res) {
    case 0:
      break;
    case 1:
      char *text = get_str();
      res = Dialog(MSGS1, 3);
      if (res == 1)
        a = CreateFromCharArray(ascii, strlen(text), text, errorlog);
      else if (res == 2)
        b = CreateFromCharArray(ascii, strlen(text), text, errorlog);
      break;
    case 2:
      text = get_str();
      res = Dialog(MSGS1, 3);
      if (res == 1)
        a = CreateFromCharArray(unicode, strlen(text), text, errorlog);
      else if (res == 2)
        b = CreateFromCharArray(unicode, strlen(text), text, errorlog);
      break;
    case 3:
      text = get_str();
      res = Dialog(MSGS1, 3);
      if (res == 1)
        a = CreateFromCharArray(utf8, UTF8GetStrLen(text, errorlog), text,
                                errorlog);
      else if (res == 2)
        b = CreateFromCharArray(utf8, UTF8GetStrLen(text, errorlog), text,
                                errorlog);
      break;
    case 4:
      res = Dialog(MSGS1, 3);
      if (res == 1)
        PrintStr(a, errorlog);
      else if (res == 2)
        PrintStr(b, errorlog);
      break;
    case 5:
      res = Dialog(MSGS2, 3);
      printf("%d\n", StrStr(a, b, res, errorlog));
      break;
    case 6:
      RunAllTests();
      break;
    case 7:
      *errorlog = calloc(1, 1);
      break;
    default:
      printf("How did you end up here?\n");
      break;
    }
    printf("%s\n", *errorlog);
  }
  Delete(&a, errorlog);
  Delete(&b, errorlog);
  free(ascii);
  free(utf8);
  free(unicode);
  free(*errorlog);
  free(errorlog);
}
