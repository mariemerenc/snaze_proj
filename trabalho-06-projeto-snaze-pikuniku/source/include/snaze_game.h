#ifndef SNAZE_GAME_H
#define SNAZE_GAME_H

#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <iomanip>
#include <exception>
#include <fstream>
#include <string>
#include <memory>
#include <thread>
#include "../lib/text_color.h"
#include "level.h"
#include "snake.h"
#include "player.h"

class SnazeGame{
    enum GameStatus{
        START = 0,
        END,
        WELCOME,
        READ_INPUT,
        RUNNING
    };

    private:
    struct RunningOptions{
        size_t fps = 12;
        size_t lives = 5;
        size_t foods = 10;
        std::string player_type = "random";
        std::string filename_data;
    };

    RunningOptions m_running_options;
    GameStatus m_game_status;
    std::vector<Level> levels;
    std::vector<Level>::iterator curr_level;
    Snake snake;
    Player player;
    size_t deaths = 0;
    size_t foods_eaten = 0;
    size_t score = 0;
    size_t last_level_score = 0;
    bool dit_it_hit_the_wall = 0;
    bool was_the_seq_found = 0; 

    public: 
    void initialize_game(int argc, char *argv[]);

    void read_file(std::string filename_data);

    bool has_it_end(void){ return m_game_status != GameStatus::END;}
    
    void process(void);

    void update(void);

    void render(void);

    void clear_screen(void);


    private:
    void print_welcome(void);

    void print_syntax(void);

    void move_snake();

    void move_snake_twds_food();
};
#endif 