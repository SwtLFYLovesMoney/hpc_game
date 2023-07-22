#include <iostream>
#include <chrono>
#include <arm_neon.h>

using namespace std;

int main()
{
    {
        float32x4_t a = vdupq_n_f32(0);
        cout << "hello neon!" << endl;
    }
    {
        
    }

    return 0;
}