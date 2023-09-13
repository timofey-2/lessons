#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>


std::vector<std::string> split(const std::string& str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::vector<std::vector<std::string>>  filter_any(const std::vector<std::vector<std::string> >& ip_pool, int num)
{
    std::vector<std::vector<std::string> > ip_pool_filtered;
    for (int i = 0; i < ip_pool.size(); i++)
    {
        const auto& ip = ip_pool[i];
        bool ok = true;
        if (atoi(ip[0].c_str()) == num || atoi(ip[1].c_str()) == num ||
            atoi(ip[2].c_str()) == num || atoi(ip[3].c_str()) == num)
        {
            ip_pool_filtered.push_back(ip_pool[i]);
        }
    }
    return ip_pool_filtered;

}

void print_pool(const std::vector<std::vector<std::string> >& ip_pool)
{
    for (std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for (std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";

            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

void sort_pool(std::vector<std::vector<std::string> >& ip_pool)
{
    std::sort(ip_pool.begin(), ip_pool.end(), [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
        std::vector<int> arr_a = { atoi(a[0].c_str()),atoi(a[1].c_str()),atoi(a[2].c_str()),atoi(a[3].c_str()) };
        std::vector<int> arr_b = { atoi(b[0].c_str()),atoi(b[1].c_str()),atoi(b[2].c_str()),atoi(b[3].c_str()) };
        return arr_a > arr_b;
        });
}

template <typename... Args>
std::vector<std::vector<std::string> >  filter(const std::vector<std::vector<std::string> >& ip_pool, Args&&... args)
{

    auto filters = std::make_tuple(args...);
    std::vector<std::vector<std::string> > ip_pool_filtered;

    constexpr int size = std::tuple_size<std::tuple<Args...>>::value;
    int k = 0;
    for (int i = 0; i < ip_pool.size(); i++)
    {
        const auto& ip = ip_pool[i];
        bool ok = true;
        if constexpr (size > 0)
        {
            int num = std::get<0>(filters);
            ok = ok && atoi(ip[0].c_str()) == num;
        }
        if constexpr (size > 1)
        {
            int num = std::get<1>(filters);
            ok = ok && atoi(ip[1].c_str()) == num;
        }
        if constexpr (size > 2)
        {
            int num = std::get<2>(filters);
            ok = ok && atoi(ip[2].c_str()) == num;
        }
        if constexpr (size > 3)
        {
            int num = std::get<3>(filters);
            ok = ok && atoi(ip[3].c_str()) == num;
        }
        if (ok)
        {
            ip_pool_filtered.push_back(ip_pool[i]);
        }
    }
    return ip_pool_filtered;
}
