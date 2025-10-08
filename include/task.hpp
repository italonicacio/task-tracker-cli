#pragma once

#include <chrono>

#include <status.hpp>

using ClockT = std::chrono::high_resolution_clock;

struct Task {
	std::size_t id;
	std::string description;
	Status status;
	ClockT::time_point createdAt;
	ClockT::time_point updateAt;
};

inline Task NewTask(unsigned int id, std::string description) {
	
	return Task{id, description, Status::todo, ClockT::now(), ClockT::now()};
}
