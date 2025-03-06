#include "Coordinates.hpp"

bool operator<(const ChessCoordinates& l, const ChessCoordinates& r) {
    return (l.collumn<r.collumn || (l.collumn==r.collumn && l.row<r.row));
}