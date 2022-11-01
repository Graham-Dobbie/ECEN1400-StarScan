#include "user.hpp"

User::User() : student_name_("NULL"), points_(-1), student_name_max_length__(16) { setUID("0 0 0 0"); }

User::User(std::string name, std::string uid) : student_name_(name), points_(0), student_name_max_length__(16) {

    int set_uid_code = setUID(uid);
    if (set_uid_code == 1) {
        std::cout << "UID incorect" << std::endl;
    }
}

std::string User::getUsername() { return student_name_; }

int User::setUsername(std::string name) {

    if (name.length() > student_name_max_length__) {

        student_name_ = name.substr(0, 15);
        return 1;

    } else {

        student_name_ = name;
        return 0;
    }
}

std::string User::getUID() {

    std::string return_string;

    for (int i = 0; i < 4; i++) {

        char hexes[2];
        int id = student_id_[i];
        intToChr(hexes, id);

        return_string += hexes[0];
        return_string += hexes[1];
        return_string += ' ';
    }

    return return_string.substr(0, 11);
}

int User::setUID(std::string uid) {

    std::string hexes[4];

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

int User::load(std::string load_string) { // uid1,uid2,uid3,uid4,name,points

    std::string components[10];
    int numb_splits = split(load_string, components, 10);

    if (numb_splits < 0) {
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        student_id_[i] = std::stoi(components[i]);
    }

    setUsername(components[4]);
    setPoints(stoi(components[5]));

    return 0;
}

std::string User::save() { // uid1,uid2,uid3,uid4,name,points

    std::string data;

    for (int id : student_id_) {
        data += std::to_string(id);
        data += ",";
    }

    data += student_name_;
    data += ",";

    data += std::to_string(points_);

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

int User::split(std::string line, std::string comps[], int max_size) {

    int err_code = 0;
    int comp_pos = 0;

    for (int pos = 0; (pos < line.length()) and (err_code == 0); pos++) {
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

Database::Database() : file_path_(""), max_users_(0), numb_users_(0) {}

Database::Database(std::string path) : file_path_(path), max_users_(50), numb_users_(0) {

    std::ifstream file;

    file.open(file_path_);
    if (file.fail()) {
        std::cout << "file failed to open" << std::endl;
        return;
    }

    int total_users = 0;
    User load_user;

    while ((!file.eof()) and (total_users < max_users_)) {

        std::string line;
        std::getline(file, line);

        load_user.load(line);

        if (line.length() > 0) {
            if (load_user.load(line) == 0) {
                user_index_[total_users] = load_user.getUID();
                total_users++;

            } else {
                std::cout << "Warning: line '" << line << "' is not a valid user" << std::endl;
            }
        }
    }

    if (!file.eof()) {
        std::cout << "Warning: you reached the max amount of users some might not have been added" << std::endl;
    }

    numb_users_ = total_users;

    file.close();
}

User Database::loadUser(std::string UID) {

    std::ifstream file;
    std::string line;
    User return_user = User();

    file.open(file_path_);
    if (file.fail()) {
        std::cout << "file failed to open" << std::endl;
        return return_user;
    }

    int uid_index = -1;
    for (int i = 0; i < max_users_; i++) {
        std::getline(file, line);

        if (user_index_[i] == UID) {
            if (line.length() != 0) {
                return_user.load(line);
                return return_user;
            } else {
                std::cout << "User deleted" << std::endl;
                return return_user;
            }
        }
    }

    std::cout << "Couldn't find user" << std::endl;
    file.close();

    return return_user;
}

int Database::saveUser(std::string UID, User user) {

    std::ifstream file;
    std::ofstream temp_file;

    std::string line;

    file.open(file_path_);
    if (file.fail()) {
        std::cout << "file failed to open" << std::endl;
        return 1;
    }

    temp_file.open("temp_users.csv");
    if (temp_file.fail()) {
        std::cout << "temp file failed to open" << std::endl;
        return 2;
    }

    for (int i = 0; ((i < max_users_) and (!file.eof())); i++) {
        std::getline(file, line);

        if (user_index_[i] == UID) {
            temp_file << user.save();
        } else {
            temp_file << line;
        }
        if (!file.eof()) {
            temp_file << "\n";
        }
    }

    file.close();
    temp_file.close();
    std::ifstream temp_file_read;
    std::ofstream file_write;

    file_write.open(file_path_);
    if (file.fail()) {
        std::cout << "file failed to open" << std::endl;
        return 1;
    }

    temp_file_read.open("temp_users.csv");
    if (file.fail()) {
        std::cout << "file failed to open" << std::endl;
        return 1;
    }

    int gone_through = 0;
    while (!temp_file_read.eof()) {

        std::getline(temp_file_read, line);
        file_write << line;

        gone_through++;

        if (gone_through < numb_users_) {
            file_write << "\n";
        }
    }

    return 0;
}

int Database::addUser(User user) {

    if (numb_users_ >= max_users_) {
        return 2;
    }

    for (std::string uid : user_index_) {
        if (uid == user.getUID()) {
            return 3;
        }
    }

    std::ofstream app_file(file_path_, std::ios::app);

    if (app_file.fail()) {
        std::cout << "file failed to open" << std::endl;
        return 1;
    }

    app_file << "\n" << user.save();

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

    std::ifstream file;
    std::ofstream temp_file;

    std::string line;

    file.open(file_path_);
    if (file.fail()) {
        std::cout << "file failed to open" << std::endl;
        return 1;
    }

    temp_file.open("temp_users.csv");
    if (temp_file.fail()) {
        std::cout << "temp file failed to open" << std::endl;
        return 2;
    }

    for (int i = 0; ((i < max_users_) and (!file.eof())); i++) {
        std::getline(file, line);

        if (i != place) {
            temp_file << line;

            if (!file.eof()) {
                temp_file << "\n";
            }
        }
    }

    numb_users_--;

    file.close();
    temp_file.close();
    std::ifstream temp_file_read;
    std::ofstream file_write;

    file_write.open(file_path_);
    if (file.fail()) {
        std::cout << "file failed to open" << std::endl;
        return 1;
    }

    temp_file_read.open("temp_users.csv");
    if (file.fail()) {
        std::cout << "file failed to open" << std::endl;
        return 1;
    }

    int gone_through = 0;
    while (!temp_file_read.eof()) {

        std::getline(temp_file_read, line);
        file_write << line;

        gone_through++;

        if (gone_through < numb_users_) {
            file_write << "\n";
        }
    }

    return 0;
}
