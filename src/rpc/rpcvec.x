/* Author: Dionisis Nikolopoulos
*  Description: rpcvec.x protocol file for the vector program.
*  Outlines the basics.
*  License: GPLv3
*  Date Written: April 2022

struct vec {
    double *vector_array;
    unsigned int vector_size;
};
*/
typedef double vec<255>;

struct min_and_max {
    double min;
    double max;
};

struct prod_and_num {
    vec * product;
    double number;
};

program VEC_PROGRAM {
    version VEC_VERS {
        /*Average of the Vector*/
        double AVERAGE(vec) = 1;
        /*Min and Max of Vector*/
        min_and_max MINMAX(vec) = 2;
        /*Product of Vector with a number*/
        vec PRODUCT(prod_and_num) = 3;
    } = 1;
} = 0x23451111;
