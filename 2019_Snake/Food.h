#ifndef FOOD_H

#define FOOD_H

#include <utility>
#include <set>

class Food {
	// Food status. true - food is on the field, false - no food
	bool food_status;

	// Current food position
	std::pair<short, short> position_food;

public:
	// Constructor
	Food();

	// Set food status to false.
	void eat_food();

	// Returns position of the new food or food(if not eaten). Parameter - this is set of the free coordinates on the field
	std::pair<short, short> get_food(std::set<std::pair<short, short>> &);
};

#endif // FOOD_H