#ifndef GAMEOFLIFE_GRID_H
#define GAMEOFLIFE_GRID_H

template<typename T>
class Grid
{
public:
    class Row
    {
        public:
            virtual ~Row() = default;
            virtual T& operator[](int) = 0;
            virtual const T& operator[](int) const = 0;
            virtual int length() const = 0;
    };
    virtual ~Grid() = default;
    virtual Row& operator[](int) = 0;
    virtual const Row& operator[](int) const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual Grid* copy() const = 0;
};

#endif //GAMEOFLIFE_GRID_H
