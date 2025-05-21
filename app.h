#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

// ============== Logger ==============
class Logger
{
private:
    std::ofstream logFile;

public:
    Logger(const std::string& filename);
    ~Logger();
    void log(const std::string& message);
};