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
    for (int i = 0; i < MAT_SIZ; i++) {
        if (p->element[product][i] > 0.0) {
            count += p->element[product][i];  // 统计这个公式中需要喷涂的物品数量
        }
    }
    p->element[product][qwq] = count / 75.0;
}

// 给配方矩阵中的某个公式使用自喷涂蓝增产剂进行增产(矩阵指针, 产物id)
void set_recipe_mat_extra(Mat* p, item_t product) {
    double count = 0.0;
    for (int i = 0; i < MAT_SIZ; i++) {
        if (p->element[product][i] > 0.0) {
            p->element[product][i] *= 0.8;
            count += p->element[product][i];  // 把公式中的原料全部*0.8，再统计，顺序不能反
        }
    }
    p->element[product][qwq] = count / 75.0;
}

// 排除某一项的计算(矩阵指针，排除产品id)
void exclusion_recipe_mat(Mat* p, item_t product) {
    for (int i = 0; i < MAT_SIZ; i++)
        p->element[product][i] = 0.0;
}

// 输出整个物品列表
void print_cargo(double* v) {
    for (int i = 0; i < MAT_SIZ; i++) {
        if (v[i] > 1e-15 || v[i] < -1e-15) {
            printf("%s\t\t%lf\n", item_name[i], v[i]);
        }
    }
}

// 遍历设置列表，修改配方矩阵
void request_recipe_mat(int* request_list, Mat* p_recipe_mat) {
    for (int i = 0; i < MAT_SIZ; i++) {
        switch (request_list[i]) {
            case 0:
                break;
            case -1:
                exclusion_recipe_mat(p_recipe_mat, i);
                break;
            case 1:
                set_recipe_mat_speedup(p_recipe_mat, i);
                break;
            case 2:
                set_recipe_mat_extra(p_recipe_mat, i);
                break;
        }
    }
}

void solve(double* result_list, double* need_list, int* request_list, item_t byproduct) {
    // 创建需求向量
    Mat need_vec;
    MatCreate(&need_vec, 1, MAT_SIZ);
    MatSetVal(&need_vec, need_list);

    // 创建公式矩阵
    Mat recipe_mat;
    MatCreate(&recipe_mat, MAT_SIZ, MAT_SIZ);
    MatZeros(&recipe_mat);

    // 根据用户所选公式初始化配方矩阵
    for (int i = 0; i < MAT_SIZ; i++) {
        item_t product;
        double product_num;

        for (int j = 0; j < 2; j++) {
            // 这句可读性不行，意思是如果当前产物种类和副产物相同，并且公式没有其他产物，说明当前产物就是公式副产物
            if (recipe_list[i].product[j].item == byproduct && recipe_list[i].product[1 - j].item != none) {
                double byproduct_num = -((double)recipe_list[i].product[j].num / (double)recipe_list[i].product[1 - j].num);
                set_recipe_mat_val(&recipe_mat, recipe_list[i].product[1 - j].item, byproduct, byproduct_num);
            } else if (recipe_list[i].product[j].item != none) {  //否则还不为空，说明是主产物
                product = recipe_list[i].product[j].item;
                product_num = (double)recipe_list[i].product[j].num;
            }
        }

        for (int k = 0; k < 6; k++) {
            item_t resource = recipe_list[i].resource[k].item;
            if (resource == none) {
                break;
            }
            double resource_num = (double)recipe_list[i].resource[k].num;
            set_recipe_mat_val(&recipe_mat, product, resource, resource_num / product_num);
        }
    }

    request_recipe_mat(request_list, &recipe_mat);

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

    Mat result_vec;
    MatCreate(&result_vec, 1, MAT_SIZ);

    // 计算物流流量
    MatMul(&need_vec, &series_mat, &result_vec);
    for (int i = 0; i < MAT_SIZ; i++)
        result_list[i] = result_vec.element[0][i];

    MatDelete(&need_vec);
    MatDelete(&result_vec);
    MatDelete(&recipe_mat);
    MatDelete(&I_mat);
    MatDelete(&tmp_mat);
    MatDelete(&series_mat);
}

int main(void) {
    double time0 = omp_get_wtime();

    // 创建需求列表
    double need_list[MAT_SIZ] = {0.0};

    // 创建设置列表，包括了增产/加速/排除等信息，暂时是硬编码的，以后换成枚举
    // 0  不做任何更改
    // -1 排除
    // 1  加速
    // 2  增产
    int request_list[MAT_SIZ] = {0};

    // 根据用户需求初始化需求列表
#define TEST 3

#if TEST == 1
    need_list[processor] = 60;
    request_list[circuit_board] = -1;  //排除电路板

#elif TEST == 2
    need_list[qwq] = 1488;
    for (item_t i = iron_ingot; i <= proliferator_mk2; i++)  // 遍历蓝增产剂以外的所有产线
        request_list[i] = 1;                                 // 将这些这些产线设置为加速
    request_list[proliferator_mk3] = 2;                      // 将蓝增产剂产线设置为增产

#elif TEST == 3
    need_list[refined_oil] = 120;
    need_list[hydrogen] = 30;

    for (item_t i = iron_ingot; i <= proliferator_mk3; i++)  // 遍历所有产线
        request_list[i] = 2;                                 // 将这些产线设置为增产
    request_list[qwq] = -1;                                  // 排除增产剂
#endif

    // 创建物流流量总和列表
    double result_list[MAT_SIZ] = {0.0};

    // 求解
    solve(result_list, need_list, request_list, hydrogen);         // 先把氢视为副产物求解
    if (result_list[hydrogen] > 0.0)                               // 如果发现氢不够
        solve(result_list, need_list, request_list, refined_oil);  // 把精炼油作为副产物产物重新求解

    // 输出结果
    double time1 = omp_get_wtime();
    printf("time = %lf s\n", time1 - time0);

    puts("result:");
    print_cargo(result_list);
    putchar('\n');

    return 0;
}