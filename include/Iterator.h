//
// Created by nik on 12/1/22.
//

#ifndef LANG2_ITERATOR_H
#define LANG2_ITERATOR_H

#include <string>
#include <iterator>
#include <exception>

namespace Lang::Iterator {

template<typename T>
class Iterator {
public:
	virtual T next() = 0;
	virtual T peek() = 0;
	virtual T offset(int) = 0;
	virtual bool has_next() = 0;

protected:
	Iterator() = default;
	~Iterator() = default;
};

class String_Iterator : public Iterator<char> {
public:
	using iterator = std::basic_string<char, std::char_traits<char>, std::allocator<char>>::const_iterator;

	explicit String_Iterator(const std::string& text) : text(text), iter(text.cbegin()), end(text.cend()) {}

	char next() override {
		if (!has_next())
			throw std::range_error("Index out of range");
		return *(iter++);
	}

	inline char peek() override {
		return *iter;
	}

	inline char offset(int offset) override {
		return *(iter + offset);
	}

	inline bool has_next() override {
		return iter < end;
	}

protected:
	iterator iter;
	iterator end;
	const std::string text;
};

class Indexed_Char_Iterator : public String_Iterator {
public:
	explicit Indexed_Char_Iterator(std::string& text) : String_Iterator(text) {}

	char next() override {
		char next = String_Iterator::next();

		if (next == '\n') {
			row++;
			col = 0;
		} else {
			col++;
		}

		return next;
	}

	bool has_next() override {
		return String_Iterator::has_next();
	}

protected:
	int row = 0;
	int col = 0;

};

}

#endif //LANG2_ITERATOR_H
