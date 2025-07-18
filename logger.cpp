#include "logger.h"
#include <iostream>

Logger logger;

void Logger::info(const std::string& message) {
	write(LogLevel::Info, message);
}

void Logger::warn(const std::string& message) {
	write(LogLevel::Warn, message);
}

void Logger::error(const std::string& message) {
	write(LogLevel::Error, message);
}

void Logger::write(LogLevel level, const std::string& message) {
	std::cout << "[" << levelToString(level) << "] " << message << std::endl;
}

std::string Logger::levelToString(LogLevel level) {
	switch (level) {
		case LogLevel::Info: return "INFO";
		case LogLevel::Warn: return "WARN";
		case LogLevel::Error: return "ERROR";
		default: return "UNKNOWN";
	}
}
