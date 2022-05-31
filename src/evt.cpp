#include <util/evt.hpp>


void util::evt::emitter::off(const std::string& event) {
	events.erase(event);
}
