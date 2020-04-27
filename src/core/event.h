//
// Created by novasurfer on 4/20/20.
// Based on http://bitsquid.blogspot.com/2011/02/managing-decoupling-part-2-polling.html
//

#ifndef SCARECROW2D_EVENT_H
#define SCARECROW2D_EVENT_H

#include "collections/arr.h"
#include "core/types.h"
#include <cstdint>

namespace sc2d
{

    enum class EventType
    {
        INP_TOGGLE_MENU
    };

    struct EventHeader
    {
        EventType type;
        u32 size;
    };
    constexpr const size_t SIZE_EVENT_HEADER = sizeof(EventHeader);

//    struct ButtonPressedEvent
//    {
//        u32 keycode;
//        double test_data;
//    };


    /**
     * [event_1_enum] [event_1_data] [event_2_enum] [event_2_data]
     */
    template <size_t MAX_EVENTS>
    struct EventQueue
    {
        template <typename T>
        void write(EventType type, const T& event);

        arr<char, MAX_EVENTS> stream;

    private:
        void write(EventType type, u32 size, const void* event);
    };

    template <size_t MAX_EVENTS>
    void EventQueue<MAX_EVENTS>::write(EventType type, u32 size, const void* event)
    {
        constexpr static size_t header_size = sizeof(EventHeader);
        static size_t event_idx;
        const size_t offset = header_size + size;
        DBG_RETURN_IF(stream.size() < event_idx + offset, "array overflow");

        EventHeader event_header;
        event_header.type = type;
        event_header.size = size;

        stream.insert_at((char*)&event_header, event_idx, header_size);
        stream.insert_at((char*)event, event_idx + header_size, size);
        event_idx += offset;
    }

    template <size_t MAX_EVENTS>
    template <typename T>
    void EventQueue<MAX_EVENTS>::write(EventType type, const T& event)
    {
        write(type, sizeof(T), &event);
    }

    /*
     * * * * * EXAMPLE:

    sc2d::EventStream<200> events;
    sc2d::ButtonPressedEvent ev;
    sc2d::ButtonPressedEvent ev2;

    ev.keycode = 455;
    ev.test_data = 5.6;
    ev2.keycode = 121;
    ev2.test_data = 3.5;

    events.write(sc2d::EventType::BUTTON_PRESSED, ev);
    events.write(sc2d::EventType::BUTTON_PRESSED, ev2);

    const size_t size = events.stream.size();
    uint32_t read = 0;

    while(read < size) {
        const sc2d::EventHeader* header = (sc2d::EventHeader*)&events.stream[read];
        const char* data = (char*)&header[1];
        read += sizeof(*header) + header->size;

        switch(header->type) {
        case sc2d::EventType::BUTTON_PRESSED: {
            const sc2d::ButtonPressedEvent btnev = *(sc2d::ButtonPressedEvent*)data;
            log_info_cmd("%d, %f", btnev.keycode, btnev.test_data);
        } break;
        default:
            log_err_cmd("no such event");
            break;
        }
    }

     * * * * *
     */
}

#endif //SCARECROW2D_EVENT_H
