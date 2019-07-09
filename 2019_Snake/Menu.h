#ifndef MENU_H

#define MENU_H

#include <utility>

// Class works with menu. You can create only one instance
class Menu {
	// Symbol displayed on the current parameter
	char selection_symbol;

	// Flag to check the number of instances
	static bool limit_obj;

public:
	// Constructor, checks creation only one instance. If there are more than one instances, throw exception (std::exception)
	Menu();

	// Launch functions of Menu and return difficulty and size playing field
	std::pair<short, short> launch();

private:
	// Copy constructor
	Menu(const Menu &) = delete;

	// Copy operator=
	Menu & operator=(const Menu &) = delete;

	// Print logo
	void logo() const;

	// Print start menu, read symbols, choice of action
	void start_menu();

	// Choice of difficulty
	short difficulty_menu();

	// Choice of size playing field
	short size_menu();

	// Read symbol and set status
	void read_set_symbol(short int &, bool &);

	// Read symbol and set status. First parameter for save received symbol, second for save status
	void read_set_symbol(short int &, short int &);
};

#endif // MENU_H