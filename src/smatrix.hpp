#ifndef SMATRIX_H
#define SMATRIX_H

/*
Traceback codes:
Binary:     Decimal     Meaning:
00000000    0           No traceback (for corners)
00000001    1           Left movement
00000010    2           Up movement
00000011    3           Left-Up movement
*/

template <typename T, typename S>
struct smatrix {
    public:
        /* The rows and columns variables should be larger sizes to avoid overflow. */
        uint64_t rows;          /* Number of rows; max int size for safety */
        uint64_t columns;       /* Number of columns; max int size for safety */

        /* Variable associated with query sequences. */
        T *query1;              /* First query */
        S query1_len;           /* Length of first query */
        T *query2;              /* Second query */
        S query2_len;           /* Length of second query */

        /* Scoring and traceback items */
        T *scores;                   /* Scoring matrix */
        uint8_t *traceback;          /* Traceback for the scoring matrix */

        T (*score_func)(T q1, T q2); /* Scoring function for pairwise comparisons */
        T gap_penalty;               /* Penalty for gaps */
    public:
        /*
         * Constructors
         */
        smatrix(T *query1,
                S query1_len,
                T *query2,
                S query2_len,
                T (*score_func)(T q1, T q2),
                T gap_penalty);

        /*
         * User functions
         */
        void score();

        /*
         * Destructor
         */
        ~smatrix();
};

#include "smatrix.tpp"

#endif
