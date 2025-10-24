#include <fstream>

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

std::size_t TaskRepositoryFileSystem::CountFilesInDataDir() {
	std::size_t count = 0;
	try {
		for(const auto& entry : std::filesystem::directory_iterator(this->data_dir_path)) {
			count++;
		}
	} catch(...) {}

	return count;
}
