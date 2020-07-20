#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include "HardwareSerial.h"
#include "base_regs.h"
#include "base_defs.h"

#define SPI_CS L07

enum class Image_Size
{
    j160x120,
    j176x144,
    j320x240,
    j352x288,
    j640x480,
    r640x480,
    j800x480,
    j800x600,
    j1024x768,
    j1280x960,
    r1280x960,
    j1280x1024,
    j1600x1200,
    r1920x1080,
    j2048x1536,
    j2592x1944,
    r2592x1944,
};

enum class Saturation
{
    Plus_4,
    Plus_3,
    Plus_2,
    Plus_1,
    Plus_0,
    Minus_1,
    Minus_2,
    Minus_3,
    Minus_4,
};

enum class Brightness
{
    Plus_4,
    Plus_3,
    Plus_2,
    Plus_1,
    Plus_0,
    Minus_1,
    Minus_2,
    Minus_3,
    Minus_4,
};

enum class Contrast
{
    Plus_4,
    Plus_3,
    Plus_2,
    Plus_1,
    Plus_0,
    Minus_1,
    Minus_2,
    Minus_3,
    Minus_4,
};

enum class Sharpness
{
    Auto,
    Auto1,
    Auto2,
    Off,
    Manual1,
    Manual2,
    Manual3,
    Manual4,
    Manual5,
};

enum class Hue
{
    Minus_180,
    Minus_150,
    Minus_120,
    Minus_90,
    Minus_60,
    Minus_30,
    Minus_0,
    Plus_30,
    Plus_60,
    Plus_90,
    Plus_120,
    Plus_150,
};

enum class Special_Effects
{
    Antique,
    Bluish,
    Greenish,
    Reddish,
    BW,
    Negative,
    BWnegative,
    Normal,
    Sepia,
    Overexposure,
    Solarize,
    Blueish,
    Yellowish,
};

enum class Format
{
    BMP_FMT,
    JPEG_FMT,
    RAW_FMT,
};

enum class Light_Mode
{
    Auto,
    Sunny,
    Cloudy,
    Office,
    Home,
    Fluorescent, //	Cool White Fluorescent, CWF
    Tungsten,
    Advanced_White_Balance,
    Simple_White_Balance

};

enum class Night_Mode
{
    ON,
    OFF,
};

enum class Banding_Filter
{
    OFF,
    M50HZ,
    M60HZ,
    AUTO,
};

enum class AutoExposureContol
{
    Plus_3,
    Plus_2,
    Plus_1,
    Plus_0,
    Minus_1,
    Minus_2,
    Minus_3,
};

enum class Exposure
{
    Minus_17,
    Minus_13,
    Minus_10,
    Minus_7,
    Minus_3,
    Default,
    Plus_3,
    Plus_7,
    Plus_10,
    Plus_13,
    Plus_17,
};

enum class MirrorFlip
{
    MIRROR,
    MIRROR_FLIP,
    FLIP,
    NORMAL,
};

enum class Compression
{
    High,
    Default,
    Low,
};

enum class TestPattern
{
    Bar,
    Square,
    BWSquare,
    DLI,
};

class Camera
{
public:
    Camera() {
        m_fmt = Format::JPEG_FMT;
        sensor_addr = 0x00;
    }
    virtual ~Camera() {};
    virtual void InitCAM() = 0;
    virtual bool checkModule() =0;
    virtual void SetImageSize(Image_Size size);
    virtual void SetLightMode(Light_Mode mode);
    virtual void SetColorSaturation(Saturation saturation);
    virtual void SetHue(Hue hue);
    virtual void SetBrightness(Brightness brightness);
    virtual void SetContrast(Contrast contrast);
    virtual void SetSharpness(Sharpness sharpness);
    virtual void SetSpecialEffects(Special_Effects effect);
    virtual void SetNightMode(Night_Mode mode);
    virtual void SetBandingFilter(Banding_Filter filter);
    virtual void SetAutoExposureControl(AutoExposureContol mode);
    virtual void SetExposureLevel(Exposure level);
    virtual void SetMirrorFlip(MirrorFlip style);
    virtual void SetCompression(Compression level);
    virtual void SetTestPattern(TestPattern pattern);

    void flush_fifo();
    void start_capture();
    void clear_fifo_flag();
    uint8_t read_fifo();

    uint8_t read_reg(uint8_t addr);
    void write_reg(uint8_t addr, uint8_t data);

    uint32_t read_fifo_length();
    void set_fifo_burst();

    void set_bit(uint8_t addr, uint8_t bit);
    void clear_bit(uint8_t addr, uint8_t bit);
    uint8_t get_bit(uint8_t addr, uint8_t bit);
    void set_mode(uint8_t mode);

    void bus_write(int address, int value);
    virtual uint8_t bus_read(int address);

    // Write 8 bit values to 8 bit register address
    int wrSensorRegs8_8(const struct sensor_reg *);

    // Write 16 bit values to 8 bit register address
    int wrSensorRegs8_16(const struct sensor_reg *);

    // Write 8 bit values to 16 bit register address
    int wrSensorRegs16_8(const struct sensor_reg *);

    // Write 16 bit values to 16 bit register address
    int wrSensorRegs16_16(const struct sensor_reg *);

    // Read/write 8 bit value to/from 8 bit register address
    byte wrSensorReg8_8(int regID, int regDat);
    byte rdSensorReg8_8(uint8_t regID, uint8_t *regDat);

    // Read/write 16 bit value to/from 8 bit register address
    byte wrSensorReg8_16(int regID, int regDat);
    byte rdSensorReg8_16(uint8_t regID, uint16_t *regDat);

    // Read/write 8 bit value to/from 16 bit register address
    byte wrSensorReg16_8(int regID, int regDat);
    byte rdSensorReg16_8(uint16_t regID, uint8_t *regDat);

    // Read/write 16 bit value to/from 16 bit register address
    byte wrSensorReg16_16(int regID, int regDat);
    byte rdSensorReg16_16(uint16_t regID, uint16_t *regDat);

    void SetFormat(Format fmt)
    {
        m_fmt = fmt;
    };

    void resetCPLD()
    {
        //Reset the CPLD
        write_reg(0x07, 0x80);
        delay(100);
        write_reg(0x07, 0x00);
    };

    bool checkSPIBusStatus()
    {
        write_reg(ARDUCHIP_TEST1, 0x55);
        byte temp = read_reg(ARDUCHIP_TEST1);
        return temp == 0x55;
    };

protected:
    Format m_fmt;
    uint8_t sensor_addr;
};
#endif