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
	std::string* tempQ;

	std::unordered_set<char> T; //T is the tape alphabet 
								//(symbols which can be written on Tape)
	char* tempT;


	char b = 'B'; //B is blank symbol (every cell is filled with B except input alphabet initially)
	std::unordered_set<char> Sigma;//Sigma is the input alphabet 
											//(symbols which are part of input alphabet)
	std::unordered_set<std::string> F;//F is the set of final states. 
										//If any state of F is reached, input string is accepted.

	std::map<std::pair<std::string, char>,
		std::pair<std::pair<std::string, char>, char>> transitionsTable;


	bool writeInto(std::string, int k);
	
	bool isIn(const std::unordered_set<std::string>,
		const std::unordered_set<std::string>)const;
	bool isIn(const std::unordered_set<char>,
		const std::unordered_set<char>)const;

	bool cellIsValid(std::string, std::string& q, char& t, char& dir);

	bool inputIsValid(std::string);

	void printTape();

public:
	TuringMachine(std::string filePath);
	void run(std::string);
	void debug(std::string);
};

