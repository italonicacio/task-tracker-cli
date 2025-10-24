#include "repository/TaskRepositoryInMemory.hpp"


std::pair<std::error_code, std::size_t> TaskRepositoryInMemory::Add(std::string& description) {
		std::size_t new_id = data.size() + 1;
		data.emplace_back(NewTask(new_id, description));

		return std::make_pair(std::error_code{}, new_id);
	}	

std::error_code TaskRepositoryInMemory::Update(std::size_t id, std::string& new_description) {
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

std::error_code TaskRepositoryInMemory::Delete(std::size_t id) {
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

std::error_code TaskRepositoryInMemory::MarkInProgress(std::size_t id) {
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

std::error_code TaskRepositoryInMemory::MarkDone(std::size_t id) {
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

std::pair<std::error_code, Task> TaskRepositoryInMemory::GetTask(std::size_t id) {
	if(id <= 0) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	if(id <= 0) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	return std::make_pair(std::error_code{}, data[id - 1]);
}
