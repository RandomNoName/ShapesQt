#include "Ellips.h"

Shape_ellips::Shape_ellips(int x, int y, int width, int height) noexcept
    : Shape_rect(x, y, width, height)
{
    center = rect.center();
}

Shape::ptr_t Shape_ellips::deserialize(QTextStream& line)
{
    int width, height;
    int x, y;
    line    >> x
        >> y
        >> width
        >> height;
    return std::make_shared<Shape_ellips>(x, y, width, height);
}

void Shape_ellips::serialize(QTextStream& file) const
{
    file    << shape_type       << " "
            << rect.left()      << " "
            << rect.top()       << " "
            << rect.width()     << " "
            << rect.height()    << "\n";
}

void Shape_ellips::draw(QPainter& painter) const
{
    painter.drawEllipse(rect);
}
