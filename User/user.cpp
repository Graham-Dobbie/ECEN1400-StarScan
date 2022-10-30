#include "user.hpp"

User::User() : student_name_("NULL"), points_(-1), student_name_max_length__(16) {}

User::User(std::string name, std::string uid) : student_name_(name), points_(0), student_name_max_length__(16){
    
    int set_uid_code = setUID(uid);
    if (set_uid_code == 1){
        std::cout << "UID incorect" << std::endl;
    }
    
    
}

std::string User::getUsername(){
    
    return student_name_;
}

int User::setUsername(std::string name){
    
    if( name.length() > student_name_max_length__) {
        
        student_name_ = name.substr(0 , 15);
        return 1;
        
    }else {
        
        student_name_ = name;
        return 0;
    }
}




std::string User::getUID(){
    
    std::string return_string;
    
    for(int i = 0; i < 4; i++){
        
        char hexes[2];
        int id = student_id_[i];
        intToChr(hexes, id);
        
        std::cout << id << " " << hexes[0] << hexes[1] << std::endl;
        
        return_string += hexes[0];
        return_string += hexes[1];
        return_string += ' ';
    }
    
    return return_string.substr(0,10);
}


int User::setUID(std::string uid){
    
    std::string hexes[4];
    
    
    int current_hex = 0;
    for(int i = 0; i < uid.length(); i++){
        
        if(uid[i] == ' '){
            
            if(current_hex <= 3){
                current_hex++;
                
                
            } else{
                return 1;
            }
            
        }
        else{
            hexes[current_hex] += uid[i];
        }
    }
    
    for(int i = 0; i < 4; i++){
        int i_hex = 16*chrToInt(hexes[i][0]) +chrToInt(hexes[i][1]);
    }
    
    return 0;
}
    
    

// std::string User::getUserDataByElement(std::string element);
// int User::writeUserDataByElement( std::string element, std::string value);

int User::givePoint(){
    points_ ++;
    return 0;
    
}
int User::givePoints( int points){
    points_ += points;
    return 0;
    
}
int User::setPoints(int points){
    points_ = points;
    return 0;
}

int User::getPoints(){
    return points_;
}


int User::intToChr(char chrs[2], int convert_int){
    int h[2];
    if (convert_int < 256){
        
        h[1] = convert_int % 16;
        h[0] = (convert_int - h[1])/16;
        
        for(int i = 0; i < 2; i++){
            if(h[i] == 10){
                chrs[i] = 'A';
            }
            else if(h[i] == 11){
                chrs[i] = 'B';
            }
            else if(h[i] == 12){
                chrs[i] = 'C';
            }
            else if(h[i] == 13){
                chrs[i] = 'D';
            }
            else if(h[i] == 14){
                chrs[i] = 'E';
            }
            else if(h[i] == 15){
                chrs[i] = 'F';
            }
            else{
                chrs[i] = char(48 + h[i]);
            }   
        }
        
        return 0;
    }
    
    else{
        
        return -1;
    }
}


int User::chrToInt(char hex_value){
    
    if(hex_value == 'A'){
        return 10;
    }
    else if(hex_value == 'B'){
        return 11;
    }
    else if(hex_value == 'C'){
        return 12;
    }
    else if(hex_value == 'D'){
        return 13;
    }
    else if(hex_value == 'E'){
        return 14;
    }
    else if(hex_value == 'F'){
        return 15;
    }
    else{
        return hex_value - '0';
    }
}