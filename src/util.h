#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <chrono>
#include <vector>


namespace util {
	namespace time {
		template <typename T = std::chrono::milliseconds>
		long now () {
			return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	}

	namespace console {
		void ignoreLine ();

		template <typename T>
		T prompt (std::string message = "", bool repeat = false) {
			T result = T();
			do {
				std::cout << message;
				std::cin >> result;
				if (!std::cin.fail()) {
					return result;
				}
				util::console::ignoreLine();
			} while (repeat);
		}
	}

	namespace file {
		std::string read (std::string path);

		void write (std::string path, std::string content);
	}

	namespace random {
		double get (double max, double min = 0.0, bool inclusive = false);
	}

	namespace string {
		std::vector<std::string> split (std::string string, std::string delimiter = "");

		std::vector<std::string> split (std::string string, char delimiter);

		std::string join (std::vector<std::string> array, std::string delimiter = ", ");
	}

	namespace vector {
		template <typename T>
		std::vector<T> erase (std::vector<T> vector, int start, int erase = 1) {
			for (int i = 0; i < erase; ++i) {
				vector.erase(vector.begin() + start);
			}
			return vector;
		}

		template <typename T>
		std::vector<T> splice (std::vector<T> vector, int start, int erase, T insert) {
			vector = util::vector::erase(vector, start, erase);
			vector.insert(vector.begin() + start, insert);
			return vector;
		}

		template <typename T>
		std::vector<T> splice (std::vector<T> vector, int start, int erase, std::vector<T> insert) {
			vector = util::vector::erase(vector, start, erase);
			vector.insert(vector.begin() + start, insert.begin(), insert.end());
			return vector;
		}

		template <typename T>
		std::vector<T> slice (std::vector<T> vector, int start, int end = -1) {
			if (start < 0) {
				start += vector.size();
			}
			if (end < 0) {
				end += vector.size();
			}
			std::vector<T> slice;
			for (int i = start; i < end; ++i) {
				slice.push_back(vector[i]);
			}
			return slice;
		}
	}
}

#endif