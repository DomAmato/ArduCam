#ifndef OV2640_MINI_2MP_H
#define OV2640_MINI_2MP_H
#include "Camera.h"

class OV2640_MINI_2MP : public Camera
{
public:
    OV2640_MINI_2MP(); // Constructor.
    void InitCAM();
    void SetImageSize(Image_Size size);
    void SetLightMode(Light_Mode mode);
    void SetColorSaturation(Saturation saturation);
    void SetBrightness(Brightness brightness);
    void SetContrast(Contrast contrast);
    void SetSpecialEffects(Special_Effects effect);
    bool checkModule();
    // These functions don't exist for this module
    void SetHue(Hue hue) {};
    void SetNightMode(Night_Mode night_mode) {};
    void SetBandingFilter(Banding_Filter band_filter) {};
    void SetAutoExposureControl(AutoExposureContol aec_mode) {};
    void SetExposureLevel(Exposure level) = {};
    void SetMirrorFlip(MirrorFlip style) = {};
    void SetCompression(Compression level) = {};
    void SetTestPattern(TestPattern pattern) = {};
};
#endif