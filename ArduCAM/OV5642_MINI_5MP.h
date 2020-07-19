#ifndef OV5642_MINI_5MP_H
#define OV5642_MINI_5MP_H
#include "Camera.h"

class OV5642_MINI_5MP : public Camera
{
public:
    OV5642_MINI_5MP(is_plus = false); // Constructor.
    void InitCAM();
    void SetImageSize(Image_Size size);
    void SetLightMode(Light_Mode mode);
    void SetColorSaturation(Saturation saturation);
    void SetHue(Hue hue);
    void SetBrightness(Brightness brightness);
    void SetContrast(Contrast contrast);
    void SetSharpness(Sharpness sharpness);
    void SetSpecialEffects(Special_Effects effect);
    void SetNightMode(Night_Mode night_mode);
    void SetBandingFilter(Banding_Filter band_filter);
    void SetExposureLevel(Exposure level);
    void SetMirrorFlip(MirrorFlip style);
    void SetCompression(Compression level);
    void SetTestPattern(TestPattern pattern);
    void SetAutoExposureControl(AutoExposureContol aec_mode) = {};
    bool checkModule();

    uint8_t bus_read(int address)
    {
#if (defined(ESP8266) || defined(__arm__) || defined(TEENSYDUINO))
        uint8_t value;
        SPI.transfer(address);
        value = SPI.transfer(0x00);
        // correction for bit rotation from readback
        value = (byte)(value >> 1) | (value << 7);
        // take the SS pin high to de-select the chip:
        sbi(P_CS, B_CS);
        return value;
#else
    return Camera::bus_read(address);
#endif
    }

private:
    bool is_plus_model = false;
};
#endif