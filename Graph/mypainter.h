#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "graph.h"

class Mypainter : public QWidget
{
    Q_OBJECT
public:
    explicit Mypainter(QWidget *parent = nullptr);
    void initialData(graph);
signals:

public slots:
    
private:
    void paintEvent(QPaintEvent *);
    QPainter *painter;
    myVector<QPoint> nodes;
    myVector<QString> nodename;
    myVector<graph::edge> edges;

    int currentID;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // MYPAINTER_H
