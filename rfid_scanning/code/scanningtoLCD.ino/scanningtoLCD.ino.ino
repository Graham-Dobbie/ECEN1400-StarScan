#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SD.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal lcd(9,8,6,4,3,2);

//File myFile;
//const int chipSelectSD = 7;

void setup()
{
  Serial.begin(9600);  
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.begin(16,2);

//  if (!SD.begin(chipSelectSD)) {
//      Serial.println("initialization failed!");
//      while (1);
//      }

  // myFile = SD.open("students.txt", FILE_WRITE);
  

}

String scanFunction() {
  bool scannedCard = false;
  String content= "";

  while(!scannedCard) {
      if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      //return "none";
    }
    
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      //return "none";
    }
    //String content= "";
    byte letter;
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
  return content;
   
  
}

void loop() 
{
  String content = scanFunction();
  Serial.print(content);
  if(content == "") {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Nothing scanned");
  }
  String teacherUID = "41 92 B9 74";
  if(content.substring(1) == teacherUID) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("teacher tag");
    lcd.setCursor(0,1);
    lcd.print(" confirmed!");
    return;
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Incorrect tag");
    return;
  }
  
}
