//#include "user.hpp"
//
//
//using namespace std;
//
//int main() {
//
//    User u = User("Graham", "0F 45 72 40");
//
//    char chrs[2];
//
//    if (u.intToChr(chrs, 115) == 0) {
//        if ((chrs[0] == '7') and (chrs[1] == '3')) {
//            cout << "intToChr working" << endl;
//        } else {
//            cout << "intToChr returning wronge" << endl;
//        }
//
//    } else {
//        cout << "intToChr not returning" << endl;
//    }
//
//    cout << endl;
//
//    if ((u.chrToInt('F') == 15) and u.chrToInt('7') == 7) {
//        cout << "chrToInt working" << endl;
//    } else {
//        cout << "chrToInt not working" << endl;
//    }
//    cout << endl;
//
//    if (u.getUID() == "0F 45 72 40") {
//        cout << "getUID working" << endl;
//    } else {
//        cout << "getUID not working" << endl;
//    }
//    cout << endl;
//
//    if (u.setUID("0F 45 72 41") == 0) {
//        if (u.getUID() == "0F 45 72 41") {
//
//            cout << "setUID working" << endl;
//
//        } else {
//
//            cout << "setUID not working" << endl;
//        }
//    } else {
//        cout << "setUID not returning" << endl;
//    }
//    cout << endl;
//
//    if (u.getPoints() == 0) {
//        cout << "getPoints working" << endl;
//    } else {
//        cout << "getPoints not working" << endl;
//    }
//    cout << endl;
//
//    if (u.setPoints(10) == 0) {
//        if (u.getPoints() == 10) {
//
//            cout << "setPoints working" << endl;
//
//        } else {
//
//            cout << "setPoints not working" << endl;
//        }
//    } else {
//        cout << "setPoints not returning" << endl;
//    }
//    cout << endl;
//
//    u.setPoints(0);
//    if (u.givePoints(3) == 0) {
//        if (u.getPoints() == 3) {
//
//            cout << "givePoints working" << endl;
//
//        } else {
//
//            cout << "givePoints not working" << endl;
//        }
//    } else {
//        cout << "givePoints not returning" << endl;
//    }
//    cout << endl;
//
//    u.setPoints(0);
//
//    if (u.givePoint() == 0) {
//        if (u.getPoints() == 1) {
//
//            cout << "givePoint working" << endl;
//
//        } else {
//
//            cout << "givePoint not working" << endl;
//        }
//    } else {
//        cout << "givePoint not returning" << endl;
//    }
//    cout << endl;
//
//    string line = "uid1,uid2,uid3,uid4,name,points,hello,hello1";
//    string components[8];
//    string test[8] = {"uid1", "uid2", "uid3", "uid4", "name", "points", "hello", "hello1"};
//
//    int numb_splits = u.split(line, components, 10);
//
//    if (numb_splits >= 0) {
//        for (int i = 0; i < numb_splits; i++) {
//            if (components[i] != test[i]) {
//                cout << "split not working" << endl;
//                break;
//            }
//        }
//        cout << "split working" << endl;
//    } else {
//        cout << "split returning with error" << endl;
//    }
//    cout << endl;
//
//    string test_line = "145,3,4,186,Graham,3";
//    string test_uid = "91 03 04 BA";
//    int test_points = 3;
//
//    User test_u = User();
//    if (test_u.load(test_line) == 0) {
//
//        if (test_u.getUsername() == "Graham") {
//            cout << "loadUser username working" << endl;
//        } else {
//
//            cout << "loadUser username not working" << endl;
//        }
//
//        if (test_u.getUID() == test_uid) {
//            cout << "loadUser uid working" << endl;
//        } else {
//
//            cout << "loadUser uid not working" << endl;
//        }
//
//        if (test_u.getPoints() == test_points) {
//            cout << "loadUser points working" << endl;
//        }
//
//        else {
//
//            cout << "loadUser points not working" << endl;
//        }
//    }
//
//    else {
//        cout << "loadUser not returning" << endl;
//    }
//    cout << endl;
//
//    if (test_u.save() == test_line) {
//        cout << "saveUser points working" << endl;
//    } else {
//        cout << "saveUser not working" << endl;
//        cout << test_u.save();
//    }
//    cout << endl;
//
//    return 0;
//}
