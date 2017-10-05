#ifndef GAMEOFLIFE_WRAPPINGGRID_TCC
#define GAMEOFLIFE_WRAPPINGGRID_TCC

#include "WrappingGrid.h"

template<typename T>
WrappingGrid<T>::WrappingGrid(int h, int w)
    :grid{new T[h * w]}, w{w}, h{h}, rows{new WrappingGrid<T>::Row*[h]}
{
    for (auto i = 0; i < h; i++) { rows[i] = new Row(&grid[i*w], w); }
}

template<typename T>
WrappingGrid<T>::WrappingGrid(int h, int w, T val)
    :grid{new T[h * w]}, w{w}, h{h}, rows{new WrappingGrid<T>::Row*[h]}
{
    for (auto i = 0; i < h; i++) { rows[i] = new Row(&grid[i*w], w); }
    for (auto i = 0; i < (h * w); i++) { grid[i] = val; }
}

template<typename T>
WrappingGrid<T>::WrappingGrid(const WrappingGrid& other)
    :grid{new T[other.h * other.w]}, w{other.w}, h{other.h}, rows{new WrappingGrid<T>::Row*[h]}
{
    for (auto i = 0; i < h; i++) { rows[i] = new Row(&grid[i * w], w); }
    for (auto i = 0; i < h * w; i++) { grid[i] = other.grid[i]; }
}

template<typename T>
WrappingGrid<T>::WrappingGrid(WrappingGrid<T>&& other) noexcept
    :h{h}, w{w}, grid{grid}, rows{rows}
{
    other.grid = nullptr;
    other.rows = nullptr;
}

template<typename T>
WrappingGrid<T>& WrappingGrid<T>::operator=(const WrappingGrid<T>& other)
{
    h = other.h;
    w = other.w;
    delete[] grid;
    for (auto i = 0; i < h; i++) { delete rows[i]; }
    delete[] rows;
    grid = new T[h*w];
    rows = new Row*[h];
    for (auto i = 0; i < h; i++) { rows[i] = new Row(&grid[i * w], w); }
    for (auto i = 0; i < h * w; i++) { grid[i] = other.grid[i]; }
    return *this;
}

template<typename T>
WrappingGrid<T>& WrappingGrid<T>::operator=(WrappingGrid<T>&& other) noexcept
{
    h = other.h;
    w = other.w;
    grid = other.grid; other.grid = nullptr;
    rows = other.rows; other.rows = nullptr;
    return *this;
}

template<typename T>
WrappingGrid<T>::~WrappingGrid() {
    delete[] grid;
    for (auto i = 0; i < h; i++) { delete rows[i]; }
    delete[] rows;
}

template<typename T>
int WrappingGrid<T>::height() const { return h; }

template<typename T>
int WrappingGrid<T>::width() const { return w; }

template<typename T>
Grid<T>* WrappingGrid<T>::copy() const
{
    auto gr = new WrappingGrid<T>(*this);
    return gr;
}

template<typename T>
int WrappingGrid<T>::get_idx(int y) const { return (((y % h) + h) % h); }

template<typename T>
typename Grid<T>::Row& WrappingGrid<T>::operator[](int y) { return *(rows[get_idx(y)]); }

template<typename T>
const typename Grid<T>::Row& WrappingGrid<T>::operator[](int y) const { return *(rows[get_idx(y)]); }

template<typename T>
WrappingGrid<T>::Row::Row(T* row, int ln)
    :ln{ln}, row{row}
{}

template<typename T>
WrappingGrid<T>::Row::Row(const Row& other)
    :ln{other.ln}, row{other.row}
{}

template<typename T>
typename WrappingGrid<T>::Row& WrappingGrid<T>::Row::operator=(const WrappingGrid<T>::Row& other)
{
    ln = other.ln;
    row = other.row;
}

template<typename T>
T& WrappingGrid<T>::Row::operator[](int x) { return row[get_idx(x)]; }

template<typename T>
const T& WrappingGrid<T>::Row::operator[](int x) const { return row[get_idx(x)]; };

template<typename T>
int WrappingGrid<T>::Row::length() const { return ln; }

template<typename T>
int WrappingGrid<T>::Row::get_idx(int x) const {
    return ((x % ln) + ln) % ln;
}

#endif //GAMEOFLIFE_WRAPPINGGRID_TCC
