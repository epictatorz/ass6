#include "main.h"

//loops through 1.txt to 20.txt to index everything
void createIndex() {
	int i = 1;
	string fileName;
	while (i < 21) {
		fileName = getFileName(i);
		readFile(fileName, i);
		i++;
	}
}

//function adds '.txt' to number for filename
string getFileName(int x) {
	string temp = to_string(x) + ".txt";
	return temp;
}

//overloads the operator to be able to output oType variables
ostream& operator << (ostream& os, oType a) {
	os << a.page << ", " << a.position << ')';
	return os;
}

//overloads the operator to be able to output iType variables
ostream& operator << (ostream& os, iType a) {
	a.occurences.ResetP();
	os << a.word;
	for (int i = 0; i < a.occurences.Length(); i++) {
		a.occurences.Iterate();
		os << " (" << a.occurences.Read();
	}
	return os;
}

//opens file and reads word for word while indexing
void readFile(string fileName, int pageNum) {
	ifstream in;
	in.open(fileName);
	//checks if file can be opened
	if (!in.is_open()){
		cout << "Error with files." << endl;
		return;
	}

	string word;
	int position = 0;					//counter for position of word
	while (in >> word) {
		position++;

		//removes last character if it is punctuation
		if (word.back() == '.' || word.back() == ',' || word.back() == ';' || word.back() == ':') {	word.pop_back();}

		//changes each character to lower case
		for_each(word.begin(), word.end(), [](char &c) { c = tolower(c);});


	
		//creates new iType
		iType itemp;
		oType otemp;
		itemp.word = word;
		otemp.page = pageNum;
		otemp.position = position;
		itemp.occurences.Insert(otemp);
		//sends iType to list
		index.InsertHelper(itemp);
	}
}

void menu() {
	char choice;
	while (1) {
		cout << "1: Print without occurences." << endl;
		cout << "2: Print with occurences." << endl;
		cout << "3: Search." << endl;
		cout << "q: Quit." << endl;
		cout << "Enter what you would like to do: ";
		cin >> choice;
		switch (choice) {
		case '1':
			index.printWithoutOccurences();
			break;
		case '2':
			index.printOccurences();
			break;
		case '3':
			searchMenu();
			break;
		case 'q':
			return;
			break;
		default:
			system("cls");
			cout << "Invalid entry." << endl;
		}
	}

}

void searchMenu() {
	system("cls");
	bool phrase;
	string tempString;
	getline(cin, tempString);
	while (1) {
		phrase = false;
		//getline(cin, tempString);
		cout << "Enter -1 to exit search." << endl;
		cout << "Enter word/phrase to search:";
		getline(cin,tempString);
		cout << endl;
		if (tempString == "-1") {
			break;
		}
		for (int i = 0; i < tempString.length(); i++) {
			if (tempString[i] == ' ') {
				phrase = true;
			}
		}
		if (phrase == true) {
			searchPhrase(tempString);
		}
		else if (phrase == false) {
			searchWord(tempString);
		}
	}
}

void searchWord(string word) {
	iType temp;
	temp.word = word;
	index.FindHelper(temp);
	if (index.IsPSet() == true) {
		cout << index.Read() << endl;
	}
	else {
		cout << word << " not found." << endl;
	}
}

void searchPhrase(string phrase) {
	string word[10];
	bool hmm = true;
	string tempWord = "";
	int i = 0;
	for (auto x : phrase){
		if (x == ' ' || x == '/n'){
			word[i] = tempWord;
			tempWord = "";
			i++;
		}
		else{
			tempWord = tempWord + x;
		}
	}
	word[i] = tempWord;
	
	int j = 0;
	int x = 0;
	int a = 0;
	iType iTypeTemp[10];

	//grabs all the words in the phrase
	while (j <= i) {
		iTypeTemp[j].word = word[j];
		index.FindHelper(iTypeTemp[j]);
		if (index.IsPSet() == true) {
			iTypeTemp[j] = index.Read();
			iTypeTemp[j].occurences.ResetP();
		}
		j++;
	}
	int page, position;
	while (iTypeTemp[0].occurences.Read().page != iTypeTemp[1].occurences.Read().page) {
		if (iTypeTemp[0].occurences.Read().page != iTypeTemp[1].occurences.Read().page) {
			iTypeTemp[0].occurences.Iterate();
		}
	}
	page = iTypeTemp[0].occurences.Read().page;
	int count = 0;
	while (1) {
		if (count > 200) {
			hmm = false;
			break;
		}
		if (iTypeTemp[0].occurences.Read().position == iTypeTemp[1].occurences.Read().position - 1) {
			position = iTypeTemp[0].occurences.Read().position;
			break;
		}
		else if (iTypeTemp[0].occurences.Read().position > iTypeTemp[1].occurences.Read().position - 1) {
			iTypeTemp[1].occurences.Iterate();
		}
		else if (iTypeTemp[0].occurences.Read().position < iTypeTemp[1].occurences.Read().position - 1) {
			iTypeTemp[0].occurences.Iterate();
		}
		count++;
	}
	for (int a = 2; a <= i; a++) {
		count = 0;
		while (1) {
			if (count > 30) {
				hmm = false;
				break;
			}
			if (position == iTypeTemp[a].occurences.Read().position - a) {
				break;
			}
			if (count > 1 && position != iTypeTemp[a].occurences.Read().position - a) {
				iTypeTemp[a].occurences.Iterate();
			}
			count++;
		}
	}
	

	if (hmm == true) {
		a = 0;
		while (a < i) {
			cout << word[a] << ' ';
			a++;
		}
		cout << word[i] << " exists at " << endl;
		a = 0;
		while (a <= i) {
			cout << "<" << page << ", " << (position + a) << "> ";
			a++;
		}
		cout << endl << endl;
	}
	else {
		a = 0;
		while (a < i) {
			cout << word[a] << ' ';
			a++;
		}
		cout << word[i] << " does not exist in the index." << endl << endl;
	}
}