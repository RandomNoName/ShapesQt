#pragma once
#include "Shape.h"

struct Shape_triangle final : Shape
{
    static constexpr const char* shape_type = "triangle";
    static constexpr int min_height = 10;
    static constexpr int min_width = 10;
    Shape_triangle(int x = 200, int y = 200, int width = min_width, int height = min_height) noexcept;
    inline void serialize(QTextStream& file)  const override;
    static Shape::ptr_t deserialize(QTextStream& line);
    inline void draw(QPainter& painter) const override;
    inline bool is_clicked(QPoint pos)  const override;
    inline void set_right_bot(QPoint pos) override;
    inline void set_left_top(QPoint pos) override;
    inline void move_shape(QPoint pos)  override;
    virtual ~Shape_triangle() = default;
    static QPoint calc_center(QPoint a, QPoint b, QPoint c);
private:
    QRect rect;
};
