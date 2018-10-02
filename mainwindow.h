#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void NumberPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ClearButtonPressed();
    void ChangeNumberSign();

};

#endif // MAINWINDOW_H

