//
// Created by Philip on 10/17/2022.
//

#ifndef TENSORMATH_CAMERA_HPP
#define TENSORMATH_CAMERA_HPP
#include "../FixedVector.hpp"
#include "../FixedMatrix.hpp"
# define M_PI           3.14159265358979323846
namespace TensorMath {
//unified Class for projecting and un-projecting things from a camera
class Camera {
private:
    //world space
    Vector3 m_position; //camera position
    Vector3 m_direction; //camera direction
    double m_aspect_ratio; //relation width and height of camera
    Vector3 m_up; //direction of up for the world
    //camera settings
    double m_field_of_view_radians; //field of view in radians
    //projection things(going from world space to screen space like in rasterization)
    FixedMatrix<4,4> m_projection_matrix; //transformation matrix for project point into screen space

    //ray tracing things(going from screen space to world space like in ray tracing)
    Vector3 m_lower_left_corner; //corner of screen to offset by
    Vector3 m_horizontal; //rotated m_vertical direction of camera
    Vector3 m_vertical; //rotated m_horizontal direction of camera

    //update rasterization projection matrix
    void generateMatrix(){
        //todo rasterization

    }

    //update ray tracing direction variables
    void generatePlane(){
        //calculate height and width of the viewport in the world
        //the height corresponds to the field of view
        double view_height = 2.0* tan(m_field_of_view_radians/2.0);
        //width corresponds to height based on aspect ratio
        double  view_width = m_aspect_ratio * view_height;
        //rotate and scale to get horizontal and vertical vectors
        Vector3 horizontal_direction=  m_up.crossProduct(m_direction).normalized(); //rotate
        m_horizontal =horizontal_direction * view_width; //scale
        m_vertical = m_direction.crossProduct(horizontal_direction) * view_height; //get perpendicular vector
        //get lowest corner
        m_lower_left_corner = m_position - m_horizontal/2.0 - m_vertical/2.0 - m_direction;
    }

    //update the camera state to account for new settings
    void update(){
        generatePlane();
        generateMatrix();
    }

public:
    //create a camera at a position looking in a direction, with a certain size in world units, and a fov in degrees. +Z is up by default
    Camera(Vector3 position, Vector3 direction, double aspect_ratio, double degree_fov, Vector3 up = {0,0,1}){
        //set values
        m_position = position;
        m_direction = direction.normalized();
        m_aspect_ratio = aspect_ratio;
        m_up = up;
        //update
        setFOVDegrees(degree_fov);
        //no need to update, setFOV already has
    }

    //get where rays should originate in this camera
    Vector3 getRayOrigin(){
        return m_position;
    }

    //get the proper ray direction at a given position in screen space
    Vector3  getRayDirection(Vector2 position){
        return  m_lower_left_corner +  m_horizontal * position.x()  +  m_vertical * position.y() - m_position;
    }

    //convert pixel coordinates to screen space from pixel width and height
    Vector2 getScreenPosition(int x, int y, int width, int height){
        return Vector2 { (double)x / (width - 1), (double)y / (height -1 ) };
    }

    //change direction to look at coordinate and update
    void setLookAt(Vector3 look_at){
        m_direction = (m_position-look_at).normalized();
        update();
    }

    //set the camera fov in degrees and update
    void setFOVDegrees(double degrees){
        m_field_of_view_radians = ( degrees * M_PI ) / 180.0 ; //degrees to radians
        update();
    }
    //set the camera fov in radians and update
    void setFOVRadians(double radians){
        m_field_of_view_radians = radians;
        update();
    }


    //https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/orthographic-projection-matrix


};
}

#endif //TENSORMATH_CAMERA_HPP
