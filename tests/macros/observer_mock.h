#pragma once

#include <observer.h>

class observer_mock : public benchmark::Observer {
	public:
		std::string benchmark_title_reported;
		unsigned number_of_runs_reported;
		unsigned benchmark_begun_notifications;
		unsigned run_begun_notifications;
		unsigned run_ended_notifications;
		unsigned benchmark_ended_notifications;

		observer_mock() :
			number_of_runs_reported(0),
			benchmark_begun_notifications(0),
			run_begun_notifications(0),
			run_ended_notifications(0),
			benchmark_ended_notifications(0)
		{}

		void notifyBenchmarkBegun(const std::string& benchmarkTitle, unsigned numberOfRuns) {
			benchmark_title_reported = benchmarkTitle;
			number_of_runs_reported = numberOfRuns;
			benchmark_begun_notifications++;
		}

		void notifyRunBegun() {
			run_begun_notifications++;
		}

		void notifyRunEnded() {
			run_ended_notifications++;
		}

		void notifyBenchmarkEnded() {
			benchmark_ended_notifications++;
		}

		auto& list_variables_being_observed() {
			return variables_to_observe;
		}
};

