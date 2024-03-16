#pragma once
#include "PrintSystem.h"
namespace MurphEngine
{

    class PlainPrint :
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

// plain //TODO: doesn't support bold or underline. print basic text.
    // print normal text by just printing text. "this is normal"

    // print text by bold tags e.g. "this is bold!"

    // print text by printing underline tags. e.g. "This is underline"

    // print text by printing italic tags. e.g. "This is italic"
