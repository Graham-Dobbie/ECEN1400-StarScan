#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal lcd(9,8,6,4,3,2);
void setup()
{
  Serial.begin(9600);  
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.begin(16,2);
  

}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
 
  //Serial.print("UID tag :");
  //Serial.println();
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
     
  }
//  Serial.println(content);
//  byte first = 1;
//  Serial.println();
//  if(content == "41 92 b9 74") {
//    lcd.print("Teacher tag confirmed!!");
//    return;
//  } else {
//    if(first) {
//      lcd.print("Incorrect tag");
//      first = 0;
//    }
//    
//  }


if(first) {
  lcd.print("7");
  first = 0;
}


  
  
}
