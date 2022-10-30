#include <iostream>
#include <string>
#include "user.hpp"

using namespace std;

int main(){
    
    
    
    User u = User("Graham", "0F 45 72 40");
    
    char chrs[2];
    
    if ( u.intToChr(chrs, 115) == 0){
        if ((chrs[0] == '7') and (chrs[1] == '3')){
            cout << "intToChr working" << endl;
        } else{
            cout << "intToChr returning wronge" << endl;
        }
        
    }
    else{
        cout << "intToChr not returning" << endl;
    }
    
    cout << endl;
    
    if((u.chrToInt('F') == 15) and u.chrToInt('7') == 7){
        cout << "chrToInt working" << endl;
    }
    else{
        cout << "chrToInt not working" << endl;
    }
    cout << endl;
    
    
    cout << u.getUID() << endl;
    
    
    return 0;
}