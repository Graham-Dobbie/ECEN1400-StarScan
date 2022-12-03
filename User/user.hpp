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

    int load(char load_string[], int str_len);
    String save();

    int chrToInt(char hex);
    int intToChr(char chrs[2], int convert_int);

    int split(char line[], int len, String comps[], int max_size);

private:
    String student_name_;
    int student_name_max_length__;
    int student_id_[4];

    int points_;
};

class Database
{

public:
    Database();
    Database(File file);

    User loadUser(String UID);

    int saveUser(String UID, User user);

    int addUser(User user);
    int removeUser(User user);

    int getline(File file, char line[]);

private:
    int max_users_;
    int numb_users_;

    File user_file_;
    String user_index_[50];
};

#endif