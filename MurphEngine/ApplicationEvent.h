#pragma once
#include "Event.h"
namespace MurphEngine
{
    class ApplicationUpdateEvent
        : public Event
    {
    public:
        ApplicationUpdateEvent() { }

        EVENT_CLASS_TYPE(k_Application_Update)
        EVENT_CLASS_CATEGORY(k_Event_Category_Application)
    };


    class ApplicationRenderEvent
        : public Event
    {
    public:
        ApplicationRenderEvent() { }

        EVENT_CLASS_TYPE(k_Application_Render)
            EVENT_CLASS_CATEGORY(k_Event_Category_Application)
    };

}

