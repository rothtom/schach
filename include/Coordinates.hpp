#pragma once 

struct PiexelCoordinates {
    int x;
    int y;
}; // PiexelCoordinates

struct ChessCoordinates {
    char row;
    unsigned short collumn;
}; // ChessCoordinates

bool operator<(const ChessCoordinates& l, const ChessCoordinates& r);