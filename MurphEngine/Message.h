#pragma once

namespace MurphEngine
{
    class Message
    {
        const char* id;
public:

        Message(const char* id)
            :id(id)
        {
        
        }

        const char* GetID() const { return id; }
    };

}
