#include <print>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>


#include "commands.hpp"
#include "status.hpp"
#include "task.hpp"
#include "repository/ITaskRepository.hpp"
#include "repository/TaskRepositoryFileSystem.hpp"
#include "operations/TaskOperations.hpp"
#include "managers/TaskManager.hpp"

bool IsValidArgument(auto valid_arguments, std::string& argument) {
	return std::find(valid_arguments.begin(), valid_arguments.end(), argument) != valid_arguments.end();
}

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
	
	TaskRepositoryFileSystem repository(data_path);

	TaskOperations task_op(repository);
	
	TaskManager manager(task_op);

	std::error_code err_code = manager.HandleOperation(operation, argc, argv);

	if (err_code) {
		std::println("Aconteceu um erro durante a execução da operação {}", operation);
		std::println("Error {}: {}", err_code.value(), err_code.message());
	}
 


    return 0;
}
