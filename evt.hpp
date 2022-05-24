#pragma once

#include <any>
#include <functional>
#include <string>
#include <unordered_map>


namespace util {
	struct emitter {
		std::unordered_map<std::string, std::any> events;

		template <typename... Parameters>
		void on(const std::string& event, const std::function<void(Parameters...)>& callback) {
			events[event] = std::any(callback);
		}

		template <typename... Parameters, typename Callback>
		void once(const std::string& event, const Callback& callback) {
			events[event] = std::any(std::function<void(Parameters...)>([&](Parameters... parameters) {
				callback(parameters...);
				events.erase(event);
			}));
		}

		void off(const std::string& event) {
			events.erase(event);
		}

		template <typename... Parameters>
		void emit(const std::string& event, Parameters... parameters) {
			if (events.contains(event))
				std::any_cast<std::function<void(Parameters...)>>(events[event])(parameters...);
		}
	};
}
