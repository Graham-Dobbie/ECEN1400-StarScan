#include "animation.h";

//LiquidCrystal lcd(9,8,5,4,3,2);
LiquidCrystal lcd(33,13,32,27,14,12);
void lcdClear(){
  lcd.clear();
  }
  
void lcdSetup(){
  lcd.begin(16,2);
}

void lcdPrint(String one, String two){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(one);
    lcd.setCursor(0,1);
    lcd.print(two);
  }

void image(int A, int B) {
  lcd.clear();

  byte image01[8] = {B00000, B00000, B00000, B00011, B00111, B01111, B11111, B11111};
  byte image17[8] = {B11111, B11111, B01111, B00111, B00011, B00000, B00000, B00000};
  byte image18[8] = {B10000, B11000, B11100, B11110, B11000, B00000, B00000, B00000};
  byte image02[8] = {B00000, B00000, B00000, B11000, B11110, B11100, B11000, B10000};
  byte image08[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00110};
  byte image24[8] = {B00110, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
  


  lcd.createChar(0, image01);
  lcd.createChar(1, image17);
  lcd.createChar(2, image18);
  lcd.createChar(3, image02);
  lcd.createChar(4, image08);
  lcd.createChar(5, image24);
  


  lcd.setCursor(A, 0);
  lcd.write(byte(0));
  lcd.setCursor(A, 1);
  lcd.write(byte(1));
  lcd.setCursor(B, 1);
  lcd.write(byte(2));
  lcd.setCursor(B, 0);
  lcd.write(byte(3));
  lcd.setCursor(7, 0);
  lcd.write(byte(4));
  lcd.setCursor(7, 1);
  lcd.write(byte(5));
 
}

void image1(int C, int D) {
  lcd.clear();

  byte image01[8] = {B00000, B00000, B00000, B00011, B00111, B01111, B11111, B11111};
  byte image02[8] = {B00000, B00000, B00000, B11000, B11100, B11110, B11111, B11111};
  byte image18[8] = {B11111, B11111, B11110, B11100, B11000, B00000, B00000, B00000};
  byte image17[8] = {B11111, B11111, B01111, B00111, B00011, B00000, B00000, B00000};
  byte image08[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00110};
  byte image24[8] = {B00110, B00000, B00000, B00000, B00000, B00000, B00000, B00000};



  lcd.createChar(0, image01);
  lcd.createChar(1, image02);
  lcd.createChar(2, image18);
  lcd.createChar(3, image17);
  lcd.createChar(4, image08);
  lcd.createChar(5, image24);



  lcd.setCursor(C, 0);
  lcd.write(byte(0));
  lcd.setCursor(D, 0);
  lcd.write(byte(1));
  lcd.setCursor(D, 1);
  lcd.write(byte(2));
  lcd.setCursor(C, 1);
  lcd.write(byte(3));
  lcd.setCursor(7, 0);
  lcd.write(byte(4));
  lcd.setCursor(7, 1);
  lcd.write(byte(5));


}

void image2() {
  lcd.clear();

  byte image08[8] = {B00000, B00000, B00000, B11000, B11110, B11100, B11000, B10110};
  byte image24[8] = {B10110, B11000, B11100, B11110, B11000, B00000, B00000, B00000};
  byte image07[8] = {B00000, B00000, B00000, B00011, B00111, B01111, B11111, B11111};
  byte image23[8] = {B11111, B11111, B01111, B00111, B00011, B00000, B00000, B00000};

  lcd.createChar(0, image08);
  lcd.createChar(1, image24);
  lcd.createChar(2, image07);
  lcd.createChar(3, image23);

  lcd.setCursor(7, 0);
  lcd.write(byte(0));
  lcd.setCursor(7, 1);
  lcd.write(byte(1));
  lcd.setCursor(6, 0);
  lcd.write(byte(2));
  lcd.setCursor(6, 1);
  lcd.write(byte(3));
  }

void image3() {
  lcd.clear();

  byte image08[8] = {B00000, B00000, B00000, B11000, B11100, B11110, B11111, B11111};
  byte image24[8] = {B11111, B11111, B11110, B11100, B11000, B00000, B00000, B00000};
  byte image07[8] = {B00000, B00000, B00000, B00011, B00111, B01111, B11111, B11111};
  byte image23[8] = {B11111, B11111, B01111, B00111, B00011, B00000, B00000, B00000};


  lcd.createChar(0, image08);
  lcd.createChar(1, image24);
  lcd.createChar(2, image07);
  lcd.createChar(3, image23);


  lcd.setCursor(7, 0);
  lcd.write(byte(0));
  lcd.setCursor(7, 1);
  lcd.write(byte(1));
  lcd.setCursor(6, 0);
  lcd.write(byte(2));
  lcd.setCursor(6, 1);
  lcd.write(byte(3));

}

void lcdAnimation(String Name, int Points){
  lcd.clear();
  lcdPrint("Great job", Name);
  delay(1000);
  
  lcd.clear();
  image(0,1);
  delay(300);
  image1(1,2);
  delay(300);
  image(2,3);
  delay(300);
  image1(3,4);
  delay(300);
  image(4,5);
  delay(300);
  image1(5,6);
  delay(300);
  image2();
  delay(300);
  image3();
  delay(300);
  lcdPrint("You now have", String(Points) + " Points");
  delay(2000);
  lcd.clear();
  
  }
