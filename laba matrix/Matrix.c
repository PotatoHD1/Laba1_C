#include "Matrix.h"
#include <assert.h>
#include <string.h>

Matrix *init(int height, int width, matrixmeta *meta) {
    Matrix *res = calloc(1, sizeof(Matrix));
    res->width = width;
    res->height = height;
    res->meta = meta;
    res->data = calloc(width * height, meta->type_m->size);
    return res;
}

void delete(Matrix *this) {
    free(this->data);
    free(this);
}

void *get_ij(int i, int j, Matrix *this) {
    assert(i >= 0 && i < this->height && "Impossible");
    assert(j >= 0 && j < this->width && "Impossible");
    return (char *) (this->data) + this->meta->type_m->size * (i * this->width + j);
}

void print(Matrix *this) {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (j != 0)printf(" ");
            this->meta->type_m->print_EL(get_ij(i, j, this));
        }
        printf("\n");
    }

}

Matrix *sum(Matrix *a, Matrix *b) {
    Matrix *res = init(a->height, a->width, a->meta);
    for (int i = 0; i < a->height; i++) {
        for (int j = 0; j < a->width; j++) {
            void *temp = a->meta->type_m->sum(get_ij(i, j, a), get_ij(i, j, b));
            memcpy(get_ij(i, j, res), temp, a->meta->type_m->size);

            free(temp);

        }
    }
    return res;
}

Matrix *mult(Matrix *a, Matrix *b) {
    assert(a->width == b->height);
    Matrix *res = init(a->height, b->width, b->meta);
    for (int i = 0; i < res->height; i++) {
        for (int j = 0; j < res->width; j++) {
            for (int r = 0; r < b->height; r++) {
                void *temp = a->meta->type_m->mult(get_ij(i, r, a), get_ij(r, j, b));
                void *temp1 = a->meta->type_m->sum(get_ij(i, j, res), temp);
                memcpy(get_ij(i, j, res), temp1, a->meta->type_m->size);
                free(temp);
                free(temp1);
//                *((int*)res2->pObject + (i*height) + j) += (*((int*)a->pObject + (i*height) + r)) * (*((int*)b->pObject + (r*height) + j));
            }
        }
    }
    return res;
}


Matrix *trans(Matrix *this) {
    Matrix *res = init(this->width, this->height, this->meta);


    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {

            memcpy(get_ij(j, i, res), get_ij(i, j, this), this->meta->type_m->size);
        }
    }
    return res;

}

void set_ij(int i, int j,void *data, Matrix *this){
    assert(i >= 0 && i < this->height && "Impossible");
    assert(j >= 0 && j < this->width && "Impossible");
    memcpy(get_ij(i, j, this), data, this->meta->type_m->size);

}

Matrix *init_from_arr(int height, int width, void * data, matrixmeta *meta){
    Matrix *res = init(height, width, meta);
    memcpy(res->data, data, width * height * meta->type_m->size);
    return res;
}



