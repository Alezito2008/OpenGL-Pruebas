#pragma once
#include <string>

enum class LogLevel {
	Info,
	Warn,
	Error
};

class Logger {
public:
	void info(const std::string& message);
	void warn(const std::string& message);
	void error(const std::string& message);

private:
	std::string levelToString(LogLevel level);
	void write(LogLevel level, const std::string& message);
};

extern Logger logger;
