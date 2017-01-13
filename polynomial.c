#include <stdio.h>
#include <stdlib.h>

struct term {
    int coeff;
    unsigned int exp;
    struct term *next;
}

typedef struct term polynomial;

//WARNING: Watch when subtracting equal coefficients

char *poly_to_string(const polynomial *p);
polynomial *poly_add(const polynomial *a, const polynomial *b);
polynomial *poly_sub(const polynomial *a, const polynomial *b);
bool poly_equal(const polynomial *a, const polynomial *b);
void poly_iterate(polynomial *p, void (*transform)(struct term *));
double poly_eval(const polynomial *p, double x);
//Write in a simplifier
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

struct term *term_create(int coeff, int exp)
{
    struct term *node = malloc(sizeof(*node));
    if(node) {
        node->coeff = coeff;
        node->exp = exp;
        node->next = NULL;
    }
    return node;
}

void poly_destroy(polynomial *eqn)
{
    while(eqn) {
        struct term *tmp = eqn->next;
        free(eqn);
        eqn = tmp;
    }
}

void poly_print(const polynomial *eqn)
{
    if(!eqn) {
        return;
    }
    if(eqn->coeff) {
        printf("%c%d", eqn->coeff > 0 ? '+' : '\0\, eqn->coeff);
        if(eqn->exp > 1) {
            printf("x^%d", eqn->exp);
        } else if (eqn->exp == 1) {
            printf("x");
        }
        printf(" ");
    }
    poly_print(eqn->next);
}
