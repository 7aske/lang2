//
// Created by nik on 3/16/23.
//

#include "Interpreter.h"

void Lang::Interpreter::run() {
	for (const auto& interp: interpretables) {
		try {
			interp->interpret(this);
		} catch (Interpreter_Error& ex) {
			std::cerr << MAGENTA << "Runtime error:" << std::endl << RESET;
			print_location(text, ex.get_row(), ex.get_start_col(),
						   ex.get_end_col());
			std::cerr << RED << ex.what() << std::endl << RESET;
			return;
		}
	}
}
