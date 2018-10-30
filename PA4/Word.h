#pragma once
using namespace std;

class Word
{
	int freq;
	string key;

public:
	Word(int f, string k)
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
};
