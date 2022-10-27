//
// Created by Philip on 10/17/2022.
//

#ifndef TENSORMATH_CAMERA_HPP
#define TENSORMATH_CAMERA_HPP
#include "../FixedVector.hpp"
#include "../FixedMatrix.hpp"
namespace TensorMath {
//Class for projecting things from a camera
class Camera {
private:
    Vector3 m_position; //camera position
    Vector3 m_direction; //camera direction
    FixedMatrix<4,4> m_projection_matrix; //transformation matrix for project point into screen space
public:
    //https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/orthographic-projection-matrix

    //todo finish
};
}

#endif //TENSORMATH_CAMERA_HPP
