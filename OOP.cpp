#include "Database.h"
#include "UserAccount.h"
void start() {
	cout << "                                                       -> WELCOME TO ASKFM <-" << endl << endl;
	cout << "Menu:" << endl;
	cout << "\t1: Login" << endl;
	cout << "\t2: Sign Up" << endl << endl;
	int num;
	account per;
	do {
		cout << "Enter number in range 1 - 2: ";
		cin >> num;
		if (num > 2 || num < 1) {
			cout << "Invalid number...Try again." << endl;
			continue;
		}
		else {
			num == 1 ? per.Login() : per.Signup();
		}
	} while (num != 1 && num != 2);
	
}
int main()
{
	start();
	return 0;
}