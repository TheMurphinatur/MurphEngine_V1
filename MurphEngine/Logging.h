#pragma once


#include "fstream"
namespace MurphEngine
{
    namespace Log
    {
        void LogToFile(const char* logMessage);
        void LogToConsole(const char* logMessage);
        void InitializeLog();
        void EndLogging();
    };
}


