#pragma once

#include <string>


constexpr const char* ADD_OP = "add";
constexpr const char* UPDATE_OP = "update";
constexpr const char* DELETE_OP = "delete";
constexpr const char* MARK_IN_PROGRESS_OP = "mark-in-progress";
constexpr const char* MARK_DONE_OP = "mark-done";
constexpr const char* LIST_OP = "list";
constexpr const char* LIST_DONE_OP = "done";
constexpr const char* LIST_TODO_OP = "todo";
constexpr const char* LIST_IN_PROGRESS_OP = "in-progress";



inline bool IsThisOperation(const std::string& selected_operation, const std::string& operation) {
	return selected_operation == operation;
}
