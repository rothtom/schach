#pragma once 

struct PixelCoordinates {
    float x;
    float y;
}; // PiexelCoordinates

struct ChessCoordinates {
    unsigned short row;
    char collumn;
}; // ChessCoordinates

bool operator<(const ChessCoordinates& l, const ChessCoordinates& r);
