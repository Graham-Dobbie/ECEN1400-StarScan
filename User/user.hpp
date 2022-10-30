#ifndef User_h
#define User_h

#include <bitset>
#include <cstddef>
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

    std::string getUserDataByElement(std::string element);
    int writeUserDataByElement(std::string element, std::string value);

    int givePoint();
    int givePoints(int points);
    int setPoints(int points);

    int getPoints();

    int loadUser(std::string load_string);
    std::string saveUser();

    int chrToInt(char hex);
    int intToChr(char chrs[2], int convert_int);

    int split(std::string line, std::string comps[], int max_size);

  private:
    std::string student_name_;
    int student_name_max_length__;
    int student_id_[4];

    int points_;

    std::map<std::string, std::string> user_data_;
};

#endif