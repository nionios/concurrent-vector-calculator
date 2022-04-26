/* Author: Dionisis Nikolopoulos
*  Description: A program that calls the rusers() service
*  License: GPLv3
*  Date Written: April 2022
*/
#include <stdio.h>
#include "../rpc/rpcvec.h"

int hello_server(int argc,char **argv)
{
  fprintf(stdout, "Hello World from server");
}

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
  printf("helloworld");
}

double * product_1_svc(vec_and_num * input_vector_pair,struct svc_req *req)
{
  printf("helloworld");
}
