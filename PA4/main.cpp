// David dahlberg
// CS 211 - PA4
// HSU stu id: 013669107
// Completion time: 5 hours
// Collaborators: none

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "Word.h"
#include <unordered_map>
#include <sstream>

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
string binaryStringer(int n);
string insertCompressedInString(string s);
string insertCodesInString(string s);

int main()
{
	int user_input;
	string file_name;
	string compressed_file_name;
	string codes_file_name;
	priority_queue<Word, vector<Word>, myComparator> max_heap;
	unordered_map<string, int> um;
	unordered_map<string, string> um_codes;

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
		file_name = getFileName();

		//grab strings from file
		ifstream is;
		is.open(file_name);

		//grabs entire file as a string and puts it into file_string
		stringstream ss;
		ss << is.rdbuf();
		string file_string = ss.str();
		cout << file_string;
		
		is.close();
		is.open(file_name);

		while (is)
		{
			string string_from_file;
			//grabs a word from file stream, space delimited
			is >> string_from_file;

			//ignore empty string
			if (string_from_file != "")
			{
				//get frequencies by putting each word into unordered_map and incrementing the value
				um[string_from_file]++;
			}
		}
		is.close();

		//iterate map and put data into max heap
		for (auto i : um)
		{
			//create Word with data from unordered_map
			if (true)
			{
				Word w = Word(i.first, i.second);
				max_heap.push(w);
			}

		}

		//insert .codes and .compressed into file_name strings for output
		codes_file_name = insertCodesInString(file_name);
		compressed_file_name = insertCompressedInString(file_name);

		//set up the two files outputs
		ofstream codes_file_output(codes_file_name);
		ofstream compressed_file_output(compressed_file_name);

		int binary_num = 0;  //counter for "binary strings"

		//top(), assign binary, output file_name.codes.txt, and pop() max_heap until empty, increment counter
		while (!max_heap.empty())
		{
			//assigning binary strings to each word according to importance (most important is most frequent)
			//1st = 1 = "0", 2nd = 2 = "1", 3rd = 3 = "10"
			Word w = max_heap.top();
			w.setFreq(binary_num++); //put the counter into the value of the word
			string binary_string = binaryStringer(w.getFreq()); //change int binary_num to string binary_string

			//insert word and its binary string into um_codes
			um_codes[w.getKey()] = binary_string;

			//output into codes file
			codes_file_output << w.getKey() << ":" << binary_string << '\n';

			max_heap.pop();
		}

		//output file_name.compressed.txt
		//iterate file_string, for each word, gets data from unordered_map and outputs "binary string"
		stringstream fs(file_string);
		while (fs)
		{	
			string sub_file_string;
			//grabs substring from file_string '\n' delimited
			getline(fs, sub_file_string);

			//parse the substring with spaces
			stringstream subs(sub_file_string);
			while (subs)
			{
				string sub_sub_file_string;
				getline(subs, sub_sub_file_string, ' ');

				if (sub_sub_file_string != "")
				{
					cout << "sub_sub_file_string: " << sub_sub_file_string << endl;

					//output the string_from_file with it's "binary string" from um_codes
					compressed_file_output << um_codes[sub_sub_file_string] << " ";
				}
			}

			compressed_file_output << '\n';
		}
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

		//Load codes file file_name.code.txt, load each item into a hash table
		string str;
		ifstream is_compressed(compressed_file_name);
		ifstream is_codes(codes_file_name);
		while (is_codes)
		{
			string word;
			string code;
			//gets string up to new line
			getline(is_codes, str);
			if (str != "")
			{
				//parse line for word and code
				stringstream sub_s(str);
				getline(sub_s, word, ':');
				getline(sub_s, code, '\n');
				
				//insert word/code combo into um_codes
				um_codes[code] = word;
			}
		}
		//grabs entire file as a string and puts it into file_string
		ifstream is(compressed_file_name);
		stringstream ss;
		ss << is.rdbuf();
		string compressed_file_string = ss.str();
		
		//fix file_name to have file_name.txt instead of file_name.codes.txt
		stringstream name_fixer(codes_file_name);
		getline(name_fixer, file_name, '.');
		file_name.append(".txt");
		cout << "file_name appended: " << file_name << endl;

		ofstream file_output(file_name);

		//iterate the compressed_file_string, outputting to file_name.txt the equivalent string

		stringstream fs(compressed_file_string);
		while (fs)
		{
			string sub_file_string;
			//grabs substring from file_string '\n' delimited
			getline(fs, sub_file_string);

			//parse the substring with spaces
			stringstream subs(sub_file_string);
			while (subs)
			{
				string sub_sub_file_string;
				//parse sub_string space delimited
				getline(subs, sub_sub_file_string, ' ');

				if (sub_sub_file_string != "")
				{
					//output the string_from_file with it's "binary string" from um_codes
					file_output << um_codes[sub_sub_file_string] << " ";
				}
			}

			file_output << '\n';
		}
		file_output.close();
	}

	else
	{
		//error catch
		cout << "error - user input not 1 or 2 somehow...program should nver be here!";
	}

}//END MAIN


//takes in a string and inserts ".codes" when it finds ".txt"
string insertCodesInString(string file_name)
{
	string s = file_name;
	s.insert(s.find(".txt"), ".codes");
	return s;
}

//takes in a string and inserts ".compressed" when it finds ".txt"
string insertCompressedInString(string file_name)
{
	string s = file_name;
	s.insert(s.find(".txt"), ".compressed");
	return s;
}

string binaryStringer(int n)
{
	int power = 1;
	string output;
	int mask = 1;
	if (n == 0)
	{
		return "0";
	}
	while (mask <= n)
	{
		int digit = (n / mask) % 2;
		if (digit == 1)
		{
			output = "1" + output;
		}
		else
		{
			output = "0" + output;
		}
		mask = pow(2, power);
		power++;
	}

	return output;
}

string getFileName()
{
	string return_string;
	getline(cin, return_string);
	return return_string;
}

int getUserInput()
{
	string e_or_d_input;
	getline(cin, e_or_d_input);
	// get (E)ncode or (D)ecode, return 1 for Encode, 2 for Decode
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