#include <util/evt.hpp>


void util::EventEmitter::off(const std::string& event) noexcept {
	events.erase(event);
}
