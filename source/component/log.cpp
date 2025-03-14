#include "log.hpp"

void Custom::Log::Initial() {
	setFile("log/", true);
	Success("INITIAL Log system");
}