#include "pch.h"
#include "Logging.h"

std::ofstream m_outFile;

/**
 * \brief Prints message to Log.txt
 * \param logMessage Message to print to file
 */
void MurphEngine::Log::LogToFile(const char* logMessage)
{
    if (!m_outFile.is_open())
    {
        LogToConsole("Error printing to file. File is not open. ");
        LogToConsole(logMessage);
    }
    else
    {
        m_outFile << logMessage << '\n';
    }
}

/**
 * \brief Prints message to console
 * \param logMessage Message to print to console
 */
void MurphEngine::Log::LogToConsole(const char* logMessage)
{
    std::cout << logMessage << '\n';
}

/**
 * \brief Opens Log file for use.
 */
void MurphEngine::Log::InitializeLog()
{
    m_outFile.open("../Logging/Log.txt", std::ios::out | std::ios::trunc); // TODO: move this to a more appropriate area?

    if (!m_outFile.is_open())
    {
        LogToConsole("Error opening file\n");
    }
    else
    {
        LogToConsole("Log.txt opened successfully. writing to file enabled.");
    }
}

/**
 * \brief Closes log file at Engine shutdown
 */
void MurphEngine::Log::EndLogging()
{
    if (!m_outFile.is_open())
    {
        LogToConsole("Error Closing file. file was not open.");
    }
    else
        LogToConsole("Closing file. Writing to file disabled.");

    m_outFile.close();
}
