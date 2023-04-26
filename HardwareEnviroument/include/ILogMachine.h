#pragma once
#include <string>

namespace hardware_envi_lib
{
	struct ILogMachine
	{
		virtual void Init(const std::string& path, const bool need_binary) noexcept = 0;
		virtual void Log(const char* pFunction_name, const std::string& message) noexcept = 0;
		virtual void LogNumberx64i(const char* pFunction_name, const std::string& message, const int64_t argument) noexcept = 0;
		virtual void LogNumberx64f(const char* pFunction_name, const std::string& message, const double argument) noexcept = 0;
		virtual void LogNumberx32i(const char* pFunction_name, const std::string& message, const int32_t argument) noexcept = 0;
		virtual void LogNumberx32f(const char* pFunction_name, const std::string& message, const float argument) noexcept = 0;
		virtual void Save() noexcept = 0;
		virtual ~ILogMachine() = default;
	};
}
