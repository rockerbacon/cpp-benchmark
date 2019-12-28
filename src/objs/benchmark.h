#pragma once

#include <chrono>
#include <functional>
#include "observer.h"

#define BENCHMARK_GENERATE_LABEL_PASTE_EXPAND(label, line) label ## _ ## line
#define BENCHMARK_GENERATE_LABEL_PASTE(label, line) BENCHMARK_GENERATE_LABEL_PASTE_EXPAND(label, line)
#define BENCHMARK_GENERATE_LABEL(label) BENCHMARK_GENERATE_LABEL_PASTE(label, __LINE__)

#define BENCHMARK_EXECUTE_RUN 0
#define BENCHMARK_EVALUATE_RUN 1

#define benchmark(title, runs) \
	std::reference_wrapper<benchmark::Observer>* BENCHMARK_GENERATE_LABEL(benchmark_observers_ref);\
	size_t BENCHMARK_GENERATE_LABEL(benchmark_observers_length);\
	{\
		using namespace benchmark;\
		BENCHMARK_GENERATE_LABEL(benchmark_observers_ref) = benchmark_observers;\
		BENCHMARK_GENERATE_LABEL(benchmark_observers_length) = sizeof(benchmark_observers)/sizeof(std::reference_wrapper<benchmark::Observer>);\
		std::cerr << BENCHMARK_GENERATE_LABEL(benchmark_observers_length) << std::endl;\
	}\
	for (size_t o = 0; o < BENCHMARK_GENERATE_LABEL(benchmark_observers_length); o++) {\
		BENCHMARK_GENERATE_LABEL(benchmark_observers_ref)[o].get().notifyBenchmarkBegun(title, runs);\
	}\
	goto BENCHMARK_GENERATE_LABEL(benchmark_begin_execution);\
	while(true) \
		if (true) { \
			for (size_t o = 0; o < BENCHMARK_GENERATE_LABEL(benchmark_observers_length); o++) {\
				BENCHMARK_GENERATE_LABEL(benchmark_observers_ref)[o].get().notifyBenchmarkEnded();\
			}\
			break;\
		} else\
			BENCHMARK_GENERATE_LABEL(benchmark_begin_execution): \
				for(benchmark::benchmark_state benchmark_state {\
					0,\
					std::chrono::high_resolution_clock::duration(0),\
					BENCHMARK_EXECUTE_RUN,\
					std::chrono::high_resolution_clock::time_point(),\
					std::chrono::high_resolution_clock::duration()\
				}; ; )\
\
					if(benchmark_state.next_action == BENCHMARK_EXECUTE_RUN) {\
						benchmark_state.run_begin = std::chrono::high_resolution_clock::now();\
						for (size_t o = 0; o < BENCHMARK_GENERATE_LABEL(benchmark_observers_length); o++) {\
							BENCHMARK_GENERATE_LABEL(benchmark_observers_ref)[o].get().notifyRunBegun();\
						}\
						benchmark_state.next_action = BENCHMARK_EVALUATE_RUN;\
						goto BENCHMARK_GENERATE_LABEL(benchmark_block_begin);\
					}\
\
					else if (benchmark_state.next_action == BENCHMARK_EVALUATE_RUN) {\
						benchmark_state.run_duration = std::chrono::high_resolution_clock::now() - benchmark_state.run_begin;\
						benchmark_state.total_duration += benchmark_state.run_duration;\
						for (size_t o = 0; o < BENCHMARK_GENERATE_LABEL(benchmark_observers_length); o++) {\
							BENCHMARK_GENERATE_LABEL(benchmark_observers_ref)[o].get().notifyRunEnded();\
						}\
						if (++benchmark_state.current_run == runs)\
							break;\
						benchmark_state.next_action = BENCHMARK_EXECUTE_RUN;\
\
					} else\
						BENCHMARK_GENERATE_LABEL(benchmark_block_begin):

#define register_observers(...) \
	benchmark::observer_list benchmark_observers = {__VA_ARGS__};

#define observe_variable(variable_label, observation_mode)\
	{\
		using namespace benchmark;\
		static_assert(sizeof(benchmark_observers) > 0, "cannot observe variables before registering observers");\
	}\
	for (auto o : benchmark_observers) {\
		o.get().observe_variable(#variable_label, variable_label, observation_mode);\
	}

namespace benchmark {
	typedef std::reference_wrapper<Observer> observer_list[];

	struct benchmark_state {
		unsigned current_run;
		std::chrono::high_resolution_clock::duration total_duration;
		unsigned next_action;
		std::chrono::high_resolution_clock::time_point run_begin;
		std::chrono::high_resolution_clock::duration run_duration;
	};

	// dummy for benchmarks without observers
	observer_list benchmark_observers = {};

	// dummy for checking observer registration
	void registered_observers();
}

