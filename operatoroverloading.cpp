#include <iostream>
#include <cassert>
using namespace std;

class Vector {
private:
    int* _array = nullptr;
    size_t _size = 0;
    size_t _capacity = 15;

    void resize() {
        _capacity *= 2;
        int* temp = new int[_capacity];

        for (size_t i = 0; i < _size; i++)
            temp[i] = _array[i];

        delete[] _array;
        _array = temp;
    }

public:
    Vector() {
        _array = new int[_capacity];
    }

    Vector(size_t capacity) {
        _capacity = capacity;
        _array = new int[_capacity];
    }

    ~Vector() {
        delete[] _array;
    }

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }

    void print() const {
        for (size_t i = 0; i < _size; i++)
            cout << _array[i] << " ";
        cout << endl;
    }

    int& operator[](size_t index) {
        assert(index < _size && "Index out of range!");
        return _array[index];
    }

    int& operator()(size_t index) {
        return (*this)[index];
    }

    Vector& push_back(int value) {
        if (_size >= _capacity)
            resize();

        _array[_size++] = value;
        return *this;
    }

    Vector& push_front(int value) {
        if (_size >= _capacity)
            resize();

        for (size_t i = _size; i > 0; i--)
            _array[i] = _array[i - 1];

        _array[0] = value;
        _size++;
        return *this;
    }

    Vector& pop_back() {
        if (_size > 0)
            _size--;
        return *this;
    }

    Vector& pop_front() {
        if (_size == 0) return *this;

        for (size_t i = 0; i < _size - 1; i++)
            _array[i] = _array[i + 1];

        _size--;
        return *this;
    }

    void delete_by_index(size_t index) {
        assert(index < _size);

        for (size_t i = index; i < _size - 1; i++)
            _array[i] = _array[i + 1];

        _size--;
    }

    void insert_by_index(size_t index, int element) {
        assert(index <= _size);

        if (_size >= _capacity)
            resize();

        for (size_t i = _size; i > index; i--)
            _array[i] = _array[i - 1];

        _array[index] = element;
        _size++;
    }

    size_t find(int element) {
        for (size_t i = 0; i < _size; i++)
            if (_array[i] == element)
                return i;

        return -1;
    }

    size_t rfind(int element) {
        for (int i = _size - 1; i >= 0; i--)
            if (_array[i] == element)
                return i;

        return -1;
    }

    void sort(bool reverse = false) {
        for (size_t i = 0; i < _size - 1; i++) {
            for (size_t j = i + 1; j < _size; j++) {
                if ((!reverse && _array[i] > _array[j]) ||
                    (reverse && _array[i] < _array[j])) {
                    swap(_array[i], _array[j]);
                }
            }
        }
    }

    //  operator+

    Vector operator+(const Vector& other) {
        Vector result(_size + other._size);

        for (size_t i = 0; i < _size; i++)
            result.push_back(_array[i]);

        for (size_t i = 0; i < other._size; i++)
            result.push_back(other._array[i]);

        return result;
    }

    //  operator==

    bool operator==(const Vector& other) {
        if (_size != other._size) return false;

        for (size_t i = 0; i < _size; i++)
            if (_array[i] != other._array[i])
                return false;

        return true;
    }

    bool operator!=(const Vector& other) {
        return !(*this == other);
    }

    //  ++

    Vector& operator++() {
        for (size_t i = 0; i < _size; i++)
            _array[i]++;
        return *this;
    }

    Vector operator++(int) {
        Vector temp = *this;
        ++(*this);
        return temp;
    }

    //  --

    Vector& operator--() {
        for (size_t i = 0; i < _size; i++)
            _array[i]--;
        return *this;
    }

    Vector operator--(int) {
        Vector temp = *this;
        --(*this);
        return temp;
    }
};
