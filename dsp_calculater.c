#include "dsp_calculater.h"

// 设置需求列表中的一项(列表指针, 产物id, 需求多少)
void set_need_vec_val(Mat* p, item_t product, double num) {
    p->element[0][product] = num;
}

// 设置配方矩阵中的一个元素(矩阵指针, 产物id, 原料id, 原料数量)
void set_recipe_mat_element(Mat* p, item_t product, item_t resource, double num) {
    p->element[product][resource] = num;
}

// 给配方矩阵中的某个公式使用自喷涂蓝增产剂进行加速(矩阵指针, 产物id)
void set_recipe_mat_speedup(Mat* p, item_t product) {
    double count = 0.0;
    for(int i = 0; i < ITEM_NUM; i++) {
        if(p->element[product][i] > 0.0) {
            count += p->element[product][i];
        }
    }
    p->element[product][qwq] = count / 75.0;
}

// 给配方矩阵中的某个公式使用自喷涂蓝增产剂进行增产(矩阵指针, 产物id)
void set_recipe_mat_extra(Mat* p, item_t product) {
    double count = 0.0;
    for(int i = 0; i < ITEM_NUM; i++) {
        if(p->element[product][i] > 0.0) {
            p->element[product][i] *= 0.8;
            count += p->element[product][i];
        }
    }
    p->element[product][qwq] = count / 75.0;
}

// 排除某一项的计算(矩阵指针，排除产品id)
void set_recipe_mat_exclusion(Mat* p, item_t product) {
    for(int i = 0; i < ITEM_NUM; i++)
        p->element[product][i] = 0.0;
}

// 遍历设置列表，修改配方矩阵
void request_recipe_mat(request_t* request_list, Mat* p_recipe_mat) {
    for(int i = 0; i < ITEM_NUM; i++) {
        switch(request_list[i]) {
        case exclusion:
        set_recipe_mat_exclusion(p_recipe_mat, i);
        break;
        case speedup:
        set_recipe_mat_speedup(p_recipe_mat, i);
        break;
        case extra:
        set_recipe_mat_extra(p_recipe_mat, i);
        break;
        }
    }
}

void init_recipe_mat(Mat* p_recipe_mat, item_t target_byproduct) {
    // 先把整个公式矩阵初始化为0
    MatZeros(p_recipe_mat);

    for(item_t i = 0; i < ITEM_NUM; i++) {
        // 特判，如果这行对应的是氢就把公式替换为目标产氢公式，如果这行对应的是副产物就直接跳出，这样会让这行全0
        if(i == target_byproduct)
            continue;
        item_t real_recipe = (i == hydrogen) ? target_byproduct : i;

        item_t mainproduct = none;
        double mainproduct_num = 0.0;
        item_t byproduct = none;
        double byproduct_num = 0.0;

        // 确定当前公式的主产物和副产物
        for(int j = 0; j < 2; j++) {
            item_t this_product = recipe_list[real_recipe].product[j].item;
            if(this_product == none)
                continue;
            if(this_product != target_byproduct) {
                mainproduct = this_product;
                mainproduct_num = (double)recipe_list[real_recipe].product[j].num;
                continue;
            }

            item_t another_product = recipe_list[real_recipe].product[1 - j].item;
            if(another_product == none)
                continue;
            if(this_product == target_byproduct) {
                byproduct = this_product;
                byproduct_num = (double)recipe_list[real_recipe].product[j].num;
                continue;
            }
        }

        // 向公式矩阵当前行写入所有原料
        if(mainproduct != none) {
            for(int k = 0; k < 6; k++) {
                item_t resource = recipe_list[real_recipe].resource[k].item;
                double resource_num = (double)recipe_list[real_recipe].resource[k].num;
                set_recipe_mat_element(p_recipe_mat, i, resource, resource_num / mainproduct_num);
            }
        }

        // 将副产物移项到公式右边，视为原料，并且系数为负数，然后写入公式矩阵当前行
        if(byproduct != none) {
            set_recipe_mat_element(p_recipe_mat, i, byproduct, -byproduct_num / mainproduct_num);
        }
    }
}

void try_solve(double* result_list, double* need_list, request_t* request_list, item_t target_byproduct) {
    // 创建需求向量
    Mat need_vec;
    MatCreate(&need_vec, 1, ITEM_NUM);
    MatSetVal(&need_vec, need_list);

    // 创建公式矩阵
    Mat recipe_mat;
    MatCreate(&recipe_mat, ITEM_NUM, ITEM_NUM);
    init_recipe_mat(&recipe_mat, target_byproduct);
    request_recipe_mat(request_list, &recipe_mat);

    // 根据配方矩阵计算矩阵幂级数
    Mat I_mat;
    MatCreate(&I_mat, ITEM_NUM, ITEM_NUM);
    MatZeros(&I_mat);
    MatEye(&I_mat);

    Mat tmp_mat;
    MatCreate(&tmp_mat, ITEM_NUM, ITEM_NUM);
    MatSub(&I_mat, &recipe_mat, &tmp_mat);

    Mat series_mat;
    MatCreate(&series_mat, ITEM_NUM, ITEM_NUM);
    MatInv(&tmp_mat, &series_mat);

    // 计算物流流量
    Mat result_vec;
    MatCreate(&result_vec, 1, ITEM_NUM);
    MatMul(&need_vec, &series_mat, &result_vec);
    for(int i = 0; i < ITEM_NUM; i++)
        result_list[i] = result_vec.element[0][i];

    MatDelete(&need_vec);
    MatDelete(&result_vec);
    MatDelete(&recipe_mat);
    MatDelete(&I_mat);
    MatDelete(&tmp_mat);
    MatDelete(&series_mat);
}

void solve(double* result_list, double* need_list, request_t* request_list, item_t hydrogen_source) {
    try_solve(result_list, need_list, request_list, hydrogen);             // 先把氢视为副产物求解
    if(result_list[hydrogen] > 0.0 && hydrogen_source != hydrogen)    // 如果发现氢不够
        try_solve(result_list, need_list, request_list, hydrogen_source);  // 把备用氢来源作为副产物重新求解
}
