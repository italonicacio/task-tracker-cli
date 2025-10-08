#pragma once

#include "repository/ITaskRepository.hpp"

class TaskOperations {
private: 
	ITaskRepository& repository;

public:
	TaskOperations(ITaskRepository& repository) : repository(repository) {}

	std::error_code Add(std::string& description);
	
	std::error_code Update(unsigned int id, std::string& new_description);

	std::error_code Delete(unsigned int id);

	std::error_code MarkInProgress(unsigned int id);

	std::error_code MarkDone(unsigned int id);
};
