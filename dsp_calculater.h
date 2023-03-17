#ifndef DSP_CALCULATER_HEAD
#define DSP_CALCULATER_HEAD

// 注释掉可以关闭矩阵检查
#define MAT_LEGAL_CHECKING

#include "dsp.h"
#include "light_matrix.h"

typedef enum {
    exclusion = -1,
    speedup = 1,
    extra = 2
} request_t;

void solve(double* result_list, double* need_list, request_t* request_list, item_t hydrogen_source);

#endif