/*
 * Scoring matrix file.
 */

 /* Standard libraries */
 #include <cstdlib>
 #include <cstdint>
 #include <iostream>
 #include <new>
 /* 3rd party libraries */
 /* QuAl libraries */
 #include "smatrix.hpp"

/*
 * Constructor
 */
template <typename T, typename S>
smatrix<T, S>::smatrix(T *query1,
                       S query1_len,
                       T *query2,
                       S query2_len,
                       T (*score_func)(T q1, T q2),
                       T gap_penalty) {
    /* Populate the query related parameters */
    this->rows        = ((uint64_t)query1_len) + 1;
    this->columns     = ((uint64_t)query2_len) + 1;
    this->query1      = query1;
    this->query1_len  = query1_len;
    this->query1      = query2;
    this->query1_len  = query2_len;
    this->scores      = nullptr;
    this->traceback   = nullptr;
    this->score_func  = score_func;
    this->gap_penalty = gap_penalty;

    /* Allocate memory for our scoring matrix */
    try {
        this->scores = new T[(this->rows) * (this->columns)];
    }
    catch(std::bad_alloc &e) {          //catch any exception and print message
        std::cerr << "bad_alloc in " << __func__ << ": " << e.what() << std::endl;
    }

    /* Allocate memory for our traceback matrix */
    try {
        this->traceback = new uint8_t[(this->rows) * (this->columns)];
    }
    catch(std::bad_alloc &e) {          //catch any exception and print message
        std::cerr << "bad_alloc in " << __func__ << ": " << e.what() << std::endl;
        if(this->scores != nullptr) {
            delete[] this->scores;
        }
    }
}


template <typename T, typename S>
void smatrix<T, S>::score() {
    /* Seed the matrices with zeros */
    uint64_t i, j;
    /* Seed the first row with zeros */
    for(i = 0; i < this->columns; i++) {
        this->scores[i] = 0;
        this->traceback[i] = 0;
    }
    /* Seed the first column with zeros */
    for(i = 1; i < this->rows; i++) {
        this->scores[i*(this->columns)] = 0;
        this->traceback[i*(this->columns)] = 0;
    }
    /* Begin scoring */
    for(i = 1; i < this->rows; i++) {
        for(j = 1; j < this->columns; j++) {
            //Score for a gap in query1 (columns)
            T score_query1_gap =
                this->scores[(i-1)*(this->columns) + j]
                - this->gap_penalty;
                printf("%f\n", score_query1_gap);

            //Score for a gap in query2 (rows)
            T score_query2_gap =
                this->scores[i*(this->columns) + (j-1)]
                - this->gap_penalty;
            //Score for a match
            T score_match =
                this->scores[(i-1)*(this->columns) + (j-1)]
                + this->score_func(this->query1[j-1], this->query2[i-1]);

            //Find the max of the scores and populate the matrix
            if(score_match >= score_query1_gap) {
                if(score_match >= score_query2_gap) {
                    this->scores[i*(this->columns) + j] = score_match;
                    this->traceback[i*(this->columns) + j] = 3;
                }
                else {
                    this->scores[i*(this->columns) + j] = score_query2_gap;
                    this->traceback[i*(this->columns) + j] = 1;
                }
            }
            else {
                if(score_query1_gap >= score_query2_gap) {
                    this->scores[i*(this->columns) + j] = score_query1_gap;
                    this->traceback[i*(this->columns) + j] = 2;
                }
                else {
                    this->scores[i*(this->columns) + j] = score_query2_gap;
                    this->traceback[i*(this->columns) + j] = 1;
                }
            }
        }
    }

    return;
}


/*
 * Destructor
 */
template <typename T, typename S>
smatrix<T, S>::~smatrix() {
    if(this->scores != nullptr) {
        delete[] this->scores;
    }
    if(this->traceback != nullptr) {
        delete[] this->traceback;
    }
}
