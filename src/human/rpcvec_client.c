/* Author: Dionisis Nikolopoulos
*  Description: Client side for the concurrent vector calculator
*  License: GPLv3
*  Date Written: April 2022
*/
#include <stdio.h>
#include "../rpc/rpcvec.h"

void average_prompt(vec vector, CLIENT *clnt) {
    fprintf(stdout,
            "\nYou chose to calculate the average of the vector.");
}

void minmax_prompt(vec vector, CLIENT *clnt) {
    fprintf(stdout,
            "\nYou chose to calculate the minimum and maximum of the vector.");
}

void product_prompt(vec vector, CLIENT *clnt) {
    double number;
    fprintf(stdout,
            "\nYou chose to calculate the product of the vector with a number"
            "\n Please input the number you wish to multiply the vector with: "
            );
    scanf("%lf",&number);
    vec_and_num pair;
    pair.number = number;
    pair.vector = vector;
}

void client_side(CLIENT *clnt){
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
                "\n 0. Exit program"\
                "\n 1. Average of vector"\
                "\n 2. Minimum and Maximum element of vector"\
                "\n 3. Product of vector with a real number"\
                "\nChoice: ");
        scanf("%d",&choice);
        switch (choice) {
            case 0:
                return;
            case 1:
                average_prompt(vector,clnt);
                break;
            case 2:
                minmax_prompt(vector,clnt);
                break;
            case 3:
                product_prompt(vector,clnt);
                break;
            default:
                fprintf(stdout,
                        "Your choice was not valid input, please try again...");
        }
    }
}

int main(int argc,char **argv) {
    char * host;
    if (argc < 2) {
        printf ("usage: %s server_host\n", argv[0]);
        exit (1);
    }
    host = argv[1];
    CLIENT *clnt = clnt_create(host, VEC_PROGRAM, VEC_VERS, "udp");
    // After it is ensured correct info has been given, begin client side
    client_side(clnt);
    return 0;
}
