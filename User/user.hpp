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

    int split(char line[], String comps[], int max_size);

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
    Database(String path);

    User loadUser(String UID);

    int saveUser(String UID, User user);

    int addUser(User user);
    int removeUser(User user);

    String getline(File file);

private:
    int max_users_;
    int numb_users_;

    char file_path_[12];
    String user_index_[50];
};

#endif