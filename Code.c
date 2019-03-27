/*        _   _  _____ _    _ _    _ __  __          _   _     ______     _    _ ___________          _____  
    /\   | \ | |/ ____| |  | | |  | |  \/  |   /\   | \ | |   |  ____/\  | |  | |___  /  __ \   /\   |  __ \ 
   /  \  |  \| | (___ | |__| | |  | | \  / |  /  \  |  \| |   | |__ /  \ | |  | |  / /| |  | | /  \  | |__) |
  / /\ \ | . ` |\___ \|  __  | |  | | |\/| | / /\ \ | . ` |   |  __/ /\ \| |  | | / / | |  | |/ /\ \ |  _  / 
 / ____ \| |\  |____) | |  | | |__| | |  | |/ ____ \| |\  |   | | / ____ \ |__| |/ /__| |__| / ____ \| | \ \ 
/_/    \_\_| \_|_____/|_|  |_|\____/|_|  |_/_/    \_\_| \_|   |_|/_/    \_\____//_____|_____/_/    \_\_|  \_\  */

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/
#define WIFI_SSID       "SSID"
#define WIFI_PASS       "Password"

/************************* Adafruit.io Setup *********************************/

#define IO_USERNAME    "Username"
#define IO_KEY         "Unique Key"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


void setup() 
{
  

}

void loop() 
{
  

}
