#include "../include/Compacter.h"

namespace hardware_envi_lib
{
	uint8_t Compacter::sizeOf(const DateType data_type)
	{
		uint8_t bytes = 0;
		switch (data_type)
		{
			case DateType::dobl_:
			case DateType::size_:
				bytes += 4;
			case DateType::flot_:
			case DateType::uint_:
			case DateType::int__:
				bytes += 2;
			case DateType::shrt_:
				bytes += 1;
			case DateType::char_:
			case DateType::bool_:
				bytes += 1;
				return bytes;
			default:
				return 0xff;
		}
	}
	std::list<float_var>::const_iterator Compacter::_getFromIndex(const size_t index) const
	{
		size_t i = 0;
		for (auto iter = begin(); iter != end(); iter++)
		{
			if (i == index)
				return iter;
			i++;
		}
		return std::list<float_var>::const_iterator();
	}
	std::list<float_var>::const_iterator Compacter::_getVar(const std::string str_index) const
	{
		auto comp = [=](const float_var& fv) {return fv.name == str_index; };
		return std::find_if(m_Variables.begin(), m_Variables.end(), comp);
	}
	void hardware_envi_lib::Compacter::push(const DateType date_type, const std::string name, const char* p_ref)
	{
		auto fl_var = float_var();
		fl_var.date_type = date_type;
		if (sizeOf(date_type) != 255)
		{
			fl_var.binary.resize(sizeOf(date_type));
			for (uint8_t i = 0; i < fl_var.binary.size(); i++)
				fl_var.binary[i] = *(p_ref + i);
		}
		else
			fl_var.binary = p_ref;
		fl_var.name = name;
		m_Variables.push_back(fl_var);
	}

	size_t Compacter::size() const noexcept
	{
		return m_Variables.size();
	}

	std::list<float_var>::const_iterator Compacter::begin() const noexcept
	{
		return m_Variables.begin();
	}

	std::list<float_var>::const_iterator Compacter::end() const noexcept
	{
		return m_Variables.end();
	}

	void Compacter::clear()
	{
		m_Variables.clear();
	}

	const std::string Compacter::nameOfVariable(size_t index) const
	{
		for (const auto& v : m_Variables)
		{
			if (index == 0)
				return v.name;
			index--;
		}
		return std::string();
	}

	const std::string Compacter::operator[](const std::string str_index) const
	{
		return _getVar(str_index)->binary;
	}

	const std::string Compacter::operator[](const size_t index) const
	{
		return _getFromIndex(index)->binary;
	}

	const DateType Compacter::getDataType(const std::string str_index) const
	{
		return _getVar(str_index)->date_type;
	}

	bool Compacter::convertToBool(const std::string str_index) const
	{
		auto elem = _getVar(str_index);
		if (elem->date_type != DateType::bool_)
			return bool();
		return elem->binary.c_str();
	}
	char Compacter::convertToChar(const std::string str_index) const
	{
		auto elem = _getVar(str_index);
		if (elem->date_type != DateType::char_)
			return char();
		return elem->binary.c_str()[0];
	}

	short Compacter::convertToShort(const std::string str_index) const
	{
		auto elem = _getVar(str_index);
		if (elem->date_type != DateType::shrt_ && elem->binary.size() != sizeof(short))
			return short();
		return *reinterpret_cast<short*>(const_cast<char*>(elem->binary.c_str()));
	}

	int Compacter::convertToInt(const std::string str_index) const
	{
		auto elem = _getVar(str_index);
		if (elem->date_type != DateType::int__ && elem->binary.size() != sizeof(int))
			return int();
		return *reinterpret_cast<int*>(const_cast<char*>(elem->binary.c_str()));
	}

	uint32_t Compacter::convertToUInt(const std::string str_index) const
	{
		auto elem = _getVar(str_index);
		if (elem->date_type != DateType::uint_ && elem->binary.size() != sizeof(uint32_t))
			return uint32_t();
		return *reinterpret_cast<uint32_t*>(const_cast<char*>(elem->binary.c_str()));
	}

	float Compacter::convertToFloat(const std::string str_index) const
	{
		auto elem = _getVar(str_index);
		if (elem->date_type != DateType::flot_ && elem->binary.size() != sizeof(float))
			return float();
		return *reinterpret_cast<float*>(const_cast<char*>(elem->binary.c_str()));
	}

	double Compacter::convertToDouble(const std::string str_index) const
	{
		auto elem = _getVar(str_index);
		if (elem->date_type != DateType::dobl_ && elem->binary.size() != sizeof(double))
			return double();
		return *reinterpret_cast<double*>(const_cast<char*>(elem->binary.c_str()));
	}

	size_t Compacter::convertToSize(const std::string str_index) const
	{
		auto elem = _getVar(str_index);
		if (elem->date_type != DateType::size_ && elem->binary.size() != sizeof(size_t))
			return size_t();
		return *reinterpret_cast<size_t*>(const_cast<char*>(elem->binary.c_str()));
	}

	std::string Compacter::getProperties(const size_t index)
	{
		if (!(index < size()))
			return std::string();
		const auto var = _getFromIndex(index);
		auto str = " " + var->name + ": ";

		switch (var->date_type)
		{
			case DateType::dobl_:
				return "dobl" + str + std::to_string(convertToDouble(var->name));
			case DateType::size_:
				return "size" + str + std::to_string(convertToSize(var->name));
			case DateType::flot_:
				return "flot" + str + std::to_string(convertToFloat(var->name));
			case DateType::uint_:
				return "uint" + str + std::to_string(convertToUInt(var->name));
			case DateType::int__:
				return "int_" + str + std::to_string(convertToInt(var->name));
			case DateType::shrt_:
				return "shrt" + str + std::to_string(convertToShort(var->name));
			case DateType::char_:
				return "char" + str + convertToChar(var->name);
			case DateType::bool_:
				return "bool" + str + std::to_string(convertToBool(var->name));
			default:
				return "str_" + str + var->binary;
		}
	}

	std::string Compacter::getProperties(const std::string str_index)
	{
		const auto var = _getVar(str_index);
		auto str = " " + var->name + ": ";

		switch (var->date_type)
		{
			case DateType::dobl_:
				return "dobl" + str + std::to_string(convertToDouble(var->name));
			case DateType::size_:
				return "size" + str + std::to_string(convertToSize(var->name));
			case DateType::flot_:
				return "flot" + str + std::to_string(convertToFloat(var->name));
			case DateType::uint_:
				return "uint" + str + std::to_string(convertToUInt(var->name));
			case DateType::int__:
				return "int_" + str + std::to_string(convertToInt(var->name));
			case DateType::shrt_:
				return "shrt" + str + std::to_string(convertToShort(var->name));
			case DateType::char_:
				return "char" + str + convertToChar(var->name);
			case DateType::bool_:
				return "bool" + str + std::to_string(convertToBool(var->name));
			default:
				return "str_" + str + var->binary;
		}
	}

	void Compacter::pop(const std::string str_index)
	{
		auto comp = [=](const float_var& fv) {return fv.name == str_index; };
		auto iter = std::find_if(m_Variables.begin(), m_Variables.end(), comp);
		m_Variables.erase(iter);
	}
}
