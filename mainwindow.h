#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCursor>
#include <QElapsedTimer>
#include <QFont>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QRandomGenerator>
#include <QThread>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;
    void start();
    void printBlackTile(int slot, int level);
    void generateBeatmap(int totalLevelsCount);
    void clearCanvas();
    void renderCanvas();
    void updateMessage(QString message);
    int parseKey(int key);
    // QVector<int> beatmap;
    QVector<QVector<bool>> beatmap;
    QVector<int> noteInLevels;
    QRandomGenerator *gen;
    QElapsedTimer *timer;
    int index = 0;
    QString message;

  protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    QPainter *painter;
    QBrush *brush;
};
#endif // MAINWINDOW_H
