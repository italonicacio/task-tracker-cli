#pragma once 

#include <utility>

#include "repository/ITaskRepository.hpp"


class TaskRepositoryInMemory : public ITaskRepository {
public:
	std::vector<Task> data;

	std::pair<std::error_code, std::size_t> Add(std::string& description) override;

	std::error_code Update(std::size_t id, std::string& new_description) override;

	std::error_code Delete(std::size_t id) override;

	std::error_code MarkInProgress(std::size_t id) override;

	std::error_code MarkDone(std::size_t id) override;

};
