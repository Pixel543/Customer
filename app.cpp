#include <app.h>

//Logger implementation
Logger::Logger(const std::string& filename)
{
    logFile.open(filename, std::ios::app);
    if (!logFile) std::cerr << "Error opening log file: " << filename << std::endl;
}

Logger::~Logger()
{
    if(logFile.is_open()) logFile.close();
}

void Logger::log(const std::string& message)
{
    time_t now = time(nullptr);
    char buff[20];
    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", localtime(&now));
}

