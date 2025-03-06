#pragma once 

struct PixelCoordinates {
    float x;
    float y;
}; // PiexelCoordinates

struct ChessCoordinates {
    char row;
    unsigned short collumn;
}; // ChessCoordinates

bool operator<(const ChessCoordinates& l, const ChessCoordinates& r);