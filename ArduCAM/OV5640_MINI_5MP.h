#ifndef OV5640_MINI_5MP_H
#define OV5640_MINI_5MP_H
#include "Camera.h"

class OV5640_MINI_5MP : public Camera
{
public:
    OV5640_MINI_5MP(is_plus=false); // Constructor.
    void InitCAM();
    void SetImageSize(Image_Size size);
    void SetLightMode(Light_Mode mode);
    void SetColorSaturation(Saturation saturation);
    void SetHue(Hue hue) = {}; // Not a available for this module
    void SetBrightness(Brightness brightness);
    void SetContrast(Contrast contrast);
    void SetSpecialEffects(Special_Effects effect);
    void SetNightMode(Night_Mode night_mode);
    void SetBandingFilter(Banding_Filter band_filter);
    void SetAutoExposureControl(AutoExposureContol aec_mode);
    void SetExposureLevel(Exposure level) = {}; // Not a available for this module
    void SetMirrorFlip(MirrorFlip style) = {}; // Not a available for this module
    void SetCompression(Compression level) = {}; // Not a available for this module
    void SetTestPattern(TestPattern pattern) = {}; // Not a available for this module
    bool checkModule();
private:
    bool is_plus_model = false;
};
#endif