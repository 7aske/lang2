//
// Created by nik on 12/1/22.
//

#include "Utility.h"

namespace Lang {

inline void print_prefix(std::string_view const& line_no) {
	std::ranges::for_each(line_no,
						  [](const char&) { std::cerr << ' '; });
	std::cerr << BLUE << " |" << RESET;
}

inline void print_prefix_with_line_no(const std::string& line_no) {
	std::cerr << BLUE << line_no << " |" << RESET;
}

inline void print_underline(int start_char, int end_char) {
	for (int i = 0; i < start_char; ++i)
		std::cerr << " ";
	for (int i = 0; i < end_char - start_char; ++i)
		std::cerr << RED << "^";
	std::cerr << RESET << " ";
}

inline void print_error_line(std::string line, int start_char, int end_char) {
	for (int i = 0; i < start_char; ++i) {
		std::cerr << line[i];
	}
	std::cerr << BOLDRED;
	for (int i = start_char; i < end_char; ++i) {
		std::cerr << line[i];
	}
	std::cerr << RESET;
	for (int i = end_char; i < line.size(); ++i) {
		std::cerr << line[i];
	}
	std::cerr << std::endl;
}

inline std::string get_error_line(const std::string& text, int row) {
	std::istrstream in(text.c_str());

	std::string line;
	line.reserve(256);


	for (int i = 0; i < row + 1; ++i)
		std::getline(in, line);

	std::ranges::replace(std::begin(line), std::end(line), '\t', ' ');

	return line;
}

void
print_location(const std::string& text, int row, int start_char, int end_char) {
	std::string line_no = std::to_string(row + 1);

	std::string line = get_error_line(text, row);

	print_prefix(line_no);
	std::cerr << std::endl;
	print_prefix_with_line_no(line_no);

	print_error_line(line, start_char, end_char);

	print_prefix(line_no);
	print_underline(start_char, end_char);
}

template<class T>
std::string
parenthesize(std::string const& name, std::initializer_list<T> list) {
	std::stringstream buffer;

	buffer << "( " << name;
	for (auto& elem: list) {
		buffer << " " << elem;
	}
	buffer << " )" << std::endl;

	return buffer.str();
}

}