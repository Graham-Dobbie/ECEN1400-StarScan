#include "user.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {

    Database db_empty = Database();

    Database db = Database("users.csv");

    User u1 = db.loadUser("91 06 04 BA");

    u1.setPoints(100);

    db.saveUser(u1.getUID(), u1);

    User new_user = User("Simon", "91 06 04 BC");
    new_user.setPoints(12);

    // cout << new_user.save() << endl;

    cout << db.addUser(new_user) << endl;

    User graham_u = db.loadUser("91 03 04 BA");
    cout << graham_u.getUID() << endl;
    cout << db.removeUser(graham_u) << endl;

    // cout << new_user.getUsername() << endl;

    return 0;
}