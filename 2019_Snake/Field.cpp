#define _ENABLE_ATOMIC_ALIGNMENT_FIX

#include "Field.h"

#include <iostream>
#include <thread>

#include <conio.h>

namespace {
	std::atomic<short> direction_move_i;
	std::atomic<short> direction_move_j;
	std::atomic<short> repeat(false);

	void read_direction_move() {
		short int received_symbol;

		do {
			received_symbol = _getch();
			if (received_symbol == 0 || received_symbol == 224) { //Cheking function key or an arrow key
				received_symbol = _getch();
				if (received_symbol == 72) { // 72 - up arrow
					direction_move_i.store(-1);
					direction_move_j.store(0);
				}
				else if (received_symbol == 80) { // 80 - down arrow
					direction_move_i.store(1);
					direction_move_j.store(0);
				}
				else if (received_symbol == 75) { // 75 - left arrow
					direction_move_i.store(0);
					direction_move_j.store(-1);
				}
				else if (received_symbol == 77) { // 77 - right arrow
					direction_move_i.store(0);
					direction_move_j.store(1);
				}
			}
			else if (received_symbol == 13)
				repeat.store(true);
		} while (received_symbol != 27); // 27 - Esc

		std::exit(EXIT_SUCCESS);
	}
}

Field::Field(const std::pair<short, short> & difficulty_size_in) : symbol_free(' '), symbol_snake(254), 
	symbol_food(253), difficulty(difficulty_size_in.first),	size_field(difficulty_size_in.second), 
	snake(Snake::get_Instance(size_field)) {
}

void Field::draw() {
	std::pair<short, short> temp_coord; // Saves current coordinates;

	std::cout << "\n\n\n\t\t\t\t\t\t";
	for (short x = 0; x < size_field + 1; ++x)
		std::cout << "--";
	std::cout << '\n';

	for (short i = 0; i < size_field; ++i) {
		std::cout << "\t\t\t\t\t\t|";
		for (short j = 0; j < size_field; ++j) {
			temp_coord.first = i;
			temp_coord.second = j;
			if (free_coord.find(temp_coord) != free_coord.end())
				std::cout << symbol_free << ' ';
			else if (temp_coord == food.get_food(free_coord))
				std::cout << symbol_food << ' ';
			else
				std::cout << symbol_snake << ' ';
		}
		std::cout << "| \n";
	}

	std::cout << "\t\t\t\t\t\t";
	for (short x = 0; x < size_field + 1; ++x)
		std::cout << "--";
	std::cout << '\n';
}

Field & Field::get_Instance(const std::pair<short, short> & difficulty_size_in) {
	static Field playing_field(difficulty_size_in);
	return playing_field;
}

void Field::launch() {
	std::thread run_read_symbols(read_direction_move);
	run_read_symbols.detach();

	do {
		free_coord.clear();
		food.eat_food();
		snake.clear();

		std::cout << "\t\t\t\t\t\t If you want exit, press Esc \n";
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		std::system("cls");

		// Initialization of free coordinates
		for (std::pair<short, short> coord(0, 0); coord.first < size_field; ++coord.first) {
			for (coord.second = 0; coord.second < size_field; ++coord.second)
				free_coord.emplace(coord);
		}

		snake.init_snake(free_coord, size_field, direction_move_i, direction_move_j);


		do {
			draw();
			std::cout << "\t\t\t\t\t\t Score: " << snake.size() - 2 << '\n';

			std::this_thread::sleep_for(std::chrono::milliseconds(difficulty));

			snake.move(free_coord, direction_move_i, direction_move_j);

			if (snake.bite_status() || (snake.head().first < 0) || (snake.head().first > size_field - 1) || (snake.head().second < 0) || (snake.head().second > size_field - 1)) {
				std::system("cls");
				std::cout << "\n\n\n\n";
				std::cout << "\t\t\t\t\t\t GAME OVER \n";
				std::cout << "\t\t\t\t\t\t Score: " << snake.size() - 2 << '\n';
				std::cout << "\t\t\t\t\t\t If you want to repeat, press Enter \n";
				std::cout << "\t\t\t\t\t\t If you want exit, press Esc \n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin.get();
				break;
			}
			
			if (snake.head() == food.get_food(free_coord)) {
				food.eat_food();
				snake.grow();
			}

			if (snake.size() == size_field * size_field) {
				std::cout << "\t\t\t\t\t\t CONGRATULATION. YOU WIN.";
			}

			std::system("cls");
		} while (snake.size() < size_field * size_field);

	} while (repeat.load());

}