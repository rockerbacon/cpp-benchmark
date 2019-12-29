#pragma once

#include <string>

namespace benchmark {
	class observable_variable_interface {
		public:
			virtual std::string get_label () const = 0;
			virtual std::string get_value_as_string () const = 0;
			virtual void update_value () = 0;
	};

	template<typename T>
	class observable_variable : public observable_variable_interface {
		private:
			const std::string label;
			const T& value;
		public:
			observable_variable(const std::string& label, const T& value) :
				label(label),
				value(value)
			{}

			std::string get_label () const {
				return label;
			}

			std::string get_value_as_string () const {
				return std::to_string(value);
			}

			const T& get_value() const {
				return value;
			}

			virtual void update_value () {}
	};

	template<typename T>
	class observable_variable_average : public observable_variable<T> {
		private:
			const T& value;
			T average;
			unsigned number_of_samples;
		public:
			observable_variable_average (const std::string& label, const T& variable) :
				observable_variable<T>(label, average),
				value(variable),
				number_of_samples(0)
			{}

			void update_value() {
				if (number_of_samples == 0) {
					average = value;
				} else {
					average = (average*number_of_samples + value)/(number_of_samples+1);
				}
				number_of_samples++;
			}
	};

	template<typename T>
	class observable_variable_maximum : public observable_variable<T> {
		private:
			const T& value;
			T maximum;
			bool maximum_not_set;
		public:
			observable_variable_maximum (const std::string &label, const T& variable) :
				observable_variable<T>(label, maximum),
				value(variable),
				maximum_not_set(true)
			{}

			void update_value() {
				if (maximum_not_set || value > maximum) {
					maximum = value;
					maximum_not_set = false;
				}
			}
	};

	template<typename T>
	class observable_variable_minimum : public observable_variable<T> {
		private:
			const T& value;
			T minimum;
			bool minimum_not_set;
		public:
			observable_variable_minimum (const std::string &label, const T& variable) :
				observable_variable<T>(label, minimum),
				value(variable),
				minimum_not_set(true)
			{}

			void update_value () {
				if (minimum_not_set || value < minimum) {
					minimum = value;
					minimum_not_set = false;
				}
			}
	};
}
