#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#define ll long long
using namespace std;
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
