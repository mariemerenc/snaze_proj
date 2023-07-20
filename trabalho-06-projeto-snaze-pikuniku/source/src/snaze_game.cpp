#include "../include/snaze_game.h"
#include "../include/level.h"
#include "../include/snake.h"
#include "../include/player.h"


void SnazeGame::print_syntax(void){
    std::cout << "print_syntax: ./snaze [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "print_syntax: snaze [<options>] <input_level_file>\n"
         << "   Game simulation options:\n"
         << "       --help                  Print this help text.\n"
         << "       --fps <num>             Number of frames (board) presented per second. Default = 12.\n"
         << "       --lives <num>           Number of lives the snake shall have. Default = 5.\n"
         << "       --food <num>            Number of food pellets for the entire simulation. Default = 10.\n"
         << "       --playertype <type>     Type of snake intelligence: random, backtracking. Default = backtracking.\n";
    exit(1);
}

void SnazeGame::print_welcome(void){
    std::ostringstream oss;
    oss << "---------> Welcome to the Snake Maze [SNAZE] <---------\n"
        << "      Copyright © 2023, Ana Carolina, Mariana\n"
        << "=======================================================\n";

}

void SnazeGame::initialize_game(int argc, char *argv[]){
    std::string str_help{"--help"}, s_fps{"--fps"}, s_lives{"--lives"}, s_food{"--food"}, s_playertype{"--playertype"};
    std::ostringstream oss;

    //* Process the arguments from the command line.
    for(int i{1}; i < argc; i++){
        // Transform the arguments to string and lower case.
        std::string str(argv[i]);
        for (size_t j{0}; j < str.length(); j++) {
            str[j] = std::tolower(str[j]); 
        }
        if(str == s_fps){
            if(i+1 == argc){
                oss << ">>> ERROR! Missing fps value.\n";
                oss.clear();
                print_syntax();
            }
            try{
                m_running_options.fps = std::stoi(argv[i+1]);
            }
            catch( const std::invalid_argument & e ){
                oss << ">>> ERROR! Value '" << argv[i+1] << "' invalid for 'fps'.\n";
                oss.clear();
                print_syntax();
            }
            catch( const std::out_of_range & e ){
                oss << ">>> ERROR! Value '" << argv[i+1] << "' of 'fps' out of range.\n";
                oss.clear();
                print_syntax();
            }
            if(m_running_options.fps < 1 || 24 < m_running_options.fps){
                oss << ">>> ERROR! Value '" << argv[i+1] << "' invalid for 'fps'. Valid range is [1,24].\n";
                oss.clear();
                print_syntax();
            }
            i++;
        }

        else if(str == s_lives){
            if(i+1 == argc){
                oss << ">>> ERROR! Missing 'number of lives' value.\n";
                oss.clear();
                print_syntax();
            }
            try{
                m_running_options.lives = std::stoi(argv[i+1]);
            }
            catch( const std::invalid_argument & e ){
                oss << ">>> ERROR! Value '" << argv[i+1] << "' invalid for 'number of lives'.\n";
                oss.clear();
                print_syntax();
            }
            catch( const std::out_of_range & e ){
                oss << ">>> ERROR! Value '" << argv[i+1] << "' for 'number of lives' out of range.\n";
                oss.clear();
                print_syntax();
            }
            if(m_running_options.lives < 1 || 15 < m_running_options.lives){
                oss << ">>> ERROR! Value '" << argv[i+1] << "' invalid for 'number of lives'. Valid range is [1,15].\n";
                oss.clear();
                print_syntax();
            }
            i++;
        }

        else if(str == s_food){
            if(i+1 == argc){
                oss << ">>> ERROR! Missing 'number of food pellets' value.\n";
                oss.clear();
                print_syntax();
            }
            try{
                m_running_options.foods = std::stoi(argv[i+1]);
            }
            catch( const std::invalid_argument & e ){
                oss << ">>> ERROR! Value '" << argv[i+1] << "' invalid for 'number of food pellets'.\n";
                oss.clear();
                print_syntax();
            }
            catch( const std::out_of_range & e ){
                oss << ">>> ERROR! Value '" << argv[i+1] << "' for 'number of food pellets' out of range.\n";
                oss.clear();
                print_syntax();
            }
            if(m_running_options.foods < 1 || 15 < m_running_options.foods){
                oss << ">>> ERROR! Value '" << argv[i+1] << "' invalid for 'number of food pellets'. Valid range is [1,15].\n";
                oss.clear();
                print_syntax();
            }
            i++;
        }

        else if(str == s_playertype){
            if(i+1 == argc){
                oss << ">>> ERROR! Missing 'player type' value.\n";
                oss.clear();
                print_syntax();
            }
            // Transform the playertype to string and lower case.
            std::string pt_str(argv[i+1]);
            for (size_t j{0}; j < str.length(); j++) {
                pt_str[j] = std::tolower(pt_str[j]); 
            }
            m_running_options.player_type = pt_str;
            if( !(m_running_options.player_type == "random" || m_running_options.player_type == "backtracking") ){
                oss << ">>> ERROR! Type '" << argv[i+1] << "' invalid for 'player type'.\n";
                oss.clear();
                print_syntax();
            }
            i++;
        }

        else if(str == str_help) print_syntax();

        else{
            m_running_options.filename_data = argv[i];
        }
    }
    if(m_running_options.filename_data.empty()){
        oss << ">>> ERROR! Missing file name.\n";
        oss.clear();
        print_syntax();
    }

    // Set the initial game state.
    m_game_status = GameStatus::START;
}

void SnazeGame::read_file(std::string filename_data) {
    
    std::ifstream ifs(filename_data);
    std::ostringstream oss;
    
    if (not ifs.is_open())
    {
        // Print an error and exit.
        oss << "\n>>> ERROR! \"" << filename_data << "\" couldn't be opened for reading! This file probably doesn't exist.\n";
        oss.clear();
        exit(1);
    }

    std::string line;
    std::getline(ifs, line);
    if (ifs.fail()) {
        // Print an error and exit.
        oss << "\n>>> ERROR! We couldn't read \"" << filename_data << "\"! It isn't a data file.\n";
        oss.clear();
        exit(1);
    }
    ifs.seekg(0); // Put pointer at the beginning of the file

    std::string strInput;
    char point;
    int n_rows, n_cols;
    Level lv;

    while(ifs){
        ifs >> strInput;
        if(strInput == "") break;
        try{
                n_rows = stoi(strInput);
            }
            catch( const std::invalid_argument & e ){
                oss << ">>> ERROR! Value '" << strInput << "' invalid for 'number of rows'.\n";
                oss.clear();
                print_syntax();
            }
            catch( const std::out_of_range & e ){
                oss << ">>> ERROR! Value '" << strInput << "' for 'number of rows' out of range.\n";
                oss.clear();
                print_syntax();
            }
            if(n_rows < 1 || 100 < n_rows){
                oss << ">>> ERROR! Value '" << strInput << "' invalid for 'number of rows'.\n";
                oss.clear();
                print_syntax();
            }
        ifs >> strInput;
        try{
                n_cols = stoi(strInput);
            }
            catch( const std::invalid_argument & e ){
                oss << ">>> ERROR! Value '" << strInput << "' invalid for 'number of cols'.\n";
                oss.clear();
                print_syntax();
            }
            catch( const std::out_of_range & e ){
                oss << ">>> ERROR! Value '" << strInput << "' for 'number of cols' out of range.\n";
                oss.clear();
                print_syntax();
            }
            if(n_cols < 1 || 100 < n_cols){
                oss << ">>> ERROR! Value '" << strInput << "' invalid for 'number of cols'.\n";
                oss.clear();
                print_syntax();
            }
        lv.set_dimensions(n_rows, n_cols);
        std::vector<char> row;                  // Vector to store a row of the level.
        getline(ifs, strInput);                 // Gets "\n".
        for(auto i{0}; i < n_rows; i++){
            for(auto j{0}; j < n_cols; j++){
                ifs.get(point);
                if(point != '#' && point != '*' && point != '.' && point != ' '){
                    // Print an error and exit.
                    oss << "\n>>> ERROR! We couldn't read \"" << filename_data << "\" correctly, the file is corrupt.\n";
                    oss.clear();
                    exit(1);
                }
                row.push_back(point);
                if(point == '*'){
                    lv.set_snake_start_pos(i, j);
                }
            }
            lv.push_row(row);           // Push back a new row in the level matrix.
            row.clear();
            getline(ifs, strInput);     // Gets "\n". 
        }
        if(lv.has_start_pos()) levels.push_back(lv);         // Push back a new level in the levels vector.
        lv.clear();
    }
}

void SnazeGame::process(void)
{
    if( m_game_status == GameStatus::WELCOME )
    {
        read_file(m_running_options.filename_data);
    }
    else if(m_game_status == GameStatus::READ_INPUT)
    {
        while (getchar() != '\n') {
            // Waits for the user to press enter to start the animation.
        }
    }
    else if(m_game_status == GameStatus::RUNNING){
        if ((dit_it_hit_the_wall && m_running_options.lives > 0) || (foods_eaten == m_running_options.foods && curr_level != levels.end()-1)) {
            while (getchar() != '\n') {
                // Waits for the user to press enter to continue the game.
            }
        }
        std::chrono::milliseconds  duration{ 1000/m_running_options.fps };
		std::this_thread::sleep_for( duration );
    }
}

void SnazeGame::update(void)
{
    if( m_game_status == GameStatus::START )
    {
        m_game_status = GameStatus::WELCOME;
    }
    else if ( m_game_status == GameStatus::WELCOME )
    {
        m_game_status = GameStatus::READ_INPUT;
    }
    else if ( m_game_status == GameStatus::READ_INPUT )
    {
        m_game_status = GameStatus::RUNNING;
        curr_level = levels.begin();                                                 // Iterator to the current level.
        snake.set_start_pos( curr_level->get_snake_start_pos() );                          // Sets snake's start position.
        curr_level->set_element_at(curr_level->get_snake_start_pos(), '<');    // Places snake's head in the start position of the level matrix.
        curr_level->place_food();                                                    // Places the food pellet in the level matrix.
        player.set_level(&(*curr_level));                                           // Binds the level to the player.
        player.set_snake(&snake);                                                      // Binds the snake to the player.
        if(m_running_options.player_type == "backtracking") was_the_seq_found = player.solution();  // Tries to find a solution to lead the snake to the food pellet.
    }
    else if ( m_game_status == GameStatus::RUNNING )
    {
        // There is no more lives.
        if(m_running_options.lives == 0){
            m_game_status = GameStatus::END;
            return;
        }
        // Snake has eaten all level's food pellets.
        if(foods_eaten == m_running_options.foods){
            // If current level is not the last level.
            if( curr_level != levels.end()-1 ){
                curr_level++;                    // Goes to the next level.
                foods_eaten = 0;                     // restart_snakes number of food pellets eaten.
                last_level_score = score;           // Set the score of the last level.
                snake.restart_snake(curr_level->get_snake_start_pos());                                  // restart_snakes the snake with the new level start position.
                curr_level->set_element_at(curr_level->get_snake_start_pos(), '<');    // Places snake's head in the start position.
                curr_level->place_food();                                                    // Places the food pellet in the level matrix.
                player.set_level(&(*curr_level));                                           // Binds the level to the player.
                player.set_snake(&snake);                                                      // Binds the snake to the player.
                if(m_running_options.player_type == "backtracking") was_the_seq_found = player.solution();  // Tries to find a solution to lead the snake to the food pellet.
                return;
            }
            else{
                m_game_status = GameStatus::END;
                return;
            }
        }

        auto first = snake.get_it_snake_head();              // Iterator to snake's head.
        auto current_node= ++snake.get_it_snake_head();      // Iterator to the second node of the snake.                            
        auto last = snake.get_it_snake_tail();                // Iterator to the position just after the last node of the snake's body.

        // If snake grew up, find new sequence of directions towards food pellet.
        if(snake.get_last_node() == snake.get_prev_pos() && !has_it_end){
            if(m_running_options.player_type == "backtracking") was_the_seq_found = player.solution();  // Tries to find a solution to lead the snake to the food pellet.
        }
        
        if(has_it_end){
            // Erases the snake nodes in the level matrix.
            curr_level->set_element_at(*first, ' ');
            while(current_node != last){
                curr_level->set_element_at(*current_node, ' ');
                current_node++;
            }

            snake.restart_snake(curr_level->get_snake_start_pos());      // restart_snakes snake.
            first = snake.get_it_snake_head();                   // Updates iterator to head.
            current_node= ++snake.get_it_snake_head();           // Updates iterator to the second node.
            last = snake.get_it_snake_tail();                     // Updates iterator to end.
            has_it_end = 0;                                        // Turn off crashed flag.
            if(m_running_options.player_type == "backtracking") was_the_seq_found = player.solution();  // Tries to find a solution to lead the snake to the food pellet.
        }
        else{
            // cout << "was_the_seq_found: " << was_the_seq_found << "\n"; // Debug
            if( !was_the_seq_found || player.bfs() < player.get_min_dist() ){
                if(m_running_options.player_type == "backtracking") was_the_seq_found = player.solution();  // Tries to find a solution to lead the snake to the food pellet.
            }
            // cout << "was_the_seq_found: " << was_the_seq_found << "\n"; // Debug
            if(was_the_seq_found) move_snake_twds_food();                   // Moves the snake based on the sequence of directions found.
            else move_snake();                                              // Moves the snake randomly.
        }
        // Snake ate food.
        if( curr_level->is_it_food( snake.get_snake_pos() ) ){
            curr_level->set_element_at(snake.grow_body(), '+');          // Updates the level matrix with the new last node of the snake.
            first = snake.get_it_snake_head();                                   // Updates iterator to head.
            current_node = snake.get_it_snake_head()+1;                          // Updates iterator to the second node.
            last = snake.get_it_snake_tail();                                     // Updates iterator to end.
            foods_eaten++;
            score = last_level_score + foods_eaten*(foods_eaten+1)*10;            // Updates game score.
            curr_level->place_food();                                        // Places new food pellet.
        }
        // Snake crashed.
        else if(has_it_end){
            // Updates snake representation in the level matrix.
            curr_level->set_element_at(*first, 'x');
            while(current_node != last){
                curr_level->set_element_at(*current_node, '-');
                current_node++;
            }

            // Updates lives.
            m_running_options.lives--;
            // Updates deaths.
            deaths++;
            return;
        }
        
        // Updates snake's head in the level matrix.
        if(snake.get_direction() == EAST){
            curr_level->set_element_at(*first, '<');
        }
        else if(snake.get_direction() == WEST){
            curr_level->set_element_at(*first, '>');
        }
        else if(snake.get_direction() == NORTH){
            curr_level->set_element_at(*first, 'v');
        }
        else if(snake.get_direction() == SOUTH){
            curr_level->set_element_at(*first, '^');
        }
        // Updates snake's other nodes (represented by *) in the level matrix.
        while(current_node != last){
            curr_level->set_element_at(*current_node, '*');
            if(current_node == last-1) curr_level->set_element_at(*current_node, '+');
            current_node++;
        }
        // if(current_node != last) curr_level->set_element_at(*current_node, '+');
        // If snake did not grow up, update the previous position of snake's last node in the level matrix.
        if( snake.get_last_node() != snake.get_prev_pos() ){
            curr_level->set_element_at(snake.get_prev_pos(), ' ');
        }
    }
}