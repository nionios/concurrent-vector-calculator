/* Description: Prompts for the client side (part of tui)
*  License: GPLv3
*  Date Written: April 2022
*/
#include <stdio.h>
#include "../rpc/rpcvec.h"
#include <rpc/xdr.h>
#include "../rpc/rpcvec.h"

/*
#define MAXLEN 255
bool_t
make_xdr_vec(vec * vector, XDR *xdrsp)
{
    return(xdr_array(xdrsp,
                     (caddr_t *)&vector->vector_array,
                     (u_int *)&vector->vector_size,
                     MAXLEN,
                     sizeof(double),
                     (xdrproc_t)xdr_double));
}
*/

void
average_prompt(vec * vector, CLIENT *clnt)
{
    fprintf(stdout,
           "\nYou chose to calculate the average of the vector."\
            "\n* Sending info to server...");
    double *result = average_1(vector,clnt);
    if (result == (double *)NULL) {
        clnt_perror(clnt,"Call for average_1 function failed!");
        exit(1);
    }
    fprintf(stdout,"\n * Average of vector is: %lf",*result);
}

void
minmax_prompt(vec * vector, CLIENT *clnt)
{
    fprintf(stdout,
            "\nYou chose to calculate the minimum and maximum of the vector."\
            "\n* Sending info to server...");
    double *result = minmax_1(vector,clnt);
    if (result == (double *)NULL) {
        clnt_perror(clnt,"Call for minmax_1 function failed!");
        exit(1);
    }
    fprintf(stdout,"\n==> The minimum of the vector is: %lf"\
                   "\n==> The maximum of the vector is: %lf",
                   result[0], result[1]);
}

void
product_prompt(vec * vector, CLIENT *clnt)
{
    double number;
    fprintf(stdout,
            "\nYou chose to calculate the product of the vector with a number"
            "\n Please input the number you wish to multiply the vector with: "
            );
    scanf("%lf",&number);
    vec_and_num pair;
    pair.number = number;
    pair.vector = *vector;
    fprintf(stdout,"\n* Sending info to server...");
    vec *result = product_1(&pair,clnt);
    if (result == (vec *)NULL) {
        clnt_perror(clnt,"Call for product_1 function failed!");
        exit(1);
    }
    fprintf(stdout,"\n==> The product vector is:");
    for (int i=0; i<pair.vector.vector_size; i++)
        fprintf(stdout,"\n product[%d] = %lf",i,result->vector_array[i]);
}

