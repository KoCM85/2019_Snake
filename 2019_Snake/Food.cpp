#include "Food.h"

#include <random>
#include <iterator>

Food::Food() : food_status(false) {
}

void Food::eat_food() {
	food_status = false;
}

std::pair<short, short> Food::get_food(std::set<std::pair<short, short>> & free_coord) {
	if (food_status);
	else {
		std::random_device random_device_generator;
		std::mt19937 generator_numbers(random_device_generator());
		std::uniform_int_distribution<> distribution_position_food(0, free_coord.size());
		const short random_position = distribution_position_food(generator_numbers);

		auto position = free_coord.begin();

		std::advance(position, random_position);
		position_food = std::move(*position);
		food_status = true;
		free_coord.erase(position);
	}

	return position_food;
}