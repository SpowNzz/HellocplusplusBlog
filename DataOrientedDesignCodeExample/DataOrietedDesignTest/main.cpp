#include "ood_no_inheritance_stack_cars.h"
#include "ood_no_inheritance_heap_cars.h"
#include "ood_inheritance_heap_cars.h"
#include "dod_cars_split_in_data_arrays.h"

#define FRAMES_TO_SIMULATE 60
#define BASIC_BENCHMARK_TEST(x) BENCHMARK(x)    \
->Args({256, FRAMES_TO_SIMULATE})               \
->Args({512, FRAMES_TO_SIMULATE})               \
->Args({1024, FRAMES_TO_SIMULATE})              \
->Args({2048, FRAMES_TO_SIMULATE})              

BASIC_BENCHMARK_TEST(OOD_NoInheritanceStackCar);
BASIC_BENCHMARK_TEST(OOD_NoInheritanceHeapCar);
BASIC_BENCHMARK_TEST(OOD_InheritanceHeapCar);
BASIC_BENCHMARK_TEST(DOD_CarSplitInDataArrays);


int main(int argc, char** argv) 
{
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
        ::benchmark::RunSpecifiedBenchmarks();

    system("pause");
}