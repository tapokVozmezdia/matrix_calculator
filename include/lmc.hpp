// library for matrix calculation

#pragma once

#include <string>

using uint = unsigned int;
using lluint = unsigned long long int;
using llint = long long int;

namespace lmc
{
    enum CommandSelect
    {
        CMD_BAD_COMMAND = 0,
        CMD_UPDATE,
        CMD_PRINT,
        CMD_OPS,
        CMD_PERFORM,
        CMD_CLOSE
    };

    enum OperationSelect
    {
        OP_ADD = 0,
        OP_SUB,
        OP_MUL_EL,
        OP_MUL_MA,
        OP_DIV,
        OP_DET,
        OP_INV,
        OP_RAN,
        OP_TRA,
        OP_POW
    };

    bool is_int(const std::string& i_value);
    bool is_double(const std::string& i_value);

    std::string cmd_to_str(CommandSelect cmd);
    std::string operation_cheatsheet(OperationSelect op);

    double str_to_d(const std::string& val);

    bool is_operator(const std::string& op);
}