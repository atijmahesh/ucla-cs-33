#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

//This code is buggy! Find the bug and speed it up.
void parallel_avg_pixel(long img[DIM_ROW][DIM_COL][DIM_RGB], long *avgs) {
    int row, col, pixel;
    long count = DIM_ROW*DIM_COL;
    long count0 = 0;
    long count1 = 0;
    long count2 = 0;
#pragma omp parallel for reduction(+: count0, count1, count2)
    for (row = 0; row < DIM_ROW; row++) {
        for (col = 0; col < DIM_COL; col++) {
            count0 += img[row][col][0];
	    count1 += img[row][col][1];
	    count2 += img[row][col][2];
        }
    }
    #pragma omp parallel for
    for (pixel = 0; pixel < DIM_RGB; pixel++) {
        avgs[pixel] = (pixel == 0) ? count0/count : (pixel == 1) ? count1/count : count2/count;
    }
}
