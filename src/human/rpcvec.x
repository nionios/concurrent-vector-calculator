/* Author: Dionisis Nikolopoulos
*  Description: rpcvec.x protocol file for the vector program.
*  Outlines the basics.
*  License: GPLv3
*  Date Written: April 2022
*/
struct vector {
    double * vector;
};

struct vec_and_num {
    double * vector;
    double number;
};

program VEC_PROGRAM {
    version VEC_VERS {
        /*Average of the Vector*/
        double AVG(vector) = 1;
        /*Min and Max of Vector*/
        int MIN(vector) = 2;
        int MAX(vector) = 3;
        /*Product of Vector with a number*/
        double PROD(vec_and_num) = 4;
    } = 1;
} = 0x23451111;
