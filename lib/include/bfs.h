#ifndef BFS_H
#define BFS_H

#include <vector>
#include <queue>
#include "cell.h"

using std::vector;
using std::queue;

class BFS
{
public:
    BFS(vector<vector<Cell*>> &maze);
    vector<vector<Cell*>> solve(Cell *startCell, Cell *finishCell);
    vector<Cell*> getPath(Cell *startCell, Cell *finishCell);
private:
    vector<vector<Cell*>> maze_m;
    vector<vector<int>> dist;
    // Cell *startCell;
    // Cell *finishCell;
    bool fVisited;
};

#endif // BFS_H
