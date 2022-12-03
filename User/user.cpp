#include "user.hpp"

User::User() : student_name_("NULL"), points_(-1), student_name_max_length__(16) { setUID("0 0 0 0"); }

User::User(String name, String uid) : student_name_(name), points_(0), student_name_max_length__(16) {

    int set_uid_code = setUID(uid);
    if (set_uid_code == 1) {
        Serial.println("UID incorect");
    }
}

String User::getUsername() { return student_name_; }

int User::setUsername(String name) {

    if (name.length() > student_name_max_length__) {

        student_name_ = name.substring(0, 15);
        return 1;
    } else {

        student_name_ = name;
        return 0;
    }
}

String User::getUID() {

    String return_string;

    for (int i = 0; i < 4; i++) {

        char hexes[2];
        int id = student_id_[i];
        intToChr(hexes, id);

        return_string += hexes[0];
        return_string += hexes[1];
        return_string += ' ';
    }

    return return_string.substring(0, 11);
}

int User::setUID(String uid) {

    String hexes[4];

    int current_hex = 0;
    for (int i = 0; i < uid.length(); i++) {

        if (uid[i] == ' ') {

            if (current_hex <= 3) {
                current_hex++;
            } else {
                return 1;
            }
        } else {
            hexes[current_hex] += uid[i];
        }
    }

    for (int i = 0; i < 4; i++) {
        int i_hex = 16 * chrToInt(hexes[i][0]) + chrToInt(hexes[i][1]);
        student_id_[i] = i_hex;
    }

    return 0;
}

int User::givePoint() {
    givePoints(1);
    return 0;
}
int User::givePoints(int points) {
    points_ += points;
    return 0;
}
int User::setPoints(int points) {
    points_ = points;
    return 0;
}

int User::getPoints() { return points_; }

int User::load(char load_string[], int str_len) { // uid1,uid2,uid3,uid4,name,points

    String components[10];
    for(int i = 0; i < 10 ; i++){
        components[i] = "";
    }

    int numb_splits = split(load_string, str_len, components, 10);
    int i = 1;

    if ((numb_splits < 0) or (numb_splits > 6)) {
        Serial.println("Bad split");
        return 1;
    }

    Serial.println("Components");
    Serial.println(numb_splits);
    for(int i = 0; i < numb_splits; i++){
        Serial.println(components[i]);
    }
    Serial.println();

    for (int i = 0; i < 4; i++) {
        student_id_[i] = components[i].toInt();
    }

    setUsername(components[4]);
    setPoints(components[5].toInt());

    return 0;
}

String User::save() { // uid1,uid2,uid3,uid4,name,points

    String data;

    for (int id : student_id_) {
        data += String(id);
        data += ",";
    }

    data += student_name_;
    data += ",";

    data += String(points_);

    return data;
}

int User::intToChr(char chrs[2], int convert_int) {
    int h[2];
    if (convert_int < 256) {

        h[1] = convert_int % 16;
        h[0] = (convert_int - h[1]) / 16;

        for (int i = 0; i < 2; i++) {
            if (h[i] == 10) {
                chrs[i] = 'A';
            } else if (h[i] == 11) {
                chrs[i] = 'B';
            } else if (h[i] == 12) {
                chrs[i] = 'C';
            } else if (h[i] == 13) {
                chrs[i] = 'D';
            } else if (h[i] == 14) {
                chrs[i] = 'E';
            } else if (h[i] == 15) {
                chrs[i] = 'F';
            } else {
                chrs[i] = char(48 + h[i]);
            }
        }

        return 0;
    }

    else {

        return -1;
    }
}

int User::chrToInt(char hex_value) {

    if (hex_value == 'A') {
        return 10;
    } else if (hex_value == 'B') {
        return 11;
    } else if (hex_value == 'C') {
        return 12;
    } else if (hex_value == 'D') {
        return 13;
    } else if (hex_value == 'E') {
        return 14;
    } else if (hex_value == 'F') {
        return 15;
    } else {
        return hex_value - '0';
    }
}

int User::split(char line[], int line_len, String comps[], int max_size) {

    int err_code = 0;
    int comp_pos = 0;

    // Serial.println("here");
    
    
    Serial.println("Split");
    Serial.println(line_len);
    for(int i = 0; i < line_len; i++){
        Serial.print(line[i]);
    }
    Serial.println();

    for (int pos = 0; pos < line_len; pos++) {
        // Serial.println("in loop");

        if (line[pos] == ',') {
            Serial.println(",");

            comp_pos++;


            if (comp_pos >= max_size) {
                Serial.print("Too big");
                return -1;
            }
        } else {
            Serial.print(line[pos]);
            comps[comp_pos].concat(line[pos]);
        }
    }
    Serial.println();
    

    Serial.println(comp_pos + 1);
    for(int i = 0; i < comp_pos + 1; i++){
        Serial.println(comps[i]);
    }
    Serial.println("Split done");


    if (err_code != 0) {
        return err_code;
    } else {
        return comp_pos + 1;
    }
}


Database::Database(): max_users_(0), numb_users_(0){};

Database::Database(File file) : max_users_(50), numb_users_(0), user_file_(file){

    int total_users = 0;
    User load_user;
    
    char line[50];
    for(int i = 0; i < 50; i++){
        line[i] = '\x0';
    }

    user_file_.seek(0);
    Serial.println(user_file_.peek());


    while ((!(user_file_.peek() == -1)) and (total_users < max_users_)) {

        int line_len = getline(user_file_, line);

        if (line_len > 0) {
            if (load_user.load(line, line_len) == 0) {
                user_index_[total_users] = load_user.getUID();
                total_users++;
            } else {
                // Serial.println("Warning: line '" + line + "' is not a valid user");
            }
        }else{
            break;
        }
    }

    if (!user_file_.read() == -1) {
        Serial.println("Warning: you reached the max amount of users some might not have been added");
    }

    numb_users_ = total_users;
    Serial.println(numb_users_);

    for(int i = 0; i < numb_users_; i++){
        
        Serial.println(user_index_[i]);
        
        
    }
}

User Database::loadUser(String UID) {

    char line[50];
    for(int i = 0; i < 50; i++){
        line[i] = '\x0';
    }

    User return_user = User();
    user_file_.seek(0);

    int uid_index = -1;
    for (int i = 0; i < max_users_; i++) {
        int line_len = getline(user_file_, line);

        if (user_index_[i] == UID) {
            if (line_len != 0) {
                return_user.load(line, line_len);
                return return_user;
            } else {
                Serial.println("User deleted");
                return return_user;
            }
        }
    }

    Serial.println("Couldn't find user");
    

    return return_user;
}

int Database::saveUser(String UID, User user) {

    String line;
    user_file_.seek(0);


    int place = -1;
    for (int i = 0; i < max_users_; i++) {
        if (UID == user_index_[i]) {
            place = i;
            break;
        }
    }

    if (place == -1) {
        Serial.println("User doesn't exist");
        return 2;
    }

    user_file_.seek(place * 50);
    user_file_.print(user.save());

    return 0;
}

int Database::addUser(User user) {

    if(!user_file_){
        Serial.println("Can't Access File");
    }

    user_file_.seek(0);

    if (numb_users_ >= max_users_) {
        Serial.println("Reach the maximum number of users");
        return 2;
    }

    for (int i = 0; i < numb_users_; i++) {
        if (user_index_[i] == user.getUID()) {
            Serial.println("User already exists");
//            return 3;
        }
          
    }

    user_file_.seek(user_file_.size() - 1);
    String f_data = user.save();

    while (f_data.length() < 48) {
        f_data.concat('\x1F');
    }
    


    Serial.println("Add user");
    Serial.println(f_data.length());
    Serial.println(f_data);
    int lines_writen = user_file_.println(f_data);
    Serial.println(lines_writen);

    if(lines_writen < 50){
        Serial.println("Didn't write data");
        
        return 4;
    }


    user_index_[numb_users_] = user.getUID();

    numb_users_++;

    return 0;
}

int Database::removeUser(User user) {

    if(!user_file_){
        Serial.println("Can't Access File");
    }

    user_file_.seek(0);

    int place = -1;
    for (int i = 0; i < numb_users_; i++) {

        if (user_index_[i] == user.getUID()) {
            place = i;
            break;
        }
    }

    if (place == -1) {
        return 1;
    }

    user_index_[place] = "0 0 0 0";


    String f_data;

    while (f_data.length() < 49) {
        f_data += ' ';
    }
    f_data += '\n';

    user_file_.print(f_data);

    numb_users_--;

    return 0;
}

int Database::getline(File file, char line[]) {

    int pos = 0;
    int numb_chars = 0;

    char c = file.read();
    Serial.println("Getline");
    while ((c != -1) and (c != '\r') and (c != '\n') and (pos < 50)) {
        
        if(c != '\x1F'){
            line[pos] = c;
            numb_chars++;
        }
        Serial.print(line[pos]);
        pos++;
        c = file.read();
    }
    Serial.println();

    return numb_chars;
}
