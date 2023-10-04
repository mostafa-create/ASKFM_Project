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

