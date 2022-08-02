#include "argparser.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	ArgParser parser(argc, argv);

	parser.addOption("test", "just test argument", ParserOption::String,
					 [] (const std::any &value) -> bool {
		                 try{
		                     if (std::any_cast<std::string>(value).size() < 5)
								 return true;
							 return false;
		                 }catch (...) {
							 return false;
		                 }
	                 })
			("some_integer", "just integer value", ParserOption::Long,
			 		[] (const std::any &value) -> bool {
				 		try{
					 		if (std::any_cast<long>(value) >= 20)
						 		return true;
					 		return false;
				 		}catch (...) {
					 		return false;
				 		}
			 		}, 50l); // Default value = 50

	std::map<std::string, ParserOption> parsingResult;
	try{
		parsingResult = parser.parse();
	}catch(std::exception &e) {
		std::cout << "Parsing error:" << e.what() << "\n";
		return -1;
	}

	std::cout << "test: " << parsingResult["test"].toString() << "\n";
	std::cout << "some_integer: " << parsingResult["some_integer"].toLong() << "\n";

}