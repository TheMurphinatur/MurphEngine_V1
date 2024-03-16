#include "pch.h"
#include "WebPrint.h"

void MurphEngine::WebPrint::PrintTest()
{
    std::cout << '\n' << "Test Web Print Functionality:\n";
    PrintText("This is normal");
    PrintBold("This is bold");
    PrintUnderline("This is underline");
    PrintItalic("This is italic");
    std::cout << '\n';
}

// print normal text by just printing text. "this is normal"
void MurphEngine::WebPrint::PrintText(const char* text)
{
    std::cout << text << '\n';
}

// print text by bold tags e.g. "<b> this is bold!</b>"
void MurphEngine::WebPrint::PrintBold(const char* text)
{
    std::cout << "<b>" << text << "</b>" << '\n';
}

// print text by printing underline tags. e.g. "<u> This is underline </u>"
void MurphEngine::WebPrint::PrintUnderline(const char* text)
{
    std::cout << "<u>" << text << "</u>" << '\n';
}

// print text by printing italic tags. e.g. "<i> This is italic </i>"
void MurphEngine::WebPrint::PrintItalic(const char* text)
{
    std::cout << "<i>" << text << "</i>" << '\n';
}


