#ifndef animation_h

#define animation_h

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SD.h>

void lcdClear();

void lcdSetup();

void lcdPrint(String one, String two);

void image(int A, int B);

void image1(int C, int D); 

void image2() ;

void image3() ;

void lcdAnimation(String Name, int Points);

#endif
