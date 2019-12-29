#include <assertions-test/test.h>
#include <benchmark.h>

#include "observer_mock.h"
#include "observable_variable_mock.h"

using namespace std;
using namespace benchmark;

bool compare_observable_variables(const benchmark::observable_variable_interface& a, const benchmark::observable_variable_interface& b) {
	return a.get_label() < b.get_label();
}

begin_tests {
	test_suite("when declaring variables to be observed") {
		test_case("all observers should add variables to their observation list") {
			observer_mock observer1, observer2;

			int variable_a = 123;
			short variable_b = 22;

			register_observers(observer1, observer2);
			observe(variable_a, variable_a_value);
			observe(variable_b, variable_b_value);

			vector<reference_wrapper<observable_variable_interface>> observer1_observation_list {
				observer1.list_variables_being_observed()->begin(),
				observer1.list_variables_being_observed()->end()
			};

			vector<reference_wrapper<observable_variable_interface>> observer2_observation_list {
				observer1.list_variables_being_observed()->begin(),
				observer1.list_variables_being_observed()->end()
			};

			assert(observer1_observation_list.size(), ==, 2);
			assert(observer2_observation_list.size(), ==, 2);

			std::sort(observer1_observation_list.begin(), observer1_observation_list.end(), compare_observable_variables);
			std::sort(observer2_observation_list.begin(), observer2_observation_list.end(), compare_observable_variables);

			auto observer1_variable_a = observer1_observation_list[0];
			auto observer1_variable_b = observer1_observation_list[1];

			auto observer2_variable_a = observer2_observation_list[0];
			auto observer2_variable_b = observer2_observation_list[1];

			assert(observer1_variable_a.get().get_label(), ==, "variable_a_value");
			assert(observer1_variable_b.get().get_label(), ==, "variable_b_value");

			assert(observer2_variable_a.get().get_label(), ==, "variable_a_value");
			assert(observer2_variable_b.get().get_label(), ==, "variable_b_value");
		};

		test_case("observers should add variables with average observation mode") {
			observer_mock observer;

			int variable_a = 123;

			register_observers(observer);
			observe_average(variable_a, variable_a_average);

			assert(observer.list_variables_being_observed()->size(), ==, 1);

			auto observer_variable_a = observer.list_variables_being_observed()->front();

			assert(observer_variable_a.get().get_label(), ==, "variable_a_average");
		};

		test_case("observers should add variables with minimum observation mode") {
			observer_mock observer;

			int variable_a = 123;

			register_observers(observer);
			observe_minimum(variable_a, variable_a_minimum);

			assert(observer.list_variables_being_observed()->size(), ==, 1);

			auto observer_variable_a = observer.list_variables_being_observed()->front();

			assert(observer_variable_a.get().get_label(), ==, "variable_a_minimum");
		};

		test_case("observers should add variables with maximum observation mode") {
			observer_mock observer;

			int variable_a = 123;

			register_observers(observer);
			observe_maximum(variable_a, variable_a_maximum);

			assert(observer.list_variables_being_observed()->size(), ==, 1);

			auto observer_variable_a = observer.list_variables_being_observed()->front();

			assert(observer_variable_a.get().get_label(), ==, "variable_a_maximum");
		};

		test_case("observed values should be accessible") {
			observer_mock observer;

			int variable_a = 123;

			register_observers(observer);
			observe(variable_a, variable_being_observed);

			assert(variable_being_observed.get_value(), ==, variable_a);
		};
	}

	test_suite("when running benchmark with variables being observed") {
		test_case("should update variables being observed once for each run") {
			observer_mock observer1, observer2;
			observable_variable_mock variable_being_observed("variable_being_observed", "123");
			unsigned number_of_runs = 5;

			register_observers(observer1, observer2); // this macro declares 'benchmark_variables_to_observe'
			benchmark_variables_to_observe.emplace_back(variable_being_observed);

			benchmark("check variable observation", number_of_runs) {}

			assert(variable_being_observed.number_of_updates, ==, number_of_runs);
		};
	};
} end_tests;

