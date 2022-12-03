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

    int str_len = load_string.length() + 1;
    char parse_s[str_len];
    load_string.toCharArray(parse_s, str_len);

    int numb_splits = split(parse_s, str_len, components, 10);
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

int User::split(char line[], int line_len, String comps[], int max_size) {

    int err_code = 0;
    int comp_pos = 0;

    for (int pos = 0; (pos < line_len) and (err_code == 0); pos++) {
 

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


void readCSV(File file, int points_list[], int numb_users) {

    file.seek(0);
    int current_users = 0;

    char ctoi_holder[4] = {'\0' , '\0' , '\0' , '\0'};
    int holder_place = 0;

    while((file.peek() != -1)){
        char c = file.read();
        
        if(c != ','){

            if(c != '\x0'){
                // Serial.print(c);
                // Serial.print(" ");
            }else{
                return;
            }

            if(holder_place < 4){

                ctoi_holder[holder_place] = c;
                holder_place++;

            }else{
                Serial.println("Too many points");
                return;
            }
            

        }else{
            holder_place = 0;
            
            int point = 0;
            int mult = 1;

            for(int i = 3; i >= 0; i--) {

                int ic = (int)ctoi_holder[i];

                if((ic >= 48) and (ic <= 57)){
                    point += mult*(ic - 48);
                    mult = mult*10;
                }

            }

            // Serial.println(point);
            for(int i = 0; i < 4; i++){
                ctoi_holder[i] = '\x0';
            }

            points_list[current_users] = point;

            current_users++;
        }

        if(current_users >= numb_users){
            // Serial.println("Done");
            return;
        }
    }
    

    return;

}


void writeCSV(File file, int points_list[], int numb_users){

    char writeStr[500];
    for(int i = 0; i < 500; i++){
        writeStr[i] = '\x0';
    }

    int place = 0;
    for(int i = 0; i < numb_users; i++){

        int point = points_list[i];

        if(point > 9999){
            Serial.println("Too many points");
            return;
        } else{
            // Serial.println(point);
            int ones = point % 10;
            int tens = (point - ones) % 100;
            int hundreds = (point - tens -ones) % 1000;
            int thousands = (point - hundreds - tens - ones);

            if(point > 999){
                // Serial.print(thousands/1000);
                writeStr[place] = (thousands/1000) + 48;
                place++;
            }
            if(point > 99){
                // Serial.print(hundreds/100);
                writeStr[place] = (hundreds/100) + 48;
                place++;
            }
            if(point > 9){
                // Serial.print(tens/10);
                writeStr[place] = (tens/10) + 48;
                place++;
            }
            
            // Serial.println(ones);
            writeStr[place] = ones + 48;
            place++;

            
            writeStr[place] = ',';
            place++;
            
            

        }

    }

    // for(int i = 0; i < 500; i++){
    //     if(writeStr[i] != '\x0'){
    //         Serial.print(writeStr[i]);
    //     }
        
    // }
    file.seek(0);
    file.write(writeStr);

    return;
}