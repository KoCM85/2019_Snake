#include "Menu.h"

#include <iostream>
#include <cstdlib>
#include <exception>

#include <conio.h>

namespace {
	enum difficulty : short { easy = 1000, normal = 500, hard = 250 };
	enum size_field : short { small = 5, standard = 20, big = 30 };
}

bool Menu::limit_obj = false;

Menu::Menu() : selection_symbol(253) {
	if (limit_obj) {
		throw std::exception("limit of objects exceeded");
	}
	limit_obj = true;
}

std::pair<short, short> Menu::launch() {
	std::pair<short, short> dif_size;
	start_menu();
	dif_size.first = difficulty_menu();
	dif_size.second = size_menu();

	return dif_size;
}

void Menu::logo() const {
	std::cout << "	----------------------------------------------------------------------------------------------\n";
	std::cout << "	                       ******                         ****                                    \n";
	std::cout << "	                      ********                         **                                     \n";
	std::cout << "	                      **    **                         **                                     \n";
	std::cout << "	                      **                               **                                     \n";
	std::cout << "	                      *******   *** ****     ******    **  ***   ******                       \n";
	std::cout << "	                       *******   ********         **   ** **    **    **                      \n";
	std::cout << "	                            **   ***   **    *******   ****     ********                      \n";
	std::cout << "	                      **    **   **    **   **  ****   ****     **                            \n";
	std::cout << "	                      ********   **    **   ** ** **   ** **    **    **                      \n";
	std::cout << "	                       ******   ****   ***   ***  *** ***  ***   ******                       \n";
	std::cout << "	----------------------------------------------------------------------------------------------\n";
}

void Menu::start_menu() {
	bool selection_status = true;
	short int received_symbol;
	do {
		logo();

		if (selection_status) {
			std::cout << "\n\n						" << selection_symbol << " Start game \n";
			std::cout << "\n						" << "  Quit game \n";
		}
		else {
			std::cout << "\n\n						" << "  Start game \n";
			std::cout << "\n						" << selection_symbol << " Quit game \n";
		}

		read_set_symbol(received_symbol, selection_status);

		std::system("cls");

	} while (received_symbol != 13);

	if (!selection_status)
		std::exit(EXIT_SUCCESS);
}

short Menu::difficulty_menu() {
	short int selection_status = 1;
	short int received_symbol;
	do {
		std::cout << "\n\n					----Choose difficulty---- \n";
		if (selection_status == 1) {
			std::cout << "\n\n						" << selection_symbol << " Easy \n";
			std::cout << "						" << "  Normal \n";
			std::cout << "						" << "  Hard \n";
			std::cout << "\n						" << "  Quit game \n";
		}
		else if (selection_status == 2) {
			std::cout << "\n\n						" << "  Easy \n";
			std::cout << "						" << selection_symbol << " Normal \n";
			std::cout << "						" << "  Hard \n";
			std::cout << "\n						" << "  Quit game \n";
		}
		else if (selection_status == 3) {
			std::cout << "\n\n						" << "  Easy \n";
			std::cout << "						" << "  Normal \n";
			std::cout << "						" << selection_symbol << " Hard \n";
			std::cout << "\n						" << "  Quit game \n";
		}
		else {
			std::cout << "\n\n						" << "  Easy \n";
			std::cout << "						" << "  Normal \n";
			std::cout << "						" << "  Hard \n";
			std::cout << "\n						" << selection_symbol << " Quit game \n";
		}

		read_set_symbol(received_symbol, selection_status);

		std::system("cls");

	} while (received_symbol != 13);

	if (selection_status == 4)
		std::exit(EXIT_SUCCESS);
	else if (selection_status == 1)
		return easy;
	else if (selection_status == 2)
		return normal;
	else
		return hard;
}

short Menu::size_menu() {
	short int selection_status = 1;
	short int received_symbol;
	do {
		std::cout << "\n\n					----Choose size playing field---- \n";
		if (selection_status == 1) {
			std::cout << "\n\n						" << selection_symbol << " Small \n";
			std::cout << "						" << "  Normal \n";
			std::cout << "						" << "  Big \n";
			std::cout << "\n						" << "  Quit game \n";
		}
		else if (selection_status == 2) {
			std::cout << "\n\n						" << "  Small \n";
			std::cout << "						" << selection_symbol << " Normal \n";
			std::cout << "						" << "  Big \n";
			std::cout << "\n						" << "  Quit game \n";
		}
		else if (selection_status == 3) {
			std::cout << "\n\n						" << "  Small \n";
			std::cout << "						" << "  Normal \n";
			std::cout << "						" << selection_symbol << " Big \n";
			std::cout << "\n						" << "  Quit game \n";
		}
		else {
			std::cout << "\n\n						" << "  Small \n";
			std::cout << "						" << "  Normal \n";
			std::cout << "						" << "  Big \n";
			std::cout << "\n						" << selection_symbol << " Quit game \n";
		}

		read_set_symbol(received_symbol, selection_status);

		std::system("cls");

	} while (received_symbol != 13);

	if (selection_status == 4)
		std::exit(EXIT_SUCCESS);
	else if (selection_status == 1)
		return small;
	else if (selection_status == 2)
		return standard;
	else
		return big;
}

void Menu::read_set_symbol(short int & received_symbol, bool & selection_status) {
	received_symbol = _getch();
	if (received_symbol == 0 || received_symbol == 224) {
		received_symbol = _getch();
		if (received_symbol == 72 || received_symbol == 80)
			selection_status = !selection_status;
	}
}

void Menu::read_set_symbol(short int & received_symbol, short int & selection_status) {
	received_symbol = _getch();
	if (received_symbol == 0 || received_symbol == 224) {
		received_symbol = _getch();
		if (received_symbol == 72) {
			if (selection_status > 1)
				selection_status -= 1;
			else
				selection_status = 4;
		}
		else if (received_symbol == 80) {
			if (selection_status < 4)
				selection_status += 1;
			else
				selection_status = 1;
		}
	}
}