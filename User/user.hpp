#ifndef User_h
#define User_h
#define SD_chip_select__ 9

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

class User
{
public:
    User();
    User(String name, String uid);

    String getUsername();
    int setUsername(String name);

    String getUID();
    int setUID(String uid);

    int givePoint();
    int givePoints(int points);
    int setPoints(int points);

    int getPoints();

    int load(String load_string);
    String save();

    int chrToInt(char hex);
    int intToChr(char chrs[2], int convert_int);

    int split(char line[], int line_len, String comps[], int max_size);

private:
    String student_name_;
    int student_name_max_length__;
    int student_id_[4];

    int points_;
};

void readCSV(File file, int points_list[], int numb_users);

void writeCSV(File file, int points_list[], int numb_users);

#endif