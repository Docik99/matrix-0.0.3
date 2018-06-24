#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
class matrix_t {
private:
    T **elements_;
    unsigned int rows_;
    unsigned int collumns_;
public:
    matrix_t();

    matrix_t(int rows, int collumns);

    matrix_t(matrix_t<T> const &other);

    matrix_t &operator=(matrix_t<T> const &other);

    ~matrix_t();

    unsigned int rows() const;

    unsigned int collumns() const;

    matrix_t operator+(matrix_t<T> const &other) const;

    matrix_t operator-(matrix_t<T> const &other) const;

    matrix_t operator*(matrix_t<T> const &other) const;

    matrix_t &operator-=(matrix_t<T> const &other);

    matrix_t &operator+=(matrix_t<T> const &other);

    matrix_t &operator*=(matrix_t<T> const &other);

    std::istream &read(std::istream &stream);

    std::ostream &write(std::ostream &stream) const;

    T **create_matr(int rows_, int collumns_) {
        T **new_matr = new T *[rows_];
        for (int i = 0; i < rows_; i++) {
            new_matr[i] = new T[collumns_];
            for (int j = 0; j < collumns_; j++)
                new_matr[i][j] = 0;
        }
        return new_matr;
    }
};

template <typename T>
matrix_t<T>::matrix_t() {
    rows_ = 0;
    collumns_ = 0;
    elements_ = create_matr(rows_, collumns_);
}

template <typename T>
matrix_t<T>::matrix_t(int rows,int collumns){
    rows_=rows;
    collumns_=collumns;
    elements_ = create_matr(rows_, collumns_);
}

template <typename T>
matrix_t<T>::matrix_t( matrix_t<T> const & other ) {
    elements_ = create_matr(other.rows_, other.collumns_);
    for (int i = 0; i < other.rows_; i++)
        for (int j = 0; j < other.collumns_; j++)
            elements_[i][j] = other.elements_[i][j];
    rows_ = other.rows_;
    collumns_ = other.collumns_;
}

template <typename T>
matrix_t<T> & matrix_t<T>::operator =( matrix_t<T> const & other ) {
    if (this != &other) {
        for (unsigned int i = 0; i < rows_; ++i)
            delete[] elements_[i];
        delete[] elements_;
        rows_ = other.rows_;
        collumns_ = other.collumns_;
        elements_ = create_matr(rows_, collumns_);
        for (int i = 0; i < other.rows_; i++)
            for (int j = 0; j < other.collumns_; j++)
                elements_[i][j] = other.elements_[i][j];
    }
    return *this;
}

template <typename T>
matrix_t<T>::~matrix_t() {
    for (unsigned int i = 0; i < rows_; ++i) {
        delete[] elements_[i];
    }
    delete[] elements_;
}

template <typename T>
unsigned int matrix_t<T>::rows()  const {
    return rows_;
}

template <typename T>
unsigned int matrix_t<T>::collumns() const {
    return collumns_;
}

template <typename T>
matrix_t<T> matrix_t<T>::operator +( matrix_t<T> const & other ) const {
    assert(rows_ == other.rows_ && collumns_ == other.collumns_);
    matrix_t result(rows_, collumns_);
    for (unsigned int i = 0; i < rows_; i++){
        for (unsigned int j = 0; j < collumns_; j++){
            result.elements_[i][j] = elements_[i][j] + other.elements_[i][j];
        }
    }
    return result;
}

template <typename T>
matrix_t<T> matrix_t<T>::operator -( matrix_t<T> const & other ) const {
    assert(rows_ == other.rows_ && collumns_ == other.collumns_);
    matrix_t<T> result(rows_, collumns_);
    for (unsigned int i = 0; i < rows_; i++)
        for (unsigned int j = 0; j < collumns_; j++)
            result.elements_[i][j] = elements_[i][j] - other.elements_[i][j];
    return result;
}

template <typename T>
matrix_t<T> matrix_t<T>::operator *( matrix_t<T> const & other ) const {
    assert(collumns_ == other.rows_ );
    matrix_t<T> result(rows_, other.collumns_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.collumns_; j++) {
            result.elements_[i][j] = 0;
            for (int f = 0; f < collumns_; f++)
                result.elements_[i][j] += elements_[i][f] * other.elements_[f][j];
        }
    }
    return result;
}

template <typename T>
matrix_t<T> & matrix_t<T>::operator -=( matrix_t<T> const & other ) {
    assert(rows_ == other.rows_ && collumns_ == other.collumns_);
    for (unsigned int i = 0; i < rows_; i++)
        for (unsigned int j = 0; j < collumns_; j++)
            elements_[i][j] -= other.elements_[i][j];
    return *this;
}


template <typename T>
matrix_t<T> & matrix_t<T>::operator +=( matrix_t<T> const & other ) {
    assert(rows_ == other.rows_ && collumns_ == other.collumns_);
    for (unsigned int i = 0; i < rows_; i++)
        for (unsigned int j = 0; j < collumns_; j++)
            elements_[i][j] += other.elements_[i][j];
    return *this;
}

template <typename T>
matrix_t<T> & matrix_t<T>::operator *=( matrix_t<T> const & other ) {
    assert(collumns_ == other.rows_);
    matrix_t<T> copy(*this);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.collumns_; j++) {
            elements_[i][j] = 0;
            for (int f = 0; f < collumns_; f++)
                elements_[i][j] += copy.elements_[i][f] * other.elements_[f][j];
        }
    }
    collumns_ = other.collumns_;
    return *this;
}

template <typename T>
istream & matrix_t<T>::read( istream & stream ) {
    int rows;
    int collumns;
    char symbol;

    bool success = true;
    if( stream >> rows && stream >> symbol && symbol == ',' && stream >> collumns ) {
        T ** elements = new T *[ rows ];
        for( int i = 0; success && i < rows; ++i ) {
            elements[ i ] = new T[ collumns ];
            for( int j = 0; j < collumns; ++j ) {
                if( !( stream >> elements[ i ][ j ] ) ) {
                    success = false;
                    break;
                }
            }
        }

        if( success ) {
            for( int i = 0; i < rows_; ++i ) delete [] elements_[ i ];
            delete [] elements_;
            rows_ = rows;
            collumns_ = collumns;
            elements_ = elements;
        }
        else {
            for( int i = 0; i < rows; ++i ) delete [] elements[ i ];
            delete [] elements;
        }
    }
    else success = false;

    if( !success ) stream.setstate( ios_base::failbit );

    return stream;
}

template <typename T>
ostream & matrix_t<T>::write( ostream & stream ) const {
    stream << rows_ << ", " << collumns_;
    for( int i = 0; i < rows_; ++i ) {
        stream << '\n';
        for( int j = 0; j < collumns_; ++j ) {
            stream << elements_[ i ][ j ];
            if( j != collumns_ - 1 ) stream << ' ';
        }
    }
    return stream;
}
