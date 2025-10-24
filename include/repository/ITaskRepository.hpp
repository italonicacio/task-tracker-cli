#pragma once

#include <utility>

#include "task.hpp"

class ITaskRepository {
public:
	virtual ~ITaskRepository() = default;

	virtual std::pair<std::error_code, std::size_t> Add(std::string& description) = 0;
		
	virtual std::error_code Update(std::size_t id, std::string& new_description) = 0;

	virtual std::error_code Delete(std::size_t id) = 0;

	virtual std::error_code MarkInProgress(std::size_t id) = 0;

	virtual std::error_code MarkDone(std::size_t id) = 0;

};
