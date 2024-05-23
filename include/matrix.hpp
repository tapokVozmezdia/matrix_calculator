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
            for (int i = 0; i < this->_row_num; i++)
            {
                for (int j = 0; j < this->_col_num; j++)
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

        el_type& operator()(uint i, uint j)
        {
            i -= 1;
            j -= 1;

            if (i > this->_row_num || j > this->_col_num)
                throw std::logic_error("invalid matrix element access");
            return this->_data[i * this->_col_num + j];
        }

    private:
        uint _row_num;
        uint _col_num;

        /*
        Element in an n-th row and in a m-th column can be found
        like this: _data[n * this->_col_num + m]
        */
        std::vector<el_type> _data;
};