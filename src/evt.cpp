#include <util/evt>


void util::evt::emitter::off(const std::string& event) {
	events.erase(event);
}
