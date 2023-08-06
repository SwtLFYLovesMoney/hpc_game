#include <iostream>
#include <vector>
#include <chrono>
#include <arm_neon.h>

using namespace std;

int main()
{
    {
        float32x4_t a = vdupq_n_f32(3);
        vector<float> vec(4);
        vst1q_f32(vec.data(), a);
        for (size_t i = 0; i < vec.size(); ++i) {
            cout << vec[i] << " ";
        }
        cout << endl;
        cout << "hello neon!" << endl;
    }
    {
        
    }

    return 0;
}