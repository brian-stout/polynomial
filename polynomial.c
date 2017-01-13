#define _GNU_SOURCE //Used for asprintf function
                    //Should create a modified snprintf for portability later
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
//TODO: Write a highest coefficient finder to the print functions to determine if
//          The + should be used in the prints

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

polynomial *poly_add(const polynomial *a, const polynomial *b)
{
    polynomial *polySum;
    if(a->exp == b->exp)
    {
        polySum = term_create(a->coeff+b->coeff, a->exp);
        a = a->next;
        b = b->next;
    }
    else if (a->exp > b->exp)
    {
        polySum = term_create(a->coeff, a->exp);
        a = a->next;
    }
    else
    {
        polySum = term_create(b->coeff, b->exp);
        b = b->next;
    }
    while(a != NULL)
    {
        if(a->exp == b->exp)
        {
            poly_add_term(&polySum, term_create(a->coeff+b->coeff, a->exp));
            a = a->next;
            b = b->next;
        }
        else if (a->exp > b->exp)
        {
            poly_add_term(&polySum, term_create(a->coeff, a->exp));
            a = a->next;
        }
        else
        {
            poly_add_term(&polySum, term_create(b->coeff, b->exp));
            b = b->next;
        }
    }

    return polySum;
}

int main(void)
{
    polynomial *poly1 = term_create(3, 3);
    poly_add_term(&poly1, term_create(2, 2));
    poly_add_term(&poly1, term_create(1, 1));
    poly_print(poly1);     printf("\n");

    polynomial *poly2 = term_create(3, 3);
    poly_add_term(&poly2, term_create(2, 2));
    poly_print(poly2);     printf("\n");

    polynomial *results = poly_add(poly1, poly2);
    poly_print(results);    printf("\n");

}

char *poly_to_string(const polynomial *p)
{
    char sign;
    char *r;
    if(!p) {
        return r;
    }

    //First part
    if(p->coeff > 0)
    {
        sign = '+';
    }   else if (p->coeff < 0) {
        sign = '-';
    }

    //Prints out the coefficient string to a second string
    if(p->exp > 1) {
        asprintf(&r, "%c%dx^%d", sign, p->coeff*-1, p->exp);
    } else if (p->exp == 1) {
        asprintf(&r, "x");
    }

    if(p->next != NULL)
    {
        asprintf(&r, "%s%s", r, poly_to_string(p->next));
    }
    return r; 
}

