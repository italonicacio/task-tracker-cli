#include <gtest/gtest.h>

#include "operations/TaskOperations.hpp"
#include "repository/TaskRepositoryInMemory.hpp"

class TaskOperationsTest : public ::testing::Test {
protected:
	std::unique_ptr<TaskRepositoryInMemory> repository;
	std::unique_ptr<TaskOperations> task_operations;

	void SetUp() override {
		repository = std::make_unique<TaskRepositoryInMemory>();
		task_operations = std::make_unique<TaskOperations>(*repository);
	}

	void TearDown() override {
		task_operations.reset();
		repository.reset();
	}
};

TEST_F(TaskOperationsTest, ShouldBeAbleToAddATask) {
	std::string description = "Test task description";

	std::error_code result = task_operations->Add(description);

	EXPECT_FALSE(result) << "Add operation should succeed";
	EXPECT_EQ(1, repository->data.size()) << "Repository should contain 1 task";
	EXPECT_EQ(description, repository->data.back().description);
	EXPECT_EQ(Status::todo, repository->data.back().status);
}
