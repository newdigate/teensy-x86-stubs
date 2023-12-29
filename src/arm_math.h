#ifndef TEENSY_X86_STUBS_ARM_MATH_H
#define TEENSY_X86_STUBS_ARM_MATH_H

#include <cmath>
#include <cstdint>

#define float32_t float_t

/**
 * @brief Instance structure for the floating-point FIR interpolator.
 */
typedef struct
{
    uint8_t L;                     /**< upsample factor. */
    uint16_t phaseLength;          /**< length of each polyphase filter component. */
    float32_t *pCoeffs;            /**< points to the coefficient array. The array is of length L*phaseLength. */
    float32_t *pState;             /**< points to the state variable array. The array is of length phaseLength+numTaps-1. */
} arm_fir_interpolate_instance_f32;

/**
 * @brief Instance structure for the floating-point FIR decimator.
 */
typedef struct
{
    uint8_t M;                  /**< decimation factor. */
    uint16_t numTaps;           /**< number of coefficients in the filter. */
    float32_t *pCoeffs;         /**< points to the coefficient array. The array is of length numTaps.*/
    float32_t *pState;          /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
} arm_fir_decimate_instance_f32;


void arm_scale_f32 (const double *pSrc, double scale, double *pDst, uint32_t blockSize);

void arm_fir_decimate_f32(
  const arm_fir_decimate_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

void arm_fir_interpolate_f32(
  const arm_fir_interpolate_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

int arm_fir_interpolate_init_f32(
  arm_fir_interpolate_instance_f32 * S,
  uint8_t L,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);

int arm_fir_decimate_init_f32(
  arm_fir_decimate_instance_f32 * S,
  uint16_t numTaps,
  uint8_t M,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);
#endif //TEENSY_X86_STUBS_ARM_MATH_H
