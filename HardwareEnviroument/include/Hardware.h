// Target: Save and load from/to file and put all in Compactor, single object

#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "Compacter.h"

namespace hardware_envi_lib
{
	struct datatype
	{
		char value[5];
		char binary_value;
		DateType date_type;
	};

	struct IHardware
	{
		virtual void write(const std::string directory) = 0;
		virtual void read(const std::string directory) = 0;
		virtual void writeAbortLine(const std::string where, const std::string message) = 0;
	};

	class Hardware : public IHardware
	{
	public:
		void write(const std::string directory);
		void read(const std::string directory);
		bool canBeFileOpen(const std::string directory);
		Compacter& getCompacter();
		void writeAbortLine(const std::string where, const std::string message);

		// Singleton pattern
		static Hardware& getInstance()
		{
			return s_Instance;
		}
	private:
		const std::vector<datatype> c_DataTypes =
		{
			{"str_", 's', DateType::str__},
			{"int_", 'i', DateType::int__},
			{"uint", 'u', DateType::uint_},
			{"char", 'c', DateType::char_},
			{"bool", 'b', DateType::bool_},
			{"flot", 'f', DateType::flot_},
			{"dobl", 'd', DateType::dobl_},
			{"shrt", 'r', DateType::shrt_},
			{"size", 'z', DateType::size_}
		};

		Compacter m_Compacter;

		void _writeInFileSize(std::ofstream& fs, size_t size);
		void _writeInFileString(std::ofstream& fs, const std::string str);
		datatype _findFromDataTypes(const DateType date_type);
		datatype _findFromDataTypes(const char bin);

		size_t _readFromFileSize(std::ifstream& fs);
		std::string _readFromFileString(std::ifstream& fs);


		// Singleton pattern
		static Hardware s_Instance;
		Hardware() = default;
	};

	// Hardware Hardware::s_Instance;
}
