#include "parseroption.hpp"

ParserOption::ParserOption(const std::string &name,
			 const std::string &description,
			 u_short type,
			 std::function<bool(const std::any&)> validator,
			 std::any defaultValue) noexcept
	: m_name(name), m_optionType(type), m_description(description),
	  m_validator(validator), m_value(defaultValue) {
	if (!defaultValue.has_value() && type & ParserOption::Bool){
		this->m_value = false;
	}
}


ParserOption::ParserOption(const ParserOption& option){
	this->copy(option);
}

ParserOption &ParserOption::operator=(const ParserOption &option) {
	this->copy(option);
	return *this;
}


ParserOption::ParserOption(ParserOption&& option){
	this->swap(std::move(option));
}

ParserOption &ParserOption::operator=(ParserOption &&option) {
	this->swap(std::move(option));
	return *this;
}


void ParserOption::setName(const std::string &name) noexcept {
	this->m_name = name;
}

void ParserOption::setDescription(const std::string &description) noexcept {
	this->m_description = description;
}

void ParserOption::setType(u_short type) noexcept {
	this->m_optionType = type;
}

void ParserOption::setValidator(std::function<bool(const std::any&)> validator) noexcept {
	this->m_validator = validator;
}

void ParserOption::setValue(const std::any &value) {
	if (this->m_validator) {

		if (this->m_validator(value)){
			this->m_value = value;

		}else{
			throw std::runtime_error("Validation error. Argument: \"" + this->m_name + "\"");
		}

	}else{
		this->m_value = value;
	}
}


const std::string &ParserOption::name() const noexcept
	{ return this->m_name; }

std::string ParserOption::fullName() const noexcept
	{ return "--" + this->m_name; }

const std::string &ParserOption::description() const noexcept
	{ return this->m_description; }


bool ParserOption::isStringType() const noexcept
    { return this->m_optionType == ParserOption::String || this->m_optionType == ParserOption::Required; }

bool ParserOption::isBoolType() const noexcept
    { return this->m_optionType & ParserOption::Bool; }

bool ParserOption::isIntType() const noexcept
    { return this->m_optionType & ParserOption::Long; }

bool ParserOption::isRequired() const noexcept
    { return this->m_optionType & ParserOption::Required; }

bool ParserOption::isHasValue() const noexcept
    { return this->m_value.has_value(); }

std::any &ParserOption::value() noexcept
	{ return this->m_value; }

std::any ParserOption::value() const noexcept
	{ return this->m_value; }


bool ParserOption::toBool() const {
	return std::any_cast<bool>(this->m_value);
}
std::string ParserOption::toString() const {
	return std::any_cast<std::string>(this->m_value);
}
long ParserOption::toLong() const {
	return std::any_cast<long>(this->m_value);
}


bool ParserOption::isEqual(const std::string &value) const noexcept {
	return value == this->fullName();
}

void ParserOption::copy(const ParserOption &option) {
	this->m_name = option.m_name;
	this->m_description = option.m_description;
	this->m_optionType = option.m_optionType;
	this->m_validator = option.m_validator;
	this->m_value = option.m_value;
}

void ParserOption::swap(ParserOption &&option) {
	std::swap(this->m_name, option.m_name);
	std::swap(this->m_description, option.m_description);
	std::swap(this->m_optionType, option.m_optionType);
	std::swap(this->m_validator, option.m_validator);
	std::swap(this->m_value, option.m_value);
}
