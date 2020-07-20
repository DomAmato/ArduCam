#include "OV2640_MINI_2MP.h"
#include "Arduino.h"
#include "ov2640_regs.h"

OV2640_MINI_2MP::OV2640_MINI_2MP()
{
    sensor_addr = 0x60;
}

void OV2640_MINI_2MP::InitCAM()
{
    wrSensorReg8_8(0xff, 0x01);
    wrSensorReg8_8(0x12, 0x80);
    delay(100);
    if (m_fmt == Format::JPEG_FMT)
    {
        wrSensorRegs8_8(JPEG_INIT);
        wrSensorRegs8_8(YUV422);
        wrSensorRegs8_8(JPEG);
        wrSensorReg8_8(0xff, 0x01);
        wrSensorReg8_8(0x15, 0x00);
        wrSensorRegs8_8(JPEG_320x240);
        //wrSensorReg8_8(0xff, 0x00);
        //wrSensorReg8_8(0x44, 0x32);
    }
    else
    {
        wrSensorRegs8_8(QVGA);
    }
}

void OV2640_MINI_2MP::SetImageSize(Image_Size size)
{
    switch (size)
    {
    case Image_Size::j160x120:
        wrSensorRegs8_8(JPEG_160x120);
        break;
    case Image_Size::j176x144:
        wrSensorRegs8_8(JPEG_176x144);
        break;
    case Image_Size::j320x240:
        wrSensorRegs8_8(JPEG_320x240);
        break;
    case Image_Size::j352x288:
        wrSensorRegs8_8(JPEG_352x288);
        break;
    case Image_Size::j640x480:
        wrSensorRegs8_8(JPEG_640x480);
        break;
    case Image_Size::j800x600:
        wrSensorRegs8_8(JPEG_800x600);
        break;
    case Image_Size::j1024x768:
        wrSensorRegs8_8(JPEG_1024x768);
        break;
    case Image_Size::j1280x1024:
        wrSensorRegs8_8(JPEG_1280x1024);
        break;
    case Image_Size::j1600x1200:
        wrSensorRegs8_8(JPEG_1600x1200);
        break;
    default:
        wrSensorRegs8_8(JPEG_320x240);
        break;
    }
}

void OV2640_MINI_2MP::SetLightMode(Light_Mode mode)
{
    switch (mode)
    {

    case Light_Mode::Auto:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x00); //AWB on
        break;
    case Light_Mode::Sunny:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x40); //AWB off
        wrSensorReg8_8(0xcc, 0x5e);
        wrSensorReg8_8(0xcd, 0x41);
        wrSensorReg8_8(0xce, 0x54);
        break;
    case Light_Mode::Cloudy:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x40); //AWB off
        wrSensorReg8_8(0xcc, 0x65);
        wrSensorReg8_8(0xcd, 0x41);
        wrSensorReg8_8(0xce, 0x4f);
        break;
    case Light_Mode::Office:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x40); //AWB off
        wrSensorReg8_8(0xcc, 0x52);
        wrSensorReg8_8(0xcd, 0x41);
        wrSensorReg8_8(0xce, 0x66);
        break;
    case Light_Mode::Home:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x40); //AWB off
        wrSensorReg8_8(0xcc, 0x42);
        wrSensorReg8_8(0xcd, 0x3f);
        wrSensorReg8_8(0xce, 0x71);
        break;
    default:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x00); //AWB on
        break;
    }
}

void OV2640_MINI_2MP::SetColorSaturation(Saturation saturation)
{
    switch (saturation)
    {
    case Saturation::Plus_2:

        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x02);
        wrSensorReg8_8(0x7c, 0x03);
        wrSensorReg8_8(0x7d, 0x68);
        wrSensorReg8_8(0x7d, 0x68);
        break;
    case Saturation::Plus_1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x02);
        wrSensorReg8_8(0x7c, 0x03);
        wrSensorReg8_8(0x7d, 0x58);
        wrSensorReg8_8(0x7d, 0x58);
        break;
    case Saturation::Plus_0:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x02);
        wrSensorReg8_8(0x7c, 0x03);
        wrSensorReg8_8(0x7d, 0x48);
        wrSensorReg8_8(0x7d, 0x48);
        break;
    case Saturation::Minus_1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x02);
        wrSensorReg8_8(0x7c, 0x03);
        wrSensorReg8_8(0x7d, 0x38);
        wrSensorReg8_8(0x7d, 0x38);
        break;
    case Saturation::Minus_2:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x02);
        wrSensorReg8_8(0x7c, 0x03);
        wrSensorReg8_8(0x7d, 0x28);
        wrSensorReg8_8(0x7d, 0x28);
        break;
    }
}

void OV2640_MINI_2MP::SetBrightness(Brightness brightness)
{
    switch (brightness)
    {
    case Brightness::Plus_2:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x09);
        wrSensorReg8_8(0x7d, 0x40);
        wrSensorReg8_8(0x7d, 0x00);
        break;
    case Brightness::Plus_1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x09);
        wrSensorReg8_8(0x7d, 0x30);
        wrSensorReg8_8(0x7d, 0x00);
        break;
    case Brightness::Plus_0:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x09);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x00);
        break;
    case Brightness::Minus_1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x09);
        wrSensorReg8_8(0x7d, 0x10);
        wrSensorReg8_8(0x7d, 0x00);
        break;
    case Brightness::Minus_2:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x09);
        wrSensorReg8_8(0x7d, 0x00);
        wrSensorReg8_8(0x7d, 0x00);
        break;
    }
}

void OV2640_MINI_2MP::SetContrast(Contrast contrast)
{
    switch (contrast)
    {
    case Contrast::Plus_2:

        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x07);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x28);
        wrSensorReg8_8(0x7d, 0x0c);
        wrSensorReg8_8(0x7d, 0x06);
        break;
    case Contrast::Plus_1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x07);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x24);
        wrSensorReg8_8(0x7d, 0x16);
        wrSensorReg8_8(0x7d, 0x06);
        break;
    case Contrast::Plus_0:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x07);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x06);
        break;
    case Contrast::Minus_1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x07);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x2a);
        wrSensorReg8_8(0x7d, 0x06);
        break;
    case Contrast::Minus_2:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x07);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7d, 0x34);
        wrSensorReg8_8(0x7d, 0x06);
        break;
    }
}

void OV2640_MINI_2MP::SetSpecialEffects(Special_Effects effect)
{
    switch (effect)
    {
    case Special_Effects::Antique:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x40);
        wrSensorReg8_8(0x7d, 0xa6);
        break;
    case Special_Effects::Bluish:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0xa0);
        wrSensorReg8_8(0x7d, 0x40);
        break;
    case Special_Effects::Greenish:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x40);
        wrSensorReg8_8(0x7d, 0x40);
        break;
    case Special_Effects::Reddish:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x40);
        wrSensorReg8_8(0x7d, 0xc0);
        break;
    case Special_Effects::BW:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x80);
        wrSensorReg8_8(0x7d, 0x80);
        break;
    case Special_Effects::Negative:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x40);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x80);
        wrSensorReg8_8(0x7d, 0x80);
        break;
    case Special_Effects::BWnegative:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x58);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x80);
        wrSensorReg8_8(0x7d, 0x80);
        break;
    case Special_Effects::Normal:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x00);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x80);
        wrSensorReg8_8(0x7d, 0x80);
        break;
    }
}

bool OV2640_MINI_2MP::checkModule()
{
    uint8_t vid, pid;
    wrSensorReg8_8(0xff, 0x01);
    rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
    rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
    return ((vid != 0x26) && !((pid == 0x41) || (pid == 0x42)));
}