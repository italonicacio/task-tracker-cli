#pragma once

#include <chrono>
#include <format>

#include "status.hpp"

using ClockT = std::chrono::high_resolution_clock;

struct Task {
	std::size_t id;
	std::string description;
	Status status;
	ClockT::time_point createdAt;
	ClockT::time_point updateAt;

	std::string ToJson() const {
		return std::format(
R"({{
	"id": {}, 
	"description": "{}", 
	"status": "{}", 
	"createdAt": {}, 
	"updatedAt": {} 
}})", 
		id, 
		description, 
		StatusToString(status), 
		createdAt.time_since_epoch().count(), 
		updateAt.time_since_epoch().count());
	}
};

inline Task NewTask(unsigned int id, std::string description) {	
	ClockT::time_point time_now = ClockT::now();
	return Task{id, description, Status::todo, time_now, time_now};
}


