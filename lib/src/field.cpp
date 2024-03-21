#include "field.h"

Field::Field(int w, int h, QWidget *parent)
    : QGraphicsView{parent}, width{w}, height{h}
{
    QGraphicsScene *sc = new QGraphicsScene(this);
    setGeometry(0, 0, width, height);
    sc->setSceneRect(0, 0, width, height);
    setScene(sc);

    start = false;
    finish = false;

    maze.resize((sc->width()) / cellSize);

    for(auto &i: maze)
        i.resize((sc->height()) / cellSize);
}
void Field::genrateBarrier(){

    int xi, yi;
    Cell *currCell;
    int ww = width/ cellSize;
    int hh = height/cellSize;

    for (int i = 0; i < (ww*hh)/2; ++i)
    {
        xi = QRandomGenerator::global()->bounded(width);
        yi = QRandomGenerator::global()->bounded(height);

        currCell = static_cast<Cell*>(scene()->itemAt(xi, yi, QTransform()));
        currCell->updateStatus(1);
    }
}
void Field::generate()
{
    scene()->clear();

    for (int i = 0; i < sceneRect().width(); i += cellSize)
    {
        for (int j = 0; j < sceneRect().height(); j += cellSize)
        {
            Cell *cell = new Cell(i, j, cellSize, 0);
            maze.at(i / cellSize).at(j / cellSize) = cell;
            scene()->addItem(cell);
        }
    }
    genrateBarrier();
}
void Field::bfsSolve(){

    bfs = new BFS(maze);
    try{
        vector<Cell*> path = bfs->getPath(startCell, finishCell);

        while (!path.empty())
        {

            if (path.size() != 1)
            {
                QGraphicsLineItem *line = new QGraphicsLineItem(cellSize * path.at(path.size() - 1)->getX() + 25, cellSize * path.at(path.size() - 1)->getY() + 25,
                                                                cellSize * path.at(path.size() - 2)->getX() + 25, cellSize * path.at(path.size() - 2)->getY() + 25, nullptr);
                line->setPen(QPen(QColor(Qt::green), 5, Qt::SolidLine));
                scene()->addItem(line);
                lines.push_back(line);
            }
            path.pop_back();
        }
    }
    catch (const std::exception& err)
    {
        QMessageBox msgBox;
        msgBox.setText("No way..");
        msgBox.exec();
    }
}

void Field::mousePressEvent(QMouseEvent *event){
    Cell *currCell = static_cast<Cell *>(scene()->itemAt(mapToScene(mapFromGlobal(cursor().pos())), QTransform()));
    if(currCell != nullptr){
        if(event->button() == Qt::LeftButton && start == false && finish == false && currCell->getStatus() == Clean){
            currCell->clickCell(0);
            start = true;
            startCell = currCell;
        }
        else if(event->button() == Qt::LeftButton && start == true && finish == false && currCell->getStatus() == Clean){
            currCell->clickCell(1);
            finish = true;
            finishCell = currCell;
            bfsSolve();
        }else if(event->button() == Qt::LeftButton && start == true && finish == true && currCell->getStatus() == Clean){
            finishCell->updateStatus(0);
            currCell->clickCell(1);
            finish = true;
            finishCell = currCell;

            if(!lines.empty())
                for(auto &i:lines)
                    delete i;

            lines.resize(0);
            bfsSolve();
        }
    }
}
void Field::wheelEvent(QWheelEvent* event) {

       this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
       double scaleFactor = 1.15;
       if(event->angleDelta().y() > 0) {
            this-> scale(scaleFactor, scaleFactor);
        } else if(event->angleDelta().y() < 0){
            this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
 }


    // QThread* thread = QThread::create(std::bind(&DFS::solve, dfs));
    // connect(thread, &QThread::finished, dfs, &QObject::deleteLater);
    // connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    // thread->start();
