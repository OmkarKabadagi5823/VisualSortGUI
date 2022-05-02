#include "visualizer.h"
#include "ui_visualizer.h"

Visualizer::Visualizer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Visualizer)
{
    ui->setupUi(this);

    init();

    resize(W_WIDTH, W_HEIGHT);

    ui->sortType->activated(sortType);
    ui->delay->setValue(DELAY);
    ui->bars->setValue(BARS);
    ui->status->setText("Not Running");

    for(int i=0; i<BARS; i++)
        arr.push_back(QUANTUM_BAR_HEIGHT*(i+1));
}

void Visualizer::init()
{
    W_WIDTH = 1280;
    W_HEIGHT = 720;
    running = false;
    sortType = "Bubble Sort";
    DELAY = 0;
    BARS = 20;
    QUANTUM_BAR_HEIGHT = 10;
    BAR_WIDTH = 20;
    printStartX = (W_WIDTH/2) - static_cast<int>(BARS/2)*BAR_WIDTH;
    printStartY = (W_HEIGHT/2) + (QUANTUM_BAR_HEIGHT*BARS)/2;
}

void Visualizer::draw()
{
    QPainter qp(this);
    qp.setPen(QColor("#d4d4d4"));
    qp.setBrush(QBrush("#004fc5"));

    for(int i=0; i<BARS; i++)
    {
        qp.drawRect(printStartX + BAR_WIDTH*i, printStartY - arr[i], BAR_WIDTH, arr[i]);
    }
}

void Visualizer::randomize()
{
    auto rng = std::default_random_engine {};
    std::shuffle(arr.begin(), arr.end(), rng);
}

void Visualizer::barsSet()
{
    if(!running)
    {
        arr.clear();
        BARS = static_cast<int>(ui->bars->value());

        QUANTUM_BAR_HEIGHT = static_cast<int>(10/ceil(BARS/static_cast<float>(50)));
        BAR_WIDTH = static_cast<int>(20/ceil(BARS/static_cast<float>(50)));

        for(int i=0; i<BARS; i++)
            arr.push_back(QUANTUM_BAR_HEIGHT*(i+1));

        printStartX = (W_WIDTH/2) - static_cast<int>(BARS/2)*BAR_WIDTH;
        printStartY = (W_HEIGHT/2) + (QUANTUM_BAR_HEIGHT*BARS)/2;

        if(BARS%2)
            printStartX -= BAR_WIDTH/2;
    }
}

void Visualizer::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    draw();
}

void Visualizer::resizeEvent(QResizeEvent *e)
{
    W_WIDTH = size().width();
    W_HEIGHT = size().height();
    barsSet();

    QWidget::resizeEvent(e);

}

void Visualizer::bubbleSort()
{

    int temp;
    for(int n=0; n<BARS; n++)
    {
        for(int i=0; i<BARS-1; i++)
        {
            if(arr[i] > arr[i+1])
            {
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;

                repaint();
            }

            std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
        }
    }
}

void Visualizer::insertionSort()
{
    int i, key, j;
    for(i=1; i<BARS; i++)
    {
        key = arr[i];
        j = i - 1;

        while(j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
            repaint();
        }

        arr[j + 1] = key;
        std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
        repaint();
    }
}

void Visualizer::selectionSort()
{
    int i, j, min_idx, temp;

    for(i=0; i<BARS-1; i++)
    {

        min_idx = i;
        for (j=i+1; j<BARS; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;

            std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
        }

        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;

        std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
        repaint();
    }
}

void Visualizer::merge(int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;

        std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
        repaint();
    }

    while(i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;

        std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
        repaint();
    }

    while(j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;

        std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
        repaint();
    }
}

void Visualizer::mergeSort(int l, int r)
{
    if(l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(l, m);
        mergeSort(m + 1, r);

        merge(l, m, r);
    }
}

int Visualizer::partition(int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    int temp;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            repaint();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
    }

    temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;

    std::this_thread::sleep_for(std::chrono::microseconds(DELAY));
    repaint();

    return (i + 1);
}

void Visualizer::quickSort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

Visualizer::~Visualizer()
{
    delete ui;
}

void Visualizer::on_run_clicked()
{
    running = true;
    ui->status->setText("Running");
    QString type = ui->sortType->currentText();

    if(type.toLower() == "bubble sort")
    {
        sortThread = std::thread(&Visualizer::bubbleSort, this);
        thread_gaurd sort_tg(sortThread);
    }
    else if(type.toLower() == "insertion sort")
    {
        insertionSort();
    }
    else if(type.toLower() == "selection sort")
    {
        selectionSort();
    }
    else if(type.toLower() == "merge sort")
    {
        mergeSort(0, BARS-1);
    }
    else if(type.toLower() == "quick sort")
    {
        quickSort(0, BARS -1);
    }

    running = false;
    ui->status->setText("Finished");
}

void Visualizer::on_randomize_clicked()
{
    randomize();
    repaint();
}

void Visualizer::on_delaySet_clicked()
{
    DELAY = ui->delay->value();
    ui->delayLabel->setNum(ui->delay->value());
}

void Visualizer::on_barsSet_clicked()
{
    barsSet();
    repaint();
}

void Visualizer::on_descending_clicked()
{
    arr.clear();

    for(int i=0; i<BARS; i++)
        arr.push_back(QUANTUM_BAR_HEIGHT*(BARS-i));

    repaint();
}

//void Visualizer::on_stop_clicked()
//{
//    if(running)
//    {
//        running = false;
//        ui->status->setText("Interrupted");
//    }
//}
