#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeBrith(int n);

    void paintEvent(QPaintEvent* ev) override;

public slots:

    void upClick();
    void downClick();

private:
    Ui::MainWindow *ui;
    QImage* img;
    QPushButton* up_brith;
    QPushButton* down_brith;
};
#endif // MAINWINDOW_H
