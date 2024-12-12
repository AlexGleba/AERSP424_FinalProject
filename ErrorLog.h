// #ifndef LOGGER_H
// #define LOGGER_H

#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class ErrorLog
{
public:
    // Constructor: Initializes the log file
    ErrorLog(const std::string &logFileName = "error_log.txt")
    {
        logFile.open(logFileName, std::ios::out | std::ios::app); // Opens the log file in append mode
        if (!logFile.is_open())
        {
            std::cerr << "Failed to open log file: " << logFileName << std::endl;
        }
    }

    // Destructor: Closes the log file
    ~ErrorLog()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    // Writes an error message to the log file
    void WriteError(const std::string &errorMessage)
    {
        if (logFile.is_open())
        {
            logFile << getCurrentTime() << " - ERROR: " << errorMessage << std::endl;
        }
        else
        {
            std::cerr << "Error logging failed. Could not write to log file." << std::endl;
        }
    }

    // Write a general message
    // Used for warnings, info, etc.
    void WriteMessage(const std::string &message)
    {
        if (logFile.is_open())
        {
            logFile << getCurrentTime() << " - INFO: " << message << std::endl;
        }
        else
        {
            std::cerr << "Error logging failed. Could not write to log file." << std::endl;
        }
    }

private:
    std::ofstream logFile;

    // Get the current date and time as a string
    // format: YYYY-MM-DD HH:MM:SS
    std::string getCurrentTime()
    {
        time_t Time;
        struct tm *time_info;
        char buffer[80];

        time(&Time);
        time_info = localtime(&Time);

        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);
        return std::string(buffer);
    }
};

#endif // ERRORLOG_H
