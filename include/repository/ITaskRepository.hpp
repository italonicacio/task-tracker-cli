#pragma once

#include <utility>

#include "task.hpp"

class ITaskRepository {
public:
	virtual ~ITaskRepository() = default;
	virtual std::pair<std::error_code, int> Add(std::string& description) = 0;
		
	virtual std::error_code Update(unsigned int id, std::string& new_description) = 0;

	virtual std::error_code Delete(unsigned int id) = 0;

	virtual std::error_code MarkInProgress(unsigned int id) = 0;

	virtual std::error_code MarkDone(unsigned int id) = 0;

};
