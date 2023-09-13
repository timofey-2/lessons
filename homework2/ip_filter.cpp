#include "ip_filter.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line) && line.length()>0;)
        {

            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }
        sort_pool(ip_pool);
        print_pool(ip_pool);
        auto ip = filter(ip_pool, 1);
        print_pool(ip);
        ip = filter(ip_pool, 46, 70);
        print_pool(ip);
        ip = filter_any(ip_pool, 46);
        print_pool(ip);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
