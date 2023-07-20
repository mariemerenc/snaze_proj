#include "player.h"

void PLayer::set_snake(Snake *ptr_snake){
    m_snake = ptr_snake;
}

void Player::set_level(Level *ptr_lev){
    m_lev = ptr_lev;
}

Direction Player::get_next_move(){
    auto pos = m_snake->get_head_pos();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    int random = dis(gen);
    
    if(m_snake->get_direction == EAST){
        if(!(m_lev->can_move_to(pos.row, pos.col + 1) || m_lev->can_move_to(pos.first-1, pos.second) || m_lev->can_move_to(pos.first+1, pos.second))){
            return NONE;
        }

        while(true){
            choice = dis(gen);

            if(choice == 0){
                if(m_lev->can_move_to(pos.first, pos.second+1)){
                    return EAST;
                }
            }
            else if(choice == 1){
                if(m_lev->can_move_to(pos.first-1, pos.second)){
                    return NORTH;
                }
            }
            else if(choice == 2){
                if(m_lev->can_move_to(pos.first+1, pos.second)){
                    return SOUTH;
                }
            }
        }
    }

    else if(m_snake->get_direction == WEST){
        if(!(m_lev->can_go(pos.first, pos.second - 1) || m_lev->can_go(pos.first-1, pos.second) || m_lev->can_go(pos.first+1, pos.second))){
            return NONE;
        }

        while(true){
            choice = dis(gen);

            if(choice == 0){
                if(m_lev->can_move_to(pos.first, pos.second-1)){
                    return WEST;
                }
            }
            else if(choice == 1){
                if(m_lev->can_move_to(pos.first-1, pos.second)){
                    return NORTH;
                }
            }
            else if(choice == 2){
                if(m_lev->can_move_to(pos.first+1, pos.second)){
                    return SOUTH;
                }
            }
        }
    }

    else if(m_snake->get_direction() == NORTH){
        if(!(m_lev->can_move_to(pos.first-1, pos.second) || m_lev->can_move_to(pos.first, pos.second-1) || m_lev->can_move_to(pos.first, pos.second+1))){
            return NONE;
        }

        while(true){
            choice = dis(gen);

            if(choice == 0){
                if(m_lev->can_move_to(pos.first-1, pos.second)){
                    return NORTH;
                }
            }
            else if(choice == 1){
                if(m_lev->can_move_to(pos.first, pos.second+1)){
                    return EAST;
                }if(m_lev->can_move_to(pos.first, pos.second-1)){
                    return WEST;
                }
            }
            else if(choice == 2){
                if(m_lev->can_move_to(pos.first, pos.second-1)){
                    return WEST;
            }
        }
    }

    else if(m_snake->get_direction() == SOUTH){
        if(!(m_lev->can_move_to(pos.first+1, pos.second) || m_lev->can_move_to(pos.first, pos.second-1) || m_lev->can_move_to(pos.first, pos.second+1))){
            return NONE;
        }

        while(true){
            choice = dis(gen);

            if(choice == 0){
                if(m_lev->can_move_to(pos.first+1, pos.second)){
                    return SOUTH;
                }
            }
            else if(choice == 1){
                if(m_lev->can_move_to(pos.first, pos.second+1)){
                    return EAST;
                }
            }
            else if(choice == 2){
                if(m_lev->can_move_to(pos.first, pos.second-1)){
                    return WEST;
                }
            }
        }
    }

    return NONE;
}

Direction Player::get_next_move_unrandom(){
    
}