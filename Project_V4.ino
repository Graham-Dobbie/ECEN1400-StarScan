#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SD.h>
#include "playSong.h"
#include "animation.h"
#include "user.hpp"
 
#define SS_PIN 10
#define RST_PIN 6
MFRC522 mfrc522(SS_PIN, RST_PIN);   

User students[3];
User teacher;


void setup()
{
  Serial.begin(9600);  
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcdSetup();

  teacher.setUID("41 92 B9 74");

  students[0].setUID("B1 58 B4 74");
  students[0].setUsername("Graham");
  students[0].setPoints(9);

  students[1].setUID("2C 8D 62 34");
  students[1].setUsername("Seif");
  students[1].setPoints(23);

  students[2].setUID("0B F6 0A 45");
  students[2].setUsername("Nabil");
  students[2].setPoints(4);

  Serial.println("Students initilied");
  

}

String scanFunction() {
  bool scannedCard = false;
  String content = "";

  Serial.println("here6");

  while(!scannedCard ) {
      if (mfrc522.PICC_IsNewCardPresent() and mfrc522.PICC_ReadCardSerial()) {
//      byte letter;
        for (byte i = 0; i < mfrc522.uid.size; i++) 
        {
         //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
          //Serial.print(mfrc522.uid.uidByte[i], HEX);
          content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
          content.concat(String(mfrc522.uid.uidByte[i], HEX));
       
        }
        content.toUpperCase();

        if(content == "") {
          scannedCard = false;
        } else {
          scannedCard = true;
        }
      }
      Serial.println(content);
  }
  
  if (scannedCard){
    return content.substring(1);
   }

   else{
    return "No Card Found";
   }
  
}

bool verify_teacher(){
  Serial.println("here2");
  noInterrupts();
  if (scanFunction() == teacher.getUID() ){
    Serial.println("here4");
    return true;
    }else{
      Serial.println("here5");
      return false;
      }
  interrupts();
      
  }


User student_verify(){
  noInterrupts();
  String uid = scanFunction();
  for(User u : students){
    if( uid == u.getUID()){
      return u;
    }
  }
  interrupts();

//  lcdPrint("Student", "Not Found");
  User empty;
  return empty;
}
  
void loop() 
{ 
  Serial.println("Place Teacher Tag");
  lcdPrint("Scan teacher tag", "");
  Serial.println("here");
  if(verify_teacher()) {
    lcdPrint("teacher tag", "confirmed");
    delay(1000);
    lcdPrint("Scan Student tag", "");
    User student  = student_verify();
    if(student.getUID() != "00 00 00 00"){
      lcdPrint("student tag", "confirmed");
      delay(500);
      student.givePoint();
      lcdAnimation(student.getUsername(), student.getPoints());
      
      playSong();
      }
      
    
  } else {
    lcdPrint("Incorrect Tag", "");
    return;
  }
  lcdClear();
  //lcd.print(content);
  
}
