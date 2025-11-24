// EventType header file

#ifndef EVENTTYPE_H
#define EVENTTYPE_H
#include "Event.h"

class Music : public Event {
	public: 
	  Music(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class Sports : public Event {
	public:
	  Sports(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class Outdoors : public Event {
	public:
	  Outdoors(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class Theater : public Event {
	public:
		Theater(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class Conference : public Event {
	public:
	  Conference(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

#endif // EVENTTYPE_H