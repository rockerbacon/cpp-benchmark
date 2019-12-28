#include <assertions-test/test.h>
#include <benchmark.h>

#include "observer_mock.h"

begin_tests {
	test_suite("when executing benchmarks") {
		test_case("benchmark should execute the correct number of runs") {
			unsigned number_of_runs = 10;
			unsigned runs = 0;
			benchmark ("test number of runs", number_of_runs) {
				runs++;
			}
			assert(runs, ==, number_of_runs);
		};
	}

	test_suite("when observing variables in a single benchmark") {
		test_case("benchmark information should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			benchmark(benchmark_title, number_of_runs, observer1, observer2) {}

			assert(observer1.benchmark_title_reported, ==, benchmark_title);
			assert(observer2.benchmark_title_reported, ==, benchmark_title);

			assert(observer1.number_of_runs_reported, ==, number_of_runs);
			assert(observer2.number_of_runs_reported, ==, number_of_runs);
		};

		test_case("benchmark begin should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			benchmark(benchmark_title, number_of_runs, observer1, observer2) {}

			assert(observer1.benchmark_begun_notifications, ==, 1);
			assert(observer2.benchmark_begun_notifications, ==, 1);
		};

		test_case("benchmark end should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			benchmark(benchmark_title, number_of_runs, observer1, observer2) {}

			assert(observer1.benchmark_ended_notifications, ==, 1);
			assert(observer2.benchmark_ended_notifications, ==, 1);
		};


		test_case("benchmark run begin should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			benchmark(benchmark_title, number_of_runs, observer1, observer2) {}

			assert(observer1.run_begun_notifications, ==, number_of_runs);
			assert(observer2.run_begun_notifications, ==, number_of_runs);
		};

		test_case("benchmark run end should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			benchmark(benchmark_title, number_of_runs, observer1, observer2) {}

			assert(observer1.run_ended_notifications, ==, number_of_runs);
			assert(observer2.run_ended_notifications, ==, number_of_runs);
		};
	};
} end_tests;
