/* Author        : Dionisis Nikolopoulos (dennis.nik@protonmail.com)
 * Student Email : ice18390126@uniwa.gr
 * Description   : RPC Client/Socket server for the concurrent vector
 *                 calculator. Acts as middleware for the RPC Server and the
 *                 Socket Client
 * License       : GPLv3
 * Date Written  : April 2022
 * Some code based on "Simple udp server" by Silver Moon (m00n.silv3r@gmail.com)
 */
#include <stdio.h>
#include <string.h>     //for memset
#include <stdlib.h>     //for exit()
#include <sys/socket.h> //for sockets
#include <unistd.h>     //for close()
#include <arpa/inet.h>
#include <prompts.h>
#include <checkalloc.h>
#include "../rpc/rpcvec.h"

int
main(int argc, char *argv[]) {
    struct sockaddr_in si_me, si_other;
    int s, s_new, portno;
    int recv_choice, recv_size;
    double recv_val;
    char *cur;

    fprintf(stdout,"\n*** Concurrent Vector Calculator Middleware started ***");

    // Create a UDP socket
    s=socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)  {
        fprintf(stderr,"\nError: Socket could not be created");
        exit(1);
    }
    else fprintf(stdout,"\n* Socket created...");

    // Zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    // Check for arguments and store them if they are not provided
    if (argc < 2) {
        fprintf(stderr,
                "middleware - usage: %s [port_number] \n",
                argv[0]);
        exit(2);
    }

    portno = atoi(argv[1]);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(portno);
    si_me.sin_addr.s_addr = INADDR_ANY;

    //Bind socket to port
    if (bind(s, (struct sockaddr *) &si_me, sizeof(si_me)) < 0) {
        fprintf(stderr,"\nError: Socket could not be bound to port");
        exit(3);
    } else fprintf(stdout,"\n* Socket bound to port %d...", portno);

    //Start listening for data on maximum 6 clients
    if (listen(s, 5) == 0) fprintf(stdout,"\n* Listening to socket...");
    else {
        fprintf(stderr,"\nError: Could not listen to socket");
        exit(4);
    }

    // Create a CLIENT struct and connect to the RPC server
    CLIENT *clnt = clnt_create("localhost", VEC_PROGRAM, VEC_VERS, "udp");
    if (!clnt) {
        fprintf(stderr,"\nError: Could not connect to the RPC server");
        exit(5);
    } else fprintf(stdout,"\n* Connected to the RPC server...");

    int flag = 1;
    while(flag) {
        int slen = sizeof(si_other);
        s_new = accept(s, (struct sockaddr *) &si_other, &slen);
        if (s_new < 0) {
            fprintf(stderr,"\nError: Couldn't create new socket");
            // We now need to destroy the RPC client on exit too
            clnt_destroy(clnt);
            exit(6);
        } else fprintf(stdout,"\n* New socket created...");
        // Creating a new child process
        int pid = fork();
        if (pid < 0) {
            fprintf(stderr,"\nError: Couldn't fork new process, pid == %d",pid);
            // We now need to destroy the RPC client on exit too
            clnt_destroy(clnt);
            exit(7);
        } else if (pid) fprintf(stdout,"\n* New process forked...");
        else if (!pid) {
            //Close previous socket
            close(s);
            fprintf(stdout,"\n* Waiting for vector data...");
            // Try to receive the integer of vector size
            if (recv(s_new, &recv_size, sizeof(int), 0) < 0) {
                fprintf(stderr,"\nError: Couldn't receive vector size");
                clnt_destroy(clnt);
                exit(7);
            } else {
                fprintf(stdout,
                  "\n==> Received size of vector from client side, size is %d",
                  recv_size);
            }
            // Create a vector object and a vector pointer
            vec vector;
            // Vector p needed in some cases (case 3)
            vec * vectorp = &vector;
            // Allocate memory based on the size of vector given by user
            vector.vec_val = (double*)malloc(sizeof(double) * recv_size);
            // Check if allocation was successful
            checkalloc(vector.vec_val);
            vector.vec_len = recv_size;
            fprintf(stdout,
                    "\n* Initialized vector with %d elements!",
                    vector.vec_len);

            for (int i=0; i<vector.vec_len; i++) {
                //Try to receive values in double
                if (recv(s_new, &recv_val, sizeof(double), 0) < 0) {
                    fprintf(stderr,"\nError: Couldn't receive vector value");
                    clnt_destroy(clnt);
                    exit(8);
                } else {
                    fprintf(stdout,
                            "\n==> Received value of vector from client side,"\
                            " value is %lf",
                            recv_val);
                }
                //Put the received value on the vector's array
                vector.vec_val[i] = recv_val;
            }
            while (flag) {
                // Try to receive recv_choice number from client
                if (recv(s_new, &recv_choice, sizeof(int), 0) < 0) {
                    fprintf(stderr,"\nError: Couldn't receive recv_choice value");
                    clnt_destroy(clnt);
                    exit(9);
                } else {
                    fprintf(stdout,
                            "\n==> Received recv_choice number from client side,"\
                            " recv_choice is %d",
                            recv_choice);
                }
                switch (recv_choice) {
                    case 0:
                        //Exit the program
                        flag = 0;
                        return 0;
                    // Call RPC server in cases 1-3
                    case 1:
                        double *result_1 = average_1(&vector, clnt);
                        if (result_1 == (double *)NULL) {
                            clnt_perror(clnt,"Call for average_1 function failed!");
                            exit(5);
                        }
                        fprintf(stdout,"\n==> Average of vector is: %lf", *result_1);
                        //Send to user client
                        send(s_new,result_1,sizeof(double),0);
                        break;
                    case 2:
                        min_and_max *result_2 = minmax_1(&vector, clnt);
                        if (result_2 == (min_and_max *)NULL) {
                            clnt_perror(clnt,"Call for minmax_1 function failed!");
                            exit(6);
                        } fprintf(stdout,"\n==> The minimum of the vector is: %lf"\
                                "\n==> The maximum of the vector is: %lf",
                                result_2->min, result_2->max);
                        //Send to user client
                        send(s_new, result_2, sizeof(double)*2, 0);
                        break;
                    case 3:
                        // Try to receive the number that will multiply the vector
                        double number;
                        if ( recv(s_new, &number, sizeof(double), 0) < 0) {
                            fprintf(stderr,"\nError: Couldn't receive number value");
                            clnt_destroy(clnt);
                            exit(10);
                        } else {
                            fprintf(stdout,
                                    "\n==> Received number from client side,"\
                                    " number is %lf",
                                    number);
                        }
                        prod_and_num args;
                        args.number = number;
                        // Initialize the product vector with the elements of original vector
                        args.product = vectorp;
                        //fprintf(stdout,"\n==> The current vector is:");
                        //for (int i=0; i<args.product->vec_len; i++)
                        //    fprintf(stdout,"\n product[%d] = %lf", i, args.product->vec_val[i]);
                        fprintf(stdout,"\n<== Sending info to server...");
                        args.product = product_1(&args,clnt);
                        if (args.product == (vec *)NULL) {
                            clnt_perror(clnt,"Call for product_1 function failed!");
                            exit(7);
                        }
                        vec product = *args.product;
                        fprintf(stdout,"\n==> The product vector is:");
                        for (int i=0; i<product.vec_len; i++)
                            fprintf(stdout,"\n product[%d] = %lf",
                                    i, product.vec_val[i]);
                        // Only send the element array to socket client, length
                        // of vector is known
                        send(s_new,
                             product.vec_val,
                             sizeof(double)*product.vec_len,
                             0);
                        break;
                }
            }
        }
        close(s_new);
    }
    clnt_destroy(clnt);
    return 0;
}
