#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SD.h>
 
#define SS_PIN 10
#define RST_PIN 6
MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal lcd(9,8,5,4,3,2);

void setup()
{
  Serial.begin(9600);  
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.begin(16,2);

   for (byte i = 0; i < 6; i++) {

  }

}

String scanFunction() {
  bool scannedCard = false;
  String content= "";

  unsigned int start = millis();

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
  }
  if (scannedCard){
    return content.substring(1);
   }

   else{
    return "No Card Found";
   }
  
}

bool verified(String tag){
  if (scanFunction() == tag ){
    return true;
    }else{
      return false;
      }
  }

void lcdPrint(String one, String two){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(one);
    lcd.setCursor(0,1);
    lcd.print(two);
  }
  
void lcdAnimation(String Name){
  lcd.clear();
  lcdPrint("Great job", Name);
  delay(2000);
  lcd.clear();
  }




  
void loop() 
{ 

  lcdPrint("Scan teacher tag", "");
  if(verified("41 92 B9 74")) {
    lcdPrint("teacher tag", "confirmed");
    delay(1000);
    lcdPrint("Scan Student tag", "");
    if(verified("11 72 B9 74")){
      lcdPrint("student tag", "confirmed");
      delay(1000);
      lcdAnimation("Andrew");
      return;
      }
      
    
  } else {
    lcdPrint("Incorrect Tag", "");
    return;
  }

  lcd.clear();
  //lcd.print(content);
  return;
  
}
