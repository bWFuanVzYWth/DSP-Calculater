#include <omp.h>
#include <stdio.h>
#include "dsp.h"
#include "light_matrix.h"

// 设置需求列表中的一项(列表指针, 产物id, 需求多少)
void set_need_vec_val(Mat* p, item_t product, double num) {
    p->element[0][product] = num;
}

// 设置配方矩阵中的一个元素(矩阵指针, 产物id, 原料id, 原料数量)
void set_recipe_mat_val(Mat* p, item_t product, item_t resource, double num) {
    p->element[product][resource] = num;
}

// 给配方矩阵中的某个公式使用自喷涂蓝增产剂进行加速(矩阵指针, 产物id) // 一个自喷涂蓝增产剂可以喷涂75个物品
void set_recipe_mat_speedup(Mat* p, item_t product) {
    double count = 0.0;
    for (int i = 0; i < MAT_SIZ; i++)
        count += p->element[product][i];  // 统计这个公式中需要喷涂的物品数量
    p->element[product][qwq] = count / 75.0;
}

// 给配方矩阵中的某个公式使用自喷涂蓝增产剂进行增产(矩阵指针, 产物id)
void set_recipe_mat_extra(Mat* p, item_t product) {
    double count = 0.0;
    for (int i = 0; i < MAT_SIZ; i++) {
        p->element[product][i] *= 0.8;
        count += p->element[product][i];  // 把公式中的原料全部*0.8，再统计，顺序不能反
    }
    p->element[product][qwq] = count / 75.0;
}

// 排除某一项的计算(矩阵指针，排除产品id)
void exclusion_recipe_mat(Mat* p, item_t product){
    for (int i = 0; i < MAT_SIZ; i++)
        p->element[product][i] = 0.0;
}

// 输出整个物品列表
void print_cargo(Mat* v) {
    for (int i = 0; i < MAT_SIZ; i++) {
        if (v->element[0][i] > 1e-15 || v->element[0][i] < -1e-15) {
            printf("%s\t%lf\n", item_name[i], v->element[0][i]);
        }
    }
}

int main(void) {
    double time0 = omp_get_wtime();

    // 创建需求列表
    Mat need_vec;
    MatCreate(&need_vec, 1, MAT_SIZ);
    MatZeros(&need_vec);

    // 创建公式矩阵
    Mat recipe_mat;
    MatCreate(&recipe_mat, MAT_SIZ, MAT_SIZ);
    MatZeros(&recipe_mat);

    // 根据用户需求初始化需求列表
#define TEST 2

#if TEST == 1
    set_need_vec_val(&need_vec, processor, 60);  // 60处理器，90行附近还有排除测试
#elif TEST == 2
    set_need_vec_val(&need_vec, qwq, 1488);  // 1488自喷涂蓝增产，90行附近还有增产剂设置测试
#endif

    puts("need:");
    print_cargo(&need_vec);
    putchar('\n');

    // 根据用户所选公式初始化配方矩阵
    for (int i = 0; i < MAT_SIZ; i++) {
        item_t product = recipe_list[i].product[0].item;
        if (product != none) {
            double product_num = (double)recipe_list[i].product[0].num;
            for (int j = 0; j < 6; j++) {
                item_t resource = recipe_list[i].resource[j].item;
                if (resource != none) {
                    double resource_num = (double)recipe_list[i].resource[j].num;
                    set_recipe_mat_val(&recipe_mat, product, resource, resource_num / product_num);
                }
            }
        }
    }

    // 根据用户选择的增产/加速修改配方矩阵
#if TEST == 1
    exclusion_recipe_mat(&recipe_mat, circuit_board); // 排除电路板产线
#elif TEST == 2
    for (item_t i = iron_ingot; i <= proliferator_mk2; i++)
        set_recipe_mat_speedup(&recipe_mat, i);  // 除了蓝增产剂增产，其他全加速，注意挖矿和自喷涂不需要增产剂
    set_recipe_mat_extra(&recipe_mat, proliferator_mk3);
#endif

    // 根据配方矩阵计算矩阵幂级数
    Mat I_mat;
    MatCreate(&I_mat, MAT_SIZ, MAT_SIZ);
    MatZeros(&I_mat);
    MatEye(&I_mat);

    Mat tmp_mat;
    MatCreate(&tmp_mat, MAT_SIZ, MAT_SIZ);
    MatSub(&I_mat, &recipe_mat, &tmp_mat);

    Mat series_mat;
    MatCreate(&series_mat, MAT_SIZ, MAT_SIZ);
    MatInv(&tmp_mat, &series_mat);

    MatDelete(&I_mat);
    MatDelete(&tmp_mat);

    // 根据需求列表和矩阵幂级数计算物流量总和
    Mat result_vec;
    MatCreate(&result_vec, 1, MAT_SIZ);
    MatMul(&need_vec, &series_mat, &result_vec);

    double time1 = omp_get_wtime();
    printf("time = %lf s\n", time1 - time0);

    // 输出结果
    puts("result:");
    print_cargo(&result_vec);
    putchar('\n');

    return 0;
}