#pragma once

enum class Status {
	todo,
	in_progress,
	done
};


constexpr std::string_view StatusToString(Status status) {
	switch (status) {
		case Status::done: return "done";
		case Status::in_progress: return "in-progress";
		case Status::todo: return "todo";
		default: return "unknown";
	}
}
