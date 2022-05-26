#pragma once

#include <stdint.h>

#define MAT_SIZ 19  // 物品种类列表的长度

typedef enum {  // 物品种类
    none = 0,
    coal_ore,
    iron_ore,
    copper_ore,
    silicon_ore,
    kimberlite_ore,
    spiniform_stalagmite_ore,

    iron_ingot,
    copper_ingot,
    high_purity_silicon,
    diamond,
    carbon_nanotube,

    circuit_board,
    microcrystalline_component,
    processor,

    proliferator_mk1,
    proliferator_mk2,
    proliferator_mk3,
    qwq
} item_t;

char* item_name[] = {
    "none",
    "coal_ore",
    "iron_ore",
    "copper_ore",
    "silicon_ore",
    "kimberlite_ore",
    "spiniform_stalagmite_ore",

    "iron_ingot",
    "copper_ingot",
    "high_purity_silicon",
    "diamond",
    "carbon_nanotube",

    "circuit_board",
    "microcrystalline_component",
    "processor",

    "proliferator_mk1",
    "proliferator_mk2",
    "proliferator_mk3",
    "qwq"
};

typedef struct {  // 货物，有种类和数量
    item_t item;
    double num;
} cargo_t;

typedef struct {  // 合成公式，多产物公式必须把氢放在第二位也就是product[1]
    cargo_t product[2];
    double time;
    cargo_t resource[6];
} recipe_t;

recipe_t recipe_list[] = {  // 公式表
    {
        {{none, 0}},
        0.0,
        {{none, 0}}
    },
    {
        {{coal_ore, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{iron_ore, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{copper_ore, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{silicon_ore, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{kimberlite_ore, 1}},
        1.0,
        {{none, 0}}
    }, 
    {
        {{spiniform_stalagmite_ore, 1}},
        1.0,
        {{none, 0}}
    },


    {
        {{iron_ingot, 1}},
        1.0,
        {{iron_ore, 1}}
    },
    {
        {{copper_ingot, 1}},
        1.0,
        {{copper_ore, 1}}
    },
    {
        {{high_purity_silicon, 1}},
        2.0,
        {{silicon_ore, 2}}
    },
    {
        {{diamond, 2}},
        1.5,
        {{kimberlite_ore, 1}}
    },
    {
        {{carbon_nanotube, 2}},
        4.0,
        {{spiniform_stalagmite_ore, 2}}
    },

    
    {
        {{circuit_board, 2}},
        1.0,
        {{iron_ingot, 2}, {copper_ore, 1}}
    },
    {
        {{microcrystalline_component, 1}},
        2.0,
        {{high_purity_silicon, 2}, {copper_ingot, 1}}
    },
    {
        {{processor, 1}},
        3.0,
        {{circuit_board, 2}, {microcrystalline_component, 2}}
    },

    {
        {{proliferator_mk1, 1}},
        0.5,
        {{coal_ore, 1}}
    },
    {
        {{proliferator_mk2, 1}},
        1.0,
        {{proliferator_mk1, 2}, {diamond, 1}}
    },
    {
        {{proliferator_mk3, 1}},
        2.0,
        {{proliferator_mk2, 2}, {carbon_nanotube, 1}}
    },
    {
        {{qwq, 1}},
        0.0,
        {{proliferator_mk3, 1}, {qwq, 1.0 / 75.0}}
    }
};