#pragma once

#include <observable_variable.h>

class observable_variable_mock : public benchmark::observable_variable_interface {
	public:
		std::string label;
		std::string value;
		unsigned number_of_updates;

		observable_variable_mock(const std::string& label, const std::string& value) :
			label(label),
			value(value),
			number_of_updates(0)
		{}

		std::string get_label () const {
			return label;
		}

		std::string get_value_as_string () const {
			return value;
		}

		void update_value() {
			number_of_updates++;
		}
};

