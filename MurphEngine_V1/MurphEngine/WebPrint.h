#pragma once
#include "PrintSystem.h"


namespace MurphEngine
{
    
    class WebPrint :
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


// web-version
    // print normal text by just printing text. "this is normal"

    // print text by bold tags e.g. "<b> this is bold!</b>"

    // print text by printing underline tags. e.g. "<u> This is underline </u>"

    // print text by printing italic tags. e.g. "<i> This is italic </i>" 