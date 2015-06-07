#include "graph.h"

#include <QQueue>
#include <QList>

MyGraph::MyGraph()
{
    data_ = new QMultiHash<int, int>();
}

MyGraph::~MyGraph()
{
    data_->~QHash();
}

void MyGraph::addPair(int a, int b) {
    data_->insert(a, b);
    data_->insert(b, a);
}

void MyGraph::clear() {
    data_->clear();
}

const QStringList& MyGraph::wave(int startIndex) {
    QStringList *result = new QStringList();

    if (data_->find(startIndex) == data_->end()) {
        return *result;
    }

    int d = 0;
    QList<int> used;
    QQueue<int> newLayer;
    QQueue<int> layer;
    layer << startIndex;

    QString s;
    while (!layer.empty()) {
        s = "";
        while (!layer.empty()) {

            int vertex = layer.takeFirst();
            used.append(vertex);

            s += QString::number(vertex) + ' ';

            QMultiHash<int, int>::iterator it = data_->find(vertex);
            while (it != data_->end() && it.key() == vertex) {
                if (!used.contains(it.value())) {
                    newLayer << it.value();
                }
                it++;
            }
        }
        layer += newLayer;
        newLayer.clear();
        d++;

        result->append(s);
    }

    return *result;
}
