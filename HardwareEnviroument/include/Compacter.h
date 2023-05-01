// Target: Save variables in different datatypes in one and convert in needly with indexation

#pragma once
#include <string>
#include <list>

namespace hardware_envi_lib
{
	enum class DateType
	{
		str__,
		int__,
		uint_,
		bool_,
		char_,
		flot_,
		dobl_,
		shrt_,
		size_
	};

	struct float_var
	{
		std::string name;
		DateType date_type;
		std::string binary;
	};

	class Compacter
	{
	public:
		void push(const DateType date_type, const std::string name, const char* p_ref);

		size_t size() const noexcept;
		
		std::list<float_var>::const_iterator begin() const noexcept;
		std::list<float_var>::const_iterator end() const noexcept;

		void clear();

		const std::string nameOfVariable(size_t index) const;

		const std::string operator[](const std::string str_index) const;
		const std::string operator[](const size_t index) const;
		const DateType getDataType(const std::string str_index) const;

		bool convertToBool(const std::string str_index) const;
		char convertToChar(const std::string str_index) const;
		short convertToShort(const std::string str_index) const;
		int convertToInt(const std::string str_index) const;
		uint32_t convertToUInt(const std::string str_index) const;
		float convertToFloat(const std::string str_index) const;
		double convertToDouble(const std::string str_index) const;
		size_t convertToSize(const std::string str_index) const;

		std::string getProperties(const size_t index);
		std::string getProperties(const std::string str_index);

		void pop(const std::string str_index);
	private:
		std::list<float_var> m_Variables;

		uint8_t sizeOf(const DateType data_type);
		std::list<float_var>::const_iterator _getFromIndex(const size_t index) const;
		std::list<float_var>::const_iterator _getVar(const std::string str_index) const;
	};
}

