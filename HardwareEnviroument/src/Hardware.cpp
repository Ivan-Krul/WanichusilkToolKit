#include "../include/Hardware.h"

namespace hardware_envi_lib
{
	void Hardware::_writeInFileSize(std::ofstream& fs, size_t size)
	{
		fs.write(reinterpret_cast<char*>(&size), sizeof(short));
	}

	void Hardware::_writeInFileString(std::ofstream& fs, const std::string str)
	{
		auto size = str.size();
		fs.write(reinterpret_cast<char*>(&size), sizeof(short));
		for (const auto& s : str)
			fs.write(&s, 1);
	}

	size_t Hardware::_readFromFileSize(std::ifstream& fs)
	{
		auto size = size_t();

		fs.read(reinterpret_cast<char*>(&size), sizeof(short));

		return size;
	}

	std::string Hardware::_readFromFileString(std::ifstream& fs)
	{
		auto size = size_t();
		auto str = std::string();

		fs.read(reinterpret_cast<char*>(&size), sizeof(short));
		str.resize(size);

		for (auto& c : str)
			fs.read(&c, 1);

		return str;
	}

	datatype Hardware::_findFromDataTypes(const DateType date_type)
	{
		auto comp = [=](datatype datatp) { return datatp.date_type == date_type;  };
		return *std::find_if(c_DataTypes.begin(), c_DataTypes.end(), comp);
	}

	datatype Hardware::_findFromDataTypes(const char bin)
	{
		auto comp = [=](datatype datatp) { return datatp.binary_value == bin; };
		return *std::find_if(c_DataTypes.begin(), c_DataTypes.end(), comp);
	}

/*
Definition:
	&Str(string)
	{
		string.size() > s
		->
			string[s]
		<-
	}
Structure:
	Compacter.size() > c
	->
		c_DataTypes[Compacter[c].date_type].binary_value
		&Str(Compacter[c].name)
		&Str(Compacter[c].binary)
	<-
*/

	void hardware_envi_lib::Hardware::write(const std::string directory)
	{
		auto writer = std::ofstream(directory, std::ios::binary | std::ios::out);
		auto bufnum = size_t();

		_writeInFileSize(writer, m_Compacter.size());

		for (const auto& c : m_Compacter)
		{
			bufnum = _findFromDataTypes(c.date_type).binary_value;

			writer.write(reinterpret_cast<char*>(&bufnum), 1);
			_writeInFileString(writer, c.name);
			_writeInFileString(writer, c.binary);
		}
		writer.close();
	}

	void hardware_envi_lib::Hardware::read(const std::string directory)
	{
		if (!canBeFileOpen(directory))
			return;
		auto reader = std::ifstream(directory, std::ios::binary | std::ios::in);
		auto bufnum = size_t();
		auto size = _readFromFileSize(reader);
		auto fv = float_var();

		m_Compacter.clear();

		for (size_t c = 0; c < size; c++)
		{
			reader.read(reinterpret_cast<char*>(&bufnum), 1);

			fv.date_type = _findFromDataTypes(static_cast<char>(bufnum)).date_type;
			fv.name = _readFromFileString(reader);
			fv.binary = _readFromFileString(reader);

			m_Compacter.push(fv.date_type, fv.name, fv.binary.data());
		}
		reader.close();
	}

	bool Hardware::canBeFileOpen(const std::string directory)
	{
		auto reader = std::ifstream(directory);
		auto open = reader.is_open();

		reader.close();

		return open;
	}
	Compacter& Hardware::getCompacter()
	{
		return m_Compacter;
	}

	void Hardware::writeAbortLine(const std::string where, const std::string message)
	{
		auto writer = std::ofstream(where);
		
		writer.seekp(0, std::ios_base::end);
		writer << "ERROR: " << where << ": " << message << '\n';
		writer.close();
	}

	Hardware Hardware::s_Instance;
}
