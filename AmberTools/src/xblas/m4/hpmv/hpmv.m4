dnl ---------------------------------------------------------
dnl  HPMV ---- Hermitian Packed Matrix Vector Multiply
dnl
dnl    y  <---   alpha * A * x + beta * y
dnl
dnl    where matrix A is hermitian.
dnl ---------------------------------------------------------
dnl
dnl hpmv.m4 contains the macros for producing the HPMV (hermitian-packed
dnl matrix-vector multiply) routines.  See the documentation for
dnl packed.m4 for data on packed storage.
dnl
dnl All core computation in HPMV is done in the upper triangular case,
dnl since one can flip the uplo attribute by flipping the order attribute.
dnl this leads to some confusing but simple code for the conjugation.
dnl 
#include "blas_extended.h"
#include "blas_extended_private.h"
dnl
dnl
include(cblas.m4)dnl
include(packed.m4)dnl
include(hpmv-common.m4)dnl
dnl
dnl
dnl  Usage:
dnl    HEMV        ($1, $2, $3, $4)
dnl    HEMV_HEAD   ($1, $2, $3, $4)
dnl    HEMV_NAME   ($1, $2, $3, $4)
dnl    HEMV_PARAMS ($1, $2, $3, $4)
dnl    HEMV_COMMENT($1, $2, $3, $4)
dnl
dnl    $1 -- type of alpha, beta, y.
dnl    $2 -- type of A matrix
dnl    $3 -- type of x
dnl    $4 -- set to `_x' for _x routines.
dnl          Otherwise, `'.
dnl
dnl
define(`HPMV_COMMENT', `
/*
 * Purpose
 * =======
 *
 * Computes y = alpha * ap * x + beta * y, where ap is a hermitian
 * packed matrix.
 *
 * Arguments
 * =========
 *
 * order        (input) blas_order_type
 *              Order of ap; row or column major
 *
 * uplo         (input) blas_uplo_type
 *              Whether ap is upper or lower
 *
 * n            (input) int
 *              Dimension of ap and the length of vector x
 *
 * alpha        (input) $1_scalar
 *              
 * ap           (input) $2_array
 *
 * x            (input) $3_array
 * 
 * incx         (input) int
 *              The stride for vector x.
 *
 * beta         (input) $1_scalar
 *
 * y            (input/output) $1_array
 *
 * incy         (input) int
 *              The stride for vector y.
 *
PREC_COMMENT($4)dnl
 */')dnl
dnl
dnl
dnl ---------------------------------------------------------------------
dnl Usage: HPMV_LOOP(aby_type, ap_type, x_type, sum_type, tmp_type, order, 
dnl             a_zero, b_zero)
dnl ... y = alpha * ap * x + beta * y.  Assumes upper triangular storage
dnl (since we can coerce to that with no difficulties).
dnl ---------------------------------------------------------------------
define(`HPMV_LOOP', 
  `{
     y_index = y_start;
     ifelse($7, `zero', 
       `for(matrix_row = 0; matrix_row < n; matrix_row++) {
          HPMV_PERFORM_SCALED_ASSIGNMENT($1, $4, $5, $8, $7)
          y_index += incy;
        }',
       `ap_start = 0;
        if ( uplo == blas_upper ) {
          for(matrix_row = 0; matrix_row < n; matrix_row++) {
            x_index = x_start;
            ap_index = ap_start;
            ZERO(rowsum, $4)
            ZERO(rowtmp, $4)
            HPMV_PERFORM_DOT_PRODUCT($1, $2, $3, $4, 
              $6, $7, `conj_first_loop')
            HPMV_PERFORM_SCALED_ASSIGNMENT($1, $4, $5, $8, $7)
            y_index += incy;
            COLUMN_STRIDE(ap_start, n, matrix_row, $6, blas_upper, incap)
          }
        } else {  /* if uplo == ... */
          for(matrix_row = 0; matrix_row < n; matrix_row++) {
            x_index = x_start;
            ap_index = ap_start;
            ZERO(rowsum, $4)
            ZERO(rowtmp, $4)
            HPMV_PERFORM_DOT_PRODUCT($1, $2, $3, $4, 
              $6, $7, `conj_second_loop')
            HPMV_PERFORM_SCALED_ASSIGNMENT($1, $4, $5, $8, $7)
            y_index += incy;
            COLUMN_STRIDE(ap_start, n, matrix_row, $6, blas_upper, incap)
          }
        } /* end if uplo == blas_upper ... */')
   }')dnl
dnl
dnl
dnl ---------------------------------------------------------------------
dnl Usage: HPMV_PERFORM_DOT_PRODUCT(aby_type, ap_type, x_type, sum_type, 
dnl        order, a_zero) ... Sums across the row for the HPMV dot 
dnl        product if such a product is necessary (i.e. alpha is not
dnl        zero).
dnl ---------------------------------------------------------------------
define(`HPMV_PERFORM_DOT_PRODUCT', `ifelse(
  `$6', `zero', `',
  `for(step = 0; step < matrix_row; step++) {
     GET_VECTOR_ELEMENT(matval, ap_i, ap_index, $2)
     GET_VECTOR_ELEMENT(vecval, x_i, x_index, $3)
     ifelse($7, `conj_first_loop', `CONJ_AUX(matval, $2)', `')
     MUL(rowtmp, $4, matval, $2, vecval, $3)
     ADD(rowsum, $4, rowsum, $4, rowtmp, $4)
     ROW_STRIDE(ap_index, n, step, $5, blas_upper, incap)
     x_index += incx;
   }
   /* need to do diagonal element without referencing the imaginary part */
   GET_VECTOR_ELEMENT(matval[0], ap_i, ap_index, REAL_TYPE($2))
   GET_VECTOR_ELEMENT(vecval, x_i, x_index, $3)
   MUL(rowtmp, $4, vecval, $3, matval[0], REAL_TYPE($2))
   ADD(rowsum, $4, rowsum, $4, rowtmp, $4)
   COLUMN_STRIDE(ap_index, n, step, $5, blas_upper, incap)
   x_index += incx;
   for(step = matrix_row + 1; step < n; step++) {
     GET_VECTOR_ELEMENT(matval, ap_i, ap_index, $2)
     GET_VECTOR_ELEMENT(vecval, x_i, x_index, $3)
     ifelse($7, `conj_second_loop', `CONJ_AUX(matval, $2)', `')
     MUL(rowtmp, $4, matval, $2, vecval, $3)
     ADD(rowsum, $4, rowsum, $4, rowtmp, $4)
     COLUMN_STRIDE(ap_index, n, step, $5, blas_upper, incap)
     x_index += incx;
   }')')dnl
dnl
dnl
dnl ---------------------------------------------------------------------
dnl Usage: HPMV_PERFORM_SCALED_ASSIGNMENT(aby_type, sum_type, tmp_type, 
dnl        b_zero) ... Performs the last phase of the operation, adding
dnl        B*y and placing it in y.
dnl ---------------------------------------------------------------------
define(`HPMV_PERFORM_SCALED_ASSIGNMENT', `ifelse(
        `$4', `zero', 
`       ifelse($5, `one', `ASSIGN(tmp1, $3, rowsum, $2)',
                `MUL(tmp1, $3, rowsum, $2, alpha_i, $1)')
        SET_ROUND_VECTOR_ELEMENT(y_i, y_index, tmp1, $3)',
`       GET_VECTOR_ELEMENT(resval, y_i, y_index, $1)
        ifelse($5, `zero', `',
                $5, `one', `ASSIGN(tmp1, $3, rowsum, $2)',
                        `MUL(tmp1, $3, rowsum, $2, alpha_i, $1)')
        ifelse($4, `one', `ASSIGN(tmp2, $3, resval, $1)',
                `MUL(tmp2, $3, beta_i, $1, resval, $1)')
        ifelse($5, `zero', `', `ADD(tmp2, $3, tmp1, $3, tmp2, $3)')
        SET_ROUND_VECTOR_ELEMENT(y_i, y_index, tmp2, $3)')')dnl
dnl
dnl
define(`HPMV_BODY',
  `{
    enum blas_order_type order_i;

    SCALAR_CAST(alpha, $1)
    SCALAR_CAST(beta, $1)
    int matrix_row, step, ap_index, ap_start, x_index, x_start;
    int y_start, y_index, incap;
    
    PTR_CAST(ap, $2, `const')
    PTR_CAST(x, $3, `const')
    PTR_CAST(y, $1)
    DECLARE(rowsum, $4)
    DECLARE(rowtmp, $4)
    DECLARE(matval, $2)
    DECLARE(vecval, $3)
    DECLARE(resval, $1)
    DECLARE(tmp1, $5)
    DECLARE(tmp2, $5)
    ifelse(`$6', `FPU', `FPU_FIX_DECL;')

    if (n < 1)
      return;
    if (TEST_0(alpha_i, $1) && TEST_1(beta_i, $1))
      return;

    /* Check for error conditions. */
    if (order != blas_colmajor && order != blas_rowmajor)
      BLAS_error(routine_name, -1, order, NULL);
    if (uplo != blas_upper && uplo != blas_lower)
      BLAS_error(routine_name, -2, uplo, NULL);
    if (incx == 0)
      BLAS_error(routine_name, -7, incx, NULL);
    if (incy == 0) {
      BLAS_error(routine_name, -10, incy, NULL);
    }

    ifelse(`$6', `FPU', `FPU_FIX_START;')

    incap = 1;
    INC_ADJUST(incap, $2)
    INC_ADJUST(incx, $3)
    INC_ADJUST(incy, $1)

    if(incx<0) x_start = (-n+1)*incx; else x_start = 0;
    if(incy<0) y_start = (-n+1)*incy; else y_start = 0;

    if(uplo == blas_lower)
      order_i = FLIP(blas_order_type, order);
    else
      order_i = order;

    if (TEST_0(alpha_i, $1)) {
      HPMV_LOOP($1, $2, $3, $4, $5, blas_rowmajor, `zero', `')
    } else {
      if(order_i == blas_rowmajor) {
        if(TEST_1(alpha_i, $1)) {
          if(TEST_0(beta_i, $1)) {
            HPMV_LOOP($1, $2, $3, $4, $5, blas_rowmajor, `one', `zero')
          } else {
            HPMV_LOOP($1, $2, $3, $4, $5, blas_rowmajor, `one', `')
          }
        } else {
          if(TEST_0(beta_i, $1)) {
            HPMV_LOOP($1, $2, $3, $4, $5, blas_rowmajor, `', `zero')
          } else {
            HPMV_LOOP($1, $2, $3, $4, $5, blas_rowmajor, `', `')
          }
        }
      } else {
        if(TEST_1(alpha_i, $1)) {
          if(TEST_0(beta_i, $1)) {
            HPMV_LOOP($1, $2, $3, $4, $5, blas_colmajor, `one', `zero')
          } else {
            HPMV_LOOP($1, $2, $3, $4, $5, blas_colmajor, `one', `')
          }
        } else {
          if(TEST_0(beta_i, $1)) {
            HPMV_LOOP($1, $2, $3, $4, $5, blas_colmajor, `', `zero')
          } else {
            HPMV_LOOP($1, $2, $3, $4, $5, blas_colmajor, `', `')
          }
        }
      }
    } /* end alpha != 0 */
    ifelse(`$6', `FPU', `FPU_FIX_STOP;')
}')dnl
dnl
dnl
define(`SWITCH_prec', 
  `switch(prec) {
     case blas_prec_single: ifelse(`$4&&$5', `$6&&$7', `', `{
       HPMV_BODY($1, $2, $3, $4, $5)
       break;
     }
     ')dnl
     case blas_prec_indigenous:
     case blas_prec_double: {
       HPMV_BODY($1, $2, $3, $6, $7)
       break;
     }

     case blas_prec_extra: { 
       HPMV_BODY($1, $2, $3, $8, $9, FPU)
       break;
     }
   }')dnl
dnl
dnl
define(`HPMV_X_BODY', 
  `SWITCH_prec($1, $2, $3, 
    SUM_TYPE_X($1, $2, $3, S), TMP_TYPE_X($1, S), 
    SUM_TYPE_X($1, $2, $3, D), TMP_TYPE_X($1, D), 
    SUM_TYPE_X($1, $2, $3, E), TMP_TYPE_X($1, E))')dnl
dnl
dnl
define(`HPMV',
  `HPMV_COMMENT($1, $2, $3, $4)
   HPMV_HEAD($1, $2, $3, $4)
   {
     static const char routine_name[] = "HPMV_NAME($1, $2, $3, $4)";

     ifelse($4, _x, `HPMV_X_BODY($1_type, $2_type, $3_type)', 
     `HPMV_BODY($1_type, $2_type, $3_type, 
       SUM_TYPE($1_type, $2_type, $3_type), $1_type)')
   }')dnl
dnl
dnl
