#include <assertions-test/test.h>
#include <benchmark.h>

#include "observer_mock.h"

bool compare_observable_variables(benchmark::ObservableVariable* a, benchmark::ObservableVariable* b) {
	return a->get_label() < b->get_label();
}

begin_tests {
	test_suite("when declaring variables to be observed") {
		test_case("all observers should add variables to their observation list") {
			observer_mock observer1, observer2;

			int variable_a = 123;
			short variable_b = 22;

			register_observers(observer1, observer2);
			observe_variable(variable_a, benchmark::observation_mode::CURRENT_VALUE);
			observe_variable(variable_b, benchmark::observation_mode::CURRENT_VALUE);

			std::vector<benchmark::ObservableVariable*> observer1_observation_list {
				observer1.list_variables_being_observed().begin(),
				observer1.list_variables_being_observed().end()
			};

			std::vector<benchmark::ObservableVariable*> observer2_observation_list {
				observer1.list_variables_being_observed().begin(),
				observer1.list_variables_being_observed().end()
			};

			assert(observer1_observation_list.size(), ==, 2);
			assert(observer2_observation_list.size(), ==, 2);

			std::sort(observer1_observation_list.begin(), observer1_observation_list.end(), compare_observable_variables);
			std::sort(observer2_observation_list.begin(), observer2_observation_list.end(), compare_observable_variables);

			auto observer1_variable_a = observer1_observation_list[0];
			auto observer1_variable_b = observer1_observation_list[1];

			auto observer2_variable_a = observer2_observation_list[0];
			auto observer2_variable_b = observer2_observation_list[1];

			assert(observer1_variable_a->get_label(), ==, "variable_a");
			assert(observer1_variable_b->get_label(), ==, "variable_b");

			assert(observer2_variable_a->get_label(), ==, "variable_a");
			assert(observer2_variable_b->get_label(), ==, "variable_b");
		};

		test_case("observers should add variables with average observation mode") {
			observer_mock observer;

			int variable_a = 123;

			register_observers(observer);
			observe_variable(
				variable_a,
				benchmark::observation_mode::AVERAGE_VALUE
			);

			assert(observer.list_variables_being_observed().size(), ==, 1);

			auto observer_variable_a = observer.list_variables_being_observed().front();

			assert(observer_variable_a->get_label(), ==, "variable_a (avg)");
		};

		test_case("observers should add variables with minimum observation mode") {
			observer_mock observer;

			int variable_a = 123;

			register_observers(observer);
			observe_variable(
				variable_a,
				benchmark::observation_mode::MINIMUM_VALUE
			);

			assert(observer.list_variables_being_observed().size(), ==, 1);

			auto observer_variable_a = observer.list_variables_being_observed().front();

			assert(observer_variable_a->get_label(), ==, "variable_a (min)");
		};

		test_case("observers should add variables with maximum observation mode") {
			observer_mock observer;

			int variable_a = 123;

			register_observers(observer);
			observe_variable(
				variable_a,
				benchmark::observation_mode::MAXIMUM_VALUE
			);

			assert(observer.list_variables_being_observed().size(), ==, 1);

			auto observer_variable_a = observer.list_variables_being_observed().front();

			assert(observer_variable_a->get_label(), ==, "variable_a (max)");
		};

		test_case("observers should add variables with multiple observation modes") {
			observer_mock observer;

			int variable_a = 123;

			register_observers(observer);
			observe_variable(
				variable_a,
				benchmark::observation_mode::AVERAGE_VALUE
			|	benchmark::observation_mode::MINIMUM_VALUE
			);

			std::vector<benchmark::ObservableVariable*> observation_list {
				observer.list_variables_being_observed().begin(),
				observer.list_variables_being_observed().end()
			};

			assert(observation_list.size(), ==, 2);

			sort(observation_list.begin(), observation_list.end(), compare_observable_variables);

			auto observer_variable_a_avg = observation_list[0];
			auto observer_variable_a_min = observation_list[1];

			assert(observer_variable_a_avg->get_label(), ==, "variable_a (avg)");
			assert(observer_variable_a_min->get_label(), ==, "variable_a (min)");
		};
	}
} end_tests;

