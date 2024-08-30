#pragma once
//=========================//
#include <QTextStream>
#include <QString>
#include <QPainter>
#include <QPoint>
//=========================//
#include <unordered_map>
#include <algorithm>
#include <memory>

struct Shape
{
    using ptr_t = std::shared_ptr<Shape>;
    inline virtual void serialize(QTextStream& file) const = 0;
    inline virtual void draw(QPainter& painter) const = 0;
    inline virtual bool is_clicked(QPoint pos) const = 0;
    inline virtual void set_right_bot(QPoint pos) = 0;
    inline virtual void set_left_top(QPoint pos) = 0;
    inline virtual void move_shape(QPoint pos) = 0;
    virtual ~Shape() = default;

    QPoint center;
};

class Shape_register
{
public:
    inline static Shape::ptr_t get_registered(const QString& shape_type, QTextStream& line)
    {
        return factory.find(shape_type)->second(line);
    }

    inline static bool is_registered(const QString& shape_type)
    {
        return factory.find(shape_type) != factory.end();
    }

    template<class Derived>
    inline static void registrate()
    {
        factory[Derived::shape_type] = &Derived::deserialize;
    }

    inline static void clear()
    {
        factory.clear();
    }
    using deserializer = Shape::ptr_t(*)(QTextStream&);
private:
    inline static std::unordered_map<QString, deserializer> factory;
};
