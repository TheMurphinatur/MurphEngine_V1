#include "pch.h"
#include "PlainPrint.h"


void MurphEngine::PlainPrint::PrintTest()
{
    std::cout << '\n' << "Test Plain Print Functionality:\n";
    PrintText("This is normal");
    PrintBold("This is bold");
    PrintUnderline("This is underline");
    PrintItalic("This is italic");
    std::cout << '\n';
}

// print normal text by just printing text.
void MurphEngine::PlainPrint::PrintText(const char* text)
{
    std::cout << text << '\n';
}

// print normal text by just printing text.
void MurphEngine::PlainPrint::PrintBold(const char* text)
{
    std::cout << text << '\n';
}
// print normal text by just printing text.
void MurphEngine::PlainPrint::PrintUnderline(const char* text)
{
    std::cout << text << '\n';
}
// print normal text by just printing text.
void MurphEngine::PlainPrint::PrintItalic(const char* text)
{
    std::cout << text << '\n';
}