/* Author: Dionisis Nikolopoulos
 *  Description: A program that calls the rusers() service
 *  License: GPLv3
 *  Date Written: April 2022
 */
#include <stdio.h>
#include "../rpc/rpcvec.h"


//FIXME: Fix return types

int * minimum_1_svc(vec * input_vector,struct svc_req *req)
{
    printf("helloworld");
}

int * maximum_1_svc(vec * input_vector,struct svc_req *req)
{
    printf("helloworld");
}

double * average_1_svc(vec * input_vector,struct svc_req *req)
{
    double sum = 0;
    for (int i=0; i<=input_vector->vector_size; i++)
    {
        sum += input_vector->vector_array[i];
    }
    double average = sum / input_vector->vector_size;
    fprintf(stdout,"\nAverage is %lf\n",average);
    return &average;
}

double * product_1_svc(vec_and_num * input_vector_pair,struct svc_req *req)
{
    printf("helloworld");
}
