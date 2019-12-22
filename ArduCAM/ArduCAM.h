/*
  ArduCAM.h - Arduino library support for CMOS Image Sensor
  Copyright (C)2011-2015 ArduCAM.com. All right reserved
  
  Basic functionality of this library are based on the demo-code provided by
  ArduCAM.com. You can find the latest version of the library at
  http://www.ArduCAM.com

  Now supported controllers:
		- OV7670
		- MT9D111
		- OV7675
		- OV2640
		- OV3640
		- OV5642
		- OV5640
		- OV7660
		- OV7725
		- MT9M112		
		- MT9V111
		- OV5640		
		- MT9M001			
		- MT9T112
		- MT9D112
				
	We will add support for many other sensors in next release.
	
  Supported MCU platform
 		-	Theoretically support all Arduino families
  		-	Arduino UNO R3			(Tested)
  		-	Arduino MEGA2560 R3		(Tested)
  		-	Arduino Leonardo R3		(Tested)
  		-	Arduino Nano			(Tested)
  		-	Arduino DUE				(Tested)
  		- Arduino Yun				(Tested)  		
  		-	Raspberry Pi			(Tested)
  		- ESP8266-12				(Tested)  		
		* Feather M0                (Tested with OV5642)

  If you make any modifications or improvements to the code, I would appreciate
  that you share the code with me so that I might include it in the next release.
  I can be contacted through http://www.ArduCAM.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*------------------------------------
	Revision History:
	2012/09/20 	V1.0.0	by Lee	first release 
	2012/10/23  V1.0.1  by Lee  Resolved some timing issue for the Read/Write Register	
	2012/11/29	V1.1.0	by Lee  Add support for MT9D111 sensor
	2012/12/13	V1.2.0	by Lee	Add support for OV7675 sensor
	2012/12/28  V1.3.0	by Lee	Add support for OV2640,OV3640,OV5642 sensors
	2013/02/26	V2.0.0	by Lee	New Rev.B shield hardware, add support for FIFO control 
															and support Mega1280/2560 boards 
	2013/05/28	V2.1.0	by Lee	Add support all drawing functions derived from UTFT library 			
	2013/08/24	V3.0.0	by Lee	Support ArudCAM shield Rev.C hardware, features SPI interface and low power mode.
								Support almost all series of Arduino boards including DUE.	
	2014/03/09  V3.1.0  by Lee  Add the more impressive example sketches. 
								Optimise the OV5642 settings, improve image quality.
								Add live preview before JPEG capture.
								Add play back photos one by one	after BMP capture.
	2014/05/01  V3.1.1  by Lee  Minor changes to add support Arduino IDE for linux distributions.	
	2014/09/30  V3.2.0  by Lee  Improvement on OV5642 camera dirver.			
	2014/10/06  V3.3.0  by Lee  Add OV7660,OV7725 camera support.			
	2015/02/27  V3.4.0  by Lee  Add the support for Arduino Yun board, update the latest UTFT library for ArduCAM.			
	2015/06/09  V3.4.1  by Lee	Minor changes and add some comments		
	2015/06/19  V3.4.2  by Lee	Add support for MT9M112 camera.			
	2015/06/20  V3.4.3  by Lee	Add support for MT9V111 camera.			
	2015/06/22  V3.4.4  by Lee	Add support for OV5640 camera.										
	2015/06/22  V3.4.5  by Lee	Add support for MT9M001 camera.		
	2015/08/05  V3.4.6  by Lee	Add support for MT9T112 camera.	
	2015/08/08  V3.4.7  by Lee	Add support for MT9D112 camera.							
	2015/09/20  V3.4.8  by Lee	Add support for ESP8266 processor.	
	2016/02/03	V3.4.9	by Lee	Add support for Arduino ZERO board.
	2016/06/07  V3.5.0  by Lee	Add support for OV5642_CAM_BIT_ROTATION_FIXED.
	2016/06/14  V3.5.1  by Lee	Add support for ArduCAM-Mini-5MP-Plus OV5640_CAM.	
	2016/09/29	V3.5.2	by Lee	Optimize the OV5642 register settings		
	2016/10/05	V4.0.0	by Lee	Add support for second generation of ArduCAM shield V2, ArduCAM-Mini-5MP-Plus(OV5642/OV5640).				
	2016/10/28  V4.0.1  by Lee	Add support for Raspberry Pi
	2017/04/27  V4.1.0  by Lee	Add support for OV2640/OV5640/OV5642 functions.
	2017/07/07  V4.1.0  by Lee	Add support for ArduCAM_ESP32 paltform
	2017/07/25  V4.1.1  by Lee	Add support for MT9V034
	2017/11/27  V4.1.2  by Max      Add support for Feather M0
	2018/10/15  V4.1.2  by Lee      Add support for NRF52
	2018/10/15  V4.1.2  by Lee      Add support for TEENSYDUINO
--------------------------------------*/

#ifndef ArduCAM_H
#define ArduCAM_H
#include "memorysaver.h"
#include "Arduino.h"
#include <pins_arduino.h>
#include "memorysaver.h"
#include "Camera.h"

#define SPI_CS L07

/****************************************************/
/* Sensor related definition 												*/
/****************************************************/

#define Advanced_AWB 0
#define Simple_AWB 1
#define Manual_day 2
#define Manual_A 3
#define Manual_cwf 4
#define Manual_cloudy 5

#define Exposure_17_EV 0
#define Exposure_13_EV 1
#define Exposure_10_EV 2
#define Exposure_07_EV 3
#define Exposure_03_EV 4
#define Exposure_default 5
#define Exposure03_EV 6
#define Exposure07_EV 7
#define Exposure10_EV 8
#define Exposure13_EV 9
#define Exposure17_EV 10

#define Auto_Sharpness_default 0
#define Auto_Sharpness1 1
#define Auto_Sharpness2 2
#define Manual_Sharpnessoff 3
#define Manual_Sharpness1 4
#define Manual_Sharpness2 5
#define Manual_Sharpness3 6
#define Manual_Sharpness4 7
#define Manual_Sharpness5 8

#define Sharpness1 0
#define Sharpness2 1
#define Sharpness3 2
#define Sharpness4 3
#define Sharpness5 4
#define Sharpness6 5
#define Sharpness7 6
#define Sharpness8 7
#define Sharpness_auto 8

#define EV3 0
#define EV2 1
#define EV1 2
#define EV0 3
#define EV_1 4
#define EV_2 5
#define EV_3 6

#define MIRROR 0
#define FLIP 1
#define MIRROR_FLIP 2

#define high_quality 0
#define default_quality 1
#define low_quality 2

#define Color_bar 0
#define Color_square 1
#define BW_square 2
#define DLI 3

#define Night_Mode_On 0
#define Night_Mode_Off 1

#define Off 0
#define Manual_50HZ 1
#define Manual_60HZ 2
#define Auto_Detection 3

/****************************************************/
/* I2C Control Definition 													*/
/****************************************************/
#define I2C_ADDR_8BIT 0
#define I2C_ADDR_16BIT 1
#define I2C_REG_8BIT 0
#define I2C_REG_16BIT 1
#define I2C_DAT_8BIT 0
#define I2C_DAT_16BIT 1

/* Register initialization tables for SENSORs */
/* Terminating list entry for reg */
#define SENSOR_REG_TERM_8BIT 0xFF
#define SENSOR_REG_TERM_16BIT 0xFFFF
/* Terminating list entry for val */
#define SENSOR_VAL_TERM_8BIT 0xFF
#define SENSOR_VAL_TERM_16BIT 0xFFFF

//Define maximum frame buffer size
#define MAX_FIFO_SIZE 0x5FFFF //384KByte

/****************************************************/
/* ArduChip registers definition 											*/
/****************************************************/
#define RWBIT 0x80 //READ AND WRITE BIT IS BIT[7]

#define ARDUCHIP_TEST1 0x00 //TEST register

#define ARDUCHIP_MODE 0x02 //Mode register
#define MCU2LCD_MODE 0x00
#define CAM2LCD_MODE 0x01
#define LCD2MCU_MODE 0x02

#define ARDUCHIP_TIM 0x03 //Timming control

//#define FIFO_PWRDN_MASK	   		0x20  	//0 = Normal operation, 1 = FIFO power down
//#define LOW_POWER_MODE			  0x40  	//0 = Normal mode, 			1 = Low power mode

#define ARDUCHIP_FIFO 0x04 //FIFO and I2C control
#define FIFO_CLEAR_MASK 0x01
#define FIFO_START_MASK 0x02
#define FIFO_RDPTR_RST_MASK 0x10
#define FIFO_WRPTR_RST_MASK 0x20

#define ARDUCHIP_GPIO 0x06 //GPIO Write Register
#if !(defined(ARDUCAM_SHIELD_V2) || defined(ARDUCAM_SHIELD_REVC))
#define GPIO_RESET_MASK 0x01 //0 = Sensor reset,							1 =  Sensor normal operation
#define GPIO_PWDN_MASK 0x02  //0 = Sensor normal operation, 	1 = Sensor standby
#define GPIO_PWREN_MASK 0x04 //0 = Sensor LDO disable, 			1 = sensor LDO enable
#endif

#define BURST_FIFO_READ 0x3C  //Burst FIFO read operation
#define SINGLE_FIFO_READ 0x3D //Single FIFO read operation

#define ARDUCHIP_REV 0x40 //ArduCHIP revision
#define VER_LOW_MASK 0x3F
#define VER_HIGH_MASK 0xC0

#define ARDUCHIP_TRIG 0x41 //Trigger source
#define VSYNC_MASK 0x01
#define SHUTTER_MASK 0x02
#define CAP_DONE_MASK 0x08

#define FIFO_SIZE1 0x42 //Camera write FIFO size[7:0] for burst to read
#define FIFO_SIZE2 0x43 //Camera write FIFO size[15:8]
#define FIFO_SIZE3 0x44 //Camera write FIFO size[18:16]

/****************************************************/

/****************************************************************/
/* define a structure for sensor register initialization values */
/****************************************************************/
struct sensor_reg
{
	uint16_t reg;
	uint16_t val;
};

/****************************************************************/
/* define a structure for sensor register initialization values */
/****************************************************************/

class ArduCAM
{
public:
	ArduCAM(CameraModel model)
	{
		switch (model)
		{
		case OV2640
			camera = new OV2640();
			break;

			default:
			break;
		}
	}

	void InitCAM()
	{
		camera->InitCAM();
	}

	void SetJPEGsize(JPEG_Size size)
	{
		camera->SetJPEGsize(size);
	}

	void SetLightMode(Light_Mode mode)
	{
		camera->SetLightMode(mode);
	}

	void SetColorSaturation(Color_Saturation saturation)
	{
		camera->SetColorSaturation(saturation);
	}

	void SetBrightness(Brightness brightness)
	{
		camera->SetBrightness(brightness)
	}

	void SetContrast(Contrast contrast)
	{
		camera->SetContrast(contrast);
	}

	void SetSpecialEffects(Special_Effects effect)
	{
		camera->SetSpecialeffects(effect);
	}

	void SetFormat(Format fmt)
	{
		camera->SetFormat(fmt);
	}

	Camera * getCamera() {
		return camera;
	}

private:
	Camera *camera;
};

#endif
