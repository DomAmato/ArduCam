#ifndef OV5640_MINI_5MP_H
#define OV5640_MINI_5MP_H
#include "Camera.h"

class OV5640_MINI_5MP : public Camera
{
public:
    OV5640_MINI_5MP(bool is_plus=false); // Constructor.
    void InitCAM() override;
    void SetImageSize(Image_Size size) override;
    void SetLightMode(Light_Mode mode) override;
    void SetColorSaturation(Saturation saturation) override;
    void SetBrightness(Brightness brightness) override;
    void SetContrast(Contrast contrast) override;
    void SetSpecialEffects(Special_Effects effect) override;
    void SetNightMode(Night_Mode night_mode) override;
    void SetBandingFilter(Banding_Filter band_filter) override;
    void SetAutoExposureControl(AutoExposureContol aec_mode) override;
    bool checkModule() override;
    // Not available for this module
    void SetHue(Hue hue) override{};
    void SetSharpness(Sharpness sharpness) override{};
    void SetExposureLevel(Exposure level) override{};
    void SetMirrorFlip(MirrorFlip style) override{};
    void SetCompression(Compression amount) override{};
    void SetTestPattern(TestPattern pattern) override{};
private:
    bool is_plus_model = false;
};
#endif