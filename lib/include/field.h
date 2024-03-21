#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <QRandomGenerator>
#include <QMessageBox>
#include <vector>
#include "cell.h"
#include "bfs.h"

using std::vector;

class Field : public QGraphicsView //создает поле из клеток (методы generate и genrateBarrier)
{
public:
    explicit Field(int w, int h, QWidget *parent = nullptr);
    void generate();
    void genrateBarrier();
    void bfsSolve();              //функция запуска поиска в глубину
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);

private:
    int weight, height;
    bool start;
    bool finish;

    vector<vector<Cell*>> maze;
    QGraphicsLineItem *L;
    Cell *startCell;
    Cell *finishCell;
    BFS* bfs;
    vector<QGraphicsLineItem*> lines;
};

#endif // FIELD_H
