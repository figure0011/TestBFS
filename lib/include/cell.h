#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>
#include <qgraphicsscene.h>
#include <qbrush.h>


enum Status{Clean, NoClean, Start, Finish, NoStatus }; // возможные статусы клетки

const int cellSize = 50;

class Cell: public QGraphicsRectItem         // создает клетку
{
public:
    Cell(int x, int y, int size,int st, QGraphicsItem *parent = nullptr);
    Cell(const Cell &c);
    void updateStatus(int upd);                       // позволяет обновить статус клетки
    void clickCell(int id);
    int getX() const;
    int getY() const;
    Status getStatus() const;
private:
    int x_m, y_m;
    Status status;
};

#endif // CELL_H
