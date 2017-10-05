#ifndef GAMEOFLIFE_WRAPPINGGRID_H
#define GAMEOFLIFE_WRAPPINGGRID_H
#include "Grid.h"


template<typename T>
class WrappingGrid: public Grid<T>
{
public:
    class Row: public Grid<T>::Row
        {
        public:
            Row(T*, int);
            Row(const Row&);
            Row& operator=(const Row&);
            T& operator[](int) override;
            const T& operator[](int) const override;
            int length() const override;
        private:
            int ln;
            T* row;
            int get_idx(int) const;
        };
    WrappingGrid(int, int);
    WrappingGrid(int, int, T);
    WrappingGrid(const WrappingGrid<T>&);  // copy constructor
    WrappingGrid(WrappingGrid &&) noexcept;  // move constructor
    ~WrappingGrid() override;
    WrappingGrid<T>& operator=(const WrappingGrid<T>&);  // copy assignment
    WrappingGrid<T>& operator=(WrappingGrid<T>&&) noexcept;  // move assignment
    typename Grid<T>::Row& operator[](int) override;
    const typename Grid<T>::Row& operator[](int) const override;
    int height() const override;
    int width() const override;
    Grid<T>* copy() const override;
private:
    int h;
    int w;
    T* grid;
    int get_idx(int) const;
    Row** rows;
};

#endif //GAMEOFLIFE_WRAPPINGGRID_H
