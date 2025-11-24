CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wpedantic

all: main test

main: main.o EventManager.o User.o Organizer.o Attendee.o Event.o Ticket.o
	$(CXX) $(CXXFLAGS) -o main main.o EventManager.o User.o Organizer.o Attendee.o Event.o Ticket.o

main.o: main.cpp EventManager.h User.h Organizer.h Attendee.h Event.h Ticket.h
	$(CXX) $(CXXFLAGS) -c main.cpp

EventManager.o: EventManager.cpp EventManager.h Event.h User.h
	$(CXX) $(CXXFLAGS) -c EventManager.cpp

EventType.o: EventType.cpp EventType.h Event.h 
	$(CXX) $(CXXFLAGS) -c EventType.cpp

EventFactory.o: EventFactory.cpp EventFactory.h Event.h
	$(CXX) $(CXXFLAGS) -c EventFactory.cpp

User.o: User.cpp User.h
	$(CXX) $(CXXFLAGS) -c User.cpp

Organizer.o: Organizer.cpp Organizer.h User.h Event.h EventManager.h
	$(CXX) $(CXXFLAGS) -c Organizer.cpp

Attendee.o: Attendee.cpp Attendee.h User.h EventManager.h Ticket.h
	$(CXX) $(CXXFLAGS) -c Attendee.cpp

Event.o: Event.cpp Event.h
	$(CXX) $(CXXFLAGS) -c Event.cpp

Ticket.o: Ticket.cpp Ticket.h
	$(CXX) $(CXXFLAGS) -c Ticket.cpp

test: test.o EventManager.o User.o Organizer.o Attendee.o Event.o Ticket.o EventType.o EventFactory.o SpecificEvent.o
	$(CXX) $(CXXFLAGS) -o test test.o EventManager.o User.o Organizer.o Attendee.o Event.o Ticket.o EventType.o EventFactory.o SpecificEvent.o

test.o: test.cpp EventManager.h User.h Organizer.h Attendee.h Event.h EventFactory.h EventType.h SpecificEvent.h
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f *.o main test