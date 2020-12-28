#include "ood_no_inheritance_cont_memory_cars.h"
#include "ood_no_inheritance_non_cont_memory_cars.h"
#include "ood_inheritance_non_cont_memory_heap_cars.h"
#include "dod_cars_split_in_data_arrays.h"

#define FRAMES_TO_SIMULATE 60
#define BASIC_BENCHMARK_TEST(x) BENCHMARK(x)    \
->Args({256, FRAMES_TO_SIMULATE})               \
->Args({512, FRAMES_TO_SIMULATE})               \
->Args({1024, FRAMES_TO_SIMULATE})              \
->Args({2048, FRAMES_TO_SIMULATE})              

BASIC_BENCHMARK_TEST(OOD_NoInheritanceContMemoryCar);
BASIC_BENCHMARK_TEST(OOD_NoInheritanceNonContMemoryCar);
BASIC_BENCHMARK_TEST(OOD_InheritanceNonContMemoryCar);
BASIC_BENCHMARK_TEST(DOD_CarSplitInDataArrays);


int main(int argc, char** argv) 
{
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
        ::benchmark::RunSpecifiedBenchmarks();

    system("pause");
}