#include <iostream>
#include <user_db.h>

using namespace std;
//Prototype
char menu_selection();
//Function
char menu_selection(){
    char selected_option{}; 
    cout << "Menu points: " << endl;
    cout << "P: print the sum balances " << endl;
    cout << "H: show the history" << endl;
    cout << "A: add new payment " << endl;
    cout << "Q: to quit from the menu" << endl;
    cin >> selected_option;
    selected_option = toupper(selected_option);
    return selected_option;
};

int main() {
 /************************************************************************************************************************************/ 
 /************************************************************ Sign in ***************************************************************/  
    bool sign_in_status{false};
    user test;
        
    do{
    sign_in_status =test.login();     
    }while (sign_in_status != true);
 /********************************************************************************************************************************/
 /************************************************************ Menu system *******************************************************/   
    char selected_option{};
 
    do {
        selected_option = menu_selection();

        if ( selected_option == 'P'){
            test.print_sums();
        }
        else if(selected_option == 'H'){
            test.show_history();
        }
        else if(selected_option == 'A'){
            test.add_new_item();
        }
        else if(selected_option == 'Q'){
            cout<<"Good bye!"<< endl;
            
        }else{
            cout<<"Enter a valid option!"<< endl;
        }
        cout << endl;
    } while ( selected_option != 'Q' );
	return 0;
}