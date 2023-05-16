#include "Utils.h"

#include <conio.h>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace address_book::utils
{
	void set_color(bool active)
	{
		if (active)
		{
			std::cout << "\033[37;40;4m";
		}
		else
		{
			std::cout << "\033[30;47;4m";
		}

		std::cout << std::setw(100) << std::left;
	}

	std::string read_line()
	{
		std::string input;
		std::getline(std::cin, input);

		return input;
	}

	char read_sign()
	{
		char sign;

		while (true)
		{
			std::string input{read_line()};

			if (input.length() == 1)
			{
				sign = input[0];
				break;
			}

			std::cout
				<< "\033[31m"
				<< "Wrong input, enter again >> "
				<< "\033[0m"
				<< std::endl;
		}

		return std::toupper(sign);
	}
}
