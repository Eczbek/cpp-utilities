#include <util/evt.hpp>


void util::EventEmitter::off(const std::string& event) {
	events.erase(event);
}
