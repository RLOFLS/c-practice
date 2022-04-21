#ifndef GG_GameItemContract
#define GG_GameItemContract

namespace game
{
    class GameItemContract {

        public:

            virtual void draw();
            virtual bool isAlive();
    };
} // namespace game



#endif