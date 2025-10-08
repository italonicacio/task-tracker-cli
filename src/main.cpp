#include <print>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "status.hpp"
#include "task.hpp"
#include "repository/ITaskRepository.hpp"
#include "repository/TaskRepositoryInMemory.hpp"
#include "operations/TaskOperations.hpp"


bool IsValidArgument(auto valid_arguments, std::string& argument) {
	return std::find(valid_arguments.begin(), valid_arguments.end(), argument) != valid_arguments.end();
}

bool IsThisArgument(const std::string& selected_argument, const std::string& argument) {
	return selected_argument == argument;
}


constexpr const char* ADD_OP = "add";
constexpr const char* UPDATE_OP = "update";
constexpr const char* DELETE_OP = "delete";
constexpr const char* MARK_IN_PROGRESS_OP = "mark-in-progress";
constexpr const char* MARK_DONE_OP = "mark-done";
constexpr const char* LIST_OP = "list";
constexpr const char* LIST_DONE_OP = "done";
constexpr const char* LIST_TODO_OP = "todo";
constexpr const char* LIST_IN_PROGRESS_OP = "in-progress";


int main(int argc, char *argv[]) {
	std::vector<std::string> arguments;

	arguments.emplace_back(ADD_OP);
	arguments.emplace_back(UPDATE_OP);
	arguments.emplace_back(DELETE_OP);
	arguments.emplace_back(MARK_IN_PROGRESS_OP);
	arguments.emplace_back(MARK_DONE_OP);
	
	arguments.emplace_back(LIST_OP);
	arguments.emplace_back(LIST_DONE_OP);
	arguments.emplace_back(LIST_TODO_OP);
	arguments.emplace_back(LIST_IN_PROGRESS_OP);
	
	if (argc < 2) {
		std::println(stderr, "Necessário que seja passado algum argumento");
		return 1;
	}
	
	std::filesystem::path binary_path = std::filesystem::absolute(argv[0]).parent_path();
	std::filesystem::path data_path = binary_path / "../data";
	std::println("{}", binary_path.string());

	if (!std::filesystem::exists(data_path)) {
		std::error_code ec;
		bool is_data_dir_created = std::filesystem::create_directory(data_path, ec);

		if (!is_data_dir_created) {
			std::println(stderr, "Erro ao criar diretório de dados: {}", ec.message());
			return 1;
		}

		std::println("Diretório de dados criado com sucesso: {}", data_path.string());
	}

	std::string operation(argv[1]);

	if (!IsValidArgument(arguments, operation)) {
		std::println("Argumento invalido");
		std::println("Os seguintes argumentos são validos");
		for(auto& a : arguments) {
			std::println("{}", a);
		}
	}	
	
	TaskRepositoryInMemory repository;

	TaskOperations task_op(repository);
	
	if (IsThisArgument(ADD_OP, operation)) {
		if (argc < 3) {
			std::println(stderr, "Está faltando a descrição da operação add");
			return 1;
		}
		
		std::string description(argv[2]);
		std::error_code err_code = task_op.Add(description);

		if (err_code) {
			std::println("Operação não foi feita com sucesso: Error Code {} message {}", err_code.value(), err_code.message());
			return 1;
		}

	}

	if (IsThisArgument(UPDATE_OP, operation)) {
		if (argc < 4) {
			std::println(stderr, "Está faltando o id da task ou a nova descrição da operação update");
			return 1;
		}

		unsigned int id = std::stoul(argv[2]);
		std::string new_description(argv[3]);

		std::error_code err_code = task_op.Update(id, new_description);

		if(err_code) {
			std::println("Operação não foi feita com sucesso: Error Code {} message {}", err_code.value(), err_code.message());
			return 1;
		}

		std::println("Task com id {} foi atualizado", id); 
		
	}

	if (IsThisArgument(DELETE_OP, operation)) {
		if (argc < 3) {
			std::println(stderr, "Está faltando o id da task na operação delete");
			return 1;
		}

		unsigned int id = std::stoul(argv[2]);

		std::error_code err_code = task_op.Delete(id);

		if(err_code) {
			std::println("Operação não foi feita com sucesso: Error Code {} message {}", err_code.value(), err_code.message());
			return 1;
		}

		std::println("Task com id {} deletado com sucesso", id); 
	}
	
	if (IsThisArgument(MARK_IN_PROGRESS_OP, operation)) {
		if (argc < 3) {
			std::println(stderr, "Está faltando o id da task na operação mark-in-progress");
			return 1;
		}

		unsigned int id = std::stoul(argv[2]);

		std::error_code err_code = task_op.MarkInProgress(id);

		if(err_code) {
			std::println("Operação não foi feita com sucesso: Error Code {} message {}", err_code.value(), err_code.message());
			return 1;
		}

		std::println("Task com id {} em progresso", id); 
	}

	if (IsThisArgument(MARK_IN_PROGRESS_OP, operation)) {
		if (argc < 3) {
			std::println(stderr, "Está faltando o id da task na operação mark-done");
			return 1;
		}

		unsigned int id = std::stoul(argv[2]);

		std::error_code err_code = task_op.Delete(id);

		if(err_code) {
			std::println("Operação não foi feita com sucesso: Error Code {} message {}", err_code.value(), err_code.message());
			return 1;
		}

		std::println("Task com id {} foi finalizado", id); 
	}

    return 0;
}
