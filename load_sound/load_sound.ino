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


bool serial_handshake( int timeout){
  
  bool rec = false;
  byte stream[2];

  int start_time = millis();
  
  while(!rec){

    if((stream[0] == 111) and (stream[1] == 011)){
      Serial.write(100);
      return true;
    }
    else if((millis() - start_time) >= timeout*1000){
      
      Serial.write(404);
      return false;
      
    }

    else{
       if (Serial.available() > 0) {
        
        // read the incoming byte:
        stream[0] = stream[1];
        stream[1] = Serial.read();
      }
    }
    
  }
}


void setup() {

  Serial.begin(115200);
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
  if (SD.exists("sounds")) {

    Serial.println("There is a sounds directory");

  } else {

    Serial.println("There is not a sound file directory... I will make one for you!");
    if(!SD.mkdir("sounds")) {
      Serial.println("Error creating file");
      while(1);
    }
    else{
      Serial.println("Created sounds folder");
    }
  }

  Serial.println("To upload a file close the Serial Moniter");

  delay(2000);

  serial_handshake(10);
  

//  int incoming = 0;
//
//  if (Serial.available() > 0) {
//    // read the incoming byte:
//    incoming = Serial.read();  
//  }
//
//  
//  


}

void loop() {
  // put your main code here, to run repeatedly:

//  int incoming = 0;
//
//    if (Serial.available() > 0) {
//    // read the incoming byte:
//    incoming = Serial.read();
//
//    // say what you got:
//    Serial.print("I received: ");
//    Serial.println(incoming, DEC);
//  }

}
