#include <Arduino.h>
#include <user.hpp>


Sd2Card card;
SdFile root;
SdVolume volume;

void printDirectory(File dir, int numTabs) {
    while (true) {
        File entry = dir.openNextFile();
        if (!entry) {
            // No more files
            break;
        }

        for (uint8_t i = 0; i < numTabs; i++) {
            Serial.print('\t');
        }

        Serial.print(entry.name());
        if (entry.isDirectory()) {
            Serial.println("/");
            printDirectory(entry, numTabs + 1);
        } else {
            // Files have sizes, directories do not
            Serial.print("\t\t");
            Serial.println(entry.size(), DEC);
        }
    }
}

void test_read() {

    // if (!SD.begin(SD_chip_select__)) {
    //     Serial.println("SD card failed to open");
    //     while (true) {
    //     }
    // }

    if (SD.exists("test.txt")) {

        Serial.println("file open");

    }
    File wf = SD.open("test.txt", FILE_READ);

    char c = wf.read();

    while (c != -1) {
        if(c == ' '){
            Serial.print(0);
        }
        else{
            Serial.print(c);
        }
        
        c = wf.read();
    }

    wf.close();
}

void test_write() {

    if (SD.exists("test.txt")) {

        Serial.println("file open");

    } else {
        Serial.println("Creating file");
        SD.open("test.txt", O_CREAT).close();

    }

    File wf = SD.open("test.txt", O_TRUNC | O_WRITE);
    int result = wf.println("Hello     ");
    Serial.println(result);
    wf.close();

    test_read();

    File nwf = SD.open("test.txt", FILE_WRITE);
    Serial.println(nwf.seek(4));
    int nresult = nwf.print("lo");
    Serial.println(nresult);
    nwf.close();
    test_read();

}



void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);

    if (!SD.begin(SD_chip_select__)) {

        Serial.println("SD card failed to open");
        while (true) {
        }
    }

    // test_write();
    // test_read();

    File file = SD.open("users.csv", FILE_WRITE);

    if(!file){
        Serial.println("Cant open file");
    }else{
        Serial.println("Opened file");
    }

    const int numb_users = 3;
    int points_in[numb_users] = {223,3335,26};
    int points_out[numb_users];

    

    // writeCSV(file, points_in, numb_users);
    readCSV(file, points_out, numb_users);

    for(int i = 0; i < numb_users; i++){
        Serial.println(points_out[i]);
    }

    points_out[0]++;
    writeCSV(file, points_out, numb_users);

    



    // File file = SD.open("users.csv", FILE_READ);
    // String line = db.getline(file);
    // Serial.println(line.length());

    // while(line.length() != 0){
    //   line = db.getline(file);
    //   Serial.println(line);
    // }

    // if(!card.init(SPI_HALF_SPEED, SD_chip_select__)){
    //   Serial.println("Init Failed");
    // }
    // volume.init(card);
    // root.openRoot(volume);

    // root.ls(LS_R | LS_DATE | LS_SIZE);
    // root.close();

    // Serial.println("done!");
    file.close();
}

void loop() {
    // put your main code here, to run repeatedly:
}