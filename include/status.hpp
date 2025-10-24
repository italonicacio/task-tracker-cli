#pragma once

enum class Status {
	todo,
	in_progress,
	done,
	unknown
};


constexpr std::string_view StatusToString(Status status) {
	switch (status) {
		case Status::todo: return "todo";
		case Status::in_progress: return "in-progress";
		case Status::done: return "done";
		default: return "unknown";
	}
}

constexpr Status StringToStatus(std::string& status) {
	if(status == "todo") {
		return Status::todo;
	}

	
	if(status == "in-progress") {
		return Status::in_progress;
	}
	
	if(status == "done") {
		return Status::done;
	}
	
	return Status::unknown;
}
