#ifndef User_h
#define User_h

#include <fstream>
#include <iostream>
#include <map>
#include <string>

class User {
  public:
    User();
    User(std::string name, std::string uid);

    std::string getUsername();
    int setUsername(std::string name);

    std::string getUID();
    int setUID(std::string uid);

    int givePoint();
    int givePoints(int points);
    int setPoints(int points);

    int getPoints();

    int load(std::string load_string);
    std::string save();

    int chrToInt(char hex);
    int intToChr(char chrs[2], int convert_int);

    int split(std::string line, std::string comps[], int max_size);

  private:
    std::string student_name_;
    int student_name_max_length__;
    int student_id_[4];

    int points_;
};

class Database {

  public:
    Database();
    Database(std::string path);

    User loadUser(std::string UID);

    int saveUser(std::string UID, User user);

    int addUser(User user);
    int removeUser(User user);

  private:
    int max_users_;
    int numb_users_;

    std::string file_path_;
    std::string user_index_[50];
};

#endif