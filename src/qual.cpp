/*
 * Main body
 */

#include <new>
#include <cstdint>
#include <cmath>

#include "smatrix.hpp"

double scoref(double i, double j) {
    return fabs(1/(i - j));
}

int main(int argc, char *argv[]) {
    double q1[] = {5,6,7,8,9};
    double q2[] = {5.1,6.1,7.1,8.1,9.1};

    smatrix<double,uint8_t> m = smatrix<double,uint8_t>(q1,
                                                        5,
                                                        q2,
                                                        5,
                                                        scoref,
                                                        0.1);
    m.score();
    m.print_scores_matrix(true);
    m.print_traceback_matrix(true);
    return 0;
}
