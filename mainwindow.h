#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnOpen_clicked();

    void on_btnProcess_clicked();

    void on_btnSave_clicked();

private:
    Ui::MainWindow *ui;

    MyGraph *graph_;
};

#endif // MAINWINDOW_H
