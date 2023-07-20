#include "../include/player.h"
#include "../include/snake.h"
#include "../include/level.h"


void Player::set_snake(Snake *ptr_snake){
    m_snake = ptr_snake;
}

void Player::set_level(Level *ptr_lev){
    m_lev = ptr_lev;
}

Direction Player::get_next_move(){
    auto pos = m_snake->get_snake_pos();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    int choice = dis(gen);
    
    if(m_snake->get_direction() == EAST){
        if(!(m_lev->can_move_to(pos.first, pos.second + 1) || m_lev->can_move_to(pos.first-1, pos.second) || m_lev->can_move_to(pos.first+1, pos.second))){
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

    else if(m_snake->get_direction() == WEST){
        if(!(m_lev->can_move_to(pos.first, pos.second - 1) || m_lev->can_move_to(pos.first-1, pos.second) || m_lev->can_move_to(pos.first+1, pos.second))){
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
    auto pos = m_snake->get_snake_pos();

    if(m_snake->get_direction() == EAST){
        if(!(m_lev->can_move_to(pos.first, pos.second+1) || m_lev->can_move_to(pos.first-1, pos.second) || m_lev->can_move_to(pos.first+1, pos.second))){
            return NONE;
        }

        if(m_lev->can_move_to(pos.first, pos.second+1)){
            return EAST;
        }

        if(m_lev->can_move_to(pos.first-1, pos.second)){
            return NORTH;
        }

        if(m_lev->can_move_to(pos.first+1, pos.second)){
            return SOUTH;
        }
    }

    else if(m_snake->get_direction() == WEST){
        if(!(m_lev->can_move_to(pos.first, pos.second-1) || m_lev->can_move_to(pos.first-1, pos.second) || m_lev->can_move_to(pos.first+1, pos.second))){
            return NONE;
        }

        if(m_lev->can_move_to(pos.first, pos.second-1)){
            return WEST;
        }

        if(m_lev->can_move_to(pos.first-1, pos.second)){
            return NORTH;
        }

        if(m_lev->can_move_to(pos.first+1, pos.second)){
            return SOUTH;
        }
    }

    else if(m_snake->get_direction() == NORTH){
        if(!(m_lev->can_move_to(pos.first-1, pos.second) || m_lev->can_move_to(pos.first, pos.second-1) || m_lev->can_move_to(pos.first, pos.second+1))){
            return NONE;
        }

        if(m_lev->can_move_to(pos.first-1, pos.second)){
            return NORTH;
        }

        if(m_lev->can_move_to(pos.first, pos.second+1)){
            return EAST;
        }

        if(m_lev->can_move_to(pos.first, pos.second-1)){
            return WEST;
        }
    }

    else if(m_snake->get_direction() == SOUTH){
        if(!(m_lev->can_move_to(pos.first+1, pos.second) || m_lev->can_move_to(pos.first, pos.second-1) || m_lev->can_move_to(pos.first, pos.second+1))){
            return NONE;
        }

        if(m_lev->can_move_to(pos.first+1, pos.second)){
            return SOUTH;
        }

        if(m_lev->can_move_to(pos.first, pos.second+1)){
            return EAST;
        }

        if(m_lev->can_move_to(pos.first, pos.second-1)){
            return WEST;
        }
    }
    return NONE;
}

bool Player::solution(){
    auto backup_matrix = m_lev->get_matrix();
    m_directions.clear();

    int dist = BFS();

    if(dist == -1){
        std::cout << "";
        m_min_dist = dist;

        return 0;
    }

    auto food_pos = m_lev->get_food_pos();
    auto head_pos = m_snake->get_snake_pos();
    Snake init_snake = *m_snake;
    m_snakes_posit.push_back(init_snake);
    m_snakes_posit_map.insert({head_pos, init_snake.get_direction()});

    auto first = m_snake->get_it_snake_head();
    auto curr_node = m_snake->get_it_snake_head()+1;
    auto last = m_snake->get_it_snake_tail();

    while(food_pos != head_pos){
        auto direction = m_snake->get_direction();
        size_t num;

        if(direction == EAST){
            num = m_level_mtx[head_pos.first][head_pos.second+1];

            if(m_level_mtx[head_pos.first-1][head_pos.second] < num ){
                num = m_level_mtx[head_pos.first+1][head_pos.second];
                direction = SOUTH;
            }
            
            if(m_level_mtx[head_pos.first+1][head_pos.second] < num ){
                num = m_level_mtx[head_pos.first+1][head_pos.second];
                direction = NORTH;
            }
        }

        else if(direction == WEST){
            num = m_level_mtx[head_pos.first][head_pos.second-1];

            if(m_level_mtx[head_pos.first-1][head_pos.second] < num ){
                num = m_level_mtx[head_pos.first-1][head_pos.second];
                direction = NORTH;
            }

            if(m_level_mtx[head_pos.first+1][head_pos.second] < num ){
                num = m_level_mtx[head_pos.first+1][head_pos.second];
                direction = SOUTH;
            }
        }

        else if(direction == NORTH){
            num = m_level_mtx[head_pos.first-1][head_pos.second];

            if(m_level_mtx[head_pos.first][head_pos.second+1] < num ){
                num = m_level_mtx[head_pos.first][head_pos.second+1];
                direction = EAST;
            }

            if(m_level_mtx[head_pos.first][head_pos.second-1] < num ){
                num = m_level_mtx[head_pos.first][head_pos.second-1];
                direction = WEST;
            }
        }

        else if(direction == SOUTH){
            num = m_level_mtx[head_pos.first+1][head_pos.second];

            if(m_level_mtx[head_pos.first][head_pos.second+1] < num ){
                num = m_level_mtx[head_pos.first][head_pos.second+1];
                direction = EAST;
            }

            if(m_level_mtx[head_pos.first][head_pos.second-1] < num ){
                num = m_level_mtx[head_pos.first][head_pos.second-1];
                direction = WEST;
            }
        }


        if(direction == EAST){
            head_pos.second++;
            m_snake->set_direction(EAST);
        }

        else if(direction == WEST){
            head_pos.second--;
            m_snake->set_direction(WEST);
        }

        else if(direction == NORTH){
            head_pos.first--;
            m_snake->set_direction(NORTH);
        }

        else if(direction == SOUTH){
            head_pos.first++;
            m_snake->set_direction(SOUTH);
        }

        m_snake->move_snake(head_pos);
        m_directions.push_back(direction);
        m_snakes_posit.push_back(*m_snake);
        head_pos = m_snake->get_snake_pos();
    }

    m_snake->set_state(init_snake);
    m_snakes_posit.push_back(init_snake);
    m_snakes_posit_map.clear();
    m_lev->set_matrix(backup_matrix);

    return 1;
}

Direction Player::get_next_direction(){
    if(m_directions.empty()){
        return NONE;
    }

    auto direction = m_directions.front();
    m_directions.pop_front();

    return direction;
}

int Player::BFS(){
    m_level_mtx.clear();
    Point src{m_lev->get_food_pos().first, m_lev->get_food_pos().second};
    Point dest{m_snake->get_snake_pos().first, m_snake->get_snake_pos().second};
    int row_num[] = {1, 0, 0, -1};
    int col_num[] = {0, -1, 1, 0};
    size_t rows{m_lev->get_mtx_dimensions().first};
    size_t cols{m_lev->get_mtx_dimensions().second};

    bool visited[rows][cols];
    memset(visited, false, sizeof visited);
    int matrix [rows][cols];
    memset(matrix, -1, sizeof matrix);

    visited[src.row][src.col] = true;

    std::queue<queueNode> q;

    queueNode s = {src, 0};
    q.push(s);
    int x = src.row;
    int y = src.col;
    matrix[x][y] = 0;
    auto direction = m_snake->get_direction();

    while(!q.empty()){
        queueNode curr = q.front();
        Point pt = curr.pt;

        if(pt.row == dest.row && pt.col == dest.col){
            std::vector<char> other_row;

            for(auto i{0}; i<rows; i++){
                for(auto j{0}; j<cols; j++){
                    if(matrix[i][j] == -1){
                        other_row.push_back(curr.dist + 1);
                    }
                    else{
                        other_row.push_back(matrix[i][j]);
                    }
                }

                m_level_mtx.push_back((std::vector<char>)other_row);
                other_row.clear();
            }

            q.pop();

        for(int i = 0; i < 4; i++){
            size_t row = pt.row + row_num[i];
            size_t col = pt.col + col_num[i];

            if(m_lev->can_move_to(row, col) && !visited[row][col] && !((row == dest.row && col == dest.col) && matrix[row][col] == i)){
                visited[row][col] = true;
                queueNode adjCell = {{row, col}, curr.dist + 1};
                q.push(adjCell);
                matrix[row][col] = curr.dist + 1;
            }
        }
    }
    
    }
    return -1;
}

void Player::print_path(){
    for(auto i{0}; i<m_level_mtx.size(); i++){
        for(auto j{0}; j<m_level_mtx[i].size(); j++){
            std::cout << std::setw(3) << m_level_mtx[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}