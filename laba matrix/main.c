#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.c"
#include "Matrix_complex.c"
#include "Matrix_float.c"



int main() {
//    matrixmeta * matrixmeta_float = init_matrixmeta_float();
//    float * put = calloc(3*3, sizeof(float));
//    put[0] = 3;
//    put[1] = -1;
//    put[2] = 2;
//    put[3] = 4;
//    put[4] = 2;
//    put[5] = 0;
//    put[6] = -5;
//    put[7] = 6;
//    put[8] = 1;
//    Matrix * a = matrixmeta_float->set_from_arr(3, 3, put,matrixmeta_float);
//    put[0] = 8;
//    put[1] = 7;
//    put[2] = 2;
//    //put[3] = 3;
//    //put[4] = 2;
//    //put[5] = 2;
//    Matrix * b = matrixmeta_float->set_from_arr(3, 1, put,matrixmeta_float);
//    a->meta->print(a);
//    printf("\n");
//    a->meta->print(b);
//    printf("\n");
//    Matrix * c = a->meta->mult(a,b);
//    c->meta->print(c);
//
//    Matrix * d = a->meta->trans(a);
//    Matrix * l = a->meta->trans(b);
//    Matrix * k = a->meta->trans(c);
//
//    printf("\n");
//    a->meta->print(d);
//    printf("\n");
//    a->meta->print(l);
//    printf("\n");
//    a->meta->print(k);
    matrixmeta * matrixmeta_complex = init_matrixmeta_complex();
    complex * put = calloc(2*2, sizeof(complex));
    put[0].real = 1;
    put[0].imag = 1;
    put[1].real = 2;
    put[1].imag = 2;
    put[2].real = 3;
    put[2].imag = 3;
    put[3].real = 4;
    put[3].imag = 4;
    Matrix * a = matrixmeta_complex->set_from_arr(2, 2, put,matrixmeta_complex);
    put[0].real = 1;
    put[0].imag = 2;
    put[1].real = 3;
    put[1].imag = 4;
    //put[3] = 3;
    //put[4] = 2;
    //put[5] = 2;
    Matrix * b = matrixmeta_complex->set_from_arr(2, 1, put,matrixmeta_complex);
    a->meta->print(a);
    printf("\n");
    a->meta->print(b);
    printf("\n");
    Matrix * c = a->meta->mult(a,b);
    c->meta->print(c);

    Matrix * d = a->meta->trans(a);
    Matrix * l = a->meta->trans(b);
    Matrix * k = a->meta->trans(c);

    printf("\n");
    a->meta->print(d);
    printf("\n");
    a->meta->print(l);
    printf("\n");
    a->meta->print(k);
















    free(put);
    a->meta->delete(a);
    b->meta->delete(b);
    c->meta->delete(c);
    d->meta->delete(d);
    l->meta->delete(l);
    k->meta->delete(k);
    free(matrixmeta_complex);

    return 0;
}
