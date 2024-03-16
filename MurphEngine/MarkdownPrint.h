#pragma once
#include "PrintSystem.h"
namespace MurphEngine
{

    class MarkdownPrint :
        public MurphEngine::PrintSystem
    {
    public:
        void PrintTest() override;
        void PrintText(const char* text) override;
        void PrintBold(const char* text) override;
        void PrintUnderline(const char* text) override;
        void PrintItalic(const char* text) override;
    };

}


// markdown
    // print normal text by just printing text. "this is normal"

    // print text by bold asterisk e.g. "*this is bold!*"

    // print text by printing underline tags. e.g. "_This is underline_"

    // print text by printing italic tags. e.g. "/This is italic/"
