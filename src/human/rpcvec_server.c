/* Author: Dionisis Nikolopoulos
 *  Description: A program that calls the rusers() service
 *  License: GPLv3
 *  Date Written: April 2022
 */
#include <stdio.h>
#include "../rpc/rpcvec.h"

double * minmax_1_svc(vec * input_vector,struct svc_req *req)
{
    static double minmax_array[2];
    double min,max;
    // min and max are assigned as the first element of array initially..
    min = max = input_vector->vector_array[0];
    //..so we start at 1 (second element)
    double current;
    for (int i=1; i<input_vector->vector_size; i++)
    {
        current = input_vector->vector_array[i];
        if (current > max) max = current;
        if (current < min) min = current;
    }
    // Min is first element, max in second
    minmax_array[0] = min;
    minmax_array[1] = max;
    fprintf(stdout,"\nMax is %lf\n",max);
    fprintf(stdout,"\nMin is %lf\n",min);
    return minmax_array;
}

double * average_1_svc(vec * input_vector,struct svc_req *req)
{
    static double average;
    double sum = 0;
    for (int i=0; i<=input_vector->vector_size; i++)
        sum += input_vector->vector_array[i];
    average = sum / input_vector->vector_size;
    fprintf(stdout,"\nAverage is %lf\n",average);
    return &average;
}

vec * product_1_svc(vec_and_num * input_vector_pair,struct svc_req *req)
{
    static vec product;
    product.vector_size = input_vector_pair->vector.vector_size;
    for (int i=0; i<=input_vector_pair->vector.vector_size; i++)
        product.vector_array[i] = input_vector_pair->vector.vector_array[i]
                                * input_vector_pair->number;
    return &product;
}
