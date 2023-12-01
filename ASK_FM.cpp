#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#define ll long long
using namespace std;
struct user {
	string Username, Password, Email;
	ll Id;
};
struct Question {
	string Qs;
	ll Qid, fromUser, toUser, Anonymous;
};
struct Answer {
	string Ans;
	ll fromUser, toUser, Aid;
};
fstream Usersfile("Users.txt");
fstream Questionsfile("Questions.txt");
fstream Answersfile("Answers.txt");
class services {
protected:
	vector < user > Users;
	vector < Question > Questions;
	vector < Answer > Answers;
	map < string, ll > mp;
protected:
	void download_users() {
		Users.clear();
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
	}
	void download_questions() {
		Questions.clear();
		ll cnt = 0;
		string line;
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
	}
	void download_Answers() {
		Answers.clear();
		ll cnt = 0;
		string line;
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
	void uploadusers() {
		fstream uploadUsers;
		uploadUsers.open("Users.txt", ios::out | ios::trunc);
		for (auto it : Users) {
			uploadUsers << it.Username << endl << it.Password << endl << it.Email << endl << it.Id << endl;
		}
		uploadUsers.close();
	}
	void uploadAnswers() {
		fstream uploadans;
		uploadans.open("Answers.txt", ios::out | ios::trunc);
		for (auto it : Answers) {
			uploadans << it.Ans << endl << it.fromUser << endl << it.toUser << endl << it.Aid << endl;
		}
		uploadans.close();
	}
	void uploadQuestions() {
		fstream uploadque;
		uploadque.open("Questions.txt", ios::out | ios::trunc);
		for (auto it : Questions) {
			uploadque << it.Qs << endl << it.Qid << endl << it.Anonymous << endl << it.fromUser << endl << it.toUser << endl;
		}
		uploadque.close();
	}
	void print_questions_to_me(ll id) {
		download_questions();
		download_Answers();
		cout << endl;
		bool isfound = false;
		for (auto it : Questions) {
			if (it.toUser == id) {
				isfound = true;
				cout << "Question Id (" << it.Qid << ") ";
				if (it.Anonymous == -1) {
					cout << "from Anonymous user: " << it.Qs << endl;
				}
				else {
					cout << "from user id (" << it.fromUser << ") : " << it.Qs << endl;
				}
				bool answered = false;
				for (auto it2 : Answers) {
					if (it2.Aid == it.Qid) {
						answered = true;
						cout << "\tAnswer: " << it2.Ans << endl;
						break;
					}
				}
				if (!answered) {
					cout << "\tNot answered yet." << endl;
				}
			}
		}
		if (!isfound) {
			cout << "There isn't any Questions sent to you." << endl;
		}
	}
	void print_questions_from_me(ll id) {
		download_questions();
		download_Answers();
		cout << endl;
		bool ok = false;
		for (auto it : Questions) {
			if (it.fromUser == id) {
				ok = 1;
				if (it.Anonymous == -1) {
					cout << "Question id (" << it.Qid << ") !AQ to user id (" << it.toUser << ") ";
				}
				else {
					cout << "Question id (" << it.Qid << ") to user id (" << it.toUser << ") ";
				}
				cout << "       Question: " << it.Qs;
				bool isfound = false;
				for (auto it2 : Answers) {
					if (it2.Aid == it.Qid) {
						isfound = true;
						cout << "\n      Answer: " << it2.Ans << endl;
						break;
					}
				}
				if (!isfound) {
					cout << "\n      Not answered yet." << endl;
				}
			}
		}
		if (!ok) {
			cout << "you didn't ask any questions." << endl;
		}
	}
	void answer_question(ll id) {
		download_questions();
		download_Answers();
		cout << endl;
		cout << "Enter Question id or -1 to cancel: ";
		ll i, x; cin >> i;
		if (i != -1) {
			bool isfound = false;
			Question q;
			Answer a;
			for (auto it : Questions) {
				if (it.Qid == i && it.toUser == id) {
					q = it;
					isfound = true;
					break;
				}
			}
			if (isfound == true) {
				cout << "Question Id (" << q.Qid << ") ";
				if (q.Anonymous == -1) {
					cout << "from Anonymous user: " << q.Qs << endl;
				}
				else {
					cout << "from user id (" << q.fromUser << ") : " << q.Qs << endl;
				}
				bool isfound2 = false;
				for (int i = 0; i < Answers.size(); i++) {
					if (Answers[i].Aid == q.Qid) {
						isfound2 = true;
						cout << "      Answer: " << Answers[i].Ans << endl;
						cout << "Warning: already answered. answer will be updated press 1 to confirme or 0 to cancel: ";
						cin >> x;
						if (x == 1) {
							string s;
							cout << "Enter answer: ";
							cin.ignore();
							getline(cin, s);
							Answers[i].Ans = s;
						}
						else return;
						break;
					}
				}
				if (isfound2 == false) {
					string ans;
					cout << "Enter answer: ";
					cin.ignore();
					getline(cin, ans);
					a.Ans = ans;
					a.fromUser = id;
					a.toUser = q.fromUser;
					a.Aid = q.Qid;
					Answers.push_back(a);
				}
				uploadAnswers();
			}
			else if (isfound == false) cout << "\nThis question doesn't exist in the system." << endl;
		}
	}
	void delete_question(ll id) {
		download_questions();
		download_Answers();
		cout << endl;
		cout << "Enter Question id that you want to delete: ";
		ll qid; cin >> qid;
		ll i = 0;
		bool isfound = false;
		for (auto it : Questions) {
			if (it.fromUser == id && it.Qid == qid) {
				isfound = true;
				break;
			}
			i++;
		}
		if (isfound == true) {
			Questions.erase(Questions.begin() + i);
			uploadQuestions();
			ll j = 0;
			bool ok = 0;
			for (auto it2 : Answers) {
				if (it2.Aid == qid) {
					ok = 1;
					break;
				}
				j++;
			}
			if (ok) {
				Answers.erase(Answers.begin() + j);
				uploadAnswers();
			}

		}
		else {
			cout << "You don't have a question with that id." << endl;
		}
	}
	void delete_Answer(ll id) {
		download_Answers();
		cout << endl;
		cout << "Enter Question id that you want to delete it's answer: ";
		ll qid; cin >> qid;
		ll i = 0;
		bool isfound = false;
		for (auto it : Answers) {
			if (it.fromUser == id && it.Aid == qid) {
				isfound = true;
				break;
			}
			i++;
		}
		if (isfound == true) {
			Answers.erase(Answers.begin() + i);
			uploadAnswers();
		}
		else {
			cout << "You don't have an answer to that question." << endl;
		}
	}
	void ask_question(ll id) {
		download_users();
		download_questions();
		cout << endl;
		cout << "Enter the user id or -1 to cancel: ";
		ll userid; cin >> userid;
		if (userid != -1) {
			if (userid == id) {
				cout << "You can't ask your self." << endl;
				return;
			}
			bool isfound = false;
			for (auto it : Users) {
				if (it.Id == userid) {
					isfound = true;
					break;
				}
			}
			if (isfound == true) {
				cout << "Do you want to send Anonymous question (y/n)? ";
				char c; cin >> c;
				string s;
				cout << "Enter your Question: ";
				cin.ignore();
				getline(cin, s);
				ll qid;
				if (c == 'n') {
					if (Questions.size() == 0) {
						qid = 1;
					}
					else {
						qid = Questions.size() + 1;
					}
					Question l;
					l.Qid = qid;
					l.Qs = s;
					l.Anonymous = 0;
					l.fromUser = id;
					l.toUser = userid;
					Questions.push_back(l);
					ofstream infile;
					infile.open("Questions.txt", ios::app);
					if (infile.is_open())
					{
						infile << s << endl;
						infile << qid << endl;
						infile << 0 << endl;
						infile << id << endl;
						infile << userid << endl;
						infile.close();
					}
				}
				else { // y
					if (Questions.size() == 0) {
						qid = 1;
					}
					else {
						qid = Questions.size() + 1;
					}
					Question r;
					r.Qid = qid;
					r.Qs = s;
					r.fromUser = id;
					r.Anonymous = -1;
					r.toUser = userid;
					Questions.push_back(r);
					ofstream infile;
					infile.open("Questions.txt", ios::app);
					if (infile.is_open())
					{
						infile << s << endl;
						infile << qid << endl;
						infile << -1 << endl;
						infile << id << endl;
						infile << userid << endl;
						infile.close();
					}
				}

			}
			else {
				cout << "This id doesn't exist in the system." << endl;
				return;
			}
		}
	}
	void users_list() {
		download_users();
		cout << endl;
		ll c = 1;
		for (auto it : Users) {
			cout << "     Person: " << c << "#" << endl;
			cout << "Username: " << it.Username;
			cout << "     Id: " << it.Id << endl;
			c++;
		}
	}
	void feed(ll id) {
		download_questions();
		download_Answers();
		cout << endl;
		for (auto it : Questions) {
			bool isfound = false;
			for (auto it2 : Answers) {
				if (it.Qid == it2.Aid) {
					isfound = true;
					if (it.Anonymous == -1) {
						cout << "Question id (" << it.Qid << ") from Anonymous user to user id (" << it.toUser << ") ";
						cout << "        Question: " << it.Qs << endl;
					}
					else {
						cout << "Question id (" << it.Qid << ") form user id (" << it.fromUser << ") to user id (" << it.toUser << ") ";
						cout << "        Question: " << it.Qs << endl;
					}
					cout << "\tAnswer: " << it2.Ans << endl;
					break;
				}
			}
		}
	}
	void logout() {
		return;
	}
	bool delete_account(ll id) {
		download_users();
		cout << "Are you sure you want to delete your account (y/n) ? ";
		char c; cin >> c;
		ll i = 0;
		if (c == 'y') {
			for (auto it : Users) {
				if (it.Id == id) {
					break;
				}
				i++;
			}
			Users.erase(Users.begin() + i);
			uploadusers();
			cout << "Your account has been deleted." << endl;
			return 0;
		}
		else {
			return 1;
		}
	}
};

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
	void menulist(string username, string pass, string email, ll id) {
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
