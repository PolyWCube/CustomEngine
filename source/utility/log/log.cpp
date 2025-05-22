#include "log.hpp"

void Custom::Log::Initial() {
	SetFile("log/", true);
	Success("INITIAL Log system");
}