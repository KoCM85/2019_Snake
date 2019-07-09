#ifndef FIELD_H

#define FIELD_H

#include "Food.h"
#include "Snake.h"

#include <set>
#include <utility>

// Singleton. Class work with playing field
class Field {
	// Stores free coordinates of the playing field
	std::set<std::pair<short, short>> free_coord;

	// The symbol display the free position
	char symbol_free;

	// The symbol display snake
	char symbol_snake;

	// The symbol display food
	char symbol_food;

	// Stores difficulty
	size_t difficulty;

	// Stores size of the playing field
	size_t size_field;

	// Food on the field
	Food food;

	// Snake on the field
	Snake & snake;

private:
	// Constructor
	Field(const std::pair<short, short> &);

	// Copy constructor
	Field(const Field &) = delete;

	// Copy operator=
	Field & operator=(const Field &) = delete;

	// Draws playing field
	void draw();

public:
	// Create single object and returns. Parameter pair.first - difficulty, pair.second - size of the playing field 
	static Field & get_Instance(const std::pair<short, short> &);

	// Launch functions of Field and some other logic
	void launch();
};

#endif // FIELD_H