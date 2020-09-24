#include "ood.h"
#include "dod.h"

#define BASIC_BENCHMARK_TEST(x) BENCHMARK(x)  \
->Args({20000})                               \
->Args({40000})                               \
->Args({80000})                               \
->Args({160000})              

BASIC_BENCHMARK_TEST(OOD);
//BASIC_BENCHMARK_TEST(DOD);

int main(int argc, char** argv) 
{
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
        ::benchmark::RunSpecifiedBenchmarks();

    system("pause");
}