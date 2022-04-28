#pragma once
#include<iostream>
#include <string>
#include <deque>
#include <unordered_set>
#include <map>
#include <fstream>
class TuringMachine
{
	std::deque<char> tape;

	std::unordered_set<std::string> Q; //set of states
	std::string* tempQ; // temp string arr for keeping input order so the transition table can be made

	std::unordered_set<char> T; //T is the tape alphabet (symbols which can be written on Tape)
	char* tempT;

	std::unordered_set<char> Sigma;//Sigma is the input alphabet (symbols which are part of input alphabet)
	std::unordered_set<std::string> F;//F is the set of final states. If any state of F is reached, input string is accepted.

	std::map<std::pair<std::string, char>,
		std::pair<std::pair<std::string, char>, char>> transitionsTable;

	// writes into Q, T, Sigma or F according to dest value 
	bool writeInto(std::string, int k);
	
	bool isIn(const std::unordered_set<std::string>,
		const std::unordered_set<std::string>)const;
	bool isIn(const std::unordered_set<char>,
		const std::unordered_set<char>)const;
	
	//returns true if string is valid cell of TT and writes values in q t and dir
	bool cellIsValid(std::string, std::string& q, char& t, char& dir);
	
	//checks if input string is valid, if so writes it into tape
	bool inputIsValid(std::string);
	
	void printTape();

public:
	TuringMachine(std::string filePath);
	void run(std::string);
	void debug(std::string);
};

