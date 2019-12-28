#include "observer.h"
#include <sstream>
#include <iostream>

#define SAVE_CURSOR_POSITION "\033[s"
#define MOVE_CURSOR_TO_SAVED_POSITION "\033[u"
#define MOVE_UP_LINES(numberOfLines) "\033[" << numberOfLines << 'A'
#define CLEAR_LINE "\033[K"

using namespace benchmark;
using namespace std;

/* OBSERVER */
void Observer::observe_variable(observable_variable_interface& observable_variable) {
	variables_to_observe.emplace_back(observable_variable);
}

/*TERMINAL OBSERVER*/
void TerminalObserver::notifyBenchmarkBegun (const string& benchmarkTitle, unsigned numberOfRuns) {
	cout << "Executing '" << benchmarkTitle << "' " << numberOfRuns << " times..." << endl;
	cout << SAVE_CURSOR_POSITION;
}

void TerminalObserver::notifyRunBegun (void) {
	// do nothing
}

void TerminalObserver::notifyRunEnded (void) {
	cout << MOVE_CURSOR_TO_SAVED_POSITION << CLEAR_LINE;
	for (auto observable_variable : this->variables_to_observe) {
		cout << CLEAR_LINE;
		cout << "\t" << observable_variable.get().get_label() << ": " << observable_variable.get().get_value_as_string() << endl;
	}
	cout << endl;
}

void TerminalObserver::notifyBenchmarkEnded (void) {
	// do nothing
}
/*TERMINAL OBSERVER*/

/*TEXT FILE OBSERVER*/
TextFileObserver::TextFileObserver (const string& outputFilePath) {
	this->outputFile.open(outputFilePath, ios::app);
}

TextFileObserver::~TextFileObserver (void) {
	this->outputFile.close();
}

void TextFileObserver::notifyBenchmarkBegun (const string& benchmarkTitle, unsigned numberOfRuns) {
	time_t currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
	tm *ptm = localtime(&currentTime);
	char formatedTime[20];
	strftime(formatedTime, 20, "%Y-%m-%d %H:%M:%S", ptm);
	this->outputFile << "Executing '" << benchmarkTitle << "' " << numberOfRuns << " times - " << formatedTime << endl;
}

void TextFileObserver::notifyRunBegun (void) {
	// do nothing
}

void TextFileObserver::notifyRunEnded (void) {
	for (auto observable_variable : this->variables_to_observe) {
		this->outputFile << '\t' << observable_variable.get().get_label() << ": " << observable_variable.get().get_value_as_string() << endl;
	}
	this->outputFile << endl;
}

void TextFileObserver::notifyBenchmarkEnded (void) {
	// do nothing
}
/*TEXT FILE OBSERVER*/

/*CSV FILE OBSERVER*/
TsvFileObserver::TsvFileObserver (const string& outputFilePath) {
	this->outputFile.open(outputFilePath, ios::app);
}

TsvFileObserver::~TsvFileObserver (void) {
	this->outputFile.close();
}

void TsvFileObserver::notifyBenchmarkBegun(const string& benchmarkTitle, unsigned numberOfRuns) {
	for (auto observable_variable : this->variables_to_observe) {
		this->outputFile << observable_variable.get().get_label() << '\t';
	}
	this->outputFile << benchmarkTitle << '\t' << numberOfRuns << " runs";
	this->outputFile << '\n';
}

void TsvFileObserver::notifyRunBegun(void) {
	//do nothing
}

void TsvFileObserver::notifyRunEnded(void) {
	for (auto observable_variable : this->variables_to_observe) {
		this->outputFile << observable_variable.get().get_value_as_string() << '\t';
	}
	this->outputFile << '\n';
}

void TsvFileObserver::notifyBenchmarkEnded(void) {
	// do nothing
}
/*CSV FILE OBSERVER*/

