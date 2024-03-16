#pragma once
// Print System Header
// MurphEngine

#include <iostream>


namespace MurphEngine
{
    
    class PrintSystem
    {
    public:
        virtual void PrintTest();
        virtual void PrintText(const char* text);
        virtual void PrintBold(const char* text);
        virtual void PrintUnderline(const char* text);
        virtual void PrintItalic(const char* text);
    };

}

//TODO: Create versions of print system using guidelines below:

// PrintText(const char* text); // print the text.
// PrintBold(const char* text); // print bold text.
// PrintUnderline(const char* text); // print Underlined text.
// PrintItalic(const char* text); //Print italic text

// web-version
    // print normal text by just printing text. "this is normal"

    // print text by bold tags e.g. "<b> this is bold!</b>"

    // print text by printing underline tags. e.g. "<u> This is underline </u>"

    // print text by printing italic tags. e.g. "<i> This is italic </i>" 

// markdown
    // print normal text by just printing text. "this is normal"

    // print text by bold asterisk e.g. "*this is bold!*"

    // print text by printing underline tags. e.g. "_This is underline_"

    // print text by printing italic tags. e.g. "/This is italic/"

// plain //TODO: doesn't support bold or underline. print basic text.
    // print normal text by just printing text. "this is normal"

    // print text by bold tags e.g. "this is bold!"

    // print text by printing underline tags. e.g. "This is underline"

    // print text by printing italic tags. e.g. "This is italic"
