#pragma once

#include <unordered_map>

#include "matrix.hpp"

class MatrixCalculator
{
    public:
        MatrixCalculator() = default;

        Matrix<Fraction> getLastResult();

        void run();

    private:
        void __save_matrix(const Matrix<Fraction>& matrix,
            const std::string& key);

        void __display_menu();
        void __display_operations();

        void __update_matrices();
        void __print_matrices();

        void __perform_op();
        void __perform_command(lmc::CommandSelect cmd);

        Matrix<Fraction> __extract(const std::string& key);

        Matrix<Fraction> _res;

        std::unordered_map<std::string, Matrix<Fraction>> _saved_matrices;
};