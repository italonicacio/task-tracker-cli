#pragma once 

#include "repository/ITaskRepository.hpp"


class TaskRepositoryInMemory : public ITaskRepository {
public:
	std::vector<Task> data {{1, "Teste", Status::todo, ClockT::now(), ClockT::now()}};

	std::pair<std::error_code, int> Add(std::string& description) override;

	std::error_code Update(unsigned int id, std::string& new_description) override;

	std::error_code Delete(unsigned int id) override;

	std::error_code MarkInProgress(unsigned int id) override;

	std::error_code MarkDone(unsigned int id) override;

};
