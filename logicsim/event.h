#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

typedef struct EventLess {
        //write the operator() required to make this a functor that compares Events by time
        bool operator()(const Event* lhs, const Event* rhs) const
        {
            // true when lhs happens EARLIER than rhs -> earliest event has priority (min-heap)
            return lhs->time < rhs->time;
        }
} EventLess;
	
#endif
