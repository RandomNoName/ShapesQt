#include "Rectangle.h"

Shape_rect::Shape_rect(int x, int y, int width, int height) noexcept
{
    rect = QRect(x, y, width, height);
    center = rect.center();
}

Shape::ptr_t Shape_rect::deserialize(QTextStream& line)
{
    int width, height;
    int x, y;
    line    >> x
            >> y
            >> width
            >> height;
    return std::make_shared<Shape_rect>(x, y, width, height);
}

void Shape_rect::serialize(QTextStream& file) const
{
    file    << shape_type       << " "
            << rect.left()      << " "
            << rect.top()       << " "
            << rect.width()     << " "
            << rect.height()    << "\n";
}

void Shape_rect::draw(QPainter& painter) const
{
    painter.drawRect(rect);
}

bool Shape_rect::is_clicked(QPoint pos) const
{
    return rect.contains(pos);
}

void Shape_rect::set_right_bot(QPoint pos)
{
    QRect temp = rect;
    temp.setBottomRight(pos);

    int height = temp.height();
    int width = temp.width();
    if (width > min_width)
    {
        rect.setWidth(width);
    }
    if (height > min_height)
    {
        rect.setHeight(height);
    }
    center = rect.center();
}

void Shape_rect::set_left_top(QPoint pos)
{
    rect.moveTopLeft(pos);
    center = rect.center();
}

void Shape_rect::move_shape(QPoint pos)
{
    rect.moveCenter(pos);
    center = rect.center();
}
