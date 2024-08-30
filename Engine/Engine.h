#pragma once
//=========================//
#include <QWidget>
#include <QString>
#include <QFile>
//=========================//
#include "Rectangle/Rectangle.h"
#include "Triangle/Triangle.h"
#include "Ellips/Ellips.h"
//=========================//
#include <functional>
#include <vector>
//=========================//

struct Engine
{
public:
    using iterator  = std::vector<Shape::ptr_t>::iterator;
    void update_mouse_info(QMouseEvent* event);

    void draw(QPainter& painter);
    void clear_tasks();

    void add_and_resize_shape_task(const Shape::ptr_t& ptr);
    void delete_shape_task();
    void move_shape_task();
    void bind_shape_task();

    void save_file();
    void load_file();

    std::vector<Shape::ptr_t> shapes;

    std::function<void()> mouse_released_task;
    std::function<void()> mouse_pressed_task;
    std::function<void()> mouse_moved_task;
    std::function<void()> keyboard_task;

    QWidget* widget;
    int key;
private:
    QString get_file_name();
    iterator find_clicked();

    std::vector<std::pair<QPoint*, QPoint*>> lines;
    bool unfinished{};

    Qt::MouseButtons buttons;
    QPoint mouse_pos;
};
