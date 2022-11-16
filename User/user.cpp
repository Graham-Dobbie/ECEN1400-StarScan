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

int User::load(String load_string) { // uid1,uid2,uid3,uid4,name,points

    String components[10];
    
    char parse_s[50];
    load_string.toCharArray(parse_s, 50);

    int numb_splits = split(parse_s, components, 10);
    int i = 1;
    // for(String comp : components){
    //     Serial.print(i);
    //     i++;
    //     Serial.println(comp);
    // }

    if (numb_splits < 0) {
        Serial.println("Bad split");
        return 1;
    }

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

int User::split(char line[], String comps[], int max_size) {

    int err_code = 0;
    int comp_pos = 0;

    int line_len = sizeof(*line)/sizeof(line[0]);

    Serial.println("here");
    Serial.println(line);
    // Serial.println(line_len);

    for (int pos = 0; (pos < line_len) and (err_code == 0); pos++) {
        Serial.println("in loop");

        if (line[pos] == ',') {

            comp_pos++;

            if (comp_pos >= max_size) {
                err_code = -1;
            }
        } else {
            comps[comp_pos] += line[pos];
        }
    }

    if (err_code != 0) {
        return err_code;
    } else {
        return comp_pos + 1;
    }
}

Database::Database() : max_users_(0), numb_users_(0) {}

Database::Database(String path) : max_users_(50), numb_users_(0){
    if (!SD.begin(SD_chip_select__)) {
        Serial.println("SD card failed to open");
        while (true) {
        }
    }

    if(path.length() > 12){
        Serial.println("File name too long");
    }
    path.toCharArray(file_path_, 12);

    if (!SD.exists(file_path_)) {
        Serial.println("File failed to open");
        SD.open(file_path_, FILE_WRITE);
    }

    File file = SD.open(file_path_, FILE_READ);

    if (!file) {
        Serial.println("Cant read file");
    }

    int total_users = 0;
    User load_user;

    while (!(file.peek() == -1) and (total_users < max_users_)) {

        String line = getline(file);

        if (line.length() > 0) {
            if (load_user.load(line) == 0) {
                user_index_[total_users] = load_user.getUID();
                total_users++;
            } else {
                Serial.println("Warning: line '" + line + "' is not a valid user");
            }
        }
    }

    if (!file.read() == -1) {
        Serial.println("Warning: you reached the max amount of users some might not have been added");
    }

    numb_users_ = total_users;

    for(String uid : user_index_){
        if(uid.length() != 0){
            Serial.println(uid);
        }
        
    }

    file.close();
    SD.end();
}

User Database::loadUser(String UID) {

    String line;
    User return_user = User();

    if (!SD.exists(file_path_)) {
        Serial.println("file failed to open");
        return return_user;
    }

    File file = SD.open(file_path_, FILE_READ);

    if (!file) {
        Serial.println("Cant read file");
    }

    int uid_index = -1;
    for (int i = 0; i < max_users_; i++) {
        line = getline(file);

        if (user_index_[i] == UID) {
            if (line.length() != 0) {
                return_user.load(line);
                return return_user;
            } else {
                Serial.println("User deleted");
                return return_user;
            }
        }
    }

    Serial.println("Couldn't find user");
    file.close();

    return return_user;
}

int Database::saveUser(String UID, User user) {

    String line;

    if (!SD.exists(file_path_)) {
        Serial.println("file failed to open");
        return 1;
    }
    File file = SD.open(file_path_, FILE_WRITE);

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

    file.seek(place * 50);
    file.print(user.save());

    return 0;
}

int Database::addUser(User user) {

    if (!SD.begin(SD_chip_select__)) {

        Serial.println("SD card failed to open");
        while (true) {
        }
    }

    if (numb_users_ >= max_users_) {
        Serial.println("Reach the maximum number of users");
        return 2;
    }

    for (String uid : user_index_) {
        if (uid == user.getUID()) {
            Serial.println("User already exists");
            return 3;
        }
    }

    if (!SD.exists(file_path_)) {
        Serial.print("file failed to open: ");
        Serial.println(file_path_);
        return 1;
    }

    File file = SD.open(file_path_, O_WRITE | O_READ);

    if (!file) {
        Serial.println("Cant open file");
    }
    file.seek(file.size() - 1);
    String f_data = user.save();

    while (f_data.length() < 48) {
        f_data += '\x1F';
    }

    Serial.println(f_data);
    Serial.println(file.println(f_data));
    // if(file.print(f_data) < 50){
    //     Serial.println("Didn't write data");
    //     file.close();
    //     return 4;
    // }

    file.close();
    SD.end();

    user_index_[numb_users_] = user.getUID();

    numb_users_++;

    return 0;
}

int Database::removeUser(User user) {

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

    if (!SD.exists(file_path_)) {
        Serial.println("file failed to open");
        return 1;
    }
    File file = SD.open(file_path_, FILE_WRITE);

    String f_data;

    while (f_data.length() < 49) {
        f_data += ' ';
    }
    f_data += '\n';

    file.print(f_data);

    numb_users_--;

    file.close();

    return 0;
}

String Database::getline(File file) {

    String line;

    char c = file.read();
    while ((c != -1) and (c != '\n')) {
        if(c != '\x1F'){
            line += c;
            
        }
        c = file.read();
    }

    return line;
}
