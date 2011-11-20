#include<iostream>
#include<string>
#include<ctime>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

string dict[] = {"A", "B", "C", "D"};

int rand_int(int lb, int ub){
    return ((int)(rand() * 1.0 / RAND_MAX * (ub - lb + 1))) + lb;
}
string generate(int left, string s){
    if (!left) {
        return s;
    }
    return generate(left - 1, s + dict[rand_int(0, 3)]);
}

int main() {
    srand((unsigned)time(0));
    freopen("data.txt", "w", stdout);
    for (int i = 1; i <= 50; ++i) {
        printf("%s\n", generate(14, "").c_str());
    }
    return 0;
}
