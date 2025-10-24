#pragma once 

#include <filesystem>

#include "repository/ITaskRepository.hpp"


class TaskRepositoryFileSystem : public ITaskRepository {
public:
	std::size_t number_tasks;
	
	std::filesystem::path data_dir_path;

	TaskRepositoryFileSystem(std::filesystem::path& data_dir_path);

	std::pair<std::error_code, std::size_t> Add(std::string& description) override;

	std::error_code Update(std::size_t id, std::string& new_description) override;

	std::error_code Delete(std::size_t id) override;

	std::error_code MarkInProgress(std::size_t id) override;

	std::error_code MarkDone(std::size_t id) override;


private:
	std::size_t CountFilesInDataDir();
};
