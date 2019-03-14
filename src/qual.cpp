/*
 * Main body
 */

#include <new>
#include <cstdint>

#include "smatrix.hpp"

double scoref(double i, double j) {
    return 0.0;
}

int main(int argc, char *argv[]) {
    double q1[] = {5,6,7,8,9};
    double q2[] = {0.4,0.3,0.2,0.1,0.5};
    uint8_t q1_len = 5, q2_len = 5;

    smatrix<double,uint8_t> m = smatrix<double,uint8_t>(q1,
                                                        q1_len,
                                                        q2,
                                                        q2_len,
                                                        scoref,
                                                        0.0);
    m.score();
    return 0;
}
