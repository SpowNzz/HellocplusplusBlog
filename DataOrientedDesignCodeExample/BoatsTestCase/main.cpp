#include "ood.h"
#include "dod.h"

#define BASIC_BENCHMARK_TEST(x) BENCHMARK(x)  \
->Args({2000})                               \
->Args({4000})                               \
->Args({8000})                               \
->Args({16000})              

BASIC_BENCHMARK_TEST(OOD);
BASIC_BENCHMARK_TEST(DOD);

int main(int argc, char** argv) 
{
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
        ::benchmark::RunSpecifiedBenchmarks();

    system("pause");
}