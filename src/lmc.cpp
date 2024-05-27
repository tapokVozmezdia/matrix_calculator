#include "lmc.hpp"

#include <iostream>
#include <string>

bool lmc::is_int(const std::string& i_value)
{
    std::string value = i_value;

    if (value[0] == '-')
        value = value.substr(1);

    for (auto c : value)
    {
        if (c < '0' || c > '9')
            return false;
    }

    return true;
}

bool lmc::is_double(const std::string& i_value)
{
    std::string value = i_value;

    if (value[0] == '-')
        value = value.substr(1);

    bool met_point = false;

    for (auto c : value)
    {
        if (c == '.')
        {
            if (met_point)
                return false;
            met_point = true;
            continue;
        }
        if (c < '0' || c > '9')
            return false;
    }

    return true;
}

std::string lmc::cmd_to_str(CommandSelect cmd)
{
    switch (cmd)
    {
        case CMD_BAD_COMMAND:
            return "bad command";
        
        case CMD_UPDATE:
            return "update matrix list";

        case CMD_PRINT:
            return "print matrix list from file";

        case CMD_OPS:
            return "print available matrix operations";

        case CMD_PERFORM:
            return "perform operation";
        
        case CMD_CLOSE:
            return "close program";

        default:
            return "unknown command";
    }
}

std::string lmc::operation_cheatsheet(OperationSelect op)
{
    switch (op)
    {
        case OP_ADD:
            return "A + B";

        case OP_SUB:
            return "A - B";

        case OP_MUL_EL:
            return "A * val";

        case OP_MUL_MA:
            return "A * B";

        case OP_DIV:
            return "A / val";

        case OP_DET:
            return "A det";

        case OP_INV:
            return "A inv";

        case OP_RAN:
            return "A rk";

        case OP_TRA:
            return "A tr";

        case OP_POW:
            return "A ^ n";

        default:
            return "unknown operation";
    }
}

double lmc::str_to_d(const std::string& c_val)
{

    bool met = false;
    float x = 1;

    std::string val = c_val;

    if (c_val[0] == '-')
    {   
        x = -1;
        val = c_val.substr(1);
    }

    float d = 0;
    float mul = 0.1;

    for (auto it : val)
    {
        if (it == '.')
        {
            met = true;
            continue;
        }
        int i = it - '0';
        if (!met)
        {
            d *= 10;
            d += i;
            continue;
        }
        d += ((float)i * mul);
        mul *= 0.1;
    }
    return (double)(d * x);
}

bool lmc::is_operator(const std::string& op)
{
    return (
        op == "+" ||
        op == "-" ||
        op == "*" ||
        op == "/" ||
        op == "det" ||
        op == "inv" ||
        op == "rk" ||
        op == "tr" ||
        op == "^"
    );
}