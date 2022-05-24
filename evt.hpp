#pragma once

#include <any>
#include <functional>
#include <string>
#include <unordered_map>


namespace util {
	class emitter {
	private:
		std::unordered_map<std::string, std::any> events;

	public:
		template <typename... Parameters, typename Callback>
		void on(const std::string& event, const Callback& callback) {
			events[event] = std::any(std::function<void(Parameters...)>(callback));
		}

		template <typename... Parameters, typename Callback>
		void once(const std::string& event, const Callback& callback) {
			events[event] = std::any(std::function<void(Parameters...)>([&](Parameters... arguments) {
				events.erase(event);
				callback(arguments...);
			}));
		}

		void off(const std::string& event);

		template <typename... Parameters>
		void emit(const std::string& event, Parameters... parameters) {
			if (events.contains(event))
				std::any_cast<std::function<void(Parameters...)>>(events[event])(parameters...);
		}
	};
}
