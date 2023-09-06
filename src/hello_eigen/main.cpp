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
    {
        // eigen base data structure: Matrix<dataType, row, col>
        Eigen::Matrix<float,2,3> m_23f;
        // And also provide other data structure, but all is based on Matrix
        // Vector3d means Matrix<double, 3, 1>
        Eigen::Vector3d v_3d;
        // Matrix<double, 3, 3>
        Eigen::Matrix3d m_33d = Eigen::Matrix<double, 3, 3>::Zero();
        cout << m_33d << endl;
    }

    return 0;
}