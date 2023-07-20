#include "level.h"

void Level::push_row(std::vector<char> row){
    m_level_mtx.push_back(row);
}

void Level::set_directions(int rows, int cols){
    m_rows = rows;
    m_cols = cols;
}

std::pair <size_t, size_t> Level::get_mtx_dimensions(){
    std::pair<size_t,size_t> dimensions{m_rows, m_cols};
    return dimensions;
}

void Level::clear(){
    m_rows = m_cols = 0;
    m_level_mtx.clear();
}

void Level::print_level(){
    std::ostringstream oss;

    for(auto i{0}; i<m_rows; i++){
        for(auto j{0}; j<m_cols; j++){
            switch(m_level_mtx[i][j]){
                case ' ':
                    std::cout << " ";
                    break;
                
                case 'o':
                    std::cout << "●";
                    break;
                
                case '#':
                    std::cout << "█";
                    break;

                case '*':
                    std::cout << "✱";
                    break;

                case '+':
                    std::cout << "✱";
                    break;

                case '<':
                    std::cout << "<";
                    break;

                case '>':
                    std::cout << ">";
                    break;

                case 'v':
                    std::cout << "v";
                    break;

                case '^':
                    std::cout << "∧";
                    break;

                case '.':
                    std::cout << " ";
                    break;

                case 'x':
                    std::cout << "×";
                    break;

                case '-':
                    std::cout << "◌";
                    break;
            }
        }
        std::cout << "\n"; 
    }
}

void Level::print_level_old(){
    for(auto i{0}; i<m_rows; i++){
        for(auto j{0}; j<m_cols; j++){
            std::cout << m_level_mtx[i][j];
        }
        std::cout << "\n"; 
    }
}

void Level::place_food(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> r_dist(0, m_rows-1);
    std::uniform_int_distribution<> c_dist(0, m_cols-1);

    auto r = r_dist(gen);
    auto c = c_dist(gen);

    while(m_level_mtx[r][c] != ' '){
        r = r_dist(gen);
        c = c_dist(gen);
    }

    m_level_mtx[r][c] = 'o';
    m_food_pos.first = r;
    m_food_pos.second = c;
}

std::pair<size_t, size_t> Level::get_food_pos(){
    return m_food_pos;
}

void Level::set_snake_start_pos(int row, int col){
    m_has_start_pos = 1;
    m_snake_start_pos = {row, col};
}

std::pair<size_t, size_t> Level::get_snake_start_pos(){
    return m_snake_start_pos;
}  

bool Level::has_start_pos(){
    return m_has_start_pos;
}

char Level::get_element_at(int row, int col){
    return m_level_mtx[row][col];
}

bool Level::can_move_to(int row, int col){
    if(m_level_mtx[row][col] != '#' || m_level_mtx[row][col] != '*'){
        return 1;
    }
    return 0;
}

bool Level::is_it_food(int row, int col){
    if(m_level_mtx[row][col] == 'o'){
        return 1;
    }
    return 0;
}

bool Level::is_it_wall(std::pair<size_t, size_t> pos){
    if(m_level_mtx[pos.first][pos.second] == '#'){
        return 1;
    }
    return 0;
}

void Level::set_element_at(int row, int col, char element){
    m_level_mtx[row][col] = element;
}

void Level::set_element_at(std::pair<size_t, size_t> pos, char element){
    m_level_mtx[pos.first][pos.second] = element;
}

void Level::set_matrix(vector<vector<char>> mtx){
    m_level_mtx = mtx;
}

vector<vector<char>> Level::get_matrix(){
    return m_level_mtx;
}


