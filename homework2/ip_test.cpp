#include <gtest/gtest.h>
#include "ip_filter.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

std::vector<std::vector<std::string> > read_pool(const std::string &fname)
{
    std::ifstream is(fname);
    std::vector<std::vector<std::string> >ip_pool;
  
    for (std::string line, dummy1, dummy2; is>>line>>dummy1>>dummy2;)
    {
        ip_pool.push_back(split(line, '.'));
    }
    return ip_pool;
}

TEST(IPTest, SortList) {
   auto ip_pool = read_pool("ip_filter.tsv");
   auto tmp_pool = ip_pool;
   sort_pool(tmp_pool);

   auto cmp = [](const std::vector<std::string>& a, std::vector<std::string>& b) {
       int nCol = 0;
       while (nCol < 4)
       {
           int na = atoi(a[nCol].c_str());
           int nb = atoi(b[nCol].c_str());
           if (na == nb && nCol < 3)
           {   
               nCol++;
               continue;
            }
           if (na > nb)
               return true;
           else
               return false;
       }
       return false;

       };
   std::sort(ip_pool.begin(), ip_pool.end(), cmp);
   for (int i = 0;i< ip_pool.size(); i++)
   {
      ASSERT_EQ(ip_pool[i][0], tmp_pool[i][0]);
      ASSERT_EQ(ip_pool[i][1], tmp_pool[i][1]);
      ASSERT_EQ(ip_pool[i][2], tmp_pool[i][2]);
      ASSERT_EQ(ip_pool[i][3], tmp_pool[i][3]);
   }
}

TEST(IPTest, FilterAny) {
   auto ip_pool = read_pool("ip_filter.tsv");
   auto res = filter_any(ip_pool, 46);
   EXPECT_EQ(res.size(), 34);
}

TEST(IPTest, Filter) {
    auto ip_pool = read_pool("ip_filter.tsv");
    auto res = filter(ip_pool, 46, 70,147, 26);
    ASSERT_EQ(res.size(), 1);
    std::vector<std::string> v = { "46","70","147","26" };
    ASSERT_EQ(res[0], v);
}


