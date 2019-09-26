////////////////////////////////////////////////////////////////////////////////
// Module Name:  xipoint.h/cpp
// Authors:      Ryabtsev Yaroslav
// Version:      0.2.2
// Date:         26.09.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "xipoint.h"

#include <algorithm>        // min
#include <cmath>

namespace xi {

    // Point class implementation
    Point::Point(int x, int y) : _x(x), _y(y) {}

    void Point::shift(int xSh, int ySh) {
        setX(getX() + xSh);
        setY(getY() + ySh);
    }

    void Point::shift(int shf) {
        shift(shf, shf);
    }

    void Point::shift(const xi::Point &pt) {
        shift(pt.getX(), pt.getY());
    }

    double Point::dist(const xi::Point &other) const {
        return sqrt(
                (other.getX() - getX()) * (other.getX() - getX())
                + (other.getY() - getY()) * (other.getY() - getY()));
    }

    int Point::getX() const { return _x; }

    int Point::getY() const { return _y; }

    void Point::setX(int x) { _x = x; }

    void Point::setY(int y) { _y = y; }

    // PointArray class implementation
    PointArray::PointArray() {
        _size = 0;
        _arr = nullptr;
    }

    PointArray::PointArray(const xi::Point points[], xi::PointArray::Uint n) {
        _size = n;
        _arr = new Point[n];
        for (int i = 0; i < n; ++i) {
            _arr[i] = Point(points[i].getX(), points[i].getY());
        }
    }

    PointArray::PointArray(const xi::PointArray &pv) : PointArray(pv.getRawPtr(), pv.getSize()) {}

    PointArray::~PointArray() {
        delete[] _arr;
		_size = 0;
    }

    void PointArray::append(const xi::Point &pt) {
        resize(_size + 1);
        _arr[_size - 1] = Point(pt.getX(), pt.getY());
    }

    void PointArray::insert(const xi::Point &pt, xi::PointArray::Uint pos) {
        if (pos >= _size) {  // append to end if pos >= _size
            append(pt);
            return;
        }
        resize(_size + 1);
        for (int i = _size - 1; i > pos; --i) {  // shift elements before inserting
            _arr[i] = _arr[i - 1];
        }
        _arr[pos] = Point(pt.getX(), pt.getY());
    }

    void PointArray::remove(xi::PointArray::Uint pos) {
        if (pos >= _size)  // validity check
            return;
        for (int i = pos; i < _size - 1; ++i) {  // shift elements and overwrite the removed element
            _arr[i] = _arr[i + 1];
        }
        resize(_size - 1);
    }

    void PointArray::clear() { resize(0); }

    double PointArray::computePath() const {
        double distSum = 0.0;
        for (int i = 1; i < _size; ++i) {
            distSum += _arr[i - 1].dist(_arr[i]);
        }
        return distSum;
    }

    PointArray::Uint PointArray::getSize() const {
        return _size;
    }

    Point *PointArray::get(xi::PointArray::Uint pos) {
        if (pos >= _size)  // validity check
            return nullptr;
        return _arr + pos;
    }

    const Point *PointArray::get(xi::PointArray::Uint pos) const {
        if (pos >= _size)  // validity check
            return nullptr;
        return new Point(_arr[pos].getX(), _arr[pos].getY());
    }

    void PointArray::resize(xi::PointArray::Uint n) {
        if (n == 0) {
            _arr = nullptr;
            _size = 0;
            return;
        }

        auto *newArray = new Point[n];
        if (_arr != nullptr) {
            for (int i = 0; i < std::min(n, _size); ++i) {  // copy elements to new array
                newArray[i] = _arr[i];
            }
            delete[] _arr;
        }

        _arr = newArray;
        _size = n;
    }
} // namespace xi {
