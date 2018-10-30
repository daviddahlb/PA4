#pragma once
using namespace std;

class Word
{
	int freq;
	string key;

public:
	Word(string k, int f)
	{
		freq = f;
		key = k;
	}
	Word(string k)
	{
		key = k;
		freq = 1;
	}
	//getters
	int getFreq() const
	{
		return freq;
	} 
	string getKey() const
	{
		return key;
	}
	//setters
	void setFreq(int f)
	{
		freq = f;
	}

	void setKey(string s)
	{
		key = s;
	}

	void toString()
	{
		cout << "Key: " << key 
			<< " Freq: " << freq << endl;
	}
};
