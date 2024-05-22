#include <vector>

template <class el_type>
class Matrix
{
    public:
        Matrix();
    private:
        std::vector<el_type> _data;
};