//
// Created by korna on 09.03.2021.
//
void PrintRes(float testsCount, float passTestsCount) {
  if (testsCount > 0)
    printf("All tests count: %.0f\nAll passed tests count: %.0f\nPassed tests "
           "percentage: %.2f%%\n\n",
           testsCount, passTestsCount, passTestsCount / testsCount * 100);
}

void ConcatTests(float *testsCount, float *passTestsCount, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "ConcatTests");
  printf("ConcatTests:\n");
  float localTestsCount = 0;
  float localPassTestsCount = 0;
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
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
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
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);
  Delete(c, errorlog);
  utf8->SetLocale(errorlog);
  char input5[] = "Немного входного текста\n";
  char input6[] = "Ещё немного входного текста\n";
  a = CreateFromCharArray(utf8, strlen(input5), input5, errorlog);
  b = CreateFromCharArray(utf8, strlen(input6), input6, errorlog);
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
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);
  Delete(c, errorlog);
  free(ascii);
  free(utf8);
  free(unicode);
  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
  RemoveFromLog(errorlog);
}

void SubStrTests(float *testsCount, float *passTestsCount, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "SubStrTests");
  printf("SubStrTests:\n");
  float localTestsCount = 0;
  float localPassTestsCount = 0;
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
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
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
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);
  utf8->SetLocale(errorlog);
  char input3[] = "йцукен";
  a = CreateFromCharArray(utf8, strlen(input3), input3, errorlog);
  b = Substring(3, 5, a, errorlog);
  localTestsCount++;

  char res3[] = "кен";
  voidString *c =
      CreateFromCharArray(utf8, UTF8GetStrLen(res3, errorlog), res3, errorlog);
  if (StrIsEqual(b, c, errorlog)) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);
  Delete(c, errorlog);
  free(ascii);
  free(utf8);
  free(unicode);
  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
  RemoveFromLog(errorlog);
}

void RecodeTests(float *testsCount, float *passTestsCount, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "RecodeTests");
  printf("RecodeTests:\n");
  float localTestsCount = 0;
  float localPassTestsCount = 0;
  typeMetadata *ascii = CreateASCIIMeta(errorlog);
  typeMetadata *utf8 = CreateUTF8Meta(errorlog);
  typeMetadata *unicode = CreateUNICODEMeta(errorlog);
  ascii->SetLocale(errorlog);
  char input1[] = "1234567890";
  voidString *a = CreateFromCharArray(ascii, strlen(input1), input1, errorlog);
  voidString *b = Recode(a->typeMeta->ToUTF8, a, utf8, errorlog);
  localTestsCount++;
  char res1[] = "1234567890";
  voidString *c = CreateFromCharArray(utf8, strlen(res1), res1, errorlog);
  if (StrIsEqual(b, c, errorlog)) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);

  Delete(a, errorlog);
  Delete(b, errorlog);
  Delete(c, errorlog);
  a = CreateFromCharArray(ascii, strlen(input1), input1, errorlog);
  b = Recode(a->typeMeta->ToUNICODE, a, unicode, errorlog);
  localTestsCount++;
  c = CreateFromCharArray(unicode, strlen(res1), res1, errorlog);
  if (StrIsEqual(b, c, errorlog)) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);

  Delete(a, errorlog);
  Delete(b, errorlog);
  Delete(c, errorlog);

  a = CreateFromCharArray(ascii, strlen(input1), input1, errorlog);
  b = Recode(a->typeMeta->ToASCII, a, ascii, errorlog);
  localTestsCount++;
  if (StrIsEqual(a, b, errorlog)) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);
  a = CreateFromCharArray(unicode, strlen(input1), input1, errorlog);
  b = Recode(a->typeMeta->ToUTF8, a, utf8, errorlog);

  localTestsCount++;

  c = CreateFromCharArray(utf8, strlen(res1), res1, errorlog);
  if (StrIsEqual(c, b, errorlog)) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);
  Delete(c, errorlog);
  free(ascii);
  free(utf8);
  free(unicode);
  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
  RemoveFromLog(errorlog);
}

void StrStrTests(float *testsCount, float *passTestsCount, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "StrStrTests");
  printf("StrStrTests:\n");
  float localTestsCount = 0;
  float localPassTestsCount = 0;
  typeMetadata *ascii = CreateASCIIMeta(errorlog);
  typeMetadata *utf8 = CreateUTF8Meta(errorlog);
  typeMetadata *unicode = CreateUNICODEMeta(errorlog);
  ascii->SetLocale(errorlog);
  char input1[] = "12354123412345";
  char input2[] = "1234";
  voidString *a = CreateFromCharArray(ascii, strlen(input1), input1, errorlog);
  voidString *b = CreateFromCharArray(ascii, strlen(input2), input2, errorlog);
  localTestsCount++;
  int res1 = 5;
  if (StrStr(a, b, false, errorlog) == res1) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);
  char input3[] = "abcedAbcdabcde";
  char input4[] = "abcd";
  a = CreateFromCharArray(ascii, strlen(input3), input3, errorlog);
  b = CreateFromCharArray(ascii, strlen(input4), input4, errorlog);
  localTestsCount++;
  int res2 = 9;
  if (StrStr(a, b, false, errorlog) == res2) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);

  localTestsCount++;
  if (StrStr(a, b, true, errorlog) == res1) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);
  a = CreateFromCharArray(unicode, strlen(input3), input3, errorlog);
  b = CreateFromCharArray(unicode, strlen(input4), input4, errorlog);
  localTestsCount++;
  if (StrStr(a, b, false, errorlog) == res2) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);

  localTestsCount++;
  if (StrStr(a, b, true, errorlog) == res1) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);
  utf8->SetLocale(errorlog);
  a = CreateFromCharArray(utf8, strlen(input3), input3, errorlog);
  b = CreateFromCharArray(utf8, strlen(input4), input4, errorlog);
  localTestsCount++;
  if (StrStr(a, b, false, errorlog) == res2) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);

  localTestsCount++;
  if (StrStr(a, b, true, errorlog) == res1) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);

  free(ascii);
  free(utf8);
  free(unicode);
  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
  RemoveFromLog(errorlog);
}
void ErrorsTests(float *testsCount, float *passTestsCount) {
  char **errorlog = calloc(1, sizeof(char *));
  *errorlog = calloc(1, 1);
  AddToLog(errorlog, "ErrorsTests");
  printf("ErrorsTests:\n");
  float localTestsCount = 0;
  float localPassTestsCount = 0;
  typeMetadata *ascii = CreateASCIIMeta(errorlog);
  typeMetadata *utf8 = CreateUTF8Meta(errorlog);
  typeMetadata *unicode = CreateUNICODEMeta(errorlog);
  char input1[] = "12354123412345";
  char input2[] = "1234";
  utf8->SetLocale(errorlog);
  voidString *a = CreateFromCharArray(NULL, strlen(input1), input1, errorlog);
  voidString *b = CreateFromCharArray(utf8, strlen(input2), input2, errorlog);
  printf("%s\n", *errorlog);
  localTestsCount++;
  if (IsLogError(errorlog)) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  *errorlog = calloc(1, 1);
  AddToLog(errorlog, "ErrorsTests");
  Delete(a, errorlog);
  Delete(b, errorlog);

  utf8->Lower = NULL;
  a = CreateFromCharArray(utf8, strlen(input1), input1, errorlog);
  b = CreateFromCharArray(utf8, strlen(input2), input2, errorlog);
  printf("%s\n", *errorlog);
  localTestsCount++;
  if (IsLogError(errorlog)) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  *errorlog = calloc(1, 1);
  AddToLog(errorlog, "ErrorsTests");
  Delete(a, errorlog);
  Delete(b, errorlog);
  free(utf8);
  utf8 = CreateUTF8Meta(errorlog);
  char input3[] = "12354123412345";
  char input4[] = "";
  a = CreateFromCharArray(utf8, strlen(input3), input3, errorlog);
  b = CreateFromCharArray(utf8, strlen(input4), input4, errorlog);
  voidString *c = Concat(a, b, errorlog);
  localTestsCount++;
  if (c->len == a->len) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(b, errorlog);
  Delete(c, errorlog);
  b = Recode(a->typeMeta->ToASCII, a, ascii, errorlog);
  printf("%s\n", *errorlog);
  localTestsCount++;
  if (IsLogError(errorlog)) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  *errorlog = calloc(1, 1);
  AddToLog(errorlog, "ErrorsTests");
  localTestsCount++;
  if (IsLogError(errorlog)) {
    localPassTestsCount++;
    printf("Pass test %.0f\n", localTestsCount);
  } else
    printf("Fail test %.0f\n", localTestsCount);
  Delete(a, errorlog);
  Delete(b, errorlog);
  free(ascii);
  free(utf8);
  free(unicode);

  PrintRes(localTestsCount, localPassTestsCount);
  *testsCount += localTestsCount;
  *passTestsCount += localPassTestsCount;
  RemoveFromLog(errorlog);
}
void RunAllTests() {
  char **errorlog = calloc(1, sizeof(char *));
  *errorlog = calloc(1, 1);
  AddToLog(errorlog, "RunAllTests");
  float testsCount = 0;
  float passTestsCount = 0;
  ConcatTests(&testsCount, &passTestsCount, errorlog);
  SubStrTests(&testsCount, &passTestsCount, errorlog);
  RecodeTests(&testsCount, &passTestsCount, errorlog);
  StrStrTests(&testsCount, &passTestsCount, errorlog);
  ErrorsTests(&testsCount, &passTestsCount);
  printf("Total:\n");
  PrintRes(testsCount, passTestsCount);
  RemoveFromLog(errorlog);
  printf("%s", *errorlog);
  free(*errorlog);
  free(errorlog);
}