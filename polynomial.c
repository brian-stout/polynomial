#define _GNU_SOURCE //Used for asprintf function
                    //Should create a modified snprintf for portability later
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

char *poly_to_string(const polynomial *p);
polynomial *poly_add(const polynomial *a, const polynomial *b);
polynomial *poly_sub(const polynomial *a, const polynomial *b);
struct term *term_equal 
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
//TODO: Fix the discrepencies between using polynominal versus struct term
//          struct term should be used when only one term is expected
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
    polynomial *poly1 = term_create(4, 3);
    poly_add_term(&poly1, term_create(3, 2));
    poly_add_term(&poly1, term_create(2, 1));
    poly_add_term(&poly1, term_create(2, 0));
    poly_print(poly1);     printf("\n");

    polynomial *poly2 = term_create(1, 3);
    poly_add_term(&poly2, term_create(1, 2));
    poly_print(poly2);     printf("\n");

    polynomial *results = poly_sub(poly1, poly2);
    poly_print(results);    printf("\n");

    poly_destroy(poly1);
    poly_destroy(poly2);
    poly_destroy(results);

}

polynomial *poly_add(const polynomial *a, const polynomial *b)
{
    polynomial *polySum = term_create(0, 0);
    
    while(a != NULL && b != NULL)
    {
        if(a == NULL)
        {
            poly_add_term(&polySum, term_create(b->coeff, b->exp));
            b = b->next;            
        }
        else if(b == NULL)
        {
            poly_add_term(&polySum, term_create(a->coeff, a->exp));
            a = a->next;
        }
        else if(a->exp == b->exp)
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

    //Removes the zero, could replace this with the polynomial simplifier later on
    //  or add a specific function for removing exp 0s
    polynomial *cursor = polySum;
    polySum = polySum->next;
    free(cursor);

    return polySum;
}

polynomial *poly_sub(const polynomial *a, const polynomial *b)
{
    polynomial *polySum = term_create(0, 0);
    
    while(a != NULL && b != NULL)
    {
        if(a == NULL)
        {
            poly_add_term(&polySum, term_create(b->coeff, b->exp));
            b = b->next;            
        }
        else if(b == NULL)
        {
            poly_add_term(&polySum, term_create(a->coeff, a->exp));
            a = a->next;
        }
        else if(a->exp == b->exp)
        {
            poly_add_term(&polySum, term_create(a->coeff-b->coeff, a->exp));
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

    //Removes the zero, could replace this with the polynomial simplifier later on
    //  or add a specific function for removing exp 0s
    polynomial *cursor = polySum;
    polySum = polySum->next;
    free(cursor);

    return polySum;
}

//TODO: Test this more thoroughly
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
        asprintf(&r, "%c%dx", sign, p->coeff*-1);
    } else {
        asprintf(&r, "%c%d", sign, p->coeff*-1);
    }

    if(p->next != NULL)
    {
        asprintf(&r, "%s%s", r, poly_to_string(p->next));
    }
    return r; 
}

