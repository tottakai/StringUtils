#include "stringutils.h"
#include <iostream>

int main()
{
	auto csv_input = "Year,Make,Model,Description,Price\n" \
					 "1997,Ford,E350,pickup,3000.00\n" \
					 "1999,Chevy,Venture Extended,foo,4900.00\n" \
					 "1999,Chevy,Venture Extended,Very Large,5000.00";

	tottakai::each_line(csv_input, [] (const std::string& line) {
		tottakai::split_map(line, ',', [] (const std::string& cell) {
			std::cout << cell << "- -";
		});
		std::cout << std::endl;
	});
}