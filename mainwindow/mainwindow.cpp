//=========================//
#include "ui_mainwindow.h"
#include "mainwindow.h"
//=========================//

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFocus();
    setMouseTracking(true);

    ui->setupUi(this);
    ui->centralwidget->setFocus();
    ui->centralwidget->setMouseTracking(true);

    engine.widget = this;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    engine.update_mouse_info(event);
    if (engine.mouse_released_task)
    {
        engine.mouse_released_task();
    }
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    engine.update_mouse_info(event);
    if (engine.mouse_pressed_task)
    {
        engine.mouse_pressed_task();
    }
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    engine.update_mouse_info(event);
    if (engine.mouse_moved_task)
    {
        engine.mouse_moved_task();
    }
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    engine.key = event->key();
    if (engine.keyboard_task)
    {
        engine.keyboard_task();
    }
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPen pen;
    pen.setWidth(2);
    QPainter painter(this);
    painter.setBrush(Qt::lightGray);
    painter.setPen(pen);

    update();
    engine.draw(painter);
}

void MainWindow::on_actionSave_triggered()
{
    engine.save_file();
}

void MainWindow::on_actionLoad_triggered()
{
    engine.load_file();
}

void MainWindow::on_actionDelete_triggered()
{
    engine.delete_shape_task();
}

void MainWindow::on_actionMove_triggered()
{
    engine.move_shape_task();
}

void MainWindow::on_actionBind_triggered()
{
    engine.bind_shape_task();
}

void MainWindow::on_actionRectangle_triggered()
{
    engine.add_and_resize_shape_task(std::make_shared<Shape_rect>());
}

void MainWindow::on_actionTriangle_triggered()
{
    engine.add_and_resize_shape_task(std::make_shared<Shape_triangle>());
}

void MainWindow::on_actionEllips_triggered()
{
    engine.add_and_resize_shape_task(std::make_shared<Shape_ellips>());
}
