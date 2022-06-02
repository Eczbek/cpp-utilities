#include <util/evt.hpp>


void util::event_emitter::off(const std::string& event) {
	events.erase(event);
}
