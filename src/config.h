/*#################################################################*\

Copyright 2020 Jakob Föger

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

\*#################################################################*/

#include "Arduino.h"

#define Display_SSD1351 1351 //Color 128x128
#define Display Display_SSD1351

#if Display == Display_SSD1351
#include "cover.h"
#include "GrayscaleFonts.h"
#include "SSD1351.h"
#endif

//WiFi
String ssid = "EOLO - FRITZ!Box 7530 TF";
String password = "carol2008";

//Volumio
String host = "192.168.178.109";
int port = 80;

//Touch-pins
#define PIN_TOUCH0 1
#define PIN_TOUCH1 2
#define PIN_TOUCH2 3
#define PIN_TOUCH3 4
#define PIN_TOUCH4 5
#define PIN_TOUCH5 6
#define PIN_TOUCH6 7
#define PIN_TOUCH7 8
#define PIN_TOUCH8 9
#define PIN_TOUCH9 14

//Display-pins
#define PIN_SPI_MOSI 11
#define PIN_SPI_CLK 12
#define PIN_SPI_CS 38
#define PIN_SPI_DC 10
#define rst  13

//Left encoder
#define PIN_LeftEncoder_SW 35 
#define PIN_LeftEncoder_DT 36
#define PIN_LeftEncoder_CLK 37

//Right encoder
#define PIN_RightEncoder_SW 41
#define PIN_RightEncoder_DT 40
#define PIN_RightEncoder_CLK 39

//Min and Max possible volume on my System, standard would be 0-100
int volumeMinimum = 0;
int volumeMaximum = 100;

//How often the volume is sent to Volumio when different
long volumeSetInterval = 300; //ms

//scroll one pixel each x ms
long ScrollInterval = 10; //ms

//Gap between end and start of scrolling text
int scrollGapStatus = 32; //px
int scrollGapMenu = 16;   //px

//Toast message switches display on
bool toastActivatesDisplay = true;

/*#################################################################*\
|* Delays                                                        
\*#################################################################*/

//How long volume bar is displayed after last change ( 0 deactivates function)
long durationShowVolume = 2 * 1000; //ms

//How long toest messages are displayed ( 0 deactivates toast display)
long durationShowToast = 0; //ms //5 * 1000;

//How long menu must stand still until scrolling starts, when texts are too long (0 deactivates function)
long delayScrollMenu = 1 * 1000; //ms

//After x ms without operation go back to status display (0 deactivates function)
long delayBackStatus = 30 * 1000; //ms

//After x ms without operation switch display off, if not play (0 deactivates function)
long delayDisplayOffWhenNotPlay = 600 * 1000; //ms

//After x ms without operation switch display off (0 deactivates function)
long delayDisplayOff = 0; //ms

/*#################################################################*\
|* Display                                                        
\*#################################################################*/

#define DisplayWidth 128
#define DisplayHeight 128

#if Display == Display_SSD1351
SSD1351 display = SSD1351();
#endif

/*#################################################################*\
|* Menu                                                        
\*#################################################################*/

#define MenuItemHeight 16
#define MenuTextHeight 10
#define MenuVisibleItems 8
#define MenuPixelHeight 128
#define MenuPixelWidth 128

//https://github.com/olikraus/u8g2/wiki/fntlistall#u8g2-font-names

#define MenuTextFont u8g2_font_t0_12_tf
#define StatusTextFont u8g2_font_t0_12_tf
#define ToastTextFont u8g2_font_t0_12_tf
#define MenuIconFont u8g2_font_open_iconic_all_1x_t
