// Event Factory implementation file

#include "EventFactory.h"
#include "SpecificEvent.h"
#include "Event.h"

std::shared_ptr<Event> EventFactory::CreateEvent(
	int id,
	const std::string& category,
	const std::string& name,
	float base_price,
	int total_tickets,
	const std::string& tier,
	int organizer_id)
{
	// Music events
	if (category == "Music" || category == "Concert") {
		return std::make_shared<ConcertEvent>(id, name, base_price, total_tickets, tier, organizer_id);
	}
	else if (category == "Festival") {
		return std::make_shared<FestivalEvent>(id, name, base_price, total_tickets, tier, organizer_id);
	}
	// Sports events
	else if (category == "Sports" || category == "Game") {
		return std::make_shared<GameEvent>(id, name, base_price, total_tickets, tier, organizer_id);
	}
	else if (category == "Tournament") {
		return std::make_shared<TournamentEvent>(id, name, base_price, total_tickets, tier, organizer_id);
	}
	// Outdoors events
	else if (category == "Outdoors" || category == "Snow") {
		return std::make_shared<SnowEvent>(id, name, base_price, total_tickets, tier, organizer_id);
	}
	else if (category == "Hiking") {
		return std::make_shared<HikingEvent>(id, name, base_price, total_tickets, tier, organizer_id);
	}
	// Theater events
	else if (category == "Theater" || category == "Play") {
		return std::make_shared<PlayEvent>(id, name, base_price, total_tickets, tier, organizer_id);
	}
	else if (category == "Musical") {
		return std::make_shared<MusicalEvent>(id, name, base_price, total_tickets, tier, organizer_id);
	}
	// Conference events
	else if (category == "Conference" || category == "Tech Conference") {
		return std::make_shared<TechConferenceEvent>(id, name, base_price, total_tickets, tier, organizer_id);
	}
	else if (category == "Business Conference") {
		return std::make_shared<BusinessConferenceEvent>(id, name, base_price, total_tickets, tier, organizer_id);
	}
	
	return std::make_shared<Event>(id, category, name, base_price, total_tickets, tier, organizer_id);
}