#pragma once
#include "ILogMachine.h"

#include <list>
#include <chrono>

namespace hardware_envi_lib
{
	class LogMachineFile : public ILogMachine
	{
	public:
		LogMachineFile() = default;
		inline LogMachineFile(const std::string& path, const bool need_binary) noexcept { init(path, need_binary); }

		virtual void init(const std::string& path, const bool need_binary) noexcept;
		virtual void log(const char* pFunction_name, const std::string& message) noexcept;
		virtual void logNumberx64i(const char* pFunction_name, const std::string& message, const int64_t argument) noexcept;
		virtual void logNumberx64f(const char* pFunction_name, const std::string& message, const double argument) noexcept;
		virtual void logNumberx32i(const char* pFunction_name, const std::string& message, const int32_t argument) noexcept;
		virtual void logNumberx32f(const char* pFunction_name, const std::string& message, const float argument) noexcept;
		virtual void save() noexcept;
		virtual ~LogMachineFile() = default;

	private:
		template<typename T>
		void f_WriteAnyLogWithArgument(const char* pFunction_name, const std::string& message, T argument);
		float f_UpdateElapsedTime();


		std::list<std::string> m_Logs;
		std::string m_Path;
		bool m_NeedBinary = false;

		std::chrono::high_resolution_clock::time_point m_TimePointLastLog = std::chrono::high_resolution_clock::now();

		const std::string c_LogFormat = ":\t";
	};
}
