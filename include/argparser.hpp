#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include "parseroption.hpp"
#include <map>

class ArgParser {
	public:
		ArgParser() = default;
		ArgParser (int argc, char **argv) noexcept;
		ArgParser(std::initializer_list<ParserOption> options);

		ArgParser &operator()(const std::string &name,
							 const std::string &description = "",
							 u_short type = ParserOption::String,
							 std::function<bool(const std::any&)> validator = nullptr,
							 std::any defaultValue = std::any());
		ArgParser &operator()(ParserOption &&option);

		ArgParser &addOption(const std::string &name,
							 const std::string &description = "",
							 u_short type = ParserOption::String,
							 std::function<bool(const std::any&)> validator = nullptr,
							 std::any defaultValue = std::any());
		ArgParser &addOption(ParserOption &&option);

		const std::map<std::string, ParserOption> &parse(int argc, char **argv);
		const std::map<std::string, ParserOption> &parse();

		std::string getHelpString() const noexcept;

	private:
		void checkRequiredOptions() const;

	private:
		ArgParser(const ArgParser &) = delete;
		ArgParser(ArgParser &&) = delete;
		ArgParser &operator=(const ArgParser&) = delete;
		ArgParser &operator=(ArgParser&&) = delete;

	private:
		std::map<std::string, ParserOption> m_parserOptions;
		std::vector<std::string> m_arguments;
};
#endif // ARGPARSER_HPP
