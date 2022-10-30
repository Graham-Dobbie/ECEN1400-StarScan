#ifndef User_h
#define User_h

#include <string>
#include <map>
#include <cstddef>
#include <bitset>
#include <iostream>

class User
{
  public:
    User();
    User(std::string name , std::string uid);

    std::string getUsername();
    int setUsername(std::string name);

    std::string getUID();
    int setUID(std::string uid);

    std::string getUserDataByElement(std::string element);
    int writeUserDataByElement( std::string element, std::string value);

    int givePoint();
    int givePoints( int points);
    int setPoints(int points);

    int getPoints();
    
    int chrToInt(char hex);
    int intToChr(char chrs[2], int convert_int);

  private:
  
    
    std::string student_name_;
    int student_name_max_length__;
    int student_id_[4];

    int points_;

    std::map< std::string , std::string> user_data_;

};

#endif