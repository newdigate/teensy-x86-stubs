//
// Created by Nicholas Newdigate on 23/12/2023.
//

#include "arm_math.h"
void arm_scale_f32 (const double *pSrc, double scale, double *pDst, uint32_t blockSize) {
    const double *end = pSrc + blockSize;
    while (pSrc < end) {
        *pDst++ = (*pSrc++) * scale;
    }
}