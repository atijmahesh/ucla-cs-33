#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

//This code is buggy! Find the bug and speed it up.
void parallel_to_grayscale(long img[DIM_ROW][DIM_COL][DIM_RGB], long ***grayscale_img, long *min_max_gray) {
    int row, col, pixel, gray_pixel;
    int min_gray = 256;
    int max_gray = -1;

#pragma omp parallel for private(row, col, pixel) reduction(min:min_gray) reduction(max:max_gray)
    for (row = 0; row < DIM_ROW; row++) {
        for (col = 0; col < DIM_COL; col++){
	  int sum_pixel = 0;
	  for(pixel = 0; pixel < DIM_RGB; pixel++) {
	    sum_pixel+=img[row][col][pixel];
	  }
	  int grayPixel = sum_pixel/3;
	  grayscale_img[row][col][0] = grayscale_img[row][col][1] = grayscale_img[row][col][2] = grayPixel;

	  if(grayPixel < min_gray) {
	    min_gray = grayPixel;
	  }
	  if(grayPixel > max_gray) {
            max_gray = grayPixel;
          }
        }
    }
    #pragma omp critical
    {
      min_max_gray[0] = min_gray;
      min_max_gray[1] = max_gray;
    }
}
