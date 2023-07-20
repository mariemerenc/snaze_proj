#include "snaze_game.h"

int main(int argc, char *argv[]) {
    SnazeGame game;
    game.initialize_game(argc, argv);

    while(game.has_it_end){
        game.process();
        game.update():
        game.render();
    }


    return EXIT_SUCCESS;
}