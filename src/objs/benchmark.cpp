#include "benchmark.h"

using namespace std;
using namespace benchmark;

list<Observer*> benchmark::observers;

void benchmark::register_observer(Observer *observer) {
	/*
	observer->observe_variable("Run", benchmark::current_run);
	observer->observe_variable("Total execution time", benchmark::benchmark_duration);
	observer->observe_variable("Run execution time", benchmark::run_duration, observation_mode::AVERAGE_VALUE);
	*/
	benchmark::observers.push_back(observer);
}

void benchmark::delete_observers() {
	for (auto o : benchmark::observers) {
		delete o;
	}
}
