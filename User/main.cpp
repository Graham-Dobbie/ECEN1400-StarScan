#include "user.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {

    Database db_empty = Database();

    Database db = Database("users.csv");

    User u1 = db.loadUser("91 03 04 BA");

    cout << u1.getUsername() << endl;

    return 0;
}