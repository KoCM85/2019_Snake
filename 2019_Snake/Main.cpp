//#include <iostream>
//#include <vector>
//
//int main() {
//	std::vector<char> vect;
//	vect.reserve(10);
//	vect.push_back(254);
//	vect.push_back(253);
//
//	size_t end = vect.size() > 5 ? 5 : vect.size();
//	do {
//		for (size_t index = 0; index < end; ++index)
//			std::cout << vect[index];
//		std::cout << '\n';
//		end += vect.size() - end > 5 ? 5 : vect.size();
//	} while (end < vect.size());
//
//	std::cin.get();
//	std::cin.get();
//	return 0;
//}

//#include <cstdio>
//#include <conio.h>
//#include <iostream>
//
//int main()
//{
//	unsigned char ch;
//	do
//	{
//		ch = _getch();
//		std::cout << "befor: " << ch << ' ' << (int)ch << '\n';
//		if (ch == 0 || ch == 224) //Cheking function key or an arrow key
//		{
//			ch = _getch();
//			switch (ch)
//			{
//			case 75: printf("left\n"); break;
//			case 77: printf("right\n"); break;
//			case 72: printf("up\n"); break;
//			case 80: printf("down\n"); break;
//			default: printf("unknown\n");
//			}
//			std::cout << ch << ' ' << (int)ch << '\n';
//		}
//	} while (ch != 27);
//	
//	std::cout << ch << ' ' << (int)ch << '\n';
//
//	std::cin.get();
//	return 0;
//}

#include "Menu.h"
#include "Snake.h"
#include "Field.h"

#include <iostream>

int main() {
	Menu menu;
	std::pair<short, short> difficulty_size;
	difficulty_size = menu.launch();
	
	Field & play_field = Field::get_Instance(difficulty_size);

	play_field.launch();

	std::cin.get();
}