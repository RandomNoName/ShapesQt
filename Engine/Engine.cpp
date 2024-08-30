//=========================//
#include <QFileDialog>
//=========================//
#include "mainwindow/mainwindow.h"
#include "Engine/Engine.h"
//=========================//

void Engine::draw(QPainter& painter)
{
    for (auto& shape : shapes)
    {
        shape->draw(painter);
    }
    for (auto [from, to] : lines)
    {
        painter.drawLine(*from, *to);
    }
}

void Engine::update_mouse_info(QMouseEvent* event)
{
    buttons = event->buttons();
    mouse_pos = event->pos();
}

void Engine::clear_tasks()
{
    widget->setCursor(Qt::ArrowCursor);
    mouse_released_task = nullptr;
    mouse_pressed_task = nullptr;
    mouse_moved_task = nullptr;
    keyboard_task = nullptr;
    key = 0;

    if (unfinished)
    {
        lines.pop_back();
        unfinished = false;
    }
}

Engine::iterator Engine::find_clicked()
{
    return std::find_if(shapes.begin(), shapes.end(), [this](const Shape::ptr_t& element)
        {
            return element->is_clicked(mouse_pos);
        });
}

void Engine::add_and_resize_shape_task(const Shape::ptr_t& ptr)
{
    clear_tasks();
    mouse_pressed_task = [this, ptr = std::move(ptr)]()
    {
        widget->setCursor(Qt::PointingHandCursor);
        if (buttons & Qt::LeftButton)
        {
            ptr->set_left_top(mouse_pos);
            shapes.push_back(ptr);

            mouse_pressed_task = [this]()
            {
                if (buttons & Qt::RightButton)
                {
                    shapes.pop_back();
                    return clear_tasks();
                }
            };
            mouse_moved_task = [this]()
            {
                shapes.back()->set_right_bot(mouse_pos);
            };
        }
    };
    keyboard_task = [this]()
    {
        if (key == Qt::Key_Escape)
        {
            shapes.pop_back();
            return clear_tasks();
        }
    };
    mouse_released_task = [this]()
    {
        clear_tasks();
    };
}

void Engine::delete_shape_task()
{
    clear_tasks();
    widget->setCursor(Qt::ForbiddenCursor);
    mouse_pressed_task = [this]()
    {
        if (buttons & Qt::LeftButton)
        {
            auto it = find_clicked();
            if (it != shapes.end())
            {
                QPoint* center = &(*it)->center;
                auto to_erase = std::remove_if(lines.begin(), lines.end(), [center](std::pair<QPoint*, QPoint*> line)
                {
                    return center == line.first || center == line.second;
                });
                lines.erase(to_erase, lines.end());
                shapes.erase(it);
                clear_tasks();
            }
        }
    };
}

void Engine::move_shape_task()
{
    clear_tasks();
    mouse_pressed_task = [this]()
    {
        widget->setCursor(Qt::PointingHandCursor);
        if (buttons & Qt::RightButton)
        {
            return clear_tasks();
        }
        auto it = find_clicked();
        if (it == shapes.end())
        {
            return clear_tasks();
        }
        auto& ptr = *it;
        ptr->move_shape(mouse_pos);
        mouse_moved_task = [this, ptr]()
        {
            ptr->move_shape(mouse_pos);
        };
    };
    keyboard_task = [this]()
    {
        if (key == Qt::Key_Escape)
        {
            return clear_tasks();
        }
    };
    mouse_released_task = [this]()
    {
        clear_tasks();
    };
}

void Engine::bind_shape_task()
{
    clear_tasks();
    widget->setCursor(Qt::CrossCursor);
    mouse_pressed_task = [this]()
    {
        auto it = find_clicked();
        if (it == shapes.end())
        {
            return clear_tasks();
        }
        unfinished = true;
        auto& ptr = *it;
        lines.emplace_back(&ptr->center, &mouse_pos);
        keyboard_task = [this]()
        {
            if (key == Qt::Key_Escape)
            {
                lines.pop_back();
                unfinished = false;
                return clear_tasks();
            }
        };
        mouse_pressed_task = [this]()
        {
            auto it = find_clicked();
            if (it != shapes.end())
            {
                QPoint* p1 = lines.back().first;
                QPoint* p2 = &(*it)->center;
                lines.back().second = p2;
                auto same_line = std::find_if(lines.begin(), lines.end(), [p1, p2](std::pair<QPoint*, QPoint*> line)
                {
                    return line.first == p1 && line.second == p1 ||
                           line.first == p2 && line.second == p1;
                });
                if (same_line == lines.end())
                {
                    unfinished = false;
                    return clear_tasks();
                }
            }
            unfinished = false;
            lines.pop_back();
            clear_tasks();
        };
    };
}

QString Engine::get_file_name()
{
    return QFileDialog::getOpenFileName(
        nullptr,
        "Open Text File",
        "",
        "Text Files (*.txt)"
        );
}

void Engine::save_file()
{
    QFile file = get_file_name();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    clear_tasks();
    QTextStream file_stream(&file);
    for (auto& shape : shapes)
    {
        shape->serialize(file_stream);
    }
    if (lines.empty())
        return;
    file_stream << "Lines:\n";
    QString buffer;
    QString temp;
    for (auto [from, to] : lines)
    {
        auto it = std::find_if(shapes.begin(), shapes.end(), [from](const Shape::ptr_t& ptr)
        {
           return &ptr->center == from;
        });
        size_t p1 = (it - shapes.begin());

        it = std::find_if(shapes.begin(), shapes.end(), [&to](const Shape::ptr_t& ptr)
        {
            return &ptr->center == to;
        });
        size_t p2 = (it - shapes.begin());

        temp = QString("%1 %2\n").arg(p1).arg(p2);
        buffer.append(temp);
    }
    buffer.chop(1); // Removes extra "\n"
    file_stream << buffer;
}

void Engine::load_file()
{
    Shape_register::registrate<Shape_triangle>();
    Shape_register::registrate<Shape_ellips>();
    Shape_register::registrate<Shape_rect>();

    QFile file = get_file_name();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    clear_tasks();
    shapes.clear();
    lines.clear();
    QTextStream file_stream(&file); 
    QString word;
    while (!file_stream.atEnd())
    {
        file_stream >> word;
        if (Shape_register::is_registered(word))
        {
            shapes.push_back(Shape_register::get_registered(word, file_stream));
        }
        else if (word == "Lines:")
        {
            size_t i, j;
            while(!file_stream.atEnd())
            {
                file_stream >> i >> j;
                QPoint* p1 = &shapes[i]->center;
                QPoint* p2 = &shapes[j]->center;
                lines.emplace_back(p1, p2);
            }
            break;
        }
        else break;
    }
    Shape_register::clear();
}
