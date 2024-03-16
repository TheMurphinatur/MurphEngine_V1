#include "pch.h"
#include "MarkdownPrint.h"


void MurphEngine::MarkdownPrint::PrintTest()
{
    std::cout << '\n' << "Test Markdown Print Functionality:\n";
    PrintText("This is normal");
    PrintBold("This is bold");
    PrintUnderline("This is underline");
    PrintItalic("This is italic");
    std::cout << '\n';
}

// print normal text by just printing text. "this is normal"
void MurphEngine::MarkdownPrint::PrintText(const char* text)
{
    std::cout << text << '\n';
}

// print text by bold tags e.g. "*this is bold!*"
void MurphEngine::MarkdownPrint::PrintBold(const char* text)
{
    std::cout << '*' << text << '*' << '\n';
}

// print text by printing underline tags. e.g. "_This is underline_"
void MurphEngine::MarkdownPrint::PrintUnderline(const char* text)
{
    std::cout << '_' << text << '_' << '\n';
}

// print text by printing italic tags. e.g. "/This is italic/"
void MurphEngine::MarkdownPrint::PrintItalic(const char* text)
{
    std::cout << '/' << text << '/' << '\n';
}

// markdown
// print normal text by just printing text. "this is normal"

// print text by bold asterisk e.g. "*this is bold!*"

// print text by printing underline tags. e.g. "_This is underline_"

// print text by printing italic tags. e.g. "/This is italic/"