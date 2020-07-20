#include "OV5640_MINI_5MP.h"
#include "Arduino.h"
#include "ov5640_regs.h"

OV5640_MINI_5MP::OV5640_MINI_5MP(bool is_plus)
{
    is_plus_model = is_plus;
    sensor_addr = 0x78;
}

void OV5640_MINI_5MP::InitCAM()
{
    delay(100);
    if (m_fmt == JPEG_FMT)
    {
        wrSensorReg16_8(0x3103, 0x11);
        wrSensorReg16_8(0x3008, 0x82);
        delay(100);
        wrSensorRegs16_8(YUV_Sensor_Dvp_Init);
        delay(500);
        wrSensorRegs16_8(JPEG_QSXGA);
        wrSensorRegs16_8(QSXGA2QVGA);
        if (is_plus_model)
        {
            wrSensorReg16_8(0x4407, 0x04);
        }
        else
        {
            wrSensorReg16_8(0x4407, 0x0C);
        }
    }
    else
    {
        wrSensorReg16_8(0x3103, 0x11);
        wrSensorReg16_8(0x3008, 0x82);
        delay(500);
        wrSensorRegs16_8(YUV_Sensor_Dvp_Init);
        wrSensorRegs16_8(RGB_QVGA);
    }
}

void OV5640_MINI_5MP::SetImageSize(Image_Size size)
{
    switch (size)
    {
    case j320x240:
        wrSensorRegs16_8(QSXGA2QVGA);
        break;
    case j352x288:
        wrSensorRegs16_8(QSXGA2CIF);
        break;
    case j640x480:
        wrSensorRegs16_8(QSXGA2VGA);
        break;
    case j800x480:
        wrSensorRegs16_8(QSXGA2WVGA);
        break;
    case j1024x768:
        wrSensorRegs16_8(QSXGA2XGA);
        break;
    case j1280x960:
        wrSensorRegs16_8(QSXGA2SXGA);
        break;
    case j1600x1200:
        wrSensorRegs16_8(QSXGA2UXGA);
        break;
    case j2048x1536:
        wrSensorRegs16_8(QSXGA2QXGA);
        break;
    case j2592x1944:
        wrSensorRegs16_8(JPEG_QSXGA);
        break;
    default:
        //320x240
        wrSensorRegs16_8(QSXGA2QVGA);
        break;
    }
}

void OV5640_MINI_5MP::SetLightMode(Light_Mode mode)
{
    switch (mode)
    {
    case Auto:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x3406, 0x00);
        wrSensorReg16_8(0x3400, 0x04);
        wrSensorReg16_8(0x3401, 0x00);
        wrSensorReg16_8(0x3402, 0x04);
        wrSensorReg16_8(0x3403, 0x00);
        wrSensorReg16_8(0x3404, 0x04);
        wrSensorReg16_8(0x3405, 0x00);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // lanuch group 3
        wrSensorReg16_8(0x5183, 0x0);
        break;
    case Sunny:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x3406, 0x01);
        wrSensorReg16_8(0x3400, 0x06);
        wrSensorReg16_8(0x3401, 0x1c);
        wrSensorReg16_8(0x3402, 0x04);
        wrSensorReg16_8(0x3403, 0x00);
        wrSensorReg16_8(0x3404, 0x04);
        wrSensorReg16_8(0x3405, 0xf3);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // lanuch group 3
        break;
    case Office:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x3406, 0x01);
        wrSensorReg16_8(0x3400, 0x05);
        wrSensorReg16_8(0x3401, 0x48);
        wrSensorReg16_8(0x3402, 0x04);
        wrSensorReg16_8(0x3403, 0x00);
        wrSensorReg16_8(0x3404, 0x07);
        wrSensorReg16_8(0x3405, 0xcf);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // lanuch group 3
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x3406, 0x01);
        wrSensorReg16_8(0x3400, 0x06);
        wrSensorReg16_8(0x3401, 0x48);
        wrSensorReg16_8(0x3402, 0x04);
        wrSensorReg16_8(0x3403, 0x00);
        wrSensorReg16_8(0x3404, 0x04);
        wrSensorReg16_8(0x3405, 0xd3);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // lanuch group 3
        break;
    case Cloudy:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x3406, 0x01);
        wrSensorReg16_8(0x3400, 0x06);
        wrSensorReg16_8(0x3401, 0x48);
        wrSensorReg16_8(0x3402, 0x04);
        wrSensorReg16_8(0x3403, 0x00);
        wrSensorReg16_8(0x3404, 0x04);
        wrSensorReg16_8(0x3405, 0xd3);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // lanuch group 3
        break;
    case Home:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x3406, 0x01);
        wrSensorReg16_8(0x3400, 0x04);
        wrSensorReg16_8(0x3401, 0x10);
        wrSensorReg16_8(0x3402, 0x04);
        wrSensorReg16_8(0x3403, 0x00);
        wrSensorReg16_8(0x3404, 0x08);
        wrSensorReg16_8(0x3405, 0x40);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // lanuch group 3
        break;
    default:
        break;
    }
}

void OV5640_MINI_5MP::SetColorSaturation(Saturation saturation)
{
    switch (saturation)
    {
    case Plus_3:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5381, 0x1c);
        wrSensorReg16_8(0x5382, 0x5a);
        wrSensorReg16_8(0x5383, 0x06);
        wrSensorReg16_8(0x5384, 0x2b);
        wrSensorReg16_8(0x5385, 0xab);
        wrSensorReg16_8(0x5386, 0xd6);
        wrSensorReg16_8(0x5387, 0xda);
        wrSensorReg16_8(0x5388, 0xd6);
        wrSensorReg16_8(0x5389, 0x04);
        wrSensorReg16_8(0x538b, 0x98);
        wrSensorReg16_8(0x538a, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Plus_2:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5381, 0x1c);
        wrSensorReg16_8(0x5382, 0x5a);
        wrSensorReg16_8(0x5383, 0x06);
        wrSensorReg16_8(0x5384, 0x24);
        wrSensorReg16_8(0x5385, 0x8f);
        wrSensorReg16_8(0x5386, 0xb3);
        wrSensorReg16_8(0x5387, 0xb6);
        wrSensorReg16_8(0x5388, 0xb3);
        wrSensorReg16_8(0x5389, 0x03);
        wrSensorReg16_8(0x538b, 0x98);
        wrSensorReg16_8(0x538a, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Plus_1:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5381, 0x1c);
        wrSensorReg16_8(0x5382, 0x5a);
        wrSensorReg16_8(0x5383, 0x06);
        wrSensorReg16_8(0x5384, 0x1f);
        wrSensorReg16_8(0x5385, 0x7a);
        wrSensorReg16_8(0x5386, 0x9a);
        wrSensorReg16_8(0x5387, 0x9c);
        wrSensorReg16_8(0x5388, 0x9a);
        wrSensorReg16_8(0x5389, 0x02);
        wrSensorReg16_8(0x538b, 0x98);
        wrSensorReg16_8(0x538a, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Plus_0:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5381, 0x1c);
        wrSensorReg16_8(0x5382, 0x5a);
        wrSensorReg16_8(0x5383, 0x06);
        wrSensorReg16_8(0x5384, 0x1a);
        wrSensorReg16_8(0x5385, 0x66);
        wrSensorReg16_8(0x5386, 0x80);
        wrSensorReg16_8(0x5387, 0x82);
        wrSensorReg16_8(0x5388, 0x80);
        wrSensorReg16_8(0x5389, 0x02);
        wrSensorReg16_8(0x538b, 0x98);
        wrSensorReg16_8(0x538a, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Minus_1:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5381, 0x1c);
        wrSensorReg16_8(0x5382, 0x5a);
        wrSensorReg16_8(0x5383, 0x06);
        wrSensorReg16_8(0x5384, 0x15);
        wrSensorReg16_8(0x5385, 0x52);
        wrSensorReg16_8(0x5386, 0x66);
        wrSensorReg16_8(0x5387, 0x68);
        wrSensorReg16_8(0x5388, 0x66);
        wrSensorReg16_8(0x5389, 0x02);
        wrSensorReg16_8(0x538b, 0x98);
        wrSensorReg16_8(0x538a, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Minus_2:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5381, 0x1c);
        wrSensorReg16_8(0x5382, 0x5a);
        wrSensorReg16_8(0x5383, 0x06);
        wrSensorReg16_8(0x5384, 0x10);
        wrSensorReg16_8(0x5385, 0x3d);
        wrSensorReg16_8(0x5386, 0x4d);
        wrSensorReg16_8(0x5387, 0x4e);
        wrSensorReg16_8(0x5388, 0x4d);
        wrSensorReg16_8(0x5389, 0x01);
        wrSensorReg16_8(0x538b, 0x98);
        wrSensorReg16_8(0x538a, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Minus_3:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5381, 0x1c);
        wrSensorReg16_8(0x5382, 0x5a);
        wrSensorReg16_8(0x5383, 0x06);
        wrSensorReg16_8(0x5384, 0x0c);
        wrSensorReg16_8(0x5385, 0x30);
        wrSensorReg16_8(0x5386, 0x3d);
        wrSensorReg16_8(0x5387, 0x3e);
        wrSensorReg16_8(0x5388, 0x3d);
        wrSensorReg16_8(0x5389, 0x01);
        wrSensorReg16_8(0x538b, 0x98);
        wrSensorReg16_8(0x538a, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    }
}

void OV5640_MINI_5MP::SetBrightness(Brightness brightness)
{
    switch (brightness)
    {
    case Plus_4:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5587, 0x40);
        wrSensorReg16_8(0x5588, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Plus_3:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5587, 0x30);
        wrSensorReg16_8(0x5588, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Plus_2:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5587, 0x20);
        wrSensorReg16_8(0x5588, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Plus_1:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5587, 0x10);
        wrSensorReg16_8(0x5588, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Plus_0:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5587, 0x00);
        wrSensorReg16_8(0x5588, 0x01);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Minus_1:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5587, 0x10);
        wrSensorReg16_8(0x5588, 0x09);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Minus_2:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5587, 0x20);
        wrSensorReg16_8(0x5588, 0x09);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Minus_3:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5587, 0x30);
        wrSensorReg16_8(0x5588, 0x09);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Minus_4:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5587, 0x40);
        wrSensorReg16_8(0x5588, 0x09);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    }
}

void OV5640_MINI_5MP::SetContrast(Contrast contrast)
{
    switch (contrast)
    {
    case Plus_3:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5586, 0x2c);
        wrSensorReg16_8(0x5585, 0x1c);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Plus_2:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5586, 0x28);
        wrSensorReg16_8(0x5585, 0x18);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Plus_1:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5586, 0x24);
        wrSensorReg16_8(0x5585, 0x10);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Plus_0:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5586, 0x20);
        wrSensorReg16_8(0x5585, 0x00);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Minus_1:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5586, 0x1c);
        wrSensorReg16_8(0x5585, 0x1c);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Minus_2:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5586, 0x18);
        wrSensorReg16_8(0x5585, 0x18);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Minus_3:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5586, 0x14);
        wrSensorReg16_8(0x5585, 0x14);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    }
}

void OV5640_MINI_5MP::SetSpecialEffects(Special_Effects effect)
{
    switch (effect)
    {
    case Normal:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5580, 0x06);
        wrSensorReg16_8(0x5583, 0x40); // sat U
        wrSensorReg16_8(0x5584, 0x10); // sat V
        wrSensorReg16_8(0x5003, 0x08);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group
        break;
    case Blueish:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5580, 0x1e);
        wrSensorReg16_8(0x5583, 0xa0);
        wrSensorReg16_8(0x5584, 0x40);
        wrSensorReg16_8(0x5003, 0x08);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Reddish:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5580, 0x1e);
        wrSensorReg16_8(0x5583, 0x80);
        wrSensorReg16_8(0x5584, 0xc0);
        wrSensorReg16_8(0x5003, 0x08);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case BW:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5580, 0x1e);
        wrSensorReg16_8(0x5583, 0x80);
        wrSensorReg16_8(0x5584, 0x80);
        wrSensorReg16_8(0x5003, 0x08);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Sepia:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5580, 0x1e);
        wrSensorReg16_8(0x5583, 0x40);
        wrSensorReg16_8(0x5584, 0xa0);
        wrSensorReg16_8(0x5003, 0x08);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;

    case Negative:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5580, 0x40);
        wrSensorReg16_8(0x5003, 0x08);
        wrSensorReg16_8(0x5583, 0x40); // sat U
        wrSensorReg16_8(0x5584, 0x10); // sat V
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Greenish:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5580, 0x1e);
        wrSensorReg16_8(0x5583, 0x60);
        wrSensorReg16_8(0x5584, 0x60);
        wrSensorReg16_8(0x5003, 0x08);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Overexposure:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5580, 0x1e);
        wrSensorReg16_8(0x5583, 0xf0);
        wrSensorReg16_8(0x5584, 0xf0);
        wrSensorReg16_8(0x5003, 0x08);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    case Solarize:
        wrSensorReg16_8(0x3212, 0x03); // start group 3
        wrSensorReg16_8(0x5580, 0x06);
        wrSensorReg16_8(0x5583, 0x40); // sat U
        wrSensorReg16_8(0x5584, 0x10); // sat V
        wrSensorReg16_8(0x5003, 0x09);
        wrSensorReg16_8(0x3212, 0x13); // end group 3
        wrSensorReg16_8(0x3212, 0xa3); // launch group 3
        break;
    }
}

void OV5640_MINI_5MP::SetNightMode(Night_Mode night_mode)
{
    uint8_t reg_val;
    switch (night_mode)
    {
    case ON:
        rdSensorReg16_8(0x3a00, &reg_val);
        reg_val = reg_val | 0x04;
        wrSensorReg16_8(0x3a00, reg_val);
        break;
    case OFF:
        rdSensorReg16_8(0x3a00, &reg_val);
        reg_val = reg_val & 0xfb;
        wrSensorReg16_8(0x3a00, reg_val);
        break;
    }
}

void OV5640_MINI_5MP::SetBandingFilter(Banding_Filter band_filter)
{
    uint8_t reg_val;
    switch (band_filter)
    {
    case OFF:
        rdSensorReg16_8(0x3a00, &reg_val);
        reg_val = reg_val & 0xdf; // turn off banding filter
        wrSensorReg16_8(0x3a00, reg_val);
        break;
    case M50HZ:
        wrSensorReg16_8(0x3c00, 04); // set to 50Hz
        wrSensorReg16_8(0x3c01, 80); // manual banding filter
        rdSensorReg16_8(0x3a00, &reg_val);
        reg_val = reg_val | 0x20; // turn on banding filter
        wrSensorReg16_8(0x3a00, reg_val);
        break;
    case M60HZ:
        wrSensorReg16_8(0x3c00, 00); // set to 60Hz
        wrSensorReg16_8(0x3c01, 80); // manual banding filter
        rdSensorReg16_8(0x3a00, &reg_val);
        reg_val = reg_val | 0x20; // turn on banding filter
        wrSensorReg16_8(0x3a00, reg_val);
        break;
    case AUTO:
        wrSensorReg16_8(0x3c01, 00); // auto banding filter
        rdSensorReg16_8(0x3a00, &reg_val);
        reg_val = reg_val & 0xdf; // turn off banding filter
        wrSensorReg16_8(0x3a00, reg_val);
        break;
    }
}

void OV5640_MINI_5MP::SetAutoExposureControl(AutoExposureContol aec_mode)
{
    switch (aec_mode)
    {
    case Plus_3:
        wrSensorReg16_8(0x3a0f, 0x60);
        wrSensorReg16_8(0x3a10, 0x58);
        wrSensorReg16_8(0x3a11, 0xa0);
        wrSensorReg16_8(0x3a1b, 0x60);
        wrSensorReg16_8(0x3a1e, 0x58);
        wrSensorReg16_8(0x3a1f, 0x20);
        break;
    case Plus_2:
        wrSensorReg16_8(0x3a0f, 0x50);
        wrSensorReg16_8(0x3a10, 0x48);
        wrSensorReg16_8(0x3a11, 0x90);
        wrSensorReg16_8(0x3a1b, 0x50);
        wrSensorReg16_8(0x3a1e, 0x48);
        wrSensorReg16_8(0x3a1f, 0x20);
        break;
    case Plus_1:
        wrSensorReg16_8(0x3a0f, 0x40);
        wrSensorReg16_8(0x3a10, 0x38);
        wrSensorReg16_8(0x3a11, 0x71);
        wrSensorReg16_8(0x3a1b, 0x40);
        wrSensorReg16_8(0x3a1e, 0x38);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Plus_0:
        wrSensorReg16_8(0x3a0f, 0x38);
        wrSensorReg16_8(0x3a10, 0x30);
        wrSensorReg16_8(0x3a11, 0x61);
        wrSensorReg16_8(0x3a1b, 0x38);
        wrSensorReg16_8(0x3a1e, 0x30);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Minus_1:
        wrSensorReg16_8(0x3a0f, 0x30);
        wrSensorReg16_8(0x3a10, 0x28);
        wrSensorReg16_8(0x3a11, 0x61);
        wrSensorReg16_8(0x3a1b, 0x30);
        wrSensorReg16_8(0x3a1e, 0x28);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Minus_2:
        wrSensorReg16_8(0x3a0f, 0x20);
        wrSensorReg16_8(0x3a10, 0x18);
        wrSensorReg16_8(0x3a11, 0x41);
        wrSensorReg16_8(0x3a1b, 0x20);
        wrSensorReg16_8(0x3a1e, 0x18);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    case Minus_3:
        wrSensorReg16_8(0x3a0f, 0x10);
        wrSensorReg16_8(0x3a10, 0x08);
        wrSensorReg16_8(0x3a1b, 0x10);
        wrSensorReg16_8(0x3a1e, 0x08);
        wrSensorReg16_8(0x3a11, 0x20);
        wrSensorReg16_8(0x3a1f, 0x10);
        break;
    }
}

bool OV5640_MINI_5MP::checkModule()
{
    uint8_t vid, pid;
    wrSensorReg8_8(0xff, 0x01);
    rdSensorReg8_8(OV5640_CHIPID_HIGH, &vid);
    rdSensorReg8_8(OV5640_CHIPID_LOW, &pid);
    return ((vid != 0x26) && !((pid == 0x41) || (pid == 0x42)));
}