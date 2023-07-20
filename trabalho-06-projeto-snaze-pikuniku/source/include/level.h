#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <sstream>
#include <random>
#include <vector>

class Level{
    int m_rows;
    int m_cols;
    std::vector<std::vector<char>> m_level_mtx;
    std::pair<size_t, size_t> m_snake_start_pos;
    bool m_has_start_pos = 0;
    std::pair<size_t, size_t> m_food_pos;

    public:
    void push_row(std::vector<char> row);
    void set_dimensions(int rows, int cols);
    std::pair <size_t, size_t> get_mtx_dimensions();
    void clear();
    void print_level();
    void print_level_old();
    void place_food();
    std::pair<size_t, size_t> get_food_pos();
    void set_snake_start_pos(int row, int col);
    std::pair<size_t, size_t> get_snake_start_pos();
    bool has_start_pos();
    char get_element_at(int row, int col);
    bool can_move_to(int row, int col);
    bool is_it_food(int row, int col);
    bool is_it_wall(std::pair<size_t, size_t> pos);
    void set_element_at(int row, int col, char element);
    void set_element_at(std::pair<size_t, size_t> pos, char element);
    void set_matrix(std::vector<std::vector<char>> mtx);
    std::vector<std::vector<char>> get_matrix();

};
#endif 

