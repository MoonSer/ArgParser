#ifndef PARSEROPTION_HPP
#define PARSEROPTION_HPP

#include <functional>
#include <stdexcept>
#include <any>

class ParserOption {
	public:
		enum {
			String   = 0,
			Bool     = 1 << 0,
			Long      = 1 << 1,
			Required = 1 << 2 // Required any
		};

		ParserOption() = default;

		ParserOption(const ParserOption& option);
		ParserOption &operator=(const ParserOption &option);

		ParserOption(ParserOption&& option);
		ParserOption &operator=(ParserOption &&option);

		explicit ParserOption(const std::string &name,
					 const std::string &description = "",
					 u_short type = ParserOption::String,
					 std::function<bool(const std::any&)> validator = nullptr,
					 std::any defaultValue = std::any()) noexcept;

		void setName(const std::string &name) noexcept;
		void setDescription(const std::string &description) noexcept;
		void setType(u_short type) noexcept;
		void setValidator(std::function<bool(const std::any&)> validator) noexcept;
		void setValue(const std::any &value);

		const std::string &name() const noexcept;
		std::string fullName() const noexcept;

		const std::string &description() const noexcept;

		bool isHasValue() const noexcept;
		bool isStringType() const noexcept;
		bool isBoolType() const noexcept;
		bool isIntType() const noexcept;
		bool isRequired() const noexcept;

		std::any &value() noexcept;
		std::any value() const noexcept;

		bool toBool() const;
		std::string toString() const;
		long toLong() const;

		bool isEqual(const std::string &value) const noexcept;

		void copy(const ParserOption &opt);

		void swap(ParserOption &&option);

	private:
		std::string m_name;
		std::string m_description;
		u_short m_optionType;
		std::function<bool(const std::any&)> m_validator;
		std::any m_value;
};

#endif // PARSEROPTION_HPP
