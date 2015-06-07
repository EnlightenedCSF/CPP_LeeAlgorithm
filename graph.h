#ifndef GRAPH_H
#define GRAPH_H

#include <QMultiHash>
#include <QStringList>

class MyGraph
{
public:
    MyGraph();
    ~MyGraph();

    void clear();
    void addPair(int a, int b);
    const QStringList& wave(int startIndex);

private:
    QMultiHash<int, int> *data_;
};

#endif // GRAPH_H
