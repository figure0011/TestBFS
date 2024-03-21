#include <algorithm>
#include "bfs.h"

BFS::BFS(vector<vector<Cell*>> &maze)
    :maze_m{maze}
{
    dist = vector<vector<int>>(maze.size(), vector<int>(maze[0].size(), -1));
}
vector<vector<Cell*>> BFS::solve(Cell *startCell, Cell *finishCell){
    queue<Cell*> q;
    vector<vector<Cell*>> path(maze_m.size(),vector<Cell*>(maze_m[0].size()));
    q.push(startCell);

    dist.at(startCell->getX()).at(startCell->getY()) = 0;

    int r[4][2]{{-1, 0}, {+1, 0}, {0, -1}, {0, +1}};
    int xx, yy;
    fVisited = false;

    while(!q.empty()){
        int x = q.front()->getX();
        int y = q.front()->getY();

        q.pop();

        for(auto [dx, dy] : r){
            xx = x + dx;
            yy = y + dy;

            if(xx >= 0 && xx < maze_m.size())
                if(yy >= 0 && yy < maze_m[0].size())
                    if((maze_m.at(xx).at(yy)->getStatus() == Clean || maze_m.at(xx).at(yy)->getStatus() == Finish)
                        && dist.at(xx).at(yy) == -1)
                    {
                        dist.at(xx).at(yy) = dist.at(x).at(y) + 1;
                        path.at(xx).at(yy) = maze_m.at(x).at(y);
                        //maze_m.at(xx).at(yy)->setBrush(QBrush(QColor(Qt::cyan)));

                        if(maze_m.at(xx).at(yy) == finishCell)
                            fVisited = true;
                        //maze_m.at(x).at(y)->setBrush(QBrush(QColor(Qt::yellow)));
                        q.push(maze_m.at(xx).at(yy));
                    }
        }
    }
    return path;
}
vector<Cell*> BFS::getPath(Cell *startCell, Cell *finishCell){
    vector<vector<Cell*>> path = solve(startCell, finishCell);

    if(fVisited == false)
        throw std::exception();

    vector<Cell*> path1;
    Cell *cell = finishCell;
    path1.push_back(cell);

    while(cell != startCell){
        cell = path.at(cell->getX()).at(cell->getY());
        path1.push_back(cell);
    }
    std::reverse(path1.begin(), path1.end());
    return path1;
}
