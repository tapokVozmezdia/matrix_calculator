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

        // ONLY TO BE USED WITH SINGLE-VALUE NUMERIC DATATYPES
        // (INT, FLOAT, DOUBLE, FRACTION, etc.)
        template<class coef_type>
        Matrix<el_type> operator*(coef_type value)
        {
            Matrix<el_type> result(*this);

            for (int i = 0; i < this->_data.size(); ++i)
                result._data[i] *= value;
            
            return result;
        }

        Matrix<el_type> operator-(const Matrix<el_type>& other)
        {
            Matrix<el_type> result(*this + (
                Matrix<el_type>(other) * -1
            ));
            return result;
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

        uint _row_num;
        uint _col_num;

        /*
        Element in an n-th row and in a m-th column can be found
        like this: _data[n * this->_col_num + m]
        */
        std::vector<el_type> _data;
};