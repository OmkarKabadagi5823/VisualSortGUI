#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QWidget>
#include <QPainter>
#include <QTime>

#include <vector>
#include <algorithm>
#include <random>
#include <thread>
#include "thread_guard.h"
#include <chrono>
namespace Ui {
class Visualizer;
}

class Visualizer : public QWidget
{
    Q_OBJECT

public:
    explicit Visualizer(QWidget *parent = 0);
    ~Visualizer();

private:
    Ui::Visualizer *ui;

    int W_WIDTH;
    int W_HEIGHT;
    int BAR_WIDTH;
    int QUANTUM_BAR_HEIGHT;

    QString sortType;
    int DELAY;
    int BARS;

    int timerId;
    bool running;

    int printStartX;
    int printStartY;

    std::vector<int> arr;

    std::thread sortThread;

    void init();
    void draw();
    void randomize();
    void barsSet();
    void check();
    void bubbleSort();
    void insertionSort();
    void selectionSort();
    void merge(int l, int m, int r);
    void mergeSort(int l, int r);
    int  partition(int low, int high);
    void quickSort(int low, int high);


protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_run_clicked();
    void on_randomize_clicked();
    void on_delaySet_clicked();
    void on_barsSet_clicked();
    void on_descending_clicked();
//    void on_stop_clicked();
};

#endif // VISUALIZER_H
