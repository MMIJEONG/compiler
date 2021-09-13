#include<iostream>
#include<stack>
#include<string>
#include<iomanip>
using namespace std;

#define LETTER 21
#define DIGIT 22
#define UNKNOWN 23


#define ID 0//id
#define NUM 1//num
#define ADD 2//+
#define MUL 3//*
#define LB 4//(
#define RB 5//)
#define END 6//$
#define E 30
#define T 31
#define F 32

int state;
string token = "";
int i = 0;
stack<string> s;
int line_count;

string action[13][7] = {//action table
	{"shift 5","shift 6","","","shift 4","",""},
	{"","","shift 7","","","","accept"},
	{"","","reduce 2","shift 8","","reduce 2","reduce 2"},
	{"","","reduce 4","reduce 4","","reduce 4","reduce 4"},
	{"shift 5","shift 6","","","","",""},
	{"","","reduce 6","reduce 6","","reduce 6","reduce 6"},
	{"","","reduce 7","reduce 7","","reduce 7","reduce 7"},
	{"shift 5","shift 6","","","shift 4","",""},
	{"shift 5","shift 6","","","shift 4","",""},
	{"","","shift 7","","","shift 12",""},
	{"","","reduce 1","shift 8","","reduce 1","reduce 1"},
	{"","","reduce 3","reduce 3","","reduce 3","reduce 3"},
	{"","","reduce 5","reduce 5","","reduce 5","reduce 5"}
};
string goto_table[13][3] = {//goto table
	{"1","2","3"},
	{"","",""},
	{"","",""},
	{"","",""},
	{"9","2","3"},
	{"","",""},
	{"","",""},
	{"","10","3"},
	{"","","11"},
	{"","",""},
	{"","",""},
	{"","",""},
	{"","",""}
};

char nextChar;
string str;
int index;
int charType;
string token_str = "";
string copy_str = "";
string op_str = "";

void getChar() {
	if ((nextChar = str[index]) != '\0')
	{
		if (isalpha(nextChar))
			charType = LETTER;
		else if (isdigit(nextChar))
			charType = DIGIT;
		else charType = UNKNOWN;
	}
	else
		charType = EOF;
	index++;

}

void op_check(char ch) {
	switch (ch) {
	case'(':
		token_str += " (";
		break;
	case')':
		token_str += " )";
		break;
	case'+':
		token_str += " +";
		break;
	case'*':
		token_str += " *";
		break;

	default:
		cout << "식별할수 없는 토큰입니다.";
		exit(0);

	}
}
void lex() {
	while (isspace(nextChar))
		getChar();
	switch (charType)
	{
	case LETTER:
		getChar();
		while (charType == LETTER || charType == DIGIT) {
			getChar();
		}
		token_str += " id";
		break;
	case DIGIT:
		getChar();
		while (charType == DIGIT) {
			getChar();
		}
		token_str += " num";
		break;
	case UNKNOWN:
		op_check(nextChar);
		getChar();
		break;
	}
}
void shift(int new_state) {
	s.push(token);
	s.push(to_string(new_state));
	state = atoi(s.top().c_str());
	copy_str.erase(0, token.length()+1);
}
void reduce(int syn_num) {
	string sta;
	switch (syn_num)
	{
	case 1:
		for (int k = 0;k < 6;k++)
			s.pop();
		state = atoi(s.top().c_str());
		sta = goto_table[state][E % 30];
		s.push("E");
		s.push(sta);
		state = atoi(s.top().c_str());
		break;
	case 2:
		for (int k = 0;k < 2;k++)
			s.pop();
		state = atoi(s.top().c_str());
		sta = goto_table[state][E % 30];
		s.push("E");
		s.push(sta);
		state = atoi(s.top().c_str());
		break;
	case 3:
		for (int k = 0;k < 6;k++)
			s.pop();
		state = atoi(s.top().c_str());
		sta = goto_table[state][T % 30];
		s.push("T");
		s.push(sta);
		state = atoi(s.top().c_str());
		break;
	case 4:
		for (int k = 0;k < 2;k++)
			s.pop();
		state = atoi(s.top().c_str());
		sta = goto_table[state][T % 30];
		s.push("T");
		s.push(sta);
		state = atoi(s.top().c_str());
		break;
	case 5:
		for (int k = 0;k < 6;k++)
			s.pop();
		state = atoi(s.top().c_str());
		sta = goto_table[state][F % 30];
		s.push("F");
		s.push(sta);
		state = atoi(s.top().c_str());
		break;
	case 6:
		for (int k = 0;k < 2;k++)
			s.pop();
		state = atoi(s.top().c_str());
		sta = goto_table[state][F % 30];
		s.push("F");
		s.push(sta);
		state = atoi(s.top().c_str());
		break;
	case 7:
		for (int k = 0;k < 2;k++)
			s.pop();
		state = atoi(s.top().c_str());
		sta = goto_table[state][F % 30];
		s.push("F");
		s.push(sta);
		state = atoi(s.top().c_str());
		break;

	}
}
string print_gram(int state)
{
	switch (state)
	{
	case 1:
		return "(E->E+T)";
		break;
	case 2:
		return "(E->T)";
		break;
	case 3:
		return "(T->T*F)";
		break;
	case 4:
		return "(T->F)";
		break;
	case 5:
		return "(F->(E))";
		break;
	case 6:
		return "(F->id)";
		break;
	case 7:
		return "(F->num)";
		break;
	}
}
int main() {
	
	cout << "입력:";
	getline(cin, str);
	getChar();
	while (index < str.length()) {
		lex();
	}
	if (charType == EOF) {
		token_str += " $";
	}
	token_str.erase(0, 1);

	cout << "출력:" << endl;
	cout << "스택\t\t\t\t입력\t\t\t\t\t동작" << endl;

	copy_str = token_str;

	
	s.push("0");
	state = atoi(s.top().c_str());


	while (i < token_str.length()) {
		
		cout << "(" << line_count + 1 << ")";
		stack<string> copy_s;
		int size = s.size();
		for (int t = 0;t < size;t++) {
			copy_s.push(s.top());
			s.pop();
		}
		int c_size = copy_s.size();
		for (int t = 0;t < c_size;t++) {
			s.push(copy_s.top());
			cout << copy_s.top() << " ";
			copy_s.pop();
		}
		cout << setw(35) << copy_str << setw(40);

		token = "";
		while (1)
		{
			if (token_str[i] != ' '){
				if (token_str[i] == '$') {
					token = '$';
					break;
				}
				token += token_str[i];
				
			}
			else {
				i++;
				break;
			}
			i++;
		}


		if (token == "id")
		{
			if (action[state][ID] == "")
			{
				cout << "파싱할수 없습니다";
				exit(0);
			}
			if (action[state][ID][0] == 's') {
				string term = action[state][ID];
				op_str = action[state][ID];
				shift(atoi(term.erase(0, 6).c_str()));
				
			}
			else {
				string term = action[state][ID];
				op_str = action[state][ID] + print_gram(atoi(term.erase(0, 7).c_str()));
				reduce(atoi(term.c_str()));
				i -= 2;
				
			}

		}
		else if (token == "num")
		{
			if (action[state][NUM] == "")
			{
				cout << "파싱할수 없습니다";
				exit(0);
			}
			if (action[state][NUM][0] == 's') {
				string term = action[state][NUM];
				op_str = action[state][NUM];
				shift(atoi(term.erase(0, 6).c_str()));
				
			}
			else {
				string term = action[state][NUM];
				op_str = action[state][NUM] + print_gram(atoi(term.erase(0, 7).c_str()));
				reduce(atoi(term.c_str()));
				i -= 2;
				
			}

		}
		else if (token == "+")
		{
			if (action[state][ADD] == "")
			{
				cout << "파싱할수 없습니다";
				exit(0);
			}
			if (action[state][ADD][0] == 's') {
				string term = action[state][ADD];
				op_str = action[state][ADD];
				shift(atoi(term.erase(0, 6).c_str()));
				
			}
			else {
				string term = action[state][ADD];
				op_str = action[state][ADD] + print_gram(atoi(term.erase(0, 7).c_str()));
				reduce(atoi(term.c_str()));
				i -= 2;
				
			}

		}
		else if (token == "*")
		{
			if (action[state][MUL] == "")
			{
				cout << "파싱할수 없습니다";
				exit(0);
			}
			if (action[state][MUL][0] == 's') {
				string term = action[state][MUL];
				op_str = action[state][MUL];
				shift(atoi(term.erase(0, 6).c_str()));
				
			}
			else {
				string term = action[state][MUL];
				op_str = action[state][MUL] + print_gram(atoi(term.erase(0, 7).c_str()));
				reduce(atoi(term.c_str()));
				i -= 2;
				
			}

		}
		else if (token == "(")
		{
			if (action[state][LB] == "")
			{
				cout << "파싱할수 없습니다";
				exit(0);
			}
			if (action[state][LB][0] == 's') {
				string term = action[state][LB];
				op_str = action[state][LB];
				shift(atoi(term.erase(0, 6).c_str()));
				
			}
			else {
				string term = action[state][LB];
				op_str = action[state][LB] + print_gram(atoi(term.erase(0, 7).c_str()));
				reduce(atoi(term.c_str()));
				i -= 2;
				
			}

		}
		else if (token == ")")
		{

			if (action[state][RB] == "")
			{
				cout << "파싱할수 없습니다";
				exit(0);
			}
			if (action[state][RB][0] == 's') {
				string term = action[state][RB];
				op_str = action[state][RB];
				shift(atoi(term.erase(0, 6).c_str()));
				
			}
			else {
				string term = action[state][RB];
				op_str = action[state][RB] + print_gram(atoi(term.erase(0, 7).c_str()));
				reduce(atoi(term.c_str()));
				i -= 2;
				
			}

		}
		else if (token == "$")
		{
			if (action[state][END] == "")
			{
				cout << "파싱할수 없습니다";
				exit(0);
			}
			if (action[state][END][0] == 's') {
				string term = action[state][END];
				op_str = action[state][END];
				shift(atoi(term.erase(0, 6).c_str()));
				
			}
			else if (action[state][END][0] == 'r') {
				string term = action[state][END];
				op_str = action[state][END] + print_gram(atoi(term.erase(0, 7).c_str()));
				reduce(atoi(term.c_str()));
				
			}
			else {
				cout << "accept" << endl;
				break;
			}
		}
		cout << op_str << endl;
		line_count++;
	}
}
