/*********************************
 * description: image resize, from chatgpt auto gen
 * author:      lfy
 * date:        2023.09.06
*********************************/

#include <arm_neon.h>

inline uint8x8_t neon_bilinear_interpolation(const uint8x8_t &src00, const uint8x8_t &src01, const uint8x8_t &src10, const uint8x8_t &src11, const int16x4_t &weightX, const int16x4_t &weightY)
{
    // 计算双线性插值结果
    const int16x4_t result00 = vmull_s8(vreinterpret_s8_u8(src00), weightX);
    const int16x4_t result01 = vmull_s8(vreinterpret_s8_u8(src01), weightX);
    const int16x4_t result10 = vmull_s8(vreinterpret_s8_u8(src10), weightX);
    const int16x4_t result11 = vmull_s8(vreinterpret_s8_u8(src11), weightX);

    const int16x4_t result0 = vadd_s16(vmovl_s8(vget_low_s8(vreinterpretq_s8_u8(vsubq_u8(src01, src00)))), result00);
    const int16x4_t result1 = vadd_s16(vmovl_s8(vget_low_s8(vreinterpretq_s8_u8(vsubq_u8(src11, src10)))), result10);

    const int16x4_t result = vadd_s16(result0, vqrdmulh_s16(vsub_s16(result1, result0), weightY));
    return vqshrn_n_s16(result, 8); // 将结果右移8位，将16位整数还原为8位无符号整数
}

inline uint8x8x4_t neon_bilinear_interpolation(const uint8x8x4_t &src00, const uint8x8x4_t &src01, const uint8x8x4_t &src10, const uint8x8x4_t &src11, float weightX, float weightY)
{
    // 将[0, 1]的浮点权重转为[0, 255]的整数权重
    const int16x4_t weightXInt = vdup_n_s16(static_cast<int16_t>(weightX * 256));
    const int16x4_t weightYInt = vdup_n_s16(static_cast<int16_t>(weightY * 256));

    // 计算双线性插值结果
    const uint8x8_t resultR = neon_bilinear_interpolation(src00.val[0], src01.val[0], src10.val[0], src11.val[0], weightXInt, weightYInt);
    const uint8x8_t resultG = neon_bilinear_interpolation(src00.val[1], src01.val[1], src10.val[1], src11.val[1], weightXInt, weightYInt);
    const uint8x8_t resultB = neon_bilinear_interpolation(src00.val[2], src01.val[2], src10.val[2], src11.val[2], weightXInt, weightYInt);
    const uint8x8_t resultA = neon_bilinear_interpolation(src00.val[3], src01.val[3], src10.val[3], src11.val[3], weightXInt, weightYInt);

    // 将四个颜色通道合并成一个结构体并返回
    return {resultR, resultG, resultB, resultA};
}

void resizeNeon(const unsigned char *src, unsigned char *dst, int srcWidth, int srcHeight, int dstWidth, int dstHeight)
{
    const int numChannels = 3; // 假设图像是RGB格式，3个通道
    const int pixelSize   = 4; // 每个像素4字节，假设是RGBA格式

    // 计算水平和垂直缩放因子
    const float scaleX = (float)srcWidth / dstWidth;
    const float scaleY = (float)srcHeight / dstHeight;

    // 在水平和垂直方向上计算缩放比例的倒数
    const float invScaleX = 1.0 / scaleX;
    const float invScaleY = 1.0 / scaleY;

    // 循环遍历目标图像的像素
    for (int y = 0; y < dstHeight; y++)
    {
        for (int x = 0; x < dstWidth; x += 8)
        {
            // 计算源图像的坐标
            const float srcX = x * scaleX;
            const float srcY = y * scaleY;

            // 计算源图像的四个最近邻像素坐标
            const int srcX0 = static_cast<int>(srcX);
            const int srcX1 = srcX0 + 1;

            const int srcY0 = static_cast<int>(srcY);
            const int srcY1 = srcY0 + 1;

            // 计算源图像的四个最近邻像素
            const unsigned char *srcPtr00 = src + (srcX0 + srcY0 * srcWidth) * numChannels * pixelSize;
            const unsigned char *srcPtr01 = src + (srcX0 + srcY1 * srcWidth) * numChannels * pixelSize;
            const unsigned char *srcPtr10 = src + (srcX1 + srcY0 * srcWidth) * numChannels * pixelSize;
            const unsigned char *srcPtr11 = src + (srcX1 + srcY1 * srcWidth) * numChannels * pixelSize;

            const uint8x8x4_t srcData00 = vld4_u8(srcPtr00);
            const uint8x8x4_t srcData01 = vld4_u8(srcPtr01);
            const uint8x8x4_t srcData10 = vld4_u8(srcPtr10);
            const uint8x8x4_t srcData11 = vld4_u8(srcPtr11);

            // 计算在四个最近邻像素之间的插值权重
            const float weightX = srcX - srcX0;
            const float weightY = srcY - srcY0;

            // 在水平和垂直方向上进行插值
            const uint8x8x4_t dstData = neon_bilinear_interpolation(srcData00, srcData01, srcData10, srcData11, weightX, weightY);

            // 存储插值结果
            vst4_u8(dst + x * numChannels * pixelSize, dstData);
        }

        dst += dstWidth * numChannels * pixelSize;
    }
}