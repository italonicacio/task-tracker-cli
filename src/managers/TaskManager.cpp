
#include <print>

#include "managers/TaskManager.hpp"
#include "commands.hpp"

std::error_code TaskManager::HandleOperation(std::string operation, int argc, char *argv[]) {

	if (IsThisOperation(ADD_OP, operation)) {
		return HandleAdd(argc, argv);
	}

	if (IsThisOperation(UPDATE_OP, operation)) {
		return HandleUpdate(argc, argv);
	}

	if (IsThisOperation(DELETE_OP, operation)) {
		return HandleDelete(argc, argv);
	}

	if (IsThisOperation(MARK_IN_PROGRESS_OP, operation)) {
		return HandleMarkInProgress(argc, argv);
	}

	if (IsThisOperation(MARK_DONE_OP, operation)) {
		return HandleMarkDone(argc, argv);
	}

	return std::make_error_code(std::errc::invalid_argument);
}

std::error_code TaskManager::HandleAdd(int argc, char *argv[]) {
	if (argc < 3) {
		std::println(stderr, "Está faltando a descrição da operação add");
	}
	
	std::string description(argv[2]);
	std::error_code err_code = operation.Add(description);

	if (err_code) {
		std::println("Operação não foi feita com sucesso: Error Code {} message {}", err_code.value(), err_code.message());
	}
	
	return std::error_code{};
}

std::error_code TaskManager::HandleUpdate(int argc, char *argv[]) {
	if (argc < 4) {
		std::println(stderr, "Está faltando o id da task ou a nova descrição da operação update");
	}

	unsigned int id = std::stoul(argv[2]);
	std::string new_description(argv[3]);

	std::error_code err_code = operation.Update(id, new_description);

	if(err_code) {
		std::println("Operação não foi feita com sucesso: Error Code {} message {}", err_code.value(), err_code.message());
	}

	return std::error_code{};
}

std::error_code TaskManager::HandleDelete(int argc, char *argv[]) {
	if (argc < 3) {
		std::println(stderr, "Está faltando o id da task na operação delete");
	}

	unsigned int id = std::stoul(argv[2]);

	std::error_code err_code = operation.Delete(id);

	if(err_code) {
		std::println("Operação não foi feita com sucesso: Error Code {} message {}", err_code.value(), err_code.message());
	}

	return std::error_code{};
}

std::error_code TaskManager::HandleMarkInProgress(int argc, char *argv[]) {
	if (argc < 3) {
		std::println(stderr, "Está faltando o id da task na operação mark-in-progress");
	}

	unsigned int id = std::stoul(argv[2]);

	std::error_code err_code = operation.MarkInProgress(id);

	if(err_code) {
		std::println("Operação não foi feita com sucesso: Error Code {} message {}", err_code.value(), err_code.message());
	}

	return std::error_code{};
}

std::error_code TaskManager::HandleMarkDone(int argc, char *argv[]) {
	if (argc < 3) {
		std::println(stderr, "Está faltando o id da task na operação mark-done");
	}

	unsigned int id = std::stoul(argv[2]);

	std::error_code err_code = operation.MarkDone(id);

	if(err_code) {
		std::println("Operação não foi feita com sucesso: Error Code {} message {}", err_code.value(), err_code.message());
	}

	return std::error_code{};
}
