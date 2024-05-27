#include "matrix_calc.hpp"
#include <fstream>
#include <string>
#include <sstream>

Matrix<Fraction> MatrixCalculator::getLastResult()
{
    return this->_res;
}

void MatrixCalculator::run()
{
    while(true)
    {
        this->__display_menu();
    }
}

void MatrixCalculator::__save_matrix(const Matrix<Fraction>& matrix, 
    const std::string& key)
{
    this->_saved_matrices[key] = matrix;
}

void MatrixCalculator::__display_menu()
{
    for (int i = 1; i <= lmc::CommandSelect::CMD_CLOSE; ++i)
        std::cout << i <<") " << 
            lmc::cmd_to_str(static_cast<lmc::CommandSelect>(i)) << std::endl;
    
    std::string k = "";
    int c = 0;
    while (true)
    {
        // std::cin.clear();
        // std::cin.ignore(1);
        // std::cout << " ";
        std::cin >> k;
        if (!lmc::is_int(k))
        {
            std::cout << lmc::cmd_to_str(lmc::CMD_BAD_COMMAND) << std::endl;
            continue;
        }
        c = std::stoi(k);
        if (c < 1 || c > lmc::CMD_CLOSE)
            std::cout << lmc::cmd_to_str(lmc::CMD_BAD_COMMAND);
        else
            break;
    }

    this->__perform_command(static_cast<lmc::CommandSelect>(c));
}

void MatrixCalculator::__display_operations()
{
    for (int i = 1; i <= lmc::OperationSelect::OP_POW; ++i)
        std::cout << lmc::operation_cheatsheet(
            static_cast<lmc::OperationSelect>(i)
        ) << std::endl;
}

void MatrixCalculator::__update_matrices()
{
    std::ofstream check;
    check.open("matrices.txt", std::ios_base::app);
    check.close();

    std::ifstream stream;
    stream.open("matrices.txt");

    if (!stream.is_open())
        throw std::logic_error("file opening error");

    std::string line, tmp_line;
    std::stringstream ss;

    uint n, m;
    std::string matrix_name;

    while (getline(stream, line))
    {
        if (line.length() == 0)
            continue;
        ss = std::stringstream(line);
        getline(ss, matrix_name, ' ');
        getline(ss, tmp_line, 'x');
        n = stoi(tmp_line);
        getline(ss, tmp_line);
        m = stoi(tmp_line);

        Matrix<Fraction> tmp_matrix(n, m);
        stream >> tmp_matrix;
        this->_saved_matrices[matrix_name] = tmp_matrix;
    }

    stream.close();
}

void MatrixCalculator::__print_matrices()
{
    for (auto it : this->_saved_matrices)
    {
        std::cout << "Matrix " << it.first << std::endl;
        std::cout << it.second << std::endl;
    }
}

void MatrixCalculator::__perform_op()
{
    std::string line, first, op, second;
    std::cin.clear();
    std::cin.ignore(1);
    getline(std::cin, line);
    std::stringstream ss(line);

    std::string save = "";

    if (line.find('=') != std::string::npos)
        std::cout << "NOT YET" << std::endl;

    std::string tmp;

    getline(ss, first, ' ');
    getline(ss, op, ' ');
    getline(ss, second);

    Matrix<Fraction> mtrx;

    if (!lmc::is_operator(op) || 
        this->_saved_matrices.find(first) == this->_saved_matrices.end())
        throw std::logic_error("operation error");

    if (op == "*")
    {
        if (this->_saved_matrices.find(second) != this->_saved_matrices.end())
            mtrx = __extract(first) * __extract(second);
        else
            mtrx = __extract(first) * Fraction(second);
    }
    if (op == "+")
    {
        mtrx = __extract(first) + __extract(second);
    }
    if (op == "-")
    {
        mtrx = __extract(first) - __extract(second);
    }
    if (op == "/")
    {
        mtrx = __extract(first) / Fraction(second);
    }
    if (op == "det")
    {
        mtrx = Matrix<Fraction>(1);
        mtrx(1, 1) = __extract(first).Determinant();
    }
    if (op == "inv")
    {
        mtrx = __extract(first).Inverse();
    }
    if (op == "rk")
    {
        mtrx = Matrix<Fraction>(1);
        mtrx(1, 1) = Fraction(__extract(first).Rank());
    }
    if (op == "tr")
    {
        mtrx = __extract(first).Transpose();
    }
    if (op == "^")
    {
        mtrx = __extract(first) ^ stoi(second);
    }


    this->_res = mtrx;

    std::cout << "\n" << mtrx << std::endl;
}

void MatrixCalculator::__perform_command(lmc::CommandSelect cmd)
{   
    switch(cmd)
    {
        case lmc::CMD_UPDATE:
            this->__update_matrices();
            break;

        case lmc::CMD_PRINT:
            this->__print_matrices();
            break;

        case lmc::CMD_OPS:
            this->__display_operations();
            break;

        case lmc::CMD_PERFORM:
            this->__perform_op();
            break;

        case lmc::CMD_CLOSE:
            this->_saved_matrices.clear();
            exit(0);

        default:
            throw std::logic_error("bad switch");
    }
}

Matrix<Fraction> MatrixCalculator::__extract(const std::string& key)
{
    return Matrix<Fraction>(this->_saved_matrices[key]);
}