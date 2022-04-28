#include "TuringMachine.h"
int count(std::string s, char c)
{
	int count = 0;
	int pos = s.find(c, 0);//find first occurrence
	while (pos != std::string::npos)
	{
		count++;
		pos = s.find(c, pos + 1);
	}
	return count;
}
// writes into Q, T, Sigma or F according to dest value 
bool TuringMachine::writeInto(std::string s, int dest)
{
	std::string elem = "";
	char e = ' ';
	int size, t;
	bool read = false;
	switch (dest)
	{
	case 0: // write states
		elem.clear();

		size = count(s, ',') + 1;
		tempQ = new std::string[size];
		t = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ',' && s[i] != ' ')//write into elem until seeing ','
			{
				elem += s[i];
			}
			else // push elem into the set
			{
				Q.insert(elem);
				tempQ[t++]= elem;
				elem.clear();
			}
		}
		if (elem != "")
		{
			Q.insert(elem);
			tempQ[t++] = elem;
		}
		if (Q.empty())
		{
			std::cerr << "The set of states should not be empty!" << std::endl;
			return false;
		}
		break;
	case 1: // get tape alphabet 
		size = count(s, ',') + 1;
		tempT = new char[size];
		t = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (!read && s[i] != ',' && s[i] != ' ')
			{
				e = s[i];
				read = true;
			}
			else // push e into the set
			{
				T.insert(e);
				tempT[t++] = e;
				e = ' ';
				read = false;
			}
		}
		if (e != ' ')
		{
			T.insert(e);
			tempT[t++] = e;
		}
		if (T.empty())
		{
			std::cerr << "The tape alphabet should not be empty!" << std::endl;
			return false;
		}
		break;
	case 2: // read input alphabet from the string
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ',' && s[i] != ' ')
			{
				e = s[i];
			}
			else // push elem into the set
			{
				Sigma.insert(e);
				elem.clear();
			}
		}
		if (e != ' ')
		{
			Sigma.insert(e);
		}
		if (!isIn(Sigma,T) || Sigma.empty())
		{
			std::cerr << "The input alphabet should not be empty and it must be a subset of the tape alphabet!" << std::endl;
			return false;
		}
		break;
	case 3:
		elem.clear();
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ',' && s[i] != ' ')//write into elem until seeing ','
			{
				elem += s[i];
			}
			else // push elem into the set
			{
				F.insert(elem);
			}
		}
		if (elem != "")
			F.insert(elem);
		if (!isIn(F, Q) || F.empty())//check if F is a subset of Q
		{
			std::cerr << "The set of final states should not be empty and it must be a subset of set of states!" << std::endl;
			return false;
		}
		break;
	default:
		std::cerr << "Wrong dest value" << std::endl;
		return false;
	}
	return true;
}

bool TuringMachine::isIn(const std::unordered_set<std::string> subset,const std::unordered_set<std::string> setB)const
{
	for (auto const& elem : subset)
		if (setB.find(elem) == setB.end())
			return false;
	return true;
}
bool TuringMachine::isIn(const std::unordered_set<char> subset, const std::unordered_set<char> setB)const
{
	for (auto const& elem : subset)
		if (setB.find(elem) == setB.end())
			return false;
	return true;
}

bool TuringMachine::cellIsValid(std::string cell, std::string& q, char& t, char& dir)
{
	if (cell.find_first_of("H") != std::string::npos)
	{
		q = "H";
		dir = t = 'B';
		return true;
	}
	if (cell.find_first_of("_") != std::string::npos)
	{
		q = "_";
		dir = t = 'B'; 
		return true;
	}
	int s = cell.find_first_of("(");
	int e = cell.find_first_of(")");
	int c1 = cell.find_first_of(",",s);
	int c2 = cell.find_first_of(",",c1 + 1);
	if (c1 == std::string::npos || c2 == std::string::npos || c2 >= e)
	{
		std::cerr << "Invalid input in transition table" << std::endl;
	}
	for (int i = s + 1; i < c2; i++)
	{
		if (cell[i] != ' ' && cell[i] != ',')
		{
			if (i < c1)
				q += cell[i];
			else if (i < c2)
				t = cell[i];
		}
	}
	if (Q.count(q) == 0)//check if Q contains such a state
	{
		std::cerr << "Invalid input in transition table\n" <<
			cell << " - " << q << "state not found." << std::endl;
		q = " ";
		return false;
	}
	if (T.count(t) == 0) // check if t is a tape alphabel symbol
	{
		std::cerr << "Invalid input in transition table cell - " <<
			cell << "\n - tape alphabet does not contain " << t << "symbol!" << std::endl;
		t = ' ';
		return false;
	}

	int n = cell.find_first_of("LR", c2);
	if (n == std::string::npos)
	{
		std::cerr << "Invalid input. The 3rd value of " << cell << "should be L or R" << std::endl;
		dir = ' ';
		return false;
	}
	else
		dir = cell[n];

	return true;
}



TuringMachine::TuringMachine(std::string filePath):tempQ(nullptr)
{
	std::ifstream file;
	file.open(filePath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open the file! " << std::endl;
		exit(1);
	}
	int k = 0;
	std::string read;
	while (k < 4 && file >> read )
	{
		if (!writeInto(read, k++))
		{
			return;
		}
	}

	// building delta function
	int i = 0, j = 0;
	int n = Q.size() * T.size();//for keeping truck of delta function elements
	std::pair<std::string, char> first;
	std::pair<std::pair<std::string, char>, char> triple;
	while (n > 0 && file >> read)
	{
		if (read != "|")
		{
			// make Q x T
			first = { tempQ[i],tempT[j++] };
			if (j >= T.size())
			{
				j = 0;
				i++;
			}
			// make Q x T x { L, R }
			std::string q;
			char dir, t;
			if (!cellIsValid(read, q, t, dir))//check if cell is Valid
			{
				return;
			}
			std::pair<std::string, char> second(q, t);
			triple = { second,dir };
			transitionsTable.insert({ first,triple });
			n--;
		}
	}
	
	if (file >> read)
	{
		std::cerr << "There’s excess information in the given table.\nPlease check the file again." << std::endl;
	}
	
	file.close();
	
	delete[]tempT;
	tempT = nullptr;
	delete[]tempQ;
	tempQ = nullptr;
}
//check if input is correct
bool TuringMachine::inputIsValid(std::string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (Sigma.count(input[i]) == 0)
		{
			std::cerr << "Unkown element in the input string" << std::endl;
			return false;
		}
		tape.push_back(input[i]);
	}
	return true;
}

void TuringMachine::printTape()
{
	for (int i = 0; i < tape.size(); i++)
	{
		if (tape[i] != 'B')
		{
			std::cout << tape[i];
		}
	}
	std::cout << std::endl;
}

void TuringMachine::run(std::string input)
{
	if (!inputIsValid(input))//check if input is correct
	{
		return;
	}
	std::string state = "q0";
	int curr = 0;//for keeping track of the current pos of the head pointer
	while(!(F.count(state) == 0 && state == "H"))
	{
		std::pair<std::string, char> p = { state, tape[curr] };
		tape[curr] = transitionsTable[p].first.second;
		if (transitionsTable[p].second == 'R')
		{
			if (curr == tape.size() - 1)
				tape.push_back('B');
			curr++;
		}
		else if (transitionsTable[p].second == 'L')
		{
			if(curr == 0)
				tape.push_front('B');
			curr--;
		}
		state = transitionsTable[p].first.first;

		if (state == "_")
		{
			std::cout << "Input string rejected." << std::endl;
			return;
		}
	}
	std::cout << "Input string accepted. "<< std::endl;
	std::cout << "Output : ";
	printTape();
	tape.clear();
}

void TuringMachine::debug(std::string input)
{
	if (!inputIsValid(input))//check if input is correct and write it into tape
	{
		return;
	}
	std::string state = "q0";
	int i = 1;//for keeping track of the tape
	std::string command;
	bool all = false;
	while (!(F.count(state) == 0 && state == "H"))
	{
		if(!all)
			std::cin >> command;
		if (command == "-s" || command == "-step") //a step
		{

			std::pair<std::string, char> p = { state, tape[i] };
			tape[i] = transitionsTable[p].first.second;
			if (transitionsTable[p].second == 'R')
				i++;
			else if (transitionsTable[p].second == 'L')
				i--;
			state = transitionsTable[p].first.first;
			if (state == "_")
			{
				std::cout << "Input string rejected." << std::endl;
				return;
			}
			if (!all)
				printTape();
		}
		else if (command == "-a" || command == "-all")
		{
			all = true;
			command = "-s";
		}
		else if (command == "-q" || command == "-quit")
		{
			std::cout << "Program execution stopped." << std::endl;
		}
		else if (command == "-c")
		{
			std::cout << "HP\tCS" << std::endl << i << "\t" << state << std::endl; //Head Pointer index, current state
		}
		else if (command == "-help")
		{
			std::cout << "< -s / -step >\t executes one step at a time\n"
				"< -q / -quit >\t quits the programm\n"
				"< -a / -all>\t executes rest of the programm\n"
				"< -c >\t\t outputs current state(CS) and header pointer index(HP)\n" << std::endl;
		}
		else 
		{
			std::cerr << "Unkown command." << std::endl;
			continue;
		}
		
	}
	std::cout << "Input string accepted. " << std::endl;
	std::cout << "Output : ";
	printTape();
	tape.clear();
}
