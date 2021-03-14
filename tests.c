//
// Created by korna on 09.03.2021.
//
void PrintRes(float testsCount, float passTestsCount) {
  if (testsCount > 0)
    printf("All tests count: %f\nAll passed tests count: %f\nPassed tests "
           "percentage: %f\n\n",
           testsCount, passTestsCount, passTestsCount / testsCount);
}

void ConcatTests(float *testsCount, float *passTestsCount) {
  float localTestsCount = 0;
  float localPassTestsCount = 0;
  char **errorlog = calloc(1, sizeof(char *));
  *errorlog = calloc(1, 1);
  typeMetadata *ascii = CreateASCIIMeta(errorlog);
  typeMetadata *utf8 = CreateUTF8Meta(errorlog);
  typeMetadata *unicode = CreateUNICODEMeta(errorlog);
  ascii->SetLocale(errorlog);
  char input1[] = "Some input text\n";
  char input2[] = "Some another input text\n";
  voidString *a = CreateFromCharArray(ascii, strlen(input1), input1, errorlog);
  voidString *b = CreateFromCharArray(ascii, strlen(input2), input2, errorlog);
  voidString *c = Concat(a, b, errorlog);
  localTestsCount++;
  char res1[] = "Some input text\nSome another input text\n";
  if (strcmp((char *)c->data, res1) == 0) {
    localPassTestsCount++;
    printf("Pass\n");
  }
  Delete(a, errorlog);
  Delete(b, errorlog);
  Delete(c, errorlog);
  unicode->SetLocale(errorlog);
  char input3[] = "Немного входного текста\n";
  char input4[] = "Ещё немного входного текста\n";
  a = CreateFromCharArray(unicode, strlen(input3), input3, errorlog);
  b = CreateFromCharArray(unicode, strlen(input4), input4, errorlog);
  c = Concat(a, b, errorlog);
  localTestsCount++;
  char res2[] = "Немного входного текста\nЕщё немного входного текста\n";
  if (strcmp((char *)c->data, res2) == 0) {
    localPassTestsCount++;
    printf("Pass\n");
  }
  Delete(a, errorlog);
  Delete(b, errorlog);
  Delete(c, errorlog);
  utf8->SetLocale(errorlog);
  char input5[] = "Н\0\0е\0\0м\0\0н\0\0о\0\0г\0\0о\0\0 "
                  "\0\0\0в\0\0х\0\0о\0\0д\0\0н\0\0о\0\0г\0\0о\0\0 "
                  "\0\0\0т\0\0е\0\0к\0\0с\0\0т\0\0а\0\0\n\0\0\0";
  char input6[] = "Е\0\0щ\0\0ё\0 н\0\0е\0\0м\0\0н\0\0о\0\0г\0\0о\0\0 "
                  "\0\0\0в\0\0х\0\0о\0\0д\0\0н\0\0о\0\0г\0\0о\0\0 "
                  "\0\0\0т\0\0е\0\0к\0\0с\0\0т\0\0а\0\0\n\0\0\0";
  a = CreateFromCharArray(utf8, strlen(input3), input5, errorlog);
  b = CreateFromCharArray(utf8, strlen(input4), input6, errorlog);
  c = Concat(a, b, errorlog);
  localTestsCount++;
  char res3[] = "Н\0\0е\0\0м\0\0н\0\0о\0\0г\0\0о\0\0 "
                "\0\0\0в\0\0х\0\0о\0\0д\0\0н\0\0о\0\0г\0\0о\0\0 "
                "\0\0\0т\0\0е\0\0к\0\0с\0\0т\0\0а\0\0\n\0\0\0Е\0\0щ\0\0ё\0 "
                "н\0\0е\0\0м\0\0н\0\0о\0\0г\0\0о\0\0 "
                "\0\0\0в\0\0х\0\0о\0\0д\0\0н\0\0о\0\0г\0\0о\0\0 "
                "\0\0\0т\0\0е\0\0к\0\0с\0\0т\0\0а\0\0\n\0\0\0";
  if (strcmp((char *)c->data, res3) == 0) {
    localPassTestsCount++;
    printf("Pass\n");
  }
  Delete(a, errorlog);
  Delete(b, errorlog);
  Delete(c, errorlog);
  free(ascii);
  free(utf8);
  free(unicode);
  free(*errorlog);
  free(errorlog);
  printf("ConcatTests:\n");
  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
}

void SubStrTests(float *testsCount, float *passTestsCount) {
  float localTestsCount = 0;
  float localPassTestsCount = 0;
  char **errorlog = calloc(1, sizeof(char *));
  *errorlog = calloc(1, 1);
  typeMetadata *ascii = CreateASCIIMeta(errorlog);
  typeMetadata *utf8 = CreateUTF8Meta(errorlog);
  typeMetadata *unicode = CreateUNICODEMeta(errorlog);
  ascii->SetLocale(errorlog);
  char input1[] = "1234567890";
  voidString *a = CreateFromCharArray(ascii, strlen(input1), input1, errorlog);
  voidString *b = Substring(3, 5, a, errorlog);
  localTestsCount++;
  char res1[] = "456";
  if (strcmp((char *)b->data, res1) == 0) {
    localPassTestsCount++;
    printf("Pass\n");
  }
  Delete(a, errorlog);
  Delete(b, errorlog);
  unicode->SetLocale(errorlog);
  char input2[] = "1234567890";
  a = CreateFromCharArray(unicode, strlen(input2), input2, errorlog);
  b = Substring(3, 5, a, errorlog);
  localTestsCount++;
  char res2[] = "456";
  if (strcmp((char *)b->data, res2) == 0) {
    localPassTestsCount++;
    printf("Pass\n");
  }
  Delete(a, errorlog);
  Delete(b, errorlog);
  utf8->SetLocale(errorlog);
  char input3[] = "й\0\0ц\0\0у\0\0к\0\0е\0\0н\0\0г\0\0";
  a = CreateFromCharArray(utf8, strlen(input2), input3, errorlog);
  b = Substring(3, 5, a, errorlog);
  localTestsCount++;
  char res3[] = "к\0\0е\0\0н\0\0";
  if (strcmp((char *)b->data, res3) == 0) {
    localPassTestsCount++;
    printf("Pass\n");
  }
  Delete(a, errorlog);
  Delete(b, errorlog);
  free(ascii);
  free(utf8);
  free(unicode);
  free(*errorlog);
  free(errorlog);
  printf("SubStrTests:\n");
  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
}

void RecodeTests(float *testsCount, float *passTestsCount) {
  float localTestsCount = 0;
  float localPassTestsCount = 0;

  printf("RecodeTests:\n");
  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
}

void ReadTests(float *testsCount, float *passTestsCount) {
  float localTestsCount = 0;
  float localPassTestsCount = 0;

  printf("ReadTests:\n");
  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
}

void WriteTests(float *testsCount, float *passTestsCount) {
  float localTestsCount = 0;
  float localPassTestsCount = 0;

  printf("WriteTests:\n");
  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
}

void ErrorsTests(float *testsCount, float *passTestsCount) {
  float localTestsCount = 0;
  float localPassTestsCount = 0;

  printf("ErrorsTests:\n");
  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
}

void RunAllTests() {
  float testsCount = 0;
  float passTestsCount = 0;
  ConcatTests(&testsCount, &passTestsCount);
  SubStrTests(&testsCount, &passTestsCount);
  RecodeTests(&testsCount, &passTestsCount);
  ReadTests(&testsCount, &passTestsCount);
  WriteTests(&testsCount, &passTestsCount);
  ErrorsTests(&testsCount, &passTestsCount);
  printf("Total:\n");
  PrintRes(testsCount, passTestsCount);
}