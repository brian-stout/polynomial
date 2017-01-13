#define _GNU_SOURCE //Used for asprintf function
                    //Should create a modified snprintf for portability later
#include <stdio.h>
#include <stdlib.h>

struct term {
    int coeff;
    unsigned int exp;
    struct term *next;
};

typedef struct term polynomial;

//WARNING: Watch when subtracting equal coefficients

char *poly_to_string(const polynomial *p);
//polynomial *poly_add(const polynomial *a, const polynomial *b);
//polynomial *poly_sub(const polynomial *a, const polynomial *b);
//bool poly_equal(const polynomial *a, const polynomial *b);
//void poly_iterate(polynomial *p, void (*transform)(struct term *));
//double poly_eval(const polynomial *p, double x);
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
        printf("%c%d", eqn->coeff > 0 ? '+' : '\0', eqn->coeff);
        if(eqn->exp > 1) {
            printf("x^%d", eqn->exp);
        } else if (eqn->exp == 1) {
            printf("x");
        }
        printf(" ");
    }
    poly_print(eqn->next);
}

void poly_add_term(polynomial **front, polynomial *newTerm)
{
    struct term *cursor;
    cursor = *front;

    while(cursor->next != NULL)
    {
        cursor = cursor->next;
    }
    cursor->next=newTerm;
}

int main(void)
{
    polynomial *myPoly = term_create(5, 2);
    poly_add_term(&myPoly, term_create(3, 1));
    char *s = poly_to_string(myPoly);
    printf("%s\n", s);
}

char *poly_to_string(const polynomial *p)
{
    char *s = "";
    if(!p) {
        return s;
    }

    if(p->exp > 1) {
        asprintf(&s, "x^%d", p->exp);
    } else if (p->exp == 1) {
        asprintf(&s, "x");
    }
    asprintf(&s, "%c%d%s", p->coeff > 0 ? '+' : '\0', p->coeff, s);

    if(p->next != NULL)
    {
        asprintf(&s, "%s%s", s, poly_to_string(p->next));
    }
    return s; 
}

