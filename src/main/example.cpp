#include <stopwatch/stopwatch.h>
#include <benchmark.h>
#include <random>
#include <thread>
#include <iostream>

using namespace benchmark;
using namespace std;

int main() {
	TerminalObserver observer;

	random_device seeder;
	mt19937 random_engine(seeder());
	uniform_int_distribution<int> random_x(-10, 10);
	uniform_int_distribution<long long> random_sleep(300, 500);
	uniform_real_distribution<float> random_y(-1, 1);

	int x;
	float y;
	float squared_x_plus_y;
	chrono::high_resolution_clock::duration execution_time;

	register_observers(observer);

	observe(execution_time, last_run);
	observe_minimum(execution_time, fastest_run);
	observe_maximum(execution_time, slowest_run);
	observe_average(execution_time, average_run);

	observe(x, x_value);
	observe_minimum(x, minimum_x);

	observe(y, y_value);
	observe_maximum(y, maximum_y);

	observe_average(squared_x_plus_y, calculation_average);

	stopwatch stopwatch;
	benchmark("just an example", 10) {
		this_thread::sleep_for(chrono::milliseconds(random_sleep(random_engine)));
		x = random_x(random_engine);
		y = random_y(random_engine);
		squared_x_plus_y = (x+y)*(x+y);

		execution_time = stopwatch.lap_time();
	}

	if (maximum_y.get_value() > minimum_x.get_value()) {
		cout << "The maximum value for y was greater than the minimum value for x" << endl;
	} else {
		cout << "The maximum value for y was smaller than or equal the minimum value for x" << endl;
	}

	return 0;
}

