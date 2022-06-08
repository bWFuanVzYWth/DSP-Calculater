#pragma once

#include <stdint.h>

#define MAT_SIZ 59  // 物品种类列表的长度

typedef enum {  // 物品种类
    none = 0,

    critical_photon,
    water,
    stone,
    coal_ore,
    iron_ore,
    copper_ore,
    silicon_ore,
    titanium_ore,
    kimberlite_ore,
    spiniform_stalagmite_ore,
    curde_oil,
    hydrogen,
    fire_ice,
    optical_grating_crystal,
    unipolar_magnet,
    organic_crystal,
    fractal_silicon,
    deuterium,

    glass,
    energetic_graphite,
    iron_ingot,
    copper_ingot,
    high_purity_silicon,
    titanium_ingot,
    diamond,
    carbon_nanotube,
    refined_oil,
    graphene,
    crystal_silicon,
    magnet,
    antimatter,

    circuit_board,
    magnetic_coil,
    microcrystalline_component,
    plastic,
    titanium_glass,
    titanium_crystal,
    partical_container,
    casimir_crystal,
    photon_combiner,

    processor,
    partical_boardband,
    plane_filter,
    quantum_chip,
    strange_matter,
    gravition_lens,

    solar_sail,

    blue_matrix,
    red_matrix,
    yellow_matrix,
    purple_matrix,
    green_matrix,
    white_matrix,
    orz,

    proliferator_mk1,
    proliferator_mk2,
    proliferator_mk3,
    qwq
} item_t;

char* item_name[] = {
    "none",

    "critical_photon",
    "water",
    "stone",
    "coal_ore",
    "iron_ore",
    "copper_ore",
    "silicon_ore",
    "titanium_ore",
    "kimberlite_ore",
    "spiniform_stalagmite_ore",
    "curde_oil",
    "hydrogen",
    "fire_ice",
    "optical_grating_crystal",
    "unipolar_magnet",
    "organic_crystal",
    "fractal_silicon",
    "deuterium",

    "glass",
    "energetic_graphite",
    "iron_ingot",
    "copper_ingot",
    "high_purity_silicon",
    "titanium_ingot",
    "diamond",
    "carbon_nanotube",
    "refined_oil",
    "graphene",
    "crystal_silicon",
    "magnet",
    "antimatter",

    "circuit_board",
    "magnetic_coil",
    "microcrystalline_component",
    "plastic",
    "titanium_glass",
    "titanium_crystal",
    "partical_container",
    "casimir_crystal",
    "photon_combiner",

    "processor",
    "partical_boardband",
    "plane_filter",
    "quantum_chip",
    "strange_matter",
    "gravition_lens",

    "solar_sail",

    "blue_matrix",
    "red_matrix",
    "yellow_matrix",
    "purple_matrix",
    "green_matrix",
    "white_matrix",
    "orz",

    "proliferator_mk1",
    "proliferator_mk2",
    "proliferator_mk3",
    "qwq"
};

typedef struct {  // 货物，有种类和数量
    item_t item;
    double num;
} cargo_t;

typedef struct {  // 合成公式
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
        {{critical_photon, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{water, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{stone, 1}},
        1.0,
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
        {{titanium_ore, 1}},
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
        {{curde_oil, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{hydrogen, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{fire_ice, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{optical_grating_crystal, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{unipolar_magnet, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{organic_crystal, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{fractal_silicon, 1}},
        1.0,
        {{none, 0}}
    },
    {
        {{deuterium, 1}},
        1.0,
        {{none, 0}}
    },

    {
        {{glass, 1}},
        2.0,
        {{stone, 2}}
    },
    {
        {{energetic_graphite, 1}},
        2.0,
        {{coal_ore, 2}}
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
        {{titanium_ingot, 1}},
        2.0,
        {{titanium_ore, 2}}
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
        {{refined_oil, 2}, {hydrogen, 1}},
        4.0,
        {{curde_oil, 2}}
    },
    {
        {{graphene, 2}, {hydrogen, 1}},
        2.0,
        {{fire_ice, 2}}
    },
    {
        {{crystal_silicon, 2}},
        1.5,
        {{fractal_silicon, 1}}
    },
    {
        {{magnet, 1}},
        1.5,
        {{iron_ore, 1}}
    },
    {
        {{antimatter, 2}, {hydrogen, 2}},
        2.0,
        {{critical_photon, 2}}
    },
    
    {
        {{circuit_board, 2}},
        1.0,
        {{iron_ingot, 2}, {copper_ingot, 1}}
    },
    {
        {{magnetic_coil, 2}},
        1.0,
        {{magnet, 2}, {copper_ingot, 1}}
    },
    {
        {{microcrystalline_component, 1}},
        2.0,
        {{high_purity_silicon, 2}, {copper_ingot, 1}}
    },
    {
        {{plastic, 1}},
        3.0,
        {{refined_oil, 2}, {energetic_graphite, 1}}
    },
    {
        {{titanium_glass, 2}},
        5.0,
        {{glass, 2}, {titanium_ingot, 2}, {water, 2}}
    },
    {
        {{titanium_crystal, 1}},
        4.0,
        {{organic_crystal, 1}, {titanium_ingot, 3}}
    },
    {
        {{partical_container, 1}},
        4.0,
        {{unipolar_magnet, 10}, {copper_ingot, 2}}
    },
    {
        {{casimir_crystal, 1}},
        4.0,
        {{optical_grating_crystal, 4}, {graphene, 2}, {hydrogen, 12}}
    },
    {
        {{photon_combiner, 1}},
        3.0,
        {{optical_grating_crystal, 1}, {circuit_board, 1}}
    },

    {
        {{processor, 1}},
        3.0,
        {{circuit_board, 2}, {microcrystalline_component, 2}}
    },
    {
        {{partical_boardband, 1}},
        8.0,
        {{carbon_nanotube, 2}, {crystal_silicon, 2}, {plastic, 1}}
    },
    {
        {{plane_filter, 1}},
        12.0,
        {{casimir_crystal, 1}, {titanium_glass, 2}}
    },
    {
        {{quantum_chip, 1}},
        6.0,
        {{processor, 2}, {plane_filter, 2}}
    },
    {
        {{strange_matter, 1}},
        8.0,
        {{partical_container, 2}, {iron_ingot, 2}, {deuterium, 10}}
    },
    {
        {{gravition_lens, 1}},
        6.0,
        {{diamond, 4}, {strange_matter, 1}}
    },
    {
        {{solar_sail, 2}},
        4.0,
        {{photon_combiner, 1}, {graphene, 1}}
    },

    {
        {{blue_matrix, 1}},
        3.0,
        {{circuit_board, 1}, {magnetic_coil, 1}}
    },
    {
        {{red_matrix, 1}},
        6.0,
        {{energetic_graphite, 2}, {hydrogen, 2}}
    },
    {
        {{yellow_matrix, 1}},
        8.0,
        {{diamond, 1}, {titanium_crystal, 1}}
    },
    {
        {{purple_matrix, 1}},
        10.0,
        {{processor, 2}, {partical_boardband, 1}}
    },
    {
        {{green_matrix, 2}},
        24.0,
        {{gravition_lens, 1}, {quantum_chip, 1}}
    },
    {
        {{white_matrix, 1}},
        15.0,
        {{blue_matrix, 1}, {red_matrix, 1}, {yellow_matrix, 1}, {purple_matrix, 1}, {green_matrix, 1}, {antimatter, 1}}
    },
    {
        {{orz, 1}},
        1.0 / 30.0,
        {{white_matrix, 1}, {qwq, 1.0 / 75.0}}
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
        1.0 / 30.0,
        {{proliferator_mk3, 1}, {qwq, 1.0 / 75.0}}
    }
};