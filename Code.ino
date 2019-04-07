/*        _   _  _____ _    _ _    _ __  __          _   _     ______     _    _ ___________          _____  
    /\   | \ | |/ ____| |  | | |  | |  \/  |   /\   | \ | |   |  ____/\  | |  | |___  /  __ \   /\   |  __ \ 
   /  \  |  \| | (___ | |__| | |  | | \  / |  /  \  |  \| |   | |__ /  \ | |  | |  / /| |  | | /  \  | |__) |
  / /\ \ | . ` |\___ \|  __  | |  | | |\/| | / /\ \ | . ` |   |  __/ /\ \| |  | | / / | |  | |/ /\ \ |  _  / 
 / ____ \| |\  |____) | |  | | |__| | |  | |/ ____ \| |\  |   | | / ____ \ |__| |/ /__| |__| / ____ \| | \ \ 
/_/    \_\_| \_|_____/|_|  |_|\____/|_|  |_/_/    \_\_| \_|   |_|/_/    \_\____//_____|_____/_/    \_\_|  \_\  */


// RFID READER

#include "AdafruitIO_WiFi.h"
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         D3         
#define SS_PIN          D8          

MFRC522 mfrc522(SS_PIN, RST_PIN);   

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/
#define WIFI_SSID       "Sudeep Singh"
#define WIFI_PASS       "9785192270"

/************************* Adafruit.io Setup *********************************/

#define IO_USERNAME    "AnshumanFauzdar"
#define IO_KEY         "5603bbb3535746bbb83d995de782102a"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *attendanceFeed = io.feed("Attendance");

void setup() 
{
  Serial.begin(9600); 
  io.connect();
  while(io.status() < AIO_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
                                          
  SPI.begin();                                                  
  mfrc522.PCD_Init();                                              
  Serial.println(F("Read data from card:"));    
}

void loop() 
{
  
//-------------------READING VALUE FROM CARD------------------------
  
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));

  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

  Serial.print(F("Name: "));

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }
  Serial.print(" ");

  //---------------------------------------- GET LAST NAME

  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT LAST NAME
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i] );
  }


  //----------------------------------------

  Serial.println(F("\n**End Reading**\n"));

  delay(1000); //change value if you want to read cards faster

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

   io.run();
   attendanceFeed->save("Anshuman");
   Serial.print("Data Sent");
   delay(5000);


}
