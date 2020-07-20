#ifndef OV2640_MINI_2MP_H
#define OV2640_MINI_2MP_H
#include "Camera.h"

class OV2640_MINI_2MP : public Camera
{
public:
    OV2640_MINI_2MP(); // Constructor.
    void InitCAM() override;
    void SetImageSize(Image_Size size) override;
    void SetLightMode(Light_Mode mode) override;
    void SetColorSaturation(Saturation saturation) override;
    void SetBrightness(Brightness brightness) override;
    void SetContrast(Contrast contrast) override;
    void SetSpecialEffects(Special_Effects effect) override;
    bool checkModule() override;
    // Not available for this module
    void SetHue(Hue hue) override{};
    void SetSharpness(Sharpness sharpness) override{};
    void SetNightMode(Night_Mode mode) override{};
    void SetBandingFilter(Banding_Filter filter) override{};
    void SetAutoExposureControl(AutoExposureContol level) override{};
    void SetExposureLevel(Exposure level) override{};
    void SetMirrorFlip(MirrorFlip style) override{};
    void SetCompression(Compression amount) override{};
    void SetTestPattern(TestPattern pattern) override{};
};
#endif