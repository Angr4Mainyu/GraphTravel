#include "graph.h"

graph::graph()
{

}

graph::~graph()
{

}

void graph::sortBylevel()//把节点按照层次排序
{
    std::sort(_vertex.begin(),_vertex.end(),cmpBylevel);
}

bool graph::cmpBylevel(graph::vertex a, graph::vertex b)//规定节点层次的比较方法
{
    return a.level < b.level;
}

bool graph::judgeOddPoint(int x, int y)//判断点的位置的独立性
{
    for(int i = 0; i < _vertex.size(); i++){
        if(_vertex[i].x == x&& _vertex[i].y == y)
            return false;
    }
    return true;
}

void graph::setOnePathin(int pos)//确保每个点只有一个入度
{
    int next = _vertex[pos].to;
    while(next != -1){
        if(next % 2 == 0){
            if(_edge[next + 1].mark)
                _edge[next + 1].mark = false;
        }
        else {
            if(_edge[next - 1].mark)
                _edge[next - 1].mark = false;
        }
        next = _edge[next].path[0];
    }
}

void graph::pushVertex(string name)//按照城市名添加节点
{
    vertex temp(name);
    _vertex.push_back(temp);
}

void graph::pushVertex(graph::vertex other)//按照节点添加节点
{
    _vertex.push_back(other);
}

void graph::pushEdge(string name1, string name2, int cost)//根据两个城市名添加边
{
    int pos1 = -1,pos2 = -1;
    for(int i = 0;i < _vertex.size(); i++){
          if(_vertex[i].name == name1)
              pos1 = i;
          if(_vertex[i].name == name2)
              pos2 = i;
    }
    if(pos1 == -1|| pos2 == -1)
        return;
    edge temp1(pos1,pos2,_vertex[pos1].to,_vertex[pos2].to,cost);
    _vertex[pos1].to = _edge.size();
    _edge.push_back(temp1);

    edge temp2(pos2,pos1,_vertex[pos2].to,_vertex[pos1].to,cost);
    _vertex[pos2].to = _edge.size();
    _edge.push_back(temp2);
}

myVector<graph::edge> graph::getEdge()//返回边集
{
    return _edge;
}

myVector<graph::vertex> graph::getVertex()//返回点集
{
    return _vertex;
}

graph graph::DFS(string start)//深度优先搜索
{
    for(int i = 0; i < _vertex.size();i++){//初始化
        _vertex[i].mark = false;
        _vertex[i].level = 0;
        _vertex[i].x = 0;
        _vertex[i].y = 0;
    }

    for(int i = 0; i < _edge.size();i++){
        _edge[i].mark = false;
    }

    int pos = -1;
    for(int i = 0;i < _vertex.size(); i++){//寻找起点的坐标
        if(_vertex[i].name == start){
            pos = i;
            break;
         }
    }
    graph temp;
    if(pos == -1)
        return temp;
    myVector<int> mycontain;//用栈来存储节点

    mycontain.push_back(pos);
    _vertex[pos].x = 30;
    _vertex[pos].y = 400;

    while(!mycontain.empty()){//标记栈顶节点并弹出
        pos = mycontain.top();
        mycontain.pop_back();
        if(_vertex[pos].mark)
            continue;

        _vertex[pos].mark = true;
        temp.pushVertex(_vertex[pos]);

        int next = _vertex[pos].to;
        int count = 0 - (_vertex[pos].level % 2);

        while(next != -1){//搜索所有跟这条边相连的点加入栈
            int nextpos = _edge[next].vertex[1];
            if(!_edge[next].mark && !_vertex[nextpos].mark){

                setOnePathin(nextpos);
                _edge[next].mark = true;

                _vertex[nextpos].level = _vertex[pos].level + 1;

                int xx = _vertex[pos].x + 90;//预处理坐标
                int yy = _vertex[pos].y + count * 80;
                while(!judgeOddPoint(xx,yy)){
                    --count;
                    yy -= 80;
                    if(yy < 0)
                        break;
                }
//                if(yy < 0)
//                    while(!judgeOddPoint(xx,yy)){
//                        ++count;
//                        yy += 80;
//                    }
                _vertex[nextpos].x = xx;
                _vertex[nextpos].y = yy;
                count++;

                mycontain.push_back(nextpos);
            }
            next = _edge[next].path[0];
        }
    }

    temp.olds = temp.getVertex();//保存初始点集
    temp.sortBylevel();//按照层次排序，便于作图

    for(int i = 0; i < _edge.size(); i++){//将标记过的边加入生成树中
        if(_edge[i].mark)
            temp.pushEdge(_vertex[_edge[i].vertex[0]].name,_vertex[_edge[i].vertex[1]].name,_edge[i].cost);
    }
    return temp;
}

graph graph::BFS(std::string start)//广度优先搜索
{
    for(int i = 0; i < _vertex.size();i++){//初始化数据
        _vertex[i].mark = false;
        _vertex[i].level = 0;
        _vertex[i].x = 0;
        _vertex[i].y = 0;
    }

    for(int i = 0; i < _edge.size();i++){
        _edge[i].mark = false;
    }

    int pos = -1;
    for(int i = 0;i < _vertex.size(); i++){//寻找起点坐标
        if(_vertex[i].name == start){
            pos = i;
            break;
         }
    }
    graph temp;
    if(pos == -1)
        return temp;
    myVector<int> mycontain;//用队列存储节点

    mycontain.push_back(pos);
    _vertex[pos].mark = true;
    _vertex[pos].x = 700;
    _vertex[pos].y = 100;

    while(!mycontain.empty()){
        pos = mycontain.front();//将队首的节点标记并出队
        temp.pushVertex(_vertex[pos]);
        mycontain.pop_front();

        int next = _vertex[pos].to;
        int count = -1;

        while(next != -1){//遍历所有跟队首节点相连的边寻找所有相邻节点
            int nextpos = _edge[next].vertex[1];
            if(!_edge[next].mark && !_vertex[nextpos].mark){
                _edge[next].mark = true;
                _vertex[nextpos].mark = true;

                _vertex[nextpos].level = _vertex[pos].level + 1;

                int xx = _vertex[pos].x + count * 90;//预处理坐标
                int yy = _vertex[pos].y + 80;
                while(!judgeOddPoint(xx,yy)){
                    ++count;
                    xx += 90;
                }
                _vertex[nextpos].x = xx;
                _vertex[nextpos].y = yy;
                count++;

                mycontain.push_back(nextpos);
            }
            next = _edge[next].path[0];
        }
    }
//    temp.sortBylevel();
    for(int i = 0; i < _edge.size(); i++){//将标记过的边加入生成树中
        if(_edge[i].mark)
            temp.pushEdge(_vertex[_edge[i].vertex[0]].name,_vertex[_edge[i].vertex[1]].name,_edge[i].cost);
    }
    return temp;
}
