#include <assertions-test/test.h>
#include <benchmark.h>

#include "observer_mock.h"

begin_tests {
	test_suite("when executing a single benchmark") {
		test_case("benchmark information should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			register_observers(observer1, observer2);
			benchmark(benchmark_title, number_of_runs) {}

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

			register_observers(observer1, observer2);
			benchmark(benchmark_title, number_of_runs) {}

			assert(observer1.benchmark_begun_notifications, ==, 1);
			assert(observer2.benchmark_begun_notifications, ==, 1);
		};

		test_case("benchmark end should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			register_observers(observer1, observer2);
			benchmark(benchmark_title, number_of_runs) {}

			assert(observer1.benchmark_ended_notifications, ==, 1);
			assert(observer2.benchmark_ended_notifications, ==, 1);
		};


		test_case("benchmark run begin should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			register_observers(observer1, observer2);
			benchmark(benchmark_title, number_of_runs) {}

			assert(observer1.run_begun_notifications, ==, number_of_runs);
			assert(observer2.run_begun_notifications, ==, number_of_runs);
		};

		test_case("benchmark run end should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			register_observers(observer1, observer2);
			benchmark(benchmark_title, number_of_runs) {}

			assert(observer1.run_ended_notifications, ==, number_of_runs);
			assert(observer2.run_ended_notifications, ==, number_of_runs);
		};
	};

	test_suite("when executing multiple benchmarks") {
		test_case("benchmark information should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark1_title("test benchmark 1 information");
			unsigned benchmark1_number_of_runs = 3;
			std::string benchmark2_title("test benchmark 2 information");
			unsigned benchmark2_number_of_runs = 5;

			register_observers(observer1, observer2);
			benchmark(benchmark1_title, benchmark1_number_of_runs) {}

			assert(observer1.benchmark_title_reported, ==, benchmark1_title);
			assert(observer2.benchmark_title_reported, ==, benchmark1_title);

			assert(observer1.number_of_runs_reported, ==, benchmark1_number_of_runs);
			assert(observer2.number_of_runs_reported, ==, benchmark1_number_of_runs);

			benchmark(benchmark2_title, benchmark2_number_of_runs) {}

			assert(observer1.benchmark_title_reported, ==, benchmark2_title);
			assert(observer2.benchmark_title_reported, ==, benchmark2_title);

			assert(observer1.number_of_runs_reported, ==, benchmark2_number_of_runs);
			assert(observer2.number_of_runs_reported, ==, benchmark2_number_of_runs);
		};

		test_case("benchmark begin should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			register_observers(observer1, observer2);

			benchmark(benchmark_title, number_of_runs) {}
			benchmark(benchmark_title, number_of_runs) {}

			assert(observer1.benchmark_begun_notifications, ==, 2);
			assert(observer2.benchmark_begun_notifications, ==, 2);
		};

		test_case("benchmark end should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned number_of_runs = 3;

			register_observers(observer1, observer2);
			benchmark(benchmark_title, number_of_runs) {}
			benchmark(benchmark_title, number_of_runs) {}

			assert(observer1.benchmark_ended_notifications, ==, 2);
			assert(observer2.benchmark_ended_notifications, ==, 2);
		};

		test_case("benchmark run begin should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned benchmark1_number_of_runs = 3;
			unsigned benchmark2_number_of_runs = 4;

			register_observers(observer1, observer2);
			benchmark(benchmark_title, benchmark1_number_of_runs) {}
			benchmark(benchmark_title, benchmark2_number_of_runs) {}

			assert(observer1.run_begun_notifications, ==, benchmark1_number_of_runs+benchmark2_number_of_runs);
			assert(observer2.run_begun_notifications, ==, benchmark1_number_of_runs+benchmark2_number_of_runs);
		};

		test_case("benchmark run end should be correctly reported to all observers") {
			observer_mock observer1;
			observer_mock observer2;

			std::string benchmark_title("test run begun");
			unsigned benchmark1_number_of_runs = 3;
			unsigned benchmark2_number_of_runs = 4;

			register_observers(observer1, observer2);
			benchmark(benchmark_title, benchmark1_number_of_runs) {}
			benchmark(benchmark_title, benchmark2_number_of_runs) {}

			assert(observer1.run_ended_notifications, ==, benchmark1_number_of_runs+benchmark2_number_of_runs);
			assert(observer2.run_ended_notifications, ==, benchmark1_number_of_runs+benchmark2_number_of_runs);
		};
	};
} end_tests;
