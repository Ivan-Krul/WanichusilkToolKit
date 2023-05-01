#pragma once
#include <string>

namespace hardware_envi_lib
{
	struct ILogMachine
	{
		virtual void init(const std::string& path, const bool need_binary) noexcept = 0;
		virtual void log(const char* pFunction_name, const std::string& message) noexcept = 0;
		virtual void logNumberx64i(const char* pFunction_name, const std::string& message, const int64_t argument) noexcept = 0;
		virtual void logNumberx64f(const char* pFunction_name, const std::string& message, const double argument) noexcept = 0;
		virtual void logNumberx32i(const char* pFunction_name, const std::string& message, const int32_t argument) noexcept = 0;
		virtual void logNumberx32f(const char* pFunction_name, const std::string& message, const float argument) noexcept = 0;
		virtual void save() noexcept = 0;
		virtual ~ILogMachine() = default;
	};
}
