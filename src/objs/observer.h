#pragma once

#include <sstream>
#include <list>
#include <fstream>
#include <functional>

#include "observable_variable.h"

namespace benchmark {
	class Observer {
		protected:
			std::list<std::reference_wrapper<observable_variable_interface>>* variables_to_observe;
		public:
			virtual void notifyBenchmarkBegun (const std::string& benchmark_title, unsigned number_of_runs) = 0;
			virtual void notifyRunBegun (void) = 0;
			virtual void notifyRunEnded (void) = 0;
			virtual void notifyBenchmarkEnded (void) = 0;

			void set_variables_to_observe(decltype(variables_to_observe) variables_to_observe);
	};

	class TerminalObserver : public Observer {
		public:
			TerminalObserver (void) = default;

			void notifyBenchmarkBegun (const std::string& benchmarkTitle, unsigned numberOfRuns);
			void notifyRunBegun (void);
			void notifyRunEnded (void);
			void notifyBenchmarkEnded (void);
	};

	class TextFileObserver : public Observer {
		private:
			std::ofstream outputFile;
		public:
			TextFileObserver (const std::string& outputFilePath);
			~TextFileObserver (void);

			void notifyBenchmarkBegun (const std::string &benchmarkTitle, unsigned numberOfRuns);
			void notifyRunBegun (void);
			void notifyRunEnded (void);
			void notifyBenchmarkEnded (void);

	};

	class TsvFileObserver : public Observer {
		private:
			std::ofstream outputFile;
		public:
			TsvFileObserver (const std::string &outputFilePath);
			~TsvFileObserver (void);

			void notifyBenchmarkBegun (const std::string &benchmarkTitle, unsigned numberOfRuns);
			void notifyRunBegun (void);
			void notifyRunEnded (void);
			void notifyBenchmarkEnded (void);
	};
}

