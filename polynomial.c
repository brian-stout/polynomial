#include "polynomial.h"

struct term *
term_create(int coeff, int exp)
{
    struct term *node = malloc(sizeof(*node));

    if (node)
    {
        node->coeff = coeff;
        node->exp = exp;
        node->next = NULL;
    }
    return node;
}

void
poly_destroy(polynomial * eqn)
{
    while (eqn)
    {
        struct term *tmp = eqn->next;

        free(eqn);
        eqn = tmp;
    }
}

void
poly_add_term(polynomial ** front, struct term * newTerm)
{
    polynomial *cursor;
    cursor = *front;

    //Goes to end of the linked list
    while (cursor->next != NULL)
    {
        cursor = cursor->next;
    }
    cursor->next = newTerm;
}

void
poly_print(const polynomial * eqn)
{
    if (!eqn)
    {
        return;
    }
    if (eqn->coeff)
    {
        printf("%c%d", eqn->coeff > 0 ? '+' : '\0', eqn->coeff);
        if (eqn->exp > 1)
        {
            printf("x^%d", eqn->exp);
        }
        else if (eqn->exp == 1)
        {
            printf("x");
        }
        printf(" ");
    }
    poly_print(eqn->next);
}

//TODO: Test this more thoroughly
char *
poly_to_string(const polynomial * p)
{
    char sign;
    char *r;

    if (!p)
    {
        return r;
    }

    //Used to determine the signage later on
    if (p->coeff > 0)
    {
        sign = '+';
    }
    else if (p->coeff < 0)
    {
        sign = '-';
    }

    //asprintf automatically handles memory
    //Handles the three cases for the exponents
    if (p->exp > 1)
    {
        asprintf(&r, "%c%dx^%d", sign, p->coeff * -1, p->exp); // * -1 avoid double negative sign
    }
    else if (p->exp == 1)
    {
        asprintf(&r, "%c%dx", sign, p->coeff * -1);
    }
    else
    {
        asprintf(&r, "%c%d", sign, p->coeff * -1);
    }

    //Uses recursion to print out the rest of the coefficients until the end
    if (p->next != NULL)
    {
        asprintf(&r, "%s%s", r, poly_to_string(p->next));
    }
    return r;
}

polynomial *
poly_add(const polynomial * a, const polynomial * b)
{
    //Creates a dummy polynomial term for poly_add_term to link new terms to
    //This easier to understand than running all the logic outside of the while loop once
    polynomial *polySum = term_create(0, 0);

    while (a != NULL && b != NULL)
    {
        if (a == NULL)
        {
            poly_add_term(&polySum, term_create(b->coeff, b->exp));
            b = b->next;
        }
        else if (b == NULL)
        {
            poly_add_term(&polySum, term_create(a->coeff, a->exp));
            a = a->next;
        }
        else if (a->exp == b->exp)
        {
            poly_add_term(&polySum, term_create(a->coeff + b->coeff, a->exp));
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
    //TODO: Write a function that elimiates 0 coefficients
    polynomial *cursor = polySum;

    polySum = polySum->next;
    free(cursor);

    return polySum;
}

polynomial *
poly_sub(const polynomial * a, const polynomial * b)
{
    polynomial *polySum = term_create(0, 0);

    while (a != NULL && b != NULL)
    {
        if (a == NULL)
        {
            poly_add_term(&polySum, term_create(b->coeff, b->exp));
            b = b->next;
        }
        else if (b == NULL)
        {
            poly_add_term(&polySum, term_create(a->coeff, a->exp));
            a = a->next;
        }
        else if (a->exp == b->exp)
        {
            poly_add_term(&polySum, term_create(a->coeff - b->coeff, a->exp));
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

    polynomial *cursor = polySum;

    polySum = polySum->next;
    free(cursor);

    return polySum;
}

int
poly_equal(const polynomial * a, const polynomial * b)
{
    int r = 1;

    while (a != NULL)
    {
        //Checks to see if polynomial b is shorter than a
        if (b == NULL)
        {
            r = 0;
            break;
        }
        //Checks to see if either the coefficient or exponents are different
        if (a->coeff != b->coeff || a->exp != b->exp)
        {
            r = 0;
            break;
        }
        else
        {
            a = a->next;
            b = b->next;
        }
    }

    //Checks to see if polynomial b is longer than a
    if(b != NULL)
    {
        r = 0;
        break;
    }
    return r;
}

void
poly_iterate(polynomial * p, void (*transform) (struct term *))
{
    struct term *cursor = p;

    while (cursor != NULL)
    {
        transform(cursor);
        cursor = cursor->next;
    }
}

void
test_print(struct term *a)
{
    printf("The coeff is %d and the exp is %d\n", a->coeff, a->exp);
}

double
poly_eval(const polynomial * p, double x)
{
    
    //Initialized as 0 so if passed a NULL pointer it just returns 0 instead of garbage
    double total = 0;
    double result = 0;

    while (p != NULL)
    {
        result = pow(x, p->exp);
        result *= p->coeff;
        total += result;
        p = p->next;
    }
    return total;
}
