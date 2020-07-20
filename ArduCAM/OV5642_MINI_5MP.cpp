#include "OV5642_MINI_5MP.h"
#include "Arduino.h"
#include "OV5642_regs.h"

OV5642_MINI_5MP::OV5642_MINI_5MP(bool is_plus)
{
    is_plus_model = is_plus;
    sensor_addr = 0x78;
}

void OV5642_MINI_5MP::InitCAM()
{
    wrSensorReg16_8(0x3008, 0x80);
    if (m_fmt == RAW_FMT)
    {
        //Init and set 640x480;
        wrSensorRegs16_8(RAW_1280x960);
        wrSensorRegs16_8(RAW_640x480);
    }
    else
    {
        wrSensorRegs16_8(QVGA_Preview);
        delay(100);
        if (m_fmt == JPEG_FMT)
        {
            delay(100);
            wrSensorRegs16_8(JPEG_Capture_QSXGA);
            wrSensorRegs16_8(JPEG_320x240);
            delay(100);
            wrSensorReg16_8(0x3818, 0xa8);
            wrSensorReg16_8(0x3621, 0x10);
            wrSensorReg16_8(0x3801, 0xb0);
            if (is_plus_model)
            {
                wrSensorReg16_8(0x4407, 0x04);
            }
            else
            {
                wrSensorReg16_8(0x4407, 0x0C);
            }
            wrSensorReg16_8(0x5888, 0x00);
        }
        else
        {
            uint8_t reg_val;
            wrSensorReg16_8(0x4740, 0x21);
            wrSensorReg16_8(0x501e, 0x2a);
            wrSensorReg16_8(0x5002, 0xf8);
            wrSensorReg16_8(0x501f, 0x01);
            wrSensorReg16_8(0x4300, 0x61);
            rdSensorReg16_8(0x3818, &reg_val);
            wrSensorReg16_8(0x3818, (reg_val | 0x60) & 0xff);
            rdSensorReg16_8(0x3621, &reg_val);
            wrSensorReg16_8(0x3621, reg_val & 0xdf);
        }
    }
}

void OV5642_MINI_5MP::SetImageSize(Image_Size size)
{
    switch (size)
    {
    case r640x480:
        wrSensorRegs16_8(RAW_1280x960);
        wrSensorRegs16_8(RAW_640x480);
        break;
    case r1280x960:
        wrSensorRegs16_8(RAW_1280x960);
        break;
    case r1920x1080:
        wrSensorRegs16_8(RAW);
        wrSensorRegs16_8(RAW_1920x1080);
        break;
    case r2592x1944:
        wrSensorRegs16_8(RAW);
        break;
    case j320x240:
        wrSensorRegs16_8(JPEG_320x240);
        break;
    case j640x480:
        wrSensorRegs16_8(JPEG_640x480);
        break;
    case j1024x768:
        wrSensorRegs16_8(JPEG_1024x768);
        break;
    case j1280x960:
        wrSensorRegs16_8(JPEG_1280x960);
        break;
    case j1600x1200:
        wrSensorRegs16_8(JPEG_1600x1200);
        break;
    case j2048x1536:
        wrSensorRegs16_8(JPEG_2048x1536);
        break;
    case j2592x1944:
        wrSensorRegs16_8(JPEG_2592x1944);
        break;
    default:
        wrSensorRegs16_8(JPEG_320x240);
        break;
    }
}

void OV5642_MINI_5MP::SetLightMode(Light_Mode mode)
{
    switch (mode)
    {
    case Advanced_White_Balance:
        wrSensorReg16_8(0x3406, 0x0);
        wrSensorReg16_8(0x5192, 0x04);
        wrSensorReg16_8(0x5191, 0xf8);
        wrSensorReg16_8(0x518d, 0x26);
        wrSensorReg16_8(0x518f, 0x42);
        wrSensorReg16_8(0x518e, 0x2b);
        wrSensorReg16_8(0x5190, 0x42);
        wrSensorReg16_8(0x518b, 0xd0);
        wrSensorReg16_8(0x518c, 0xbd);
        wrSensorReg16_8(0x5187, 0x18);
        wrSensorReg16_8(0x5188, 0x18);
        wrSensorReg16_8(0x5189, 0x56);
        wrSensorReg16_8(0x518a, 0x5c);
        wrSensorReg16_8(0x5186, 0x1c);
        wrSensorReg16_8(0x5181, 0x50);
        wrSensorReg16_8(0x5184, 0x20);
        wrSensorReg16_8(0x5182, 0x11);
        wrSensorReg16_8(0x5183, 0x0);
        break;
    case Simple_White_Balance:
        wrSensorReg16_8(0x3406, 0x00);
        wrSensorReg16_8(0x5183, 0x80);
        wrSensorReg16_8(0x5191, 0xff);
        wrSensorReg16_8(0x5192, 0x00);
        break;
    case Sunny:
        wrSensorReg16_8(0x3406, 0x1);
        wrSensorReg16_8(0x3400, 0x7);
        wrSensorReg16_8(0x3401, 0x32);
        wrSensorReg16_8(0x3402, 0x4);
        wrSensorReg16_8(0x3403, 0x0);
        wrSensorReg16_8(0x3404, 0x5);
        wrSensorReg16_8(0x3405, 0x36);
        break;
    case Tungsten:
        wrSensorReg16_8(0x3406, 0x1);
        wrSensorReg16_8(0x3400, 0x4);
        wrSensorReg16_8(0x3401, 0x88);
        wrSensorReg16_8(0x3402, 0x4);
        wrSensorReg16_8(0x3403, 0x0);
        wrSensorReg16_8(0x3404, 0x8);
        wrSensorReg16_8(0x3405, 0xb6);
        break;
    case Fluorescent:
        wrSensorReg16_8(0x3406, 0x1);
        wrSensorReg16_8(0x3400, 0x6);
        wrSensorReg16_8(0x3401, 0x13);
        wrSensorReg16_8(0x3402, 0x4);
        wrSensorReg16_8(0x3403, 0x0);
        wrSensorReg16_8(0x3404, 0x7);
        wrSensorReg16_8(0x3405, 0xe2);
        break;
    case Cloudy:
        wrSensorReg16_8(0x3406, 0x1);
        wrSensorReg16_8(0x3400, 0x7);
        wrSensorReg16_8(0x3401, 0x88);
        wrSensorReg16_8(0x3402, 0x4);
        wrSensorReg16_8(0x3403, 0x0);
        wrSensorReg16_8(0x3404, 0x5);
        wrSensorReg16_8(0x3405, 0x0);
        break;
    default:
        break;
    }
}

void OV5642_MINI_5MP::SetColorSaturation(Saturation saturation)
{
    switch (saturation)
    {
    case Plus_4:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5583, 0x80);
        wrSensorReg16_8(0x5584, 0x80);
        wrSensorReg16_8(0x5580, 0x02);
        break;
    case Plus_3:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5583, 0x70);
        wrSensorReg16_8(0x5584, 0x70);
        wrSensorReg16_8(0x5580, 0x02);
        break;
    case Plus_2:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5583, 0x60);
        wrSensorReg16_8(0x5584, 0x60);
        wrSensorReg16_8(0x5580, 0x02);
        break;
    case Plus_1:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5583, 0x50);
        wrSensorReg16_8(0x5584, 0x50);
        wrSensorReg16_8(0x5580, 0x02);
        break;
    case Plus_0:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5583, 0x40);
        wrSensorReg16_8(0x5584, 0x40);
        wrSensorReg16_8(0x5580, 0x02);
        break;
    case Minus_1:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5583, 0x30);
        wrSensorReg16_8(0x5584, 0x30);
        wrSensorReg16_8(0x5580, 0x02);
        break;
    case Minus_2:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5583, 0x20);
        wrSensorReg16_8(0x5584, 0x20);
        wrSensorReg16_8(0x5580, 0x02);
        break;
    case Minus_3:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5583, 0x10);
        wrSensorReg16_8(0x5584, 0x10);
        wrSensorReg16_8(0x5580, 0x02);
        break;
    case Minus_4:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5583, 0x00);
        wrSensorReg16_8(0x5584, 0x00);
        wrSensorReg16_8(0x5580, 0x02);
        break;
    }
}

void OV5642_MINI_5MP::SetBrightness(Brightness brightness)
{
    switch (brightness)
    {
    case Plus_4:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5589, 0x40);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Plus_3:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5589, 0x30);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Plus_2:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5589, 0x20);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Plus_1:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5589, 0x10);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Plus_0:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5589, 0x00);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Minus_1:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5589, 0x10);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x558a, 0x08);
        break;
    case Minus_2:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5589, 0x20);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x558a, 0x08);
        break;
    case Minus_3:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5589, 0x30);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x558a, 0x08);
        break;
    case Minus_4:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5589, 0x40);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x558a, 0x08);
        break;
    }
}

void OV5642_MINI_5MP::SetHue(Hue hue)
{
    switch (hue)
    {
    case Minus_180:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x80);
        wrSensorReg16_8(0x5582, 0x00);
        wrSensorReg16_8(0x558a, 0x32);
        break;
    case Minus_150:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x6f);
        wrSensorReg16_8(0x5582, 0x40);
        wrSensorReg16_8(0x558a, 0x32);
        break;
    case Minus_120:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x40);
        wrSensorReg16_8(0x5582, 0x6f);
        wrSensorReg16_8(0x558a, 0x32);
        break;
    case Minus_90:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x00);
        wrSensorReg16_8(0x5582, 0x80);
        wrSensorReg16_8(0x558a, 0x02);
        break;
    case Minus_60:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x40);
        wrSensorReg16_8(0x5582, 0x6f);
        wrSensorReg16_8(0x558a, 0x02);
        break;
    case Minus_30:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x6f);
        wrSensorReg16_8(0x5582, 0x40);
        wrSensorReg16_8(0x558a, 0x02);
        break;
    case Minus_0:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x80);
        wrSensorReg16_8(0x5582, 0x00);
        wrSensorReg16_8(0x558a, 0x01);
        break;
    case Plus_30:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x6f);
        wrSensorReg16_8(0x5582, 0x40);
        wrSensorReg16_8(0x558a, 0x01);
        break;
    case Plus_60:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x40);
        wrSensorReg16_8(0x5582, 0x6f);
        wrSensorReg16_8(0x558a, 0x01);
        break;
    case Plus_90:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x00);
        wrSensorReg16_8(0x5582, 0x80);
        wrSensorReg16_8(0x558a, 0x31);
        break;
    case Plus_120:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x40);
        wrSensorReg16_8(0x5582, 0x6f);
        wrSensorReg16_8(0x558a, 0x31);
        break;
    case Plus_150:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x01);
        wrSensorReg16_8(0x5581, 0x6f);
        wrSensorReg16_8(0x5582, 0x40);
        wrSensorReg16_8(0x558a, 0x31);
        break;
    }
}

void OV5642_MINI_5MP::SetContrast(Contrast contrast)
{
    switch (contrast)
    {
    case Plus_4:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x5587, 0x30);
        wrSensorReg16_8(0x5588, 0x30);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Plus_3:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x5587, 0x2c);
        wrSensorReg16_8(0x5588, 0x2c);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Plus_2:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x5587, 0x28);
        wrSensorReg16_8(0x5588, 0x28);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Plus_1:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x5587, 0x24);
        wrSensorReg16_8(0x5588, 0x24);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Plus_0:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x5587, 0x20);
        wrSensorReg16_8(0x5588, 0x20);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Minus_1:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x5587, 0x1C);
        wrSensorReg16_8(0x5588, 0x1C);
        wrSensorReg16_8(0x558a, 0x1C);
        break;
    case Minus_2:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x5587, 0x18);
        wrSensorReg16_8(0x5588, 0x18);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Minus_3:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x5587, 0x14);
        wrSensorReg16_8(0x5588, 0x14);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    case Minus_4:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x04);
        wrSensorReg16_8(0x5587, 0x10);
        wrSensorReg16_8(0x5588, 0x10);
        wrSensorReg16_8(0x558a, 0x00);
        break;
    }
}

void OV5642_MINI_5MP::SetSpecialEffects(Special_Effects effect)
{
    switch (effect)
    {
    case Bluish:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x18);
        wrSensorReg16_8(0x5585, 0xa0);
        wrSensorReg16_8(0x5586, 0x40);
        break;
    case Greenish:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x18);
        wrSensorReg16_8(0x5585, 0x60);
        wrSensorReg16_8(0x5586, 0x60);
        break;
    case Reddish:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x18);
        wrSensorReg16_8(0x5585, 0x80);
        wrSensorReg16_8(0x5586, 0xc0);
        break;
    case BW:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x18);
        wrSensorReg16_8(0x5585, 0x80);
        wrSensorReg16_8(0x5586, 0x80);
        break;
    case Negative:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x40);
        break;

    case Sepia:
        wrSensorReg16_8(0x5001, 0xff);
        wrSensorReg16_8(0x5580, 0x18);
        wrSensorReg16_8(0x5585, 0x40);
        wrSensorReg16_8(0x5586, 0xa0);
        break;
    case Normal:
        wrSensorReg16_8(0x5001, 0x7f);
        wrSensorReg16_8(0x5580, 0x00);
        break;
    }
}

void OV5642_MINI_5MP::SetSharpness(Sharpness sharpness)
{
    switch (sharpness)
    {
    case Auto:
        wrSensorReg16_8(0x530A, 0x00);
        wrSensorReg16_8(0x530c, 0x0);
        wrSensorReg16_8(0x530d, 0xc);
        wrSensorReg16_8(0x5312, 0x40);
        break;
    case Auto1:
        wrSensorReg16_8(0x530A, 0x00);
        wrSensorReg16_8(0x530c, 0x4);
        wrSensorReg16_8(0x530d, 0x18);
        wrSensorReg16_8(0x5312, 0x20);
        break;
    case Auto2:
        wrSensorReg16_8(0x530A, 0x00);
        wrSensorReg16_8(0x530c, 0x8);
        wrSensorReg16_8(0x530d, 0x30);
        wrSensorReg16_8(0x5312, 0x10);
        break;
    case Off:
        wrSensorReg16_8(0x530A, 0x08);
        wrSensorReg16_8(0x531e, 0x00);
        wrSensorReg16_8(0x531f, 0x00);
        break;
    case Manual1:
        wrSensorReg16_8(0x530A, 0x08);
        wrSensorReg16_8(0x531e, 0x04);
        wrSensorReg16_8(0x531f, 0x04);
        break;
    case Manual2:
        wrSensorReg16_8(0x530A, 0x08);
        wrSensorReg16_8(0x531e, 0x08);
        wrSensorReg16_8(0x531f, 0x08);
        break;
    case Manual3:
        wrSensorReg16_8(0x530A, 0x08);
        wrSensorReg16_8(0x531e, 0x0c);
        wrSensorReg16_8(0x531f, 0x0c);
        break;
    case Manual4:
        wrSensorReg16_8(0x530A, 0x08);
        wrSensorReg16_8(0x531e, 0x0f);
        wrSensorReg16_8(0x531f, 0x0f);
        break;
    case Manual5:
        wrSensorReg16_8(0x530A, 0x08);
        wrSensorReg16_8(0x531e, 0x1f);
        wrSensorReg16_8(0x531f, 0x1f);
        break;
    }
}

void OV5642_MINI_5MP::SetExposureLevel(Exposure level)
{
    switch (level)
    {
    case Minus_17:
        wrSensorReg16_8(0x3a0f, 0x10);
        wrSensorReg16_8(0x3a10, 0x08);
        wrSensorReg16_8(0x3a1b, 0x10);
        wrSensorReg16_8(0x3a1e, 0x08);
        wrSensorReg16_8(0x3a11, 0x20);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Minus_13:
        wrSensorReg16_8(0x3a0f, 0x18);
        wrSensorReg16_8(0x3a10, 0x10);
        wrSensorReg16_8(0x3a1b, 0x18);
        wrSensorReg16_8(0x3a1e, 0x10);
        wrSensorReg16_8(0x3a11, 0x30);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Minus_10:
        wrSensorReg16_8(0x3a0f, 0x20);
        wrSensorReg16_8(0x3a10, 0x18);
        wrSensorReg16_8(0x3a11, 0x41);
        wrSensorReg16_8(0x3a1b, 0x20);
        wrSensorReg16_8(0x3a1e, 0x18);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Minus_7:
        wrSensorReg16_8(0x3a0f, 0x28);
        wrSensorReg16_8(0x3a10, 0x20);
        wrSensorReg16_8(0x3a11, 0x51);
        wrSensorReg16_8(0x3a1b, 0x28);
        wrSensorReg16_8(0x3a1e, 0x20);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Minus_3:
        wrSensorReg16_8(0x3a0f, 0x30);
        wrSensorReg16_8(0x3a10, 0x28);
        wrSensorReg16_8(0x3a11, 0x61);
        wrSensorReg16_8(0x3a1b, 0x30);
        wrSensorReg16_8(0x3a1e, 0x28);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Default:
        wrSensorReg16_8(0x3a0f, 0x38);
        wrSensorReg16_8(0x3a10, 0x30);
        wrSensorReg16_8(0x3a11, 0x61);
        wrSensorReg16_8(0x3a1b, 0x38);
        wrSensorReg16_8(0x3a1e, 0x30);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Plus_3:
        wrSensorReg16_8(0x3a0f, 0x40);
        wrSensorReg16_8(0x3a10, 0x38);
        wrSensorReg16_8(0x3a11, 0x71);
        wrSensorReg16_8(0x3a1b, 0x40);
        wrSensorReg16_8(0x3a1e, 0x38);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Plus_7:
        wrSensorReg16_8(0x3a0f, 0x48);
        wrSensorReg16_8(0x3a10, 0x40);
        wrSensorReg16_8(0x3a11, 0x80);
        wrSensorReg16_8(0x3a1b, 0x48);
        wrSensorReg16_8(0x3a1e, 0x40);
        wrSensorReg16_8(0x3a1f, 0x20);
        break;
    case Plus_10:
        wrSensorReg16_8(0x3a0f, 0x50);
        wrSensorReg16_8(0x3a10, 0x48);
        wrSensorReg16_8(0x3a11, 0x90);
        wrSensorReg16_8(0x3a1b, 0x50);
        wrSensorReg16_8(0x3a1e, 0x48);
        wrSensorReg16_8(0x3a1f, 0x20);
        break;
    case Plus_13:
        wrSensorReg16_8(0x3a0f, 0x58);
        wrSensorReg16_8(0x3a10, 0x50);
        wrSensorReg16_8(0x3a11, 0x91);
        wrSensorReg16_8(0x3a1b, 0x58);
        wrSensorReg16_8(0x3a1e, 0x50);
        wrSensorReg16_8(0x3a1f, 0x20);
        break;
    case Plus_17:
        wrSensorReg16_8(0x3a0f, 0x60);
        wrSensorReg16_8(0x3a10, 0x58);
        wrSensorReg16_8(0x3a11, 0xa0);
        wrSensorReg16_8(0x3a1b, 0x60);
        wrSensorReg16_8(0x3a1e, 0x58);
        wrSensorReg16_8(0x3a1f, 0x20);
        break;
    }
}

void OV5642_MINI_5MP::SetMirrorFlip(MirrorFlip style)
{
    uint8_t reg_val;
    switch (style)
    {
    case MIRROR:
        rdSensorReg16_8(0x3818, &reg_val);
        reg_val = reg_val | 0x00;
        reg_val = reg_val & 0x9F;
        wrSensorReg16_8(0x3818, reg_val);
        rdSensorReg16_8(0x3621, &reg_val);
        reg_val = reg_val | 0x20;
        wrSensorReg16_8(0x3621, reg_val);
        break;
    case FLIP:
        rdSensorReg16_8(0x3818, &reg_val);
        reg_val = reg_val | 0x20;
        reg_val = reg_val & 0xbF;
        wrSensorReg16_8(0x3818, reg_val);
        rdSensorReg16_8(0x3621, &reg_val);
        reg_val = reg_val | 0x20;
        wrSensorReg16_8(0x3621, reg_val);
        break;
    case MIRROR_FLIP:
        rdSensorReg16_8(0x3818, &reg_val);
        reg_val = reg_val | 0x60;
        reg_val = reg_val & 0xFF;
        wrSensorReg16_8(0x3818, reg_val);
        rdSensorReg16_8(0x3621, &reg_val);
        reg_val = reg_val & 0xdf;
        wrSensorReg16_8(0x3621, reg_val);
        break;
    case NORMAL:
        rdSensorReg16_8(0x3818, &reg_val);
        reg_val = reg_val | 0x40;
        reg_val = reg_val & 0xdF;
        wrSensorReg16_8(0x3818, reg_val);
        rdSensorReg16_8(0x3621, &reg_val);
        reg_val = reg_val & 0xdf;
        wrSensorReg16_8(0x3621, reg_val);
        break;
    }
}

void OV5642_MINI_5MP::SetCompression(Compression quality)
{
    switch (quality)
    {
    case High:
        wrSensorReg16_8(0x4407, 0x02);
        break;
    case Default:
        wrSensorReg16_8(0x4407, 0x04);
        break;
    case Low:
        wrSensorReg16_8(0x4407, 0x08);
        break;
    }
}

void OV5642_MINI_5MP::SetTestPattern(TestPattern pattern)
{
    switch (pattern)
    {
    case Bar:
        wrSensorReg16_8(0x503d, 0x80);
        wrSensorReg16_8(0x503e, 0x00);
        break;
    case Square:
        wrSensorReg16_8(0x503d, 0x85);
        wrSensorReg16_8(0x503e, 0x12);
        break;
    case BWSquare:
        wrSensorReg16_8(0x503d, 0x85);
        wrSensorReg16_8(0x503e, 0x1a);
        break;
    case DLI:
        wrSensorReg16_8(0x4741, 0x4);
        break;
    }
}

bool OV5642_MINI_5MP::checkModule()
{
    uint8_t vid, pid;
    wrSensorReg8_8(0xff, 0x01);
    rdSensorReg8_8(OV5642_CHIPID_HIGH, &vid);
    rdSensorReg8_8(OV5642_CHIPID_LOW, &pid);
    return ((vid != 0x26) && !((pid == 0x41) || (pid == 0x42)));
}