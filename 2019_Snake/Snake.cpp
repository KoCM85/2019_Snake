#include "Snake.h"

#include <algorithm>
#include <random>
#include <array>
#include <iostream>

Snake::Snake(short size_field) : snake_buf(size_field * size_field), grow_status(false), snake_bite_status(false) {
}

bool Snake::check_bite() {
	auto end = snake_buf.end() - 1;
	auto find_bite = std::find(snake_buf.begin(), end, snake_buf.back());

	if (find_bite == end)
		return false;

	return true;
}

Snake & Snake::get_Instance(short size_field) {
	static Snake snake(size_field);
	return snake;
}

void Snake::move(std::set<std::pair<short, short>> & free_coord_in, std::atomic<short> & direction_move_i, std::atomic<short> & direction_move_j) {
	std::pair<short, short> new_head;
	new_head.first = snake_buf.back().first + direction_move_i.load();
	new_head.second = snake_buf.back().second + direction_move_j.load();

	snake_buf.push_back(std::move(new_head));
	free_coord_in.erase(new_head);

	snake_bite_status = check_bite();

	if (grow_status)
		grow_status = false;
	else {
		free_coord_in.emplace(snake_buf.front());
		snake_buf.pop_front();
	}
}

void Snake::grow() {
	grow_status = true;
}

std::pair<short, short> Snake::head() const {
	return snake_buf.back();
}

std::pair<short, short> Snake::end_tail() const {
	return snake_buf.front();
}

size_t Snake::size() {
	return snake_buf.size();
}

void Snake::init_snake(std::set<std::pair<short, short>> & free_coord_in, size_t & size_field, std::atomic<short> & direction_move_i, std::atomic<short> & direction_move_j) {
	std::random_device random_device_generator;
	std::mt19937 generator_numbers(random_device_generator());
	std::uniform_int_distribution<> distribution_coord(2, size_field - 3);

	// Calc random position of the snake head
	std::pair<short, short> temp_snake_head;
	temp_snake_head.first = distribution_coord(generator_numbers);
	temp_snake_head.second = distribution_coord(generator_numbers);

	std::array<short, 3> dirrection_move{ 1, 0, -1 };
	std::pair<short, short> temp_snake_tail;
	short temp_index;

	// Calc random direction
	if ((temp_snake_head.first < size_field / 2) && (temp_snake_head.second < size_field / 2)) { // move down or right
		std::uniform_int_distribution<> distribution_direction_i(0, 1);
		temp_index = distribution_direction_i(generator_numbers);

		direction_move_i.store(dirrection_move[temp_index]);

		if (dirrection_move[temp_index] == 1) { // move down
			direction_move_j.store(0);
			temp_snake_tail.first = temp_snake_head.first - 1;
			temp_snake_tail.second = temp_snake_head.second;
		}
		else { // move right
			direction_move_j.store(1);
			temp_snake_tail.first = temp_snake_head.first;
			temp_snake_tail.second = temp_snake_head.second - 1;
		}
	}
	else if ((temp_snake_head.first > size_field / 2) && (temp_snake_head.second < size_field / 2)) { // move up or right
		std::uniform_int_distribution<> distribution_direction_i(1, 2);
		temp_index = distribution_direction_i(generator_numbers);

		direction_move_i.store(dirrection_move[temp_index]);

		if (dirrection_move[temp_index] == -1) { // move up
			direction_move_j.store(0);
			temp_snake_tail.first = temp_snake_head.first + 1;
			temp_snake_tail.second = temp_snake_head.second;
		}
		else { // move right
			direction_move_j.store(1);
			temp_snake_tail.first = temp_snake_head.first;
			temp_snake_tail.second = temp_snake_head.second - 1;
		}
	}
	else if ((temp_snake_head.first < size_field / 2) && (temp_snake_head.second > size_field / 2)) { // move down or left
		std::uniform_int_distribution<> distribution_direction_i(0, 1);
		temp_index = distribution_direction_i(generator_numbers);

		direction_move_i.store(dirrection_move[temp_index]);

		if (dirrection_move[temp_index] == 0) { // move left
			direction_move_j.store(-1);
			temp_snake_tail.first = temp_snake_head.first;
			temp_snake_tail.second = temp_snake_head.second + 1;
		}
		else { // move down
			direction_move_j.store(0);
			temp_snake_tail.first = temp_snake_head.first - 1;
			temp_snake_tail.second = temp_snake_head.second;
		}
	}
	else { // move up or left
		std::uniform_int_distribution<> distribution_direction_i(1, 2);
		temp_index = distribution_direction_i(generator_numbers);

		direction_move_i.store(dirrection_move[temp_index]);

		if (dirrection_move[temp_index] == 0) { // move left
			direction_move_j.store(-1);
			temp_snake_tail.first = temp_snake_head.first;
			temp_snake_tail.second = temp_snake_head.second + 1;
		}
		else { // move up
			direction_move_j.store(0);
			temp_snake_tail.first = temp_snake_head.first + 1;
			temp_snake_tail.second = temp_snake_head.second;
		}
	}

	snake_buf.push_back(std::move(temp_snake_tail));
	snake_buf.push_back(std::move(temp_snake_head));
	free_coord_in.erase(snake_buf.back());
	free_coord_in.erase(snake_buf.front());
}

bool Snake::bite_status() {
	return snake_bite_status;
}

void Snake::clear() {
	snake_buf.clear();
}