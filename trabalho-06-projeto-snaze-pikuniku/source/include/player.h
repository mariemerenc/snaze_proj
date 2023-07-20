#ifndef PLAYER_H
#define PLAYER_H

#include <iomanip>
#include <vector>
#include <cstring>
#include <random>
#include <list>
#include <queue>
#include <map>
#include <utility>
using std::pair;

#include "level.h"
#include "snake.h"

struct Point{
    size_t row;
    size_t col;
};

struct queueNode{
    Point pt;
    size_t dist;
};

class Player {
    std::list<Direction> m_directions;
    Snake * m_snake;
    Level * m_lev;
    std::vector<std::vector<char>> m_level_mtx;
    std::vector<std::vector<size_t>> m_food_path_mtx;
    std::vector<Snake> m_snakes_posit;
    std::multimap<pair<size_t, size_t>, Direction> m_snakes_posit_map;
    size_t m_min_dist;

    public:
    void set_snake(Snake *ptr_snake);

    void set_level(Level *ptr_lev);

    void set_snake(Snake snake);

    Direction get_next_move();

    Direction get_next_move_unrandom();

    bool solution();

    Direction get_next_direction();

    int BFS();

    size_t get_min_dist();

    void print_path();

};
#endif

