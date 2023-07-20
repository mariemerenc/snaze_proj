#include "snake.h"

void Snake::set_start_pos(std::pair<size_t, size_t> start_pos){
    m_snakes_body.push_back(start_pos);
}

void Snake::restart_snake(std::pair<size_t, size_t> pos){
    m_snakes_body.clear();
    m_snakes_body.push_back(pos);
    m_current_direction = EAST;

}

size_t Snake::get_snake_size(){
    return m_snakes_body.size();
}

std::pair<size_t, size_t> Snake::grow_body(){
    m_snakes_body.push_back(m_prev_pos);
    return m_prev_pos;
}

void Snake::set_direction(Direction direction){
    m_current_direction = direction;
}

Direction Snake::get_direction(){
    return m_current_direction;
}

std::pair<size_t, size_t> Snake::get_prev_pos(){
    return m_prev_pos;
}

std::pair<size_t, size_t> Snake::get_snake_pos(){
    return *m_snakes_body.begin();
}

std::pair<size_t, size_t> Snake::get_last_node(){
    return m_snakes_body.back();
}

std::vector<std::pair<size_t, size_t>>::iterator Snake::get_it_snake_head(){
    return m_snakes_body.begin();
}

std::vector<std::pair<size_t, size_t>>::iterator Snake::get_it_snake_tail(){
    return m_snakes_body.end();
}

void Snake::print_node(std::pair<size_t, size_t> node){
    std::cout << "(" << node.first << ", " << node.second << ")" << std::endl;
}

void Snake::move_snake(std::pair<size_t, size_t> new_pos){
    auto first = m_snakes_body.begin();
    auto curr_node = --m_snakes_body.end();
    m_prev_pos = *curr_node;
    while (curr_node != first){
        *curr_node = *(--curr_node);
    }
    *first = new_pos;
}

void Snake::set_state(Snake snake){
    m_snakes_body = snake.m_snakes_body;
    m_current_direction = snake.m_current_direction;
    m_prev_pos = snake.m_prev_pos;
}



