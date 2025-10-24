#include <fstream>

#include <print>

#include "repository/TaskRepositoryFileSystem.hpp"


TaskRepositoryFileSystem::TaskRepositoryFileSystem(std::filesystem::path& data_dir_path) 
	: data_dir_path(data_dir_path) {
		this->number_tasks = CountFilesInDataDir();
	}

std::pair<std::error_code, std::size_t> TaskRepositoryFileSystem::Add(std::string& description) {
	
	if(!std::filesystem::exists(data_dir_path)) {
		return std::make_pair(std::make_error_code(std::errc::no_such_file_or_directory), 0);
	}

	std::size_t new_id = this->number_tasks + 1;
	Task t = NewTask(new_id, description);

	std::string filename(std::format("{}.json", new_id));
	std::filesystem::path filepath = this->data_dir_path / filename;

	std::ofstream output_file(filepath);

	if(output_file.is_open()) {
		output_file << t.ToJson();

		output_file.close();
	} else {
		return std::make_pair(std::make_error_code(std::errc::no_such_file_or_directory), 0);
	}

	return std::make_pair(std::error_code{}, new_id);
}

std::error_code TaskRepositoryFileSystem::Update(std::size_t id, std::string& new_description) {
	return std::error_code {};
}

std::error_code TaskRepositoryFileSystem::Delete(std::size_t id) {
	return std::error_code {};
}

std::error_code TaskRepositoryFileSystem::MarkInProgress(std::size_t id) {
	return std::error_code {};
}

std::error_code TaskRepositoryFileSystem::MarkDone(std::size_t id) {
	return std::error_code {};
}

bool TaskRepositoryFileSystem::CleanAllFiles() {
	try {
		for(const auto& entry : std::filesystem::directory_iterator(this->data_dir_path)) {
			std::filesystem::remove_all(entry.path());
		}
	} catch(...) {
		return false;
	}

	return true;
}

std::size_t TaskRepositoryFileSystem::CountFilesInDataDir() {
	std::size_t count = 0;
	try {
		for(const auto& entry : std::filesystem::directory_iterator(this->data_dir_path)) {
			count++;
		}
	} catch(...) {}

	return count;
}

std::pair<std::error_code, Task> TaskRepositoryFileSystem::GetTask(std::size_t id) {

	if(id <= 0) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	std::string filename(std::format("{}.json", id));
	std::filesystem::path filepath = this->data_dir_path/filename;
	
	std::ifstream ifs(filepath);

	if(!ifs.is_open()) {
		std::make_pair(std::make_error_code(std::errc::no_such_file_or_directory), Task{});
	}
	
	std::stringstream buffer;
	
	buffer << ifs.rdbuf();
	
	ifs.close();
	
	std::string json = buffer.str(); 
	std::println("json: {}", json);

	std::size_t pos = json.find("\"id\":");

	if (pos == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	std::size_t init = json.find_first_of("0123456789", pos);

	if (init == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	std::size_t end = json.find(',', init);

	if (end == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	std::size_t length = end - init;
	
	std::string task_id_str = json.substr(init, length);

	std::size_t task_id = 0;
	try {
		task_id = std::stoull(task_id_str);
	} catch(...) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	std::string description_key("\"description\":");
	pos = json.find(description_key, end);
	if (pos == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	init = json.find_first_of('"', pos + description_key.length());
	if (init == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	end = json.find('"', init + 1);
	if (end == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	length = end - (init + 1);
	std::string description = json.substr(init + 1, length);
	
	if(json[end + 1] != ',') {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	std::string status_key("\"status\":");
	pos = json.find(status_key, end);
	if (pos == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}


	init = json.find_first_of('"', pos + status_key.length());
	if (init == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	end = json.find('"', init + 1);
	if (end == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	length = end - (init + 1);
	std::string status = json.substr(init + 1, length);


	pos = json.find("\"createdAt\":", end);
	if (pos == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	init = json.find_first_of("0123456789", pos);
	if (init == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	end = json.find(',', init);
	if (end == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	length = end - init;

	std::string createdAt_str = json.substr(init, length);
	ClockT::time_point createdAt;
	try{
		auto duration_count = std::stoull(createdAt_str);
		
		createdAt = ClockT::time_point(ClockT::duration(duration_count));
	} catch(...) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

		pos = json.find("\"updatedAt\":", end);
	if (pos == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	init = json.find_first_of("0123456789", pos);
	if (init == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	end = json.find_first_of(", ", init);
	if (end == std::string::npos) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	length = end - init;

	std::string updatedAt_str = json.substr(init, length);
	ClockT::time_point updatedAt;
	try{
		auto duration_count = std::stoull(updatedAt_str);
		
		updatedAt = ClockT::time_point(ClockT::duration(duration_count));
	} catch(...) {
		return std::make_pair(std::make_error_code(std::errc::invalid_argument), Task{});
	}

	Task new_task{task_id, description, StringToStatus(status), createdAt, updatedAt};

	return std::make_pair(std::error_code{}, new_task);
}
