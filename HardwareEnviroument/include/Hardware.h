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
		virtual void Write(const std::string directory) = 0;
		virtual void Read(const std::string directory) = 0;
		virtual void WriteAbortLine(const std::string where, const std::string message) = 0;
	};

	class Hardware : public IHardware
	{
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
		
		void f_WriteInFileSize(std::ofstream& fs, size_t size);
		void f_WriteInFileString(std::ofstream& fs, const std::string str);
		datatype f_FindFromDataTypes(const DateType date_type);
		datatype f_FindFromDataTypes(const char bin);

		size_t f_ReadFromFileSize(std::ifstream& fs);
		std::string f_ReadFromFileString(std::ifstream& fs);


		// Singleton pattern
		static Hardware s_Instance;
		Hardware() = default;
	public:
		void Write(const std::string directory);
		void Read(const std::string directory);
		bool CanBeFileOpen(const std::string directory);
		Compacter& GetCompacter();
		void WriteAbortLine(const std::string where, const std::string message);

		// Singleton pattern
		static Hardware& GetInstance()
		{
			return s_Instance;
		}
	};

	// Hardware Hardware::s_Instance;
}
