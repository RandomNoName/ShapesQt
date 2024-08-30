#pragma once
#include "Rectangle/Rectangle.h"

struct Shape_ellips final : Shape_rect
{
    static constexpr const char* shape_type = "ellips";
    Shape_ellips(int x = 200, int y = 200, int width = min_width, int height = min_height) noexcept;
    inline void serialize(QTextStream& file)  const override;
    static Shape::ptr_t deserialize(QTextStream& line);
    inline void draw(QPainter& painter) const override;
    virtual ~Shape_ellips() = default;
};

