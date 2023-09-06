#include <iostream>
#include <vector>
#include <chrono>
#include <Eigen/Eigen>

using namespace std;

int main()
{
    {
        Eigen::Matrix3d rotateMat;
        rotateMat << 1, 2, 3,
                     4, 5, 6,
                     7, 8, 9;
        cout << rotateMat << endl;
    }

    return 0;
}