//
// Created by 罗其平 on 10/30/17.
//

#ifndef FIRST3D_MATRIX_H
#define FIRST3D_MATRIX_H

#include "Vector.h"

template <int M> class Matrix {
public:
    Matrix() {
        loadIdentity(*this);
    };
    friend class Transform;

    friend void loadIdentity(Matrix& matrix) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < M; ++j) {
                matrix.m[i][j] = (i == j ? 1.0f : 0.0f);
            }
        }
    };

    friend Matrix operator*(const Matrix& m1, const Matrix& m2) {
        Matrix<M> m;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < M; ++j) {
                m.m[i][j] = 0.0f;
                for (int k = 0; k < M; ++k) {
                    m.m[i][j] += (m1.m[i][k] * m2.m[k][j]);
                }
            }
        }
        return m;
    };
private:
    float m[M][M];
};

typedef Matrix<4> Matrix4x4;


#endif //FIRST3D_MATRIX_H
