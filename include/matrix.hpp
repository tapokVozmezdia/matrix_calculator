// refused from decomposition due to .cpp file becoming completely unreadable

#pragma once

#include <iostream>
#include <vector>

#include "fraction.hpp"

template<class el_type>
class Matrix
{
    public:
        // by default returns 3x3 identity matrix
        Matrix()
        {
            this->_row_num = 3;
            this->_col_num = 3;
            this->__identity();
        }

        // returns matrix the size of n x m, which has 1s on 
        // the main diagonal and 0s in every other element
        explicit Matrix(uint n, uint m)
        {
            this->_row_num = n;
            this->_col_num = m;

            this->__identity();
        }

        Matrix(const Matrix<el_type>& other)
        {
            this->_row_num = other._row_num;
            this->_col_num = other._col_num;

            for (auto i : other._data)
                this->_data.push_back(i);
        }

        Matrix<el_type>& operator=(const Matrix<el_type>& other)
        {
            this->ColNum = other._col_num;
            this->RowNum = other._row_num;
            this->_data.clear();

            for (auto i : other._data)
                this->_data.push_back(i);
        }

        Matrix<el_type> operator+(const Matrix<el_type>& other)
        {
            if (this->_col_num != other._col_num ||
                this->_row_num != other._row_num)
                throw std::logic_error("invalid matrix addition");

            Matrix<el_type> result(*this);
            for (int i = 0; i < result._data.size(); ++i)
                result._data[i] += other._data[i];

            return result;
        }

        Matrix<el_type> operator*(el_type value)
        {
            Matrix<el_type> result(*this);

            for (int i = 0; i < this->_data.size(); ++i)
                result._data[i] *= value;
            
            return result;
        }

        Matrix<el_type> operator*(const Matrix<el_type>& other)
        {
            if (this->_col_num != other._row_num)
                throw std::logic_error("invalid matrix multiplication");

            Matrix<el_type> result(this->_row_num, other._col_num);
            for (int i = 1; i <= this->_row_num; ++i)
            {
                for (int j = 1; j <= other._col_num; ++j)
                {
                    el_type el = 0;
                    for (int k = 1; k <= this->_col_num; ++k)
                    {
                        el += (
                            this->_data[(i - 1) * this->_col_num + (k - 1)] *
                            other._data[(k - 1) * other._col_num + (j - 1)]
                        );
                    }
                    result(i, j) = el;
                }
            }
            return result;
        }

        Matrix<el_type> operator-(const Matrix<el_type>& other)
        {
            Matrix<el_type> result(*this + (
                Matrix<el_type>(other) * -1
            ));
            return result;
        }

        Matrix<el_type> operator/(el_type value)
        {
            Matrix<el_type> result(*this);

            for (int i = 0; i < this->_data.size(); ++i)
                result._data[i] /= value;
            
            return result;
        }

        Matrix<el_type>& operator+=(const Matrix<el_type>& other)
        {
            *this = *this + other;
            return *this;
        }

        Matrix<el_type>& operator*=(el_type value)
        {
            *this = *this * value;
            return *this;
        }

        Matrix<el_type>& operator*=(const Matrix<el_type>& other)
        {
            *this = *this * other;
            return *this;
        }

        Matrix<el_type>& operator-=(const Matrix<el_type>& other)
        {
            *this = *this - other;
            return *this;
        }

        Matrix<el_type>& operator/=(el_type value)
        {
            *this = *this / value;
            return *this;
        }

        bool operator==(const Matrix<el_type>& other)
        {
            if (this->_row_num != other._row_num ||
                this->_col_num != other._col_num)
                return false;
            
            for (int i = 0; i < this->_data.size(); ++i)
                if (this->_data[i] != other._data[i])
                    return false;

            return true;
        }

        bool operator!=(const Matrix<el_type>& other)
        {
            return !(*this == other);
        }

        friend std::ostream& operator<<
            (std::ostream& ostream, const Matrix<el_type>& matrix)
        {
            for (int i = 0; i < matrix._row_num; i++)
            {
                for (int j = 0; j < matrix._col_num; j++)
                {
                    ostream << matrix._data[i * matrix._col_num + j] << " ";
                }
                ostream << "\n";
            }

            return ostream;
        }

        // use with caution
        // reads input of n*m elements from the stream
        friend std::istream& operator>>
            (std::istream& istream, Matrix<el_type>& matrix)
        {
            matrix._data.clear();

            for (int i = 0; i < matrix._row_num; ++i)
            {
                for (int j = 0; j < matrix._col_num; ++j)
                {
                    matrix._data.push_back(0);
                    istream >> matrix._data[i * matrix._col_num + j];
                }
            }

            return istream;
        }

        el_type& operator()(uint i, uint j)
        {
            i -= 1;
            j -= 1;

            if (i > this->_row_num || j > this->_col_num)
                throw std::logic_error("invalid matrix element access");
            return this->_data[i * this->_col_num + j];
        }

        // returns new matrix that is a transpose of the original
        Matrix<el_type> Transpose()
        {
            Matrix<el_type> result(this->_col_num, this->_row_num);
            for (int i = 0; i < this->_col_num; ++i)
            {
                for (int j = 0; j < this->_row_num; ++j)
                {
                    result._data[i * result._col_num + j]
                        = this->_data[j * this->_col_num + i];
                }
            }
            return result;
        }

        // returns new matrix that is an inverse of the original
        Matrix<el_type> Inverse()
        {
            Matrix<el_type> result(*this);
            result._data.clear();

            for (int i = 1; i <= this->_row_num; ++i)
            {
                for (int j = 1; j <= this->_col_num; ++j)
                {
                    result._data.push_back(
                        this->__cofactor(i, j)
                    );
                }
            }

            return (
                result.Transpose() /
                this->Determinant()
            );
        }

        el_type Determinant()
        {
            return this->__determinant(*this);
        }

        uint RowNum()
        {
            return this->RowNum;
        }

        uint ColNum()
        {
            return this->ColNum;
        }

    private:
        void __identity()
        {
            this->_data.clear();

            for (int i = 0; i < this->_row_num; ++i)
            {
                for (int j = 0; j < this->_col_num; ++j)
                {
                    if (i == j)
                    {
                        this->_data.push_back(1);
                        continue;
                    }
                    this->_data.push_back(0);
                }
            }
        }

        // returns a matrix without n-th row and m-th column
        Matrix<el_type> __matrixWOel(const Matrix<el_type>& other, uint n, uint m)
        {
            if (other._row_num < 2 || other._col_num < 2 ||
                n > other._row_num || m > other._col_num)
                throw std::logic_error("error __matrixWOel");

            Matrix<el_type> matrix(
                other._row_num - 1, 
                other._col_num - 1
            );

            matrix._data.clear();

            for (int i = 1; i <= other._row_num; ++i)
            {
                if (i == n)
                    ++i;
                if (i > other._row_num)
                        break;

                for (int j = 1; j <= other._col_num; ++j)
                {
                    if (j == m)
                        ++j;
                    if (j > other._col_num)
                        break;

                    matrix._data.push_back(
                        other._data[(i-1) * other._col_num + (j - 1)]
                    );
                }
            }

            return matrix;
        }

        el_type __determinant(const Matrix<el_type>& matrix)
        {
            if (matrix._col_num != matrix._row_num)
                throw std::logic_error("invalid matrix size");

            if (matrix._col_num == 2)
            {    
                // don't know why, but this does not work in
                // det = matrix._data[0] * matrix._data[3] - 
                // - matrix._data[1] * matrix._data[2] format
                el_type det = matrix._data[0];
                det *= matrix._data[3];
                el_type h = matrix._data[1];
                h *= matrix._data[2];
                det -= h;
                return det;
            }

            el_type det = 0;

            for (int i = 1; i <= matrix._col_num; ++i)
            {
                el_type h = matrix._data[i - 1];

                if (h == 0)
                    continue;

                Matrix<el_type> matrixWOel(
                    __matrixWOel(matrix, 1, i)
                );

                det += (
                    h *
                    (i % 2 == 0 ? -1 : 1) *
                    this->__determinant(matrixWOel)
                );
            }

            return det;
        }

        // returns cofactor of (i, j) matrix element
        // cofactor = algebraic adjustment
        el_type __cofactor(uint i, uint j)
        {
            return
                this->__determinant(
                    this->__matrixWOel(*this, i, j)
                ) * ((i + j) % 2 == 0 ? 1 : -1);
        }

        uint _row_num;
        uint _col_num;

        /*
        Element in an n-th row and in a m-th column can be found
        like this: _data[n * this->_col_num + m]
        */
        std::vector<el_type> _data;
};