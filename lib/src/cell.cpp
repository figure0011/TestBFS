#include "cell.h"

Cell::Cell(int x, int y,int size, int st, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    setRect(x, y, size, size);
    updateStatus(st);

    x_m = x / cellSize;
    y_m = y / cellSize;
}
Cell::Cell(const Cell &c){
    x_m = c.x_m;
    y_m = c.y_m;
    status = c.status;
}
int Cell::getX() const{
    return x_m;
}
int Cell::getY() const{
    return y_m;
}
Status Cell::getStatus() const{
    return status;
}
void Cell::updateStatus(int upd){
    switch (upd) {
    case 0:
        setBrush(QBrush(QColor(Qt::white)));
        status = Status::Clean;
        break;
    case 1:
        setBrush(QBrush(QColor(Qt::gray)));
        status = Status::NoClean;
        break;
    case 2:
        setBrush(QBrush(QColor(Qt::red)));
        status = Status::Start;
        break;
    case 3:
        setBrush(QBrush(QColor(Qt::blue)));
        status = Status::Finish;
        break;
    }
}
void Cell::clickCell(int id){
    if (id == 0 && status == Status::Clean){
        updateStatus(2);
    }
    else if(id == 1 && status == Status::Clean){
        updateStatus(3);
    }
}
