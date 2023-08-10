#pragma once

#include <iostream>
#include <vector>
#include <arm_neon.h>

static void VecPrint(float32x4_t vec)
{
    std::vector<float> dst(4);
    vst1q_f32(dst.data(), vec);
    std::cout << std::endl;
    for (size_t i = 0; i < dst.size(); ++i) {
        std::cout << static_cast<double>(dst[i]) << " ";
    }
    std::cout << std::endl;
}

static void VecPrint(uint8x16_t vec)
{
    std::vector<uint8_t> dst(16);
    vst1q_u8(dst.data(), vec);
    std::cout << std::endl;
    for (size_t i = 0; i < dst.size(); ++i) {
        std::cout << static_cast<double>(dst[i]) << " ";
    }
    std::cout << std::endl;
}