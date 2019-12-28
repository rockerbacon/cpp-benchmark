#pragma once

#include <vector>
#include <chrono>
#include <functional>
#include "observer.h"

#define BENCHMARK_GENERATE_LABEL_PASTE_EXPAND(label, line) label ## _ ## line
#define BENCHMARK_GENERATE_LABEL_PASTE(label, line) BENCHMARK_GENERATE_LABEL_PASTE_EXPAND(label, line)
#define BENCHMARK_GENERATE_LABEL(label) BENCHMARK_GENERATE_LABEL_PASTE(label, __LINE__)

#define BENCHMARK_EXECUTE_RUN 0
#define BENCHMARK_EVALUATE_RUN 1

#define benchmark(title, runs) \
	benchmark::observer_list* BENCHMARK_GENERATE_LABEL(benchmark_observers_ref);\
	{\
		using namespace benchmark;\
		BENCHMARK_GENERATE_LABEL(benchmark_observers_ref) = &benchmark_observers;\
	}\
	for (auto& o : *BENCHMARK_GENERATE_LABEL(benchmark_observers_ref)) {\
		o.get().notifyBenchmarkBegun(title, runs);\
	}\
	goto BENCHMARK_GENERATE_LABEL(benchmark_begin_execution);\
	while(true) \
		if (true) { \
			for (auto& o : *BENCHMARK_GENERATE_LABEL(benchmark_observers_ref)) {\
				o.get().notifyBenchmarkEnded();\
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
						for (auto& o: *BENCHMARK_GENERATE_LABEL(benchmark_observers_ref)) {\
							o.get().notifyRunBegun();\
						}\
						benchmark_state.next_action = BENCHMARK_EVALUATE_RUN;\
						goto BENCHMARK_GENERATE_LABEL(benchmark_block_begin);\
					}\
\
					else if (benchmark_state.next_action == BENCHMARK_EVALUATE_RUN) {\
						benchmark_state.run_duration = std::chrono::high_resolution_clock::now() - benchmark_state.run_begin;\
						benchmark_state.total_duration += benchmark_state.run_duration;\
						for (auto& o: *BENCHMARK_GENERATE_LABEL(benchmark_observers_ref)) {\
							o.get().notifyRunEnded();\
						}\
						if (++benchmark_state.current_run == runs)\
							break;\
						benchmark_state.next_action = BENCHMARK_EXECUTE_RUN;\
\
					} else\
						BENCHMARK_GENERATE_LABEL(benchmark_block_begin):

#define observe_variables(...) \
	std::list<std::reference_wrapper<benchmark::ObservableVariable>> benchmark_variables_to_observe{__VA_ARGS__};

#define register_observers(...) \
	std::vector<std::reference_wrapper<benchmark::Observer>> benchmark_observers{__VA_ARGS__};

namespace benchmark {
	typedef std::vector<std::reference_wrapper<Observer>> observer_list;

	struct benchmark_state {
		unsigned current_run;
		std::chrono::high_resolution_clock::duration total_duration;
		unsigned next_action;
		std::chrono::high_resolution_clock::time_point run_begin;
		std::chrono::high_resolution_clock::duration run_duration;
	};
/*
	template<typename T>
	void observe_variable(const std::string &variable_label, const T& variable, unsigned observation_mode=observation_mode::CURRENT_VALUE) {
		for (auto o : observers) {
			o->observe_variable(variable_label, variable, observation_mode);
		}
	}
*/
	// dummy for benchmarks without observers
	extern observer_list benchmark_observers;
}
