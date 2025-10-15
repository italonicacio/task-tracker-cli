#pragma once

#include "operations/TaskOperations.hpp"

class TaskManager {
private:
	TaskOperations& operation;
public:
	TaskManager(TaskOperations& operation) : operation(operation) {} 

	std::error_code HandleOperation(std::string operation, int argc, char *argv[]);

	std::error_code HandleAdd(int argc, char *argv[]);
	std::error_code HandleUpdate(int argc, char *argv[]);
	std::error_code HandleDelete(int argc, char *argv[]);
	std::error_code HandleMarkInProgress(int argc, char *argv[]);
	std::error_code HandleMarkDone(int argc, char *argv[]);

};
