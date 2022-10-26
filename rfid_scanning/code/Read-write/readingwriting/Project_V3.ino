#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SD.h>
 
#define SS_PIN 10
#define RST_PIN 6
MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal lcd(9,8,5,4,3,2);

MFRC522::MIFARE_Key key;
int block=62;  
byte blockcontent[16] = {"Student1,15"};  //an array with 16 bytes to be written into one of the 64 card blocks is defined
byte readbackblock[18];

void setup()
{
  Serial.begin(9600);  
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.begin(16,2);

   for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;  //keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
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

int readBlock(int blockNumber, byte arrayAddress[]) 
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector

  //authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed (read): ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }

//reading a block
byte buffersize = 18;
status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);
  if (status != MFRC522::STATUS_OK) {
          Serial.print("MIFARE_read() failed: ");
          Serial.println(mfrc522.GetStatusCodeName(status));
          return 4;//return "4" as error message
  }
  Serial.println("block was read");
}

int writeBlock(int blockNumber, byte arrayAddress[]) 
{
  //this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber+1)%4 == 0){Serial.print(blockNumber);Serial.println(" is a trailer block:");return 2;}
  Serial.print(blockNumber);
  Serial.println(" is a data block:");
  
  //authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed: ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
  
  //writing the block 
  status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16);
  //status = mfrc522.MIFARE_Write(9, value1Block, 16);
  if (status != MFRC522::STATUS_OK) {
           Serial.print("MIFARE_Write() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return 4;//return "4" as error message
  }
  Serial.println("block was written");
}

String getInfo(){
    String info = "";
    bool newCard = false;
   // Look for new cards
   while(!newCard) {
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
    newCard = false;
  }
  
  // Select one of the cards
  else if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    newCard = false;
  } else {
    newCard = true;
  }
   }
  
    Serial.println("card selected");
         
   //the blockcontent array is written into the card block
   
   //writeBlock(block, blockcontent);
   
   //read the block back
   readBlock(block, readbackblock);
   //uncomment below line if you want to see the entire 1k memory with the block written into it.
   //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
   
   //print the block contents
   //Serial.print("read block: ");
   for (int j=0 ; j<16 ; j++)
   { 
     //Serial.write (readbackblock[j]);
     info += readbackblock[j];
   }
   //Serial.println("");

   return info;
  }
  
void loop() 
{ 
  Serial.print(getInfo());
  exit(0);
  getInfo();
  /*lcdPrint("Scan teacher tag", "");
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
  return;*/
  
}
