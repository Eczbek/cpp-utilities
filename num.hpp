#pragma once

#include <numbers>


namespace util {
	namespace num {
		template <typename Number>
		constexpr Number tau_v = std::numbers::pi_v<Number> * 2;

		constexpr double tau = util::num::tau_v<double>;
	}
}