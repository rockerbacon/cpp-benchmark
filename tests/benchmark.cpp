#include <assertions-test/test.h>
#include <benchmark.h>

begin_tests {
	test_suite("when executing benchmarks") {
		test_case("benchmark should execute the correct number of runs") {
			unsigned number_of_runs = 10;
			unsigned runs = 0;
			benchmark ("test number of runs", number_of_runs) {
				runs++;
			}
			std::cerr << "RUNS: " << runs << std::endl;
			assert(runs, ==, number_of_runs);
		};
	}
} end_tests;
