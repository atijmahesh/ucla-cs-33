#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

//This code is NOT buggy, just sequential. Speed it up. 
void parallel_convolution(long img[DIM_ROW+PAD][DIM_COL+PAD][DIM_RGB], long kernel[DIM_KERNEL][DIM_KERNEL], long ***convolved_img) {
    int row, col, pixel, kernel_row, kernel_col;
#pragma omp parallel for private(row, col, pixel, kernel_row, kernel_col) shared(img, kernel, convolved_img)
    for (pixel = 0; pixel < DIM_RGB; pixel++) {
        for (row = 0; row < DIM_ROW; row++) {
            for (col = 0; col < DIM_COL; col++) {
	      long convolved_val = 0;
                for (kernel_col = 0; kernel_col < DIM_KERNEL; kernel_col++) {
                    for (kernel_row = 0; kernel_row < DIM_KERNEL; kernel_row++) {
                        convolved_val += img[row+kernel_row][col+kernel_col][pixel] * kernel[kernel_row][kernel_col];
                    }
                }
                convolved_img[row][col][pixel] = convolved_val/GBLUR_NORM;
            }    
        }
    }
}
