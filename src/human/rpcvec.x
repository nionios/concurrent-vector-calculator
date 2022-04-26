/* Author: Dionisis Nikolopoulos
*  Description: rpcvec.x protocol file for the vector program.
*  Outlines the basics.
*  License: GPLv3
*  Date Written: April 2022
*/
struct vec {
    double * vector_array;
    int vector_size;
};

struct vec_and_num {
    double * vector;
    double number;
};

program VEC_PROGRAM {
    version VEC_VERS {
        /*Average of the Vector*/
        double AVERAGE(vec) = 1;
        /*Min and Max of Vector*/
        int MINIMUM(vec) = 2;
        int MAXIMUM(vec) = 3;
        /*Product of Vector with a number*/
        double PRODUCT(vec_and_num) = 4;
    } = 1;
} = 0x23451111;
