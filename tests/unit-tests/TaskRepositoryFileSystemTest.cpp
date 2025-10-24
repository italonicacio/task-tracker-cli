#include <gtest/gtest.h>

#include "Environment.hpp"

#include "repository/TaskRepositoryFileSystem.hpp"

class TaskRepositoryFileSystemTest : public ::testing::Test {
protected:
	std::unique_ptr<TaskRepositoryFileSystem> repository;
	std::filesystem::path data_dir_path;
	void SetUp() override {
		this->data_dir_path = Environment::GetTestDataPath();
		this->repository = std::make_unique<TaskRepositoryFileSystem>(data_dir_path);
	}

	void TearDown() override {
		repository.reset();
	}
};

TEST_F(TaskRepositoryFileSystemTest, ShouldBeAbleToAddATask) {
	std::string description("description");

	auto [err, id] = repository->Add(description);

	EXPECT_EQ(id, 1);
	EXPECT_FALSE(err);
	EXPECT_TRUE(std::filesystem::exists(data_dir_path/"1.json"));
}

TEST_F(TaskRepositoryFileSystemTest, ShouldntBeAbleToAddATaskWhenDirectoryDontExist) {
	std::filesystem::path not_a_dir("./test");
	TaskRepositoryFileSystem repo(not_a_dir);
	std::string description("description");
	
	auto [err, id] = repo.Add(description);

	EXPECT_EQ(id, 0);
	EXPECT_TRUE(err == std::make_error_code(std::errc::no_such_file_or_directory));
	EXPECT_FALSE(std::filesystem::exists(not_a_dir/"1.json"));
}
