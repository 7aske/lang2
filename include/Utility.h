//
// Created by nik on 12/1/22.
//

#ifndef LANG2_UTILITY_H
#define LANG2_UTILITY_H

#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <strstream>
#include <algorithm>
#include <iomanip>

static constexpr char const* RESET = "\033[0m";
static constexpr char const* BLACK = "\033[30m";  /* Black */
static constexpr char const* RED = "\033[31m";    /* Red */
static constexpr char const* GREEN = "\033[32m";  /* Green */
static constexpr char const* YELLOW = "\033[33m"; /* Yellow */
static constexpr char const* BLUE = "\033[34m";   /* Blue */
static constexpr char const* MAGENTA = "\033[35m";/* Magenta */
static constexpr char const* CYAN = "\033[36m";   /* Cyan */
static constexpr char const* WHITE = "\033[37m";  /* White */
static constexpr char const* BOLDBLACK = "\033[1m\033[30m";  /* Bold Black */
static constexpr char const* BOLDRED = "\033[1m\033[31m";    /* Bold Red */
static constexpr char const* BOLDGREEN = "\033[1m\033[32m";  /* Bold Green */
static constexpr char const* BOLDYELLOW = "\033[1m\033[33m"; /* Bold Yellow */
static constexpr char const* BOLDBLUE = "\033[1m\033[34m";   /* Bold Blue */
static constexpr char const* BOLDMAGENTA = "\033[1m\033[35m";/* Bold Magenta */
static constexpr char const* BOLDCYAN = "\033[1m\033[36m";   /* Bold Cyan */
static constexpr char const* BOLDWHITE = "\033[1m\033[37m";  /* Bold White */

namespace Lang {

void
print_location(const std::string& text, int row, int start_char, int end_char);

std::string parenthesize(std::string const& name, std::string const& left);

std::string parenthesize(std::string const& name, std::string const& left, std::string const& right);

bool string_to_bool(std::string const& ip);


}

#endif //LANG2_UTILITY_H
