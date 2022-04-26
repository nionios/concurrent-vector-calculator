/* Author: Dionisis Nikolopoulos
*  Description: Client side for the concurrent vector calculator
*  License: GPLv3
*  Date Written: April 2022
*/
#include <stdio.h>
#include "../rpc/rpcvec.h"

int main(int argc,char **argv) {
    unsigned int input_size, choice;

    fprintf(stdout,"*** Concurrent Vector Calculator ***");
    fprintf(stdout,"\nPlease provide number of elements for vector: ");
    scanf("%d",&input_size);
    vec vector;
    vector.vector_array=malloc(sizeof(double) * input_size);
    vector.vector_size = input_size;
    for (int i=0; i<vector.vector_size; i++) {
        fprintf(stdout,"\nPlease provide element number %d of vector: ",i);
        scanf("%d",&vector.vector_array[i]);
    }
    while (1) {
        fprintf(stdout,"\nPlease choose calculation to make or exit:"\
                "\n0. Exit program"\
                "\n1. Average of vector"\
                "\n2. Minimum and Maximum element of vector"\
                "\n3. Product of vector with a real number"\
                "\nChoice: ");
        scanf("%d",&choice);
        if (choice == 0) break;
    }
}
