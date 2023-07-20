#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include "text_color.h"

class Level{
    int m_rows;
    int m_cols;
    std::vector<std::vector<char>> m_level_mtx;
    std::pair<size_t, size_t> m_snake_start_pos;
    bool m_has_start_pos = 0;
    std::pair<size_t, size_t> m_food_pos;

    public:
    void push_row(std::vector<char> row);
    void set_directions(int rows, int cols);
    std::pair <size_t, size_t> get_mtx_dimensions();
    void clear();
    void print_level();
    void print_level_old();
    void place_food();
    std::pair<size_t, size_t> get_food_pos();
    void set_snake_start_pos(std::pair<size_t, size_t> snake_start_pos);
};

