#ifndef OV5642_MINI_5MP_H
#define OV5642_MINI_5MP_H
#include "Camera.h"

class OV5642_MINI_5MP : public Camera
{
public:
    OV5642_MINI_5MP(is_plus = false); // Constructor.
    void InitCAM() override;
    void SetImageSize(Image_Size size) override;
    void SetLightMode(Light_Mode mode) override;
    void SetColorSaturation(Saturation saturation) override;
    void SetHue(Hue hue) override;
    void SetBrightness(Brightness brightness) override;
    void SetContrast(Contrast contrast) override;
    void SetSharpness(Sharpness sharpness) override;
    void SetSpecialEffects(Special_Effects effect) override;
    void SetNightMode(Night_Mode night_mode) override;
    void SetBandingFilter(Banding_Filter band_filter) override;
    void SetExposureLevel(Exposure level) override;
    void SetMirrorFlip(MirrorFlip style) override;
    void SetCompression(Compression level) override;
    void SetTestPattern(TestPattern pattern) override;
    void SetAutoExposureControl(AutoExposureContol aec_mode) override {};
    bool checkModule() override;

    uint8_t bus_read(int address) override
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