#include "LogMachineFile.h"

#include <fstream>

namespace hardware_envi_lib
{
	void LogMachineFile::Init(const std::string& path, const bool need_binary) noexcept
	{
		m_NeedBinary = need_binary;
		m_Path = path;

		auto now = time(0);
#pragma warning(disable : 4996)
		char* dt = ctime(&now);

		m_Path += ".log";

		std::string init_log = "Init was" + c_LogFormat + dt;
		init_log.erase((init_log.end()-1));

		m_Logs.push_back(init_log);
	}

	void LogMachineFile::Log(const char* pFunction_name, const std::string& message) noexcept
	{
		std::string log;

		log = pFunction_name;
		log += c_LogFormat + std::to_string(f_UpdateElapsedTime()) + " ms" + c_LogFormat + message;
		
		m_Logs.push_back(log);
	}

	void LogMachineFile::LogNumberx64i(const char* pFunction_name, const std::string& message, const int64_t argument) noexcept
	{
		f_WriteAnyLogWithArgument<int64_t>(pFunction_name, message, argument);
	}

	void LogMachineFile::LogNumberx64f(const char* pFunction_name, const std::string& message, const double argument) noexcept
	{
		f_WriteAnyLogWithArgument<double>(pFunction_name, message, argument);
	}

	void LogMachineFile::LogNumberx32i(const char* pFunction_name, const std::string& message, const int32_t argument) noexcept
	{
		f_WriteAnyLogWithArgument<int32_t>(pFunction_name, message, argument);
	}

	void LogMachineFile::LogNumberx32f(const char* pFunction_name, const std::string& message, const float argument) noexcept
	{
		f_WriteAnyLogWithArgument<float>(pFunction_name, message, argument);
	}

	void LogMachineFile::Save() noexcept
	{
		std::ofstream fout;
		fout.open(m_Path);

		size_t index = 0;

		for (auto& log : m_Logs)
			fout << index++ << c_LogFormat << log << '\n';

		fout.close();
	}

	float LogMachineFile::f_UpdateElapsedTime()
	{
		auto new_now = std::chrono::high_resolution_clock::now();
		size_t time_count = std::chrono::duration_cast<std::chrono::nanoseconds>(new_now - m_TimePointLastLog).count();
		m_TimePointLastLog = new_now;
		return float(time_count) / 10e5;
	}

	template<typename T>
	void LogMachineFile::f_WriteAnyLogWithArgument(const char* pFunction_name, const std::string& message, T argument)
	{
		std::string log;

		log = pFunction_name;
		log += c_LogFormat + std::to_string(f_UpdateElapsedTime()) + "ms" + c_LogFormat + message + c_LogFormat + std::to_string(argument);

		if (m_NeedBinary)
		{
			log += +" (binary represent" + c_LogFormat + '"';
			for (size_t i = 0; i < sizeof(T); i++)
			{
				log += static_cast<char>(argument);
				argument = (T)((uint64_t)argument >> 8);
			}

			log += "\")";
		}

		m_Logs.push_back(log);
	}
}
