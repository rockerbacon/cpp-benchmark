#include <assertions-test/test.h>
#include <benchmark.h>
#include <chrono>

tests {
	test_suite("when executing a single benchmark") {
		test_case("benchmark should execute the correct number of runs") {
			unsigned number_of_runs = 10;
			unsigned runs = 0;
			benchmark ("test number of runs", number_of_runs) {
				runs++;
			}
			assert(runs, ==, number_of_runs);
		};

		test_case("average benchmark overhead should be less than 500ns") {
			using namespace std::chrono_literals;

			unsigned runs = 1000;
			auto benchmark_begin = std::chrono::high_resolution_clock::now();
			benchmark("test overhead", runs) {}
			auto benchmark_overhead = (std::chrono::high_resolution_clock::now() - benchmark_begin)/runs;
			assert((benchmark_overhead < 500ns), ==, true);
		};
	}

	test_suite("when executing multiple benchmarks") {
		test_case("benchmarks should execute the correct number of runs") {
			unsigned benchmark1_number_of_runs = 10;
			unsigned benchmark2_number_of_runs = 5;
			unsigned benchmark1_runs = 0;
			unsigned benchmark2_runs = 0;

			benchmark ("test number of runs", benchmark1_number_of_runs) {
				benchmark1_runs++;
			}
			assert(benchmark1_runs, ==, benchmark1_number_of_runs);

			benchmark ("test number of runs", benchmark2_number_of_runs) {
				benchmark2_runs++;
			}
			assert(benchmark2_runs, ==, benchmark2_number_of_runs);
		};
	}
};
