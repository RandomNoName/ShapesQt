#include "Triangle.h"

Shape_triangle::Shape_triangle(int x, int y, int width, int height) noexcept
{
    rect = QRect(x, y, width, height);
    center = center = calc_center(rect.topLeft(), rect.bottomLeft(), rect.bottomRight());
}
Shape::ptr_t Shape_triangle::deserialize(QTextStream& line)
{
    int width, height;
    int x, y;
    line    >> x
            >> y
            >> width
            >> height;
    return std::make_shared<Shape_triangle>(x, y, width, height);
}

void Shape_triangle::serialize(QTextStream& file) const
{
    file    << shape_type       << " "
            << rect.left()      << " "
            << rect.top()       << " "
            << rect.width()     << " "
            << rect.height()    << "\n";
}

void Shape_triangle::draw(QPainter& painter) const
{
    QPolygon triangle;
    triangle << rect.topLeft() << rect.bottomLeft() << rect.bottomRight();
    painter.drawPolygon(triangle);
}

bool Shape_triangle::is_clicked(QPoint pos) const
{
    QPoint a = rect.topLeft();
    QPoint b = rect.bottomLeft();
    QPoint c = rect.bottomRight();

    QPoint v0 = b - a;
    QPoint v1 = c - a;
    QPoint v2 = pos - a;

    double dot00 = v0.x() * v0.x() + v0.y() * v0.y();
    double dot01 = v0.x() * v1.x() + v0.y() * v1.y();
    double dot02 = v0.x() * v2.x() + v0.y() * v2.y();
    double dot11 = v1.x() * v1.x() + v1.y() * v1.y();
    double dot12 = v1.x() * v2.x() + v1.y() * v2.y();

    double inverse_denominator = 1 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * inverse_denominator;
    double v = (dot00 * dot12 - dot01 * dot02) * inverse_denominator;
    return (u >= 0) && (v >= 0) && (u + v < 1);
}

void Shape_triangle::set_right_bot(QPoint pos)
{
    QRect temp = rect;
    temp.setBottomRight(pos);
    int height = temp.height();
    if (height > min_height)
    {
        rect.setHeight(height);
    }
    int width = temp.width();
    if (width > min_width)
    {
        rect.setWidth(width);
    }
    center = calc_center(rect.topLeft(), rect.bottomLeft(), rect.bottomRight());
}

void Shape_triangle::set_left_top(QPoint pos)
{
    rect.moveTopLeft(pos);
    center = calc_center(rect.topLeft(), rect.bottomLeft(), rect.bottomRight());
}

void Shape_triangle::move_shape(QPoint pos)
{
    rect.moveCenter(pos);
    center = calc_center(rect.topLeft(), rect.bottomLeft(), rect.bottomRight());
}

QPoint Shape_triangle::calc_center(QPoint a, QPoint b, QPoint c)
{
    return { (a.x() + b.x() + c.x()) / 3, (a.y() + b.y() + c.y()) / 3 };
}
