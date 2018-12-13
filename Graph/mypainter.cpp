#include "mypainter.h"

Mypainter::Mypainter(QWidget *parent) : QWidget(parent)//设置初始大小等
{
    setMinimumSize(1500,900);
//    setFixedSize(1500,1000);
    setWindowTitle("GraphView");
}

void Mypainter::initialData(graph other)//从图中初始化点和边的数据
{
//    int seqx = 90;
//    int seqy = 80;
    int count = 1;
    int now = 0;
    for(int i = 0;i < other.getVertex().size(); i++){
        QPoint c;
        if(other.getVertex()[i].level != now){
            count = 0;
            now = other.getVertex()[i].level;
        }
//        c.setX(now * seqx + 30);
//        c.setY(count * seqy);
        c.setX(other.getVertex()[i].x);
        c.setY(other.getVertex()[i].y);
        nodes.push_back(c);
        nodename.push_back(QString::fromStdString(other.getVertex()[i].name));
        count++;
    }
    edges = other.getEdge();

//    qDebug(QString::number(edges.size()).toStdString().c_str());
//    qDebug(QString::number(nodes.size()).toStdString().c_str());

    update();
}

void Mypainter::paintEvent(QPaintEvent *event)//画图
{
    QPainter painter(this);

    if(nodes.size() == 0)
        return;

    //draw edge
    for(int i = 0; i < edges.size(); i++){

        QPoint s(nodes[edges[i].vertex[0]]);
        QPoint e(nodes[edges[i].vertex[1]]);
        QPoint pos;
        pos.setX((s.x()+e.x()-30)/2);
        pos.setY((s.y()+e.y())/2);

        QPen pen(QColor(124, 122, 121,200));
        pen.setWidth(4);
        painter.setPen(pen);
        painter.drawLine(s,e);

        QPen npan(QColor(28, 114, 14));
        npan.setWidth(2);
        painter.setPen(npan);
        painter.setFont(QFont("Consolas",10));
        painter.drawText(pos,QString::number(edges[i].cost));
    }

    for(int i = 0; i < nodes.size();i++){

        //draw node
        painter.setBrush(QBrush(QColor((i*8)%256, (150-3*i)%256, (150-3*i)%256,(160+3*i)%256)));
        painter.setPen(QPen(QColor(255,255,255,0)));
        painter.drawEllipse(nodes[i],20,20);

        //draw nodename
        QPen pen(QColor(54, 52, 51));
        pen.setWidth(1);
        painter.setPen(pen);
        painter.setFont(QFont("Consolas",10));
        QPoint c(nodes[i].x()-14,nodes[i].y()-24);
        painter.drawText(c,nodename[i]);
    }
}

void Mypainter::mousePressEvent(QMouseEvent *event)//按下鼠标时确定最近的节点
{
    QPoint pos = event->pos();
    currentID = -1;

    for(int i=0; i<nodes.size(); i++)
    {
        int dx = pos.x() - nodes[i].x();
        int dy = pos.y() - nodes[i].y();

        int dist = sqrt(dx*dx+dy*dy);

        if(dist < 25)
        {
            currentID = i;

        }
    }
}

void Mypainter::mouseMoveEvent(QMouseEvent *event)//节点跟随鼠标移动
{
    if(currentID == -1)
        return;

    nodes[currentID] = event->pos();

    update();
}

void Mypainter::mouseReleaseEvent(QMouseEvent *event)//释放节点
{
    currentID = -1;
}
