// Specific Event implementation file

#include "SpecificEvent.h"
#include <iostream>

ConcertEvent::ConcertEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Music(id, name, base_price, total_tickets, tier, organizer_id)
{
  std::cout << "Created ConcertEvent: " << name << std::endl;
}

FestivalEvent::FestivalEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Music(id, name, base_price, total_tickets, tier, organizer_id)
{
  std::cout << "Created FestivalEvent: " << name << std::endl;
}

GameEvent::GameEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Sports(id, name, base_price, total_tickets, tier, organizer_id)
{
  std::cout << "Created GameEvent: " << name << std::endl;
}

TournamentEvent::TournamentEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Sports(id, name, base_price, total_tickets, tier, organizer_id)
{
  std::cout << "Created TournamentEvent: " << name << std::endl;
}

SnowEvent::SnowEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Outdoors(id, name, base_price, total_tickets, tier, organizer_id)
{
  std::cout << "Created SnowEvent: " << name << std::endl;
}

HikingEvent::HikingEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Outdoors(id, name, base_price, total_tickets, tier, organizer_id)
{
  std::cout << "Created HikingEvent: " << name << std::endl;
}

PlayEvent::PlayEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Theater(id, name, base_price, total_tickets, tier, organizer_id)
{
  std::cout << "Created PlayEvent: " << name << std::endl;
}

MusicalEvent::MusicalEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Theater(id, name, base_price, total_tickets, tier, organizer_id)
{
  std::cout << "Created MusicalEvent: " << name << std::endl;
}

TechConferenceEvent::TechConferenceEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Conference(id, name, base_price, total_tickets, tier, organizer_id)
{
  std::cout << "Created TechConferenceEvent: " << name << std::endl;
}

BusinessConferenceEvent::BusinessConferenceEvent(int id, const std::string& name, float base_price, int total_tickets, const std::string& tier, int organizer_id) : Conference(id, name, base_price, total_tickets, tier, organizer_id)
{
  std::cout << "Created BusinessConferenceEvent: " << name << std::endl;
}