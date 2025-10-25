#include <gtest/gtest.h>

#include "Environment.hpp"

#include <print>

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
		repository->CleanAllFiles();
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

TEST_F(TaskRepositoryFileSystemTest, ShouldBeAbleToDeleteAllFiles) {
	std::string description("description");

	repository->Add(description);
	repository->Add(description);

	repository->CleanAllFiles();

	EXPECT_TRUE(std::filesystem::exists(this->data_dir_path));
	EXPECT_TRUE(std::filesystem::is_empty(this->data_dir_path));

}

TEST_F(TaskRepositoryFileSystemTest, ShouldNotBeAbleToAddATaskWhenDirectoryDoNotExist) {
	std::filesystem::path not_a_dir("./test");
	TaskRepositoryFileSystem repo(not_a_dir);
	std::string description("description");
	
	auto [err, id] = repo.Add(description);

	EXPECT_EQ(id, 0);
	EXPECT_TRUE(err == std::make_error_code(std::errc::no_such_file_or_directory));
	EXPECT_FALSE(std::filesystem::exists(not_a_dir/"1.json"));
}

TEST_F(TaskRepositoryFileSystemTest, ShouldBeAbleToGetATask) {
	std::string description("description");

	repository->Add(description);

	auto [err, task] = repository->GetTask(1);

	EXPECT_FALSE(err);
	EXPECT_EQ(task.id, 1);
	EXPECT_EQ(task.description, description);
	EXPECT_EQ(task.status, Status::todo);
	EXPECT_GT(task.createdAt.time_since_epoch().count(), 0);
	EXPECT_EQ(task.updateAt.time_since_epoch().count(), task.createdAt.time_since_epoch().count());
}

TEST_F(TaskRepositoryFileSystemTest, ShouldNotBeAbleToGetATask) {	
	auto [err, task] = repository->GetTask(1);

	EXPECT_TRUE(err);
}


TEST_F(TaskRepositoryFileSystemTest, ShouldBeAbleToUpdateATask) {
	std::string description("description");

	repository->Add(description);
	
	std::string new_description("new description");
	
	std::error_code err = repository->Update(1, new_description);

	auto [_, task] = repository->GetTask(1);

	EXPECT_FALSE(err);
	EXPECT_EQ(task.id, 1);
	EXPECT_EQ(task.description, new_description);
	EXPECT_EQ(task.status, Status::todo);
	EXPECT_LT(task.createdAt, task.updateAt);
}

TEST_F(TaskRepositoryFileSystemTest, ShouldNotBeAbleToUpdateANonExistentTask) {	
	std::string new_description("new description");
	
	std::error_code err = repository->Update(1, new_description);

	EXPECT_TRUE(err);
}

TEST_F(TaskRepositoryFileSystemTest, ShouldNotBeAbleToOverwriteExistentTaskWhenNumberOfTasksEqualToIDTask) {
	std::string description("description");

	repository->Add(description);
	repository->Add(description);
	repository->Add(description);

	repository->Delete(1);

	auto [err, id] = repository->Add(description);
	
	EXPECT_FALSE(err);
	EXPECT_TRUE(id != 3);

	repository->Add(description);

	repository->Delete(2);

	std::tie(err, id) = repository->Add(description);

	
	EXPECT_FALSE(err);
	EXPECT_TRUE(id != 4);

}
