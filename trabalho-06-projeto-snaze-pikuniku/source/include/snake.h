#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include <text_color.h>

enum Direction{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class Snake{
    Direction m_current_direction = RIGHT;
    std::vector<std::pair<size_t, size_t>> m_snakes_body;
    std::pair<size_t, size_t> m_prev_pos;

    public:
    void set_start_pos(std::pair<size_t, size_t> start_pos);
    void restart_snake(std::pair<size_t, size_t> pos);
    size_t get_snake_size();
    std::pair<size_t, size_t> get_snake_pos();
    void set_direction(Direction direction);
    Direction get_direction();
    std::pair<size_t, size_t> get_prev_pos();
    std::pair<size_t, size_t> get_last_node();
    std::vector<std::pair<size_t, size_t>>::iterator get_it_snake_head();
    std::vector<std::pair<size_t, size_t>>::iterator get_it_snake_tail();
    void move_snake(std::pair<size_t, size_t> new_pos);
    std::pair <size_t, size_t> grow_body();
    void print_node(std::pair<size_t, size_t> node);
    void set_state(Snake snake);
};
#endif