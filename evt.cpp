#include "./evt.hpp"


void util::emitter::off(const std::string& event) {
	events.erase(event);
}
