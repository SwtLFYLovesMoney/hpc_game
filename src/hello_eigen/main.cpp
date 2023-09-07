#include <chrono>
#include <iostream>
#include <vector>
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
        // use dynamic size matrix
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> m_dy;
        // another dynamic matrix
        Eigen::MatrixXd m_dy1;

        m_23f << 1, 2, 3, 4, 5, 6;
        cout << "m_23f:" << endl << m_23f << endl;
        cout << "m_23f:" << endl;
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                cout << m_23f(i, j) << " ";
            }
            cout << endl;
        }

        v_3d << 3, 2, 1;
        // different type can not multiply, and be careful the row and col
        // Eigen::Matrix<double, 2, 1> result = m_23f * v_3d; wrong
        // Eigen::Matrix<double, 2, 3> result = m_23f.cast<double>() * v_3d; wrong
        Eigen::Matrix<double, 2, 1> result = m_23f.cast<double>() * v_3d;
        cout << result << endl;

        m_33d = Eigen::Matrix3d::Random();
        cout << "m_33d:" << endl << m_33d << endl;
        cout << "m_33d.transpose:" << endl << m_33d.transpose() << endl;
        cout << "m_33d.sum:" << endl << m_33d.sum() << endl;
        cout << "m_33d.trace:" << endl << m_33d.trace() << endl;
        cout << "10 * m_33d:" << endl << 10 * m_33d << endl;
        cout << "m_33d.inverse:" << endl << m_33d.inverse() << endl;
        cout << "m_33d.determinant:" << endl << m_33d.determinant() << endl;

        // eigen value
        // 实对称矩阵能保证对角化成功
        // 对角化：将矩阵M对角化，即确定一个对角矩阵D和一个可逆方阵P，使得 M = PDP^(-1)
        Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> e_solver(m_33d.transpose() * m_33d);
        cout << "eigen values: " << endl << e_solver.eigenvalues() << endl;
        cout << "eigen vectors: " << endl << e_solver.eigenvectors() << endl;
        // convert vec to diagonal mat, as D
        Eigen::Matrix3d em_33d = e_solver.eigenvalues().asDiagonal();
        cout << endl << em_33d << endl;
        cout << endl << m_33d.transpose() * m_33d << endl;
        // P * D * P^(-1)
        cout << endl << e_solver.eigenvectors() * em_33d * e_solver.eigenvectors().inverse() << endl;

        #define MATRIX_SIZE 50
        Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> m_nnd;
        m_nnd = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
        Eigen::Matrix<double, MATRIX_SIZE, 1> v_nd;
        v_nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);
        {
            auto begin = std::chrono::high_resolution_clock::now();
            Eigen::Matrix<double, MATRIX_SIZE, 1> x = m_nnd.inverse() * v_nd;
            auto end = std::chrono::high_resolution_clock::now();
            // milliseconds(ms) microseconds(us) nanoseconds(ns)
            auto t_cost = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
            cout << "cal inverse mat direct: " << static_cast<double>(t_cost) << " ms" << endl;
        }
        {
            auto begin = std::chrono::high_resolution_clock::now();
            // QR分解
            Eigen::Matrix<double, MATRIX_SIZE, 1> x = m_nnd.householderQr().solve(v_nd);
            auto end = std::chrono::high_resolution_clock::now();
            // milliseconds(ms) microseconds(us) nanoseconds(ns)
            auto t_cost = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
            cout << "cal inverse mat QR: " << static_cast<double>(t_cost) << " ms" << endl;
        }
        #undef MATRIX_SIZE
    }

    return 0;
}