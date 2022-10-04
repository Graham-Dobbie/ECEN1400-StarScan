/*
 *  For this code to work with the SD card module the pinout must be this:
 *  
 *  SCK - 13
 *  DO - 12
 *  DI - 11
 *  CS - 10
 *  
 *  This can share the serial bus with the RFID reader
 * 
 */


// Include libs  SPI for the serial bus and SD controls the SD card
#include <SPI.h>
#include <SD.h>


const int chip_slct = 10;

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Checks for SD card
  Serial.print("Initializing SD card...");

  if (!SD.begin(chip_slct)) {
    Serial.println("initialization failed!");
    while (1);
  }

  Serial.println("initialization done.");

  //Starts checking for sound files
  Serial.println("Checking for sound files");
  if (SD.exists("/sound_files/")) {

    Serial.println("There is a sound file directory");

  } else {

    Serial.println("There is not a sound file directory... I will make one for you!");
    if(!SD.mkdir("sound_files")) {
      sd_error("Create DATA_DIR failed");
    }

//    SD.mkdir("sound_files"); //makes sound file directory
    
  }

  
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
