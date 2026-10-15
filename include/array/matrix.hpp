//include/matrix.hpp
#pragma once

#include "vector.hpp"
#include <stdexcept>  // std::out_of_range

namespace dsac::array{
class Matrix {
    private:
        int rows{0};
        int cols{0};
        dsac::array::Vector<dsac::array::Vector<int>> data;

    public:
        Matrix(int r, int c) {
            if (r < 0 || c < 0 ) {
                throw std::out_of_range("Negative dimensions");
            }
            rows = r;
            cols = c;
            for (int i = 0; i < rows; i++) {
                Vector<int> row;
                for (int j = 0; j < cols; j++) {
                row.push_back(0);
            }
            data.push_back(row);
            }
        }

        /// TODO:
        //data.at(i).at(j)
        int& operator()(int i, int j) {
            return data.at(i).at(j);
        }

        // TODO:
        // throw std::out_of_range("dimensions must match")
        // result(i, j) = (*this)(i, j) + other(i, j)
        Matrix operator+(Matrix& other) {
            if (rows != other.rows || cols != other.cols) {
                throw std::out_of_range("dimensions should match");
            }
            Matrix res(rows, cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    res(i, j) = (*this)(i, j) + other(i, j);
                }
            }
            return res;
        }
};

}