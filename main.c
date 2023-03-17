#include <stdio.h>

#include "dsp_calculater.h"

// 输出整个物品列表
void print_cargo_list(double* cargo_list) {
    for(int i = 0; i < ITEM_NUM; i++)
        if(cargo_list[i] > 1e-15 || cargo_list[i] < -1e-15)
            printf("%s\t\t%lf\n", item_name[i], cargo_list[i]);
}

int main(void) {
    // 创建需求列表
    double need_list[ITEM_NUM] = { 0.0 };

    // 创建设置列表，包括了增产/加速/排除等信息
    request_t request_list[ITEM_NUM] = { 0 };

    // 创建氢来源变量，这个是默认值，别改这里的，要改去测试用例里直接覆盖，还有测试用例不检查错误
    item_t hydrogen_source = hydrogen;

    // 几个测试用例，可以自己加或者修改
#define TEST 4

#if TEST == 1
    need_list[qwq] = 1488;                               // 需求1488自喷涂蓝增产剂
    for(item_t i = none; i <= proliferator_mk2; i++) {  // 将除了蓝增产剂外的产线设置为加速，蓝增产剂设置为增产
        if(i == proliferator_mk3)
            request_list[i] = extra;
        else
            request_list[i] = speedup;
    }
#elif TEST == 2
    need_list[refined_oil] = 120;                        // 需求120油
    need_list[hydrogen] = 30;                            // 需求120氢
    hydrogen_source = refined_oil;                       // 将备用氢来源设置为油
    for(item_t i = none; i <= proliferator_mk3; i++) {  // 将所有产线设置为增产
        request_list[i] = extra;
    }
    request_list[qwq] = exclusion;  // 排除增产剂

#elif TEST == 3
    need_list[white_matrix] = 10000;  // 万糖

#elif TEST == 4
    need_list[orz] = 1000;  // 纯增产千糖

    for(item_t i = none; i <= proliferator_mk3; i++) {  // 将所有其他的产线设置为加速
        if(request_list[i] == 0) {
            request_list[i] = extra;
        }
    }

#endif

    puts("need:");
    print_cargo_list(need_list);
    putchar('\n');

    // 创建物流流量总和列表
    double result_list[ITEM_NUM] = { 0.0 };

    // 求解
    solve(result_list, need_list, request_list, hydrogen_source);

    // 输出结果
    puts("result:");
    print_cargo_list(result_list);
    putchar('\n');

    return 0;
}