#ifndef GG_Game
#define GG_Game

#include <list>
//#include "GameItemContract.hpp"
#include "Background.hpp"

namespace game
{

    typedef std::list<Background> GameItemList;

    class Game {
        private:
            GameItemList gameLists;

        public:

            Game()
            {
                Background bg;
                //GameItemContract *item = bg;
                addItem(bg);
            }

            ~Game()
            {
                gameLists.clear();
            }

            void render()
            {
                for (auto item = gameLists.begin(); item != gameLists.end(); item++)
                {
                    if (item->isAlive()) {
                        item->draw();
                    } else {
                        gameLists.erase(item);
                    }
                    
                }
                
            }

            void addItem(Background item)
            {
                gameLists.push_back(item);
            }

        

    };
} 

#endif