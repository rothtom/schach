#pragma once

namespace chess {
    class ChessCoordinates {
        public:
            ChessCoordinates(char coll, unsigned short row);

        private:
            unsigned short row;
            char coll;
            
    };
}
