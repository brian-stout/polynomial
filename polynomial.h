#ifndef POLYNOMINAL_H
#define POLYNOMINAL_H

#define _GNU_SOURCE //Used for asprintf function
                    //Should create a modified snprintf for portability later
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct term {
    int coeff;
    unsigned int exp;
    struct term *next;
};

typedef struct term polynomial;

//WARNING: Watch when subtracting equal coefficients
struct term *term_create(int coeff, int exp);
void poly_destroy(polynomial *eqn);
void poly_add_term(polynomial **front, polynomial *newTerm);
void poly_print(const polynomial *eqn);
char *poly_to_string(const polynomial *p);
polynomial *poly_add(const polynomial *a, const polynomial *b);
polynomial *poly_sub(const polynomial *a, const polynomial *b);
int poly_equal(const polynomial *a, const polynomial *b);
void poly_iterate(polynomial *p, void (*transform)(struct term *));

void test_print(struct term *);
double poly_eval(const polynomial *p, double x);
//Write in a simplifier

//Flourishes and challenges
//Support all solutions via complex type
//Multiplication function
//*poly_mult(const polynomial *a, const polynomial);
//Exponential function
//*poly_pow(const polynomial *a, unsigned int e);
//Solution function
// poly_real_roots(const polynomial *p, double *solutions, size_t sz);
//Real solutions function
// division function
// *poly_div(const polynomial *a, const polynomial *b, polynomial **r);
//Solution function
// poly_roots(polynomial *p, complex *solutions, size_t sz);
//TODO: Write a highest coefficient finder to the print functions to determine if
//          The + should be used in the prints
//TODO: Fix the discrepencies between using polynominal versus struct term
//          struct term should be used when only one term is expected

#endif
