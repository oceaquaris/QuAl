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
smatrix<T, S>::smatrix(T *query1, S query1_len, T *query2, S query2_len) {
    /* Populate the query related parameters */
    this->rows        = ((uint64_t)query1_len) + 1;
    this->columns     = ((uint64_t)query2_len) + 1;
    this->query1      = query1;
    this->query1_len  = query1_len;
    this->query1      = query2;
    this->query1_len  = query2_len;
    this->scores      = nullptr;
    this->traceback   = nullptr;

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
