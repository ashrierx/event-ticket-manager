// Specific Event header file

#ifndef SPECIFICEVENT_H
#define SPECIFICEVENT_H

#include "EventType.h"

class ConcertEvent : public Music {
	public:
    ConcertEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class FestivalEvent : public Music {
	public:
    FestivalEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class GameEvent : public Sports {
	public:
    GameEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class TournamentEvent : public Sports {
	public:
    TournamentEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class SnowEvent : public Outdoors {
	public:
    SnowEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class HikingEvent : public Outdoors {
	public:
    HikingEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class PlayEvent : public Theater {
	public:
    PlayEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class MusicalEvent : public Theater {
	public:
    MusicalEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class TechConferenceEvent : public Conference {
	public:
    TechConferenceEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

class BusinessConferenceEvent : public Conference {
	public:
    BusinessConferenceEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id);
};

#endif // SPECIFICEVENT_H