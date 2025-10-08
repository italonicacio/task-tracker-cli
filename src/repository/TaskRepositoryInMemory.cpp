#include "repository/TaskRepositoryInMemory.hpp"


std::pair<std::error_code, int> TaskRepositoryInMemory::Add(std::string& description) {
		int new_id = data.size() + 1;
		data.emplace_back(NewTask(new_id, description));

		return std::make_pair(std::error_code{}, new_id);
	}	

std::error_code TaskRepositoryInMemory::Update(unsigned int id, std::string& new_description) {
	if(id < 1) {
		return std::make_error_code(std::errc::invalid_argument);
	}

	if(id > data.size()) {
		return std::make_error_code(std::errc::no_such_file_or_directory);
	}

	Task& t = data[id - 1];

	if(t.id == -1) {
		return std::make_error_code(std::errc::resource_unavailable_try_again);
	}

	t.description = new_description;
	t.updateAt = ClockT::now();

	return std::error_code{};
}

std::error_code TaskRepositoryInMemory::Delete(unsigned int id) {
	if(id < 1) {
		return std::make_error_code(std::errc::invalid_argument);
	}

	if(id > data.size()) {
		return std::make_error_code(std::errc::no_such_file_or_directory);
	}
	Task& t = data[id - 1];
	
	if(t.id == -1) {
		return std::make_error_code(std::errc::resource_unavailable_try_again);
	}

	t.id = -1;

	return std::error_code{};
}

std::error_code TaskRepositoryInMemory::MarkInProgress(unsigned int id) {
	if(id < 1) {
		return std::make_error_code(std::errc::invalid_argument);
	}

	if(id > data.size()) {
		return std::make_error_code(std::errc::no_such_file_or_directory);
	}

	Task& t = data[id - 1];

	if(t.id == -1) {
		return std::make_error_code(std::errc::resource_unavailable_try_again);
	}

	t.status = Status::in_progress;
	t.updateAt = ClockT::now();

	return std::error_code{};
}

std::error_code TaskRepositoryInMemory::MarkDone(unsigned int id) {
	if(id < 1) {
		return std::make_error_code(std::errc::invalid_argument);
	}

	if(id > data.size()) {
		return std::make_error_code(std::errc::no_such_file_or_directory);
	}

	Task& t = data[id - 1];

	if(t.id == -1) {
		return std::make_error_code(std::errc::resource_unavailable_try_again);
	}

	t.status = Status::done;
	t.updateAt = ClockT::now();

	return std::error_code{};
}
