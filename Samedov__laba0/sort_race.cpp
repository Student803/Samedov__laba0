// sort_race.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <array>
#include <vector>
#include <string>
#include <iostream>
#include "smoothBySamedov.cpp"
using namespace std;




vector<int> GenerateData(int size, int max_value = INT_MAX);
using Participant = std::vector<int>(*)(std::vector<int>);
void Run(string method_name, Participant p, vector<int> data);


#define RUN(x) {                \
    Run(#x, x, data);           \
}

//place your method name here
vector<int> std_sort(vector<int>);
vector<int> Smooth_Sort(vector<int> values) {
    SmoothSorting(values);                    
    return values;                       
}




int main()
{
    const array<int, 4> N = { 10, 1'000, 10'000, 1'000'000 };
    for (int n : N)
    {
        auto data = GenerateData(n);
        RUN(std_sort);
        RUN(Smooth_Sort);
		//run your method here
    }
}
