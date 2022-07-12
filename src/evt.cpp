#include <util/evt>


void util::EventEmitter::off(const std::string& event) noexcept {
	events.erase(event);
}
