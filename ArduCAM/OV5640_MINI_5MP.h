#ifndef OV5640_MINI_5MP_H
#define OV5640_MINI_5MP_H
#include "Camera.h"

class OV5640_MINI_5MP : public Camera
{
public:
    OV5640_MINI_5MP(is_plus=false); // Constructor.
    void InitCAM() override;
    void SetImageSize(Image_Size size) override;
    void SetLightMode(Light_Mode mode) override;
    void SetColorSaturation(Saturation saturation) override;
    void SetHue(Hue hue) override {}; // Not a available for this module
    void SetBrightness(Brightness brightness) override;
    void SetContrast(Contrast contrast) override;
    void SetSpecialEffects(Special_Effects effect) override;
    void SetNightMode(Night_Mode night_mode) override;
    void SetBandingFilter(Banding_Filter band_filter) override;
    void SetAutoExposureControl(AutoExposureContol aec_mode) override;
    void SetExposureLevel(Exposure level) override {}; // Not a available for this module
    void SetMirrorFlip(MirrorFlip style) override {}; // Not a available for this module
    void SetCompression(Compression level) override {}; // Not a available for this module
    void SetTestPattern(TestPattern pattern) override {}; // Not a available for this module
    bool checkModule() override;
private:
    bool is_plus_model = false;
};
#endif