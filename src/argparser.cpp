#include "argparser.hpp"

ArgParser::ArgParser (int argc, char **argv) noexcept
	: m_arguments(argv+1, argv+argc) {
}

ArgParser::ArgParser(std::initializer_list<ParserOption> options) {
	for (auto &&option : options) {
		this->m_parserOptions.emplace(option.name(), std::move(option));
	}
}

ArgParser &ArgParser::operator()(const std::string &name,
					 const std::string &description,
					 u_short type,
					 std::function<bool(const std::any&)> validator,
					 std::any defaultValue) {
	return this->operator()(ParserOption(name, description, type, validator, defaultValue));
}

ArgParser &ArgParser::operator()(ParserOption &&option) {
	return this->addOption(std::move(option));
}


ArgParser &ArgParser::addOption(const std::string &name,
					 const std::string &description,
					 u_short type,
					 std::function<bool(const std::any&)> validator,
					 std::any defaultValue) {
	return this->addOption(ParserOption(name, description, type, validator, defaultValue));
}

ArgParser &ArgParser::addOption(ParserOption &&option) {
	this->m_parserOptions.emplace(option.name(), std::move(option));
	return *this;
}


const std::map<std::string, ParserOption> &ArgParser::parse(int argc, char **argv) {
	this->m_arguments.assign(argv, argv+argc);
	return this->parse();
}

const std::map<std::string, ParserOption> &ArgParser::parse() {
	for (auto it = this->m_arguments.begin(); it != this->m_arguments.end(); ++it) {
		bool isUsedArg = false;
		for (auto &optionIter : this->m_parserOptions) {
			ParserOption &option = optionIter.second;
			if (option.isEqual(*it)) {
				if (!option.isBoolType()) {
					// Value string/int -> just get next iter and set
					if ((++it) != this->m_arguments.end()) {
						if (option.isIntType())
							option.setValue(std::stol(*it));
						else
							option.setValue(*it);
						isUsedArg = true;
					}else{
						throw std::runtime_error("Error! Not enought arguments for: \"" + option.name() + "\"");
					}
				}else{
					// Value is bool. We just set flag
					option.setValue(true);
					isUsedArg = true;
				}
			}
		}
		if (!isUsedArg)
			throw std::runtime_error("Unresolved option: \"" + (*it) + "\"");
	}

	this->checkRequiredOptions();

	return this->m_parserOptions;
}

void ArgParser::checkRequiredOptions() const {
	for (const auto &optionIter : this->m_parserOptions) {
		const ParserOption &option = optionIter.second;
		if (option.isRequired() && !option.isHasValue()) {
			throw std::logic_error("Required option \"" + option.name() + "\" is not setted!\n"+this->getHelpString());
		}
	}
}

std::string ArgParser::getHelpString() const noexcept {
	ulong maxWidth = 0;
	for (const auto &optionIter : this->m_parserOptions ) {
		maxWidth = std::max(optionIter.second.fullName().size(), maxWidth);
	}

	std::string str;
	for (const auto &optionIter : this->m_parserOptions ) {
		str.append("\t" + optionIter.second.fullName()  + std::string(maxWidth-optionIter.second.fullName().size(), ' ') + "\t" + optionIter.second.description() + "\n");
	}
	return str;
}
