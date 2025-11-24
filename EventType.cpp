// EventType implementation file

#include "EventType.h"

Music::Music(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Event(id, "Music", name, base_price, total_tickets, tier, organizer_id) {
}

Sports::Sports(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Event(id, "Sports", name, base_price, total_tickets, tier, organizer_id) {
}

Outdoors::Outdoors(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Event(id, "Outdoors", name, base_price, total_tickets, tier, organizer_id) {
}

Theater::Theater(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Event(id, "Theater", name, base_price, total_tickets, tier, organizer_id) {
}

Conference::Conference(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Event(id, "Conference", name, base_price, total_tickets, tier, organizer_id) {
}