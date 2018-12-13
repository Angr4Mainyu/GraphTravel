#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    original = NULL;
    DFStree = NULL;
    BFStree = NULL;

    setWindowTitle("GraphTravel");
    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()//从文件初始化图
{
    original = new graph;
    fstream input;
    input.open("D:/code/Graph/vertex.txt");
    string ss;
    while(input >> ss){
        original->pushVertex(ss);
        ui->comboBox->addItem(QString::fromStdString(ss));
    }
    input.close();

    input.open("D:/code/Graph/edge.txt");
    while(input >> ss){
        string ee;
        int cost;
        input >> ee >> cost;
        original->pushEdge(ss,ee,cost);
    }

    input.close();
}

void MainWindow::on_pushButton_2_clicked()//深度优先搜索遍历图
{
    if(original == NULL)
        return;
    DFStree = new graph;
    *DFStree = original->DFS(ui->comboBox->currentText().toStdString());
    QString output;
    for(int i = 0;i < DFStree->olds.size(); i++){//输出遍历顺序的节点
        if(i > 0 &&DFStree->olds[i].level < DFStree->olds[i-1].level)
            output += "  |||-";
        if(i != 0){
            if(DFStree->olds[i].level == DFStree->olds[i-1].level){
                output += "---";
            }
            else
                output += "->";
        }

        output += QString::fromStdString(DFStree->olds[i].name);
    }
    ui->textEdit->setText(output);

    ui->listWidget->clear();//输出边集
    for(int i = 0; i < DFStree->getEdge().size();i += 2){
        QString temp;
        temp += QString::fromStdString(DFStree->getVertex()[DFStree->getEdge()[i].vertex[0]].name);
        temp += "-->";
        temp += QString::fromStdString(DFStree->getVertex()[DFStree->getEdge()[i].vertex[1]].name);
        temp += "  ";
        temp += QString::number(DFStree->getEdge()[i].cost);
        ui->listWidget->addItem(temp);
    }
}

void MainWindow::on_pushButton_3_clicked()//广度优先搜索遍历图
{
    if(original == NULL)
        return;
    BFStree = new graph;
    *BFStree = original->BFS(ui->comboBox->currentText().toStdString());

    QString output;//输出遍历点的顺序
    for(int i = 0;i < BFStree->getVertex().size(); i++){
        if(i > 0 &&BFStree->getVertex()[i].level < BFStree->getVertex()[i-1].level)
            output += "  |||-";
        if(i != 0){
            if(BFStree->getVertex()[i].level == BFStree->getVertex()[i-1].level){
                output += "---";
            }
            else
                output += "->";
        }

        output += QString::fromStdString(BFStree->getVertex()[i].name);
    }
    ui->textEdit->setText(output);

    ui->listWidget->clear();//输出边集
    for(int i = 0; i < BFStree->getEdge().size();i += 2){
        QString temp;
        temp += QString::fromStdString(BFStree->getVertex()[BFStree->getEdge()[i].vertex[0]].name);
        temp += "-->";
        temp += QString::fromStdString(BFStree->getVertex()[BFStree->getEdge()[i].vertex[1]].name);
        temp += "  ";
        temp += QString::number(BFStree->getEdge()[i].cost);
        ui->listWidget->addItem(temp);
    }
}

void MainWindow::on_pushButton_4_clicked()//画图
{
    if(DFStree == NULL)
        return;
    Mypainter  * painter = new Mypainter;
    painter->initialData(*DFStree);
    painter->show();
}

void MainWindow::on_pushButton_5_clicked()//画图
{
    if(BFStree == NULL)
        return;
    Mypainter * painter = new Mypainter;
    painter->initialData(*BFStree);
    painter->show();
}
