#include <print>

#include "operations/TaskOperations.hpp"


std::error_code TaskOperations::Add(std::string& description) {
	std::println("Está é a descrição: {}", description);

	auto [err_code, id] = repository.Add(description);
	
	if (!err_code) {
		std::println("Output: Task added successfully (ID: {})", id);
	}
	
	return err_code;
}

std::error_code TaskOperations::Update(unsigned int id, std::string& new_description) {
	return repository.Update(id, new_description);
}

std::error_code TaskOperations::Delete(unsigned int id) {
	return repository.Delete(id);
}

std::error_code TaskOperations::MarkInProgress(unsigned int id) {
	return repository.MarkInProgress(id);
}

std::error_code TaskOperations::MarkDone(unsigned int id) {
	return repository.MarkDone(id);
}
