//
// Created by nik on 12/1/22.
//

#ifndef LANG2_ITERATOR_H
#define LANG2_ITERATOR_H

#include <string>
#include <iterator>
#include <exception>

namespace Lang {

template<typename T>
class Iterator {
public:
	virtual T next() = 0;
	virtual T peek() = 0;
	virtual void skip(int) = 0;
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

	inline void skip(int num) override {
		for (int i = 0; i < num; ++i)
			next();
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

	virtual ~String_Iterator() = default;

protected:
	const std::string text;

private:
	iterator iter;
	iterator end;
};

class Indexed_Char_Iterator : public String_Iterator {
public:
	using String_Iterator::String_Iterator;

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

protected:
	int row = 0;
	int col = 0;
};

}

#endif //LANG2_ITERATOR_H
