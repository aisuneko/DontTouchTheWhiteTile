#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    start();
    ui->setupUi(this);
}
void MainWindow::start() {
    generateBeatmap(50);
    this->grabKeyboard();
    timer = new QElapsedTimer();
    message = tr("Hang tight...");
    index = 0;
}
void MainWindow::clearCanvas() {
    painter->setBrush(QBrush(QColor(Qt::white)));
    painter->drawRect(25, 0, 200, 400);
}
void MainWindow::renderCanvas() {
    for (int i = index, k = 1; i <= index + 3; i++, k++)
        if (i < beatmap.size())
            for (int j = 0; j < beatmap[i].size(); j++)
                if (beatmap[i][j])
                    printBlackTile(j + 1, k);
}
void MainWindow::updateMessage(QString message) {
    painter->setBrush(QBrush(QColor(Qt::black)));
    painter->setFont(QFont("Arial", 18));
    painter->drawText(25, 425, message);
    painter->drawText(12, 350, tr(">"));
    painter->drawText(238, 350, tr("<"));
}
void MainWindow::paintEvent(QPaintEvent *) {
    painter = new QPainter();
    // painter->setPen(QPen(Qt::NoPen));
    painter->begin(this);
    updateMessage(message);
    clearCanvas();
    renderCanvas();
    painter->end();
}
int MainWindow::parseKey(int key) {
    switch (key) {
    case Qt::Key_D:
        return 1;
    case Qt::Key_F:
        return 2;
    case Qt::Key_J:
        return 3;
    case Qt::Key_K:
        return 4;
    case Qt::Key_Q:
        return 0;
    default:
        return -1;
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event) {
    int keyPressed = parseKey(event->key());
    this->update();
    if (keyPressed == 0)
        start();
    else if (keyPressed > 0) {
        if (index < beatmap.size()) {
            if (beatmap[index][keyPressed - 1]) {
                if (index == 0) {
                    timer->start();
                    message = tr("Go!!");
                }
                beatmap[index][keyPressed - 1] = 0;
                --noteInLevels[index];
                if (noteInLevels[index] == 0) {
                    ++index;
                    if (index == beatmap.size())
                        message = tr("Congrats! ") +
                                  QString::number(timer->elapsed() / 1000.0) +
                                  tr("s elapsed.");
                }
            } else {
                message = tr("You failed...");
                index = beatmap.size();
            }
        }
    }
    QWidget::keyPressEvent(event);
}
void MainWindow::generateBeatmap(int totalLevelsCount) {
    QVector<QVector<bool>> nullVector1;
    beatmap.swap(nullVector1);
    QVector<int> nullVector2;
    noteInLevels.swap(nullVector2);
    gen = QRandomGenerator::system();
    for (int i = 1; i <= totalLevelsCount; i++) {
        int noteCount = gen->bounded(1, 3);
        noteInLevels.push_back(noteCount);
        QVector<bool> tmp(4, 0);
        for (int j = 1; j <= noteCount; j++) {
            int slotChosen = gen->bounded(1, 5);
            while (tmp[slotChosen - 1])
                slotChosen = gen->bounded(1, 5);
            tmp[slotChosen - 1] = true;
        }
        beatmap.push_back(tmp);
    }
}
void MainWindow::printBlackTile(int slot, int level) {
    painter->setBrush(QBrush(QColor(Qt::black)));
    painter->drawRect((slot - 1) * 50 + 25, 400 - 100 * level, 50, 100);
}
MainWindow::~MainWindow() { delete ui; }
