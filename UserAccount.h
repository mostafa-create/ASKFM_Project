#include "Menulist.h"
class account : public services {
public:
	account() {
		// download Users from the file
		string line;
		ll cnt = 0;
		ifstream outFile;
		outFile.open("Users.txt");
		user test;
		while (getline(outFile, line))
		{
			if (cnt % 4 == 0) {
				test.Username = line;
				cnt++;
			}
			else if (cnt % 4 == 1) {
				test.Password = line;
				cnt++;
			}
			else if (cnt % 4 == 2) {
				test.Email = line;
				cnt++;
			}
			else if (cnt % 4 == 3) {
				test.Id = stoi(line);
				Users.push_back(test);
				cnt++;
			}
		}
		outFile.close();
		// download Questions from the file
		cnt = 0;
		ifstream Que_out;
		Que_out.open("Questions.txt");
		Question qu;
		while (getline(Que_out, line))
		{
			if (cnt % 5 == 0) {
				qu.Qs = line;
				cnt++;
			}
			else if (cnt % 5 == 1) {
				qu.Qid = stoi(line);
				cnt++;
			}
			else if (cnt % 5 == 2) {
				qu.Anonymous = stoi(line);
				cnt++;
			}
			else if (cnt % 5 == 3) {
				qu.fromUser = stoi(line);
				cnt++;
			}
			else if (cnt % 5 == 4) {
				qu.toUser = stoi(line);
				Questions.push_back(qu);
				cnt++;
			}
		}
		Que_out.close();
		// download Answers from the file
		cnt = 0;
		ifstream Ans_out;
		Ans_out.open("Answers.txt");
		Answer an;
		while (getline(Ans_out, line))
		{
			if (cnt % 4 == 0) {
				an.Ans = line;
				cnt++;
			}
			else if (cnt % 4 == 1) {
				an.fromUser = stoi(line);
				cnt++;
			}
			else if (cnt % 4 == 2) {
				an.toUser = stoi(line);
				cnt++;
			}
			else if (cnt % 4 == 3) {
				an.Aid = stoi(line);
				Answers.push_back(an);
				cnt++;
			}
		}
		Ans_out.close();
	}
	void Login() {
		string man;
		user per;
		bool usernameisfound = false;
		while (usernameisfound == false) {
			cout << "Enter your username: "; cin >> man;
			for (auto it : Users) {
				if (it.Username == man) {
					per.Username = it.Username;
					per.Password = it.Password;
					per.Email = it.Email;
					per.Id = it.Id;
					usernameisfound = true;
				}
			}
			if (usernameisfound == false) {
				cout << "Username that you entered doesn't exsit...try again." << endl;
			}
		}
		string pass;
		do {
			cout << "Enter the password: ";
			cin >> pass;
			if (per.Password == pass) {
				cout << "\n\tWelcome, " << man << endl;
				menulist(per.Username, per.Password, per.Email, per.Id);
				break;
			}
			else {
				cout << "Wrong password...Try again" << endl;
			}
		} while (true);
	}
	void Signup() {
		user person;
		string s;
		do {
			cout << "Enter a username doesn't exist in the system: ";
			cin >> s;
			if (username_validation(s) == 1) {
				person.Username = s;
				break;
			}
			else {
				cout << "The username that you entered is already used...Try again" << endl;
			}
		} while (true);
		string email;
		do {
			cout << "Enter an email: ";
			cin >> email;
			if (email_validation(email) == 1) {
				person.Email = email;
				break;
			}
			else {
				cout << "The email is not valid...Try again" << endl;
			}
		} while (true);
		string pass;
		cout << "Enter password: ";
		cin >> pass;
		person.Password = pass;
		if (Users.size() == 0) {
			person.Id = 1;
		}
		else person.Id = Users.size() + 1;
		Users.push_back(person);
		ofstream put;
		put.open("Users.txt", ios::app);
		if (put.is_open())
		{
			put << person.Username << endl;
			put << person.Password << endl;
			put << person.Email << endl;
			put << person.Id << endl;
			put.close();
		}
		cout << "\tWelcome, " << person.Username << endl;
		menulist(person.Username, person.Password, person.Email, person.Id);
	}
	bool username_validation(string s) {
		for (int i = 0; i < Users.size(); i++) {
			mp[Users[i].Username] = 1;
		}
		if (mp[s] == 0) {
			return true;
		}
		else return false;
	}
	bool email_validation(string s) {
		bool atisfound = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '@' && i < s.size() - 5) {
				atisfound = true;
				break;
			}
		}
		if (atisfound == true && s[s.size() - 1] == 'm' && s[s.size() - 2] == 'o'
			&& s[s.size() - 3] == 'c' && s[s.size() - 4] == '.') {
			return true;
		}
		else return false;
	}
	void menulist(string username,string pass,string email, ll id) {
		cout << endl;
		cout << " Menu: " << endl;
		cout << " \t1: Print Questions To Me" << endl;
		cout << " \t2: Print Questions From Me" << endl;
		cout << " \t3: Answer A Question" << endl;
		cout << " \t4: Delete A Questions" << endl;
		cout << " \t5: Delete An Answer" << endl;
		cout << " \t6: Ask A Question" << endl;
		cout << " \t7: List System Users" << endl;
		cout << " \t8: Feed" << endl;
		cout << " \t9: Logout" << endl;
		cout << "\t10: Delete My Account" << endl << endl;
		int num2;
		do {
			cout << "Enter number in range 1 - 10: ";
			cin >> num2;
			if (num2 > 10 || num2 < 1) {
				cout << "Invalid number...Try again." << endl;
			}
			else {
				     if (num2 == 1) print_questions_to_me(id);
				else if (num2 == 2) print_questions_from_me(id);
				else if (num2 == 3) answer_question(id);
				else if (num2 == 4) delete_question(id);
				else if (num2 == 5) delete_Answer(id);
				else if (num2 == 6) ask_question(id);
				else if (num2 == 7) users_list();
				else if (num2 == 8) feed(id);
				else if (num2 == 9) logout();
				else if (num2 == 10) {
					if (!delete_account(id)) {
						return;
					}
				}
			}
		} while (num2 != 9);
	}
	~account() {
		cout << "You logged out." << endl;
	}

};
