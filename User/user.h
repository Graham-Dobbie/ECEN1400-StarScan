#ifndef User_h
#define User_h

#include <string>
#include <map>

class User
{
  public:
    User();
    User(std::string name , std::string uid);

    int loadUser(std::string uid);
    int saveUser();

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

  private:

    std::string student_name_;
    std::string student_id_;

    int points_;

    std::map< std::string , std::string> user_data_

    static const std::string path__;

};

#endif