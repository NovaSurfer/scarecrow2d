#define PICOBENCH_DEBUG
#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench/picobench.hpp"

#include <vector>
#include <cstdlib>
#include "../src/collections/vec.h"

void rand_vector(picobench::state& s)
{
    std::vector<int> v;
    for (auto _ : s)
    {
        int sdf = rand();
        v.push_back(sdf);
    }
}
PICOBENCH(rand_vector);

void sc2d_rand_vector(picobench::state& s)
{
  sc2d::vec<int> v;
  for (auto _ : s)
  {
    int sdf = rand();
    v.push_back(sdf);
  }
}
PICOBENCH(sc2d_rand_vector);



//void rand_vector_reserve(picobench::state& s)
//{
//    std::vector<int> v;
//    v.reserve(s.iterations());
//    for (auto _ : s)
//    {
//        v.push_back(rand());
//    }
//}
//PICOBENCH(rand_vector_reserve).iterations({10});
//
//void sc2d_rand_vector_reserve(picobench::state& s)
//{
//    sc2d::vec<int> v;
//    v.reserve(s.iterations());
//    for (auto _ : s)
//    {
//        v.push_back(rand());
//    }
//}
//PICOBENCH(sc2d_rand_vector_reserve).iterations({10});

//
//void rand_deque(picobench::state& s)
//{
//    std::deque<int> v;
//    for (auto _ : s)
//    {
//        v.push_back(rand());
//    }
//}
//PICOBENCH(rand_deque);
