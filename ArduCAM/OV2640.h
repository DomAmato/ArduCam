#include "Arduino.h"
#include "ov2640_regs.h"

class OV2640 : public Camera
{
public:
    OV2640(); // Constructor.
    void InitCAM(void);
    void SetJPEGsize(JPEG_Size size);
    void SetLightMode(Light_Mode mode);
    void SetColorSaturation(Color_Saturation saturation);
    void SetBrightness(Brightness brightness);
    void SetContrast(Contrast contrast);
    void SetSpecialEffects(Special_Effects effect);
};