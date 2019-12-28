#include <assertions-test/test.h>
#include <observable_variable.h>

using namespace benchmark;

begin_tests {
	test_suite("when observing a variable's current value") {
		test_case("observable variable should hold the correct label") {
			int x = 10;
			observable_variable<int> observable_x("x", x);

			assert(observable_x.get_label(), ==, "x");
		};

		test_case("should observe the correct value") {
			int x = 10;
			observable_variable<int> observable_x("x", x);

			assert(&observable_x.get_value(), ==, &x);
		};

		test_case("should correctly convert value to string") {
			int x = 10;
			observable_variable<int> observable_x("x", x);

			assert(observable_x.get_value_as_string(), ==, std::to_string(x));
		};
	}

	test_suite("when observing a variable's average value") {
		test_case("observable variable should hold the correct label") {
			int x = 10;
			observable_variable_average<int> average_x("x", x);
			average_x.update_value();

			assert(average_x.get_label(), ==, "x");
		};

		test_case("should observe the correct value iteratively") {
			int x;
			observable_variable_average<int> average_x("x", x);

			x = 10;
			average_x.update_value();
			assert(average_x.get_value(), ==, 10);

			x = 30;
			average_x.update_value();
			assert(average_x.get_value(), ==, (10+30)/2);

			x = 2;
			average_x.update_value();
			assert(average_x.get_value(), ==, (10+30+2)/3);

			x = 14;
			average_x.update_value();
			assert(average_x.get_value(), ==, (10+30+2+14)/4);
		};

		test_case("should correctly convert value to string") {
			int x = 10;
			observable_variable_average<int> average_x("x", x);
			average_x.update_value();

			assert(average_x.get_value_as_string(), ==, std::to_string(x));
		};
	}

	test_suite("when observing a variable's minimum value") {
		test_case("observable variable should hold the correct label") {
			int x = 10;
			observable_variable_minimum<int> minimum_x("x", x);

			assert(minimum_x.get_label(), ==, "x");
		};

		test_case("should observe the correct value iteratively") {
			int x;
			observable_variable_minimum<int> minimum_x("x", x);

			x = 10;
			minimum_x.update_value();
			assert(minimum_x.get_value(), ==, 10);

			x = 30;
			minimum_x.update_value();
			assert(minimum_x.get_value(), ==, 10);

			x = 2;
			minimum_x.update_value();
			assert(minimum_x.get_value(), ==, 2);

			x = 14;
			minimum_x.update_value();
			assert(minimum_x.get_value(), ==, 2);
		};

		test_case("should correctly convert value to string") {
			int x = 10;
			observable_variable_minimum<int> minimum_x("x", x);
			minimum_x.update_value();

			assert(minimum_x.get_value_as_string(), ==, std::to_string(x));
		};
	}

	test_suite("when observing a variable's maximum value") {
		test_case("observable variable should hold the correct label") {
			int x = 10;
			observable_variable_maximum<int> maximum_x("x", x);

			assert(maximum_x.get_label(), ==, "x");
		};

		test_case("should observe the correct value iteratively") {
			int x;
			observable_variable_maximum<int> maximum_x("x", x);

			x = 10;
			maximum_x.update_value();
			assert(maximum_x.get_value(), ==, 10);

			x = 30;
			maximum_x.update_value();
			assert(maximum_x.get_value(), ==, 30);

			x = 2;
			maximum_x.update_value();
			assert(maximum_x.get_value(), ==, 30);

			x = 14;
			maximum_x.update_value();
			assert(maximum_x.get_value(), ==, 30);
		};

		test_case("should correctly convert value to string") {
			int x = 10;
			observable_variable_maximum<int> maximum_x("x", x);
			maximum_x.update_value();

			assert(maximum_x.get_value_as_string(), ==, std::to_string(x));
		};
	}
} end_tests;

