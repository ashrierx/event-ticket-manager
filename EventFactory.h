// Event Factory header file

#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H

#include <memory>
#include <string>
#include "Event.h"

class Event;

class EventFactory {
	public:
    static std::shared_ptr<Event> CreateEvent(
		int id,
		const std::string& category,
		const std::string& name,
		float base_price,
		int total_tickets,
		const std::string& tier,
		int organizer_id);
};

#endif // EVENTFACTORY_H