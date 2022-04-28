#include "TuringMachine.h"
int main()
{
	std::cout << "Please enter file path" << std::endl;
	char s[201];
	std::cin.getline(s, 200);

	TuringMachine t(s);//C:\\Users\\Dell\\TuringMachine.txt
	while (true)
	{
		std::cout << "Please choose a working mode:" << std::endl;
		int k = 0;
		std::cout << "1. Run" << std::endl;
		std::cout << "2. Debug mode" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cin >> k;
		std::cin.ignore();
		std::cout << "Enter an input string:" << std::endl;
		std::cin.getline(s, 200);
		switch (k)
		{
		case 1:
			t.run(s);
			break;
		case 2:
			std::cout << "Debug mode activated.\n"
				"Type -help for the list of supported commands. " << std::endl;
			t.debug(s);
			break;
		case 3:
			return 0;
		default:
			std::cerr << "Unknown mode" << std::endl;
			continue;
		}
		std::cout << std::endl;

	}
	return 0;
}