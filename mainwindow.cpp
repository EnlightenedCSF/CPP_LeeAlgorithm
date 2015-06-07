#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btnProcess->setEnabled(false);
    ui->btnSave->setEnabled(false);
    ui->lineEditSelectedVertex->setEnabled(false);

    graph_ = new MyGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
    graph_->~MyGraph();
}

void MainWindow::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                      tr("Choose graph file to analyze"),
                                                      QDir::currentPath(),
                                                      tr("Text files (*.txt)"));
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);

        graph_->clear();
        ui->textEditInputGraph->clear();

        while (!in.atEnd()) {
            QString line = in.readLine();
            ui->textEditInputGraph->append(line);
            QStringList pair = line.split(' ');

            graph_->addPair(pair[0].toInt(), pair[1].toInt());
        }
        inputFile.close();

        ui->btnProcess->setEnabled(true);
        ui->btnSave->setEnabled(true);
        ui->lineEditSelectedVertex->setEnabled(true);
    }
    else
        QMessageBox::warning(this, "Error", "Reading from the file went wrong", QMessageBox::Ok);
}

void MainWindow::on_btnProcess_clicked()
{
    QString text = ui->lineEditSelectedVertex->text();
    bool isValid = true;
    int index = text.toInt(&isValid);
    if (isValid) {
        const QStringList& result = graph_->wave(index);
        if (result.empty()) {
            QMessageBox::warning(this, "Error", "Graph must contain selected index!", QMessageBox::Ok);
        }
        else {
            ui->textEditResult->setText(result.join('\n'));
        }
    }
    else
        QMessageBox::warning(this, "Error", "You must provide valid integer!", QMessageBox::Ok);
}


void MainWindow::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Choose file to save to"),
                                                    QDir::currentPath(),
                                                    tr("Text files (*.txt)"));
    QFile outputFile(fileName);
    if (outputFile.open(QIODevice::ReadWrite)) {
        QTextStream out(&outputFile);
        out << ui->textEditResult->toPlainText();
        outputFile.close();
        QMessageBox::information(this, "Success", "Successfully saved", QMessageBox::Ok);
    }
    else
        QMessageBox::warning(this, "Error", "Writing to file went wrong", QMessageBox::Ok);
}
