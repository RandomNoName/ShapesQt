#pragma once
//=========================//
#include <QMainWindow>
#include <QMouseEvent>
//=========================//
#include "Engine/Engine.h"
//=========================//

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_actionSave_triggered();
    void on_actionLoad_triggered();

    void on_actionRectangle_triggered();
    void on_actionTriangle_triggered();
    void on_actionEllips_triggered();

    void on_actionDelete_triggered();
    void on_actionBind_triggered();
    void on_actionMove_triggered();
private:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    Ui::MainWindow *ui;
    Engine engine;
};
