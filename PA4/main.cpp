// David dahlberg
// CS 211 - PA4
// HSU stu id: 013669107
// Completion time:
// Collaborators:

//#include <cstdlib>

#include <iostream>
#include <string>
#include <fstream>  //for file input/output
#include <queue>
#include "Word.h"
#include <unordered_map>

using namespace std;

class myComparator
{
public:
	int operator()(const Word& one, const Word& two)
	{
		return one.getFreq() < two.getFreq();
	}
};

int getUserInput();
string getFileName();
priority_queue<Word, vector<Word>, myComparator> frequencies(string s);
string readFile(iostream &is);



int main()
{
	int user_input;
	string file_name;
	string compressed_file_name;
	string codes_file_name;
	vector<Word> vector_Words;
	char* test[100];
	priority_queue<Word, vector<Word>, myComparator> max_heap;
	unordered_map<string, int> um;

	do {
		cout << "(E)ncode or (D)ecode file: ";
		user_input = getUserInput();
	} while (user_input == -1);

	// 1 = user chose Encode(1)
	if (user_input == 1)
	{
		// === ENCODE ===
		//get file_name from user
		cout << "Enter file to Compress: ";
		getline(cin, file_name);

		//grab all the strings from file
		//file contains a string of words e.g. "berries apples berries apples pears apples"

		ifstream is;
		is.open(file_name);
		while (is)
		{
			string string_from_file;
			//grabs a word from file stream space delimited
			is >> string_from_file;

			//get frequencies by putting each word into unordered_map
			um[string_from_file]++;
		}
		is.close();

		//iterate map and put data into max heap
		for (auto i : um)
		{
			//create Word with data from unordered_map
			Word w = Word(i.first, i.second);
			max_heap.push(w);
		}

		int counter = 0;
		//top, assign binary, and pop max_heap until empty
		while(!max_heap.empty())
		{
			//assigning binary strings to each word according to importance (most important is most frequent)
			//1st = 1 = "0", 2nd = 2 = "1", 3rd = 3 = "10"
			Word w = max_heap.top();
			
			max_heap.pop();
		}

		//these are used to build the final compressed string
			// e.g. "1 0 1 0 10 0"
		//generate file_name.codes.txt
			//the "binary" mapping
		//generate file_name.compressed.txt
			// "1 0 1 0 10 0"
			// the "binary" representation of the original file
		cout << "done!" << endl;
		system("pause");
	}

	// 2 = user chose Decode(2)
	else if (user_input == 2)
	{
		// === DECODE ===
		//get the file_name and codes_file_name
		cout << "Enter file to decompress: ";
		compressed_file_name = getFileName();

		cout << "Enter codes file: ";
		codes_file_name = getFileName();

		//Load mapping file file_name.code.txt
			//load each item into a hash table
		//Load compressed file file_name.compressed.txt
			//for each string in file, find correct mapping
			//replace compressed version with full version
		//generate file_name.txt
	}
	else
	{
		//error catch
		cout << "error - user input not 1 or 2 somehow...program should not be here! run!";
	}

	//////////////////DELETE THIS
	system("pause");  
	/////////////////////////////
}//END MAIN

string readFile(istream &is)
{
	string string_to_return = "";
	//parses each word creating one string of all words, with spaces in between
	
	//returns string
	return string_to_return;
}
priority_queue<Word, vector<Word>, myComparator> frequencies(string big_string)
{

	priority_queue<Word, vector<Word>, myComparator> pq_to_return;
	return pq_to_return;
}

string getFileName()
{
	string return_string;
	getline(cin, return_string);
	cout << "debug return_string: " << return_string;
	return return_string;
}

int getUserInput()
{
	string e_or_d_input;
	getline(cin, e_or_d_input);
	// get (E)ncode or (D)ecode
	// return 1 for Encode, 2 for Decode
	if (e_or_d_input == "e" || e_or_d_input == "E")
	{
		return 1;
	}
	else if (e_or_d_input == "d" || e_or_d_input == "D")
	{
		return 2;
	}
	else {
		cout << "Bad input received..." << endl;
		return -1; //else bad input
	}
}