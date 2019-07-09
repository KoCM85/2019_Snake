#ifndef  SNAKE_H

#define SNAKE_H

#include <utility>
#include <set>
#include <atomic>

#include <boost/circular_buffer.hpp>

class Snake {
	// Stores coordinates of the snake
	boost::circular_buffer<std::pair<short, short>> snake_buf;

	// Growth status. true - grow, false - not growing
	bool grow_status;

	// Bite status. true - snake bite the tail, false - snake did not bite the tail
	bool snake_bite_status;

private:
	// Constructor. Sets the maximum snake length. Parameter size field
	Snake(short);

	// Copy constructor
	Snake(const Snake &) = delete;

	// Copy operator=
	Snake & operator=(const Snake &) = delete;

	// Checks snake bite its tail or not. true - snake bite the tail, false - snake did not bite the tail
	bool check_bite();

public:
	// Create single object and returns
	static Snake & get_Instance(short);

	// Snake moves
	void move(std::set<std::pair<short, short>> &, std::atomic<short> &, std::atomic<short> &);

	// Snake grow
	void grow();

	// Returns head of the snake
	std::pair<short, short> head() const;

	// Returns the end of the snake tail
	std::pair<short, short> end_tail() const;

	// Returns the size of the snake
	size_t size();

	// Initialization snake
	void init_snake(std::set<std::pair<short, short>> &, size_t &, std::atomic<short> &, std::atomic<short> &);

	// Return Bite status
	bool bite_status();

	// Clear snake
	void clear();
};

#endif // SNAKE_H