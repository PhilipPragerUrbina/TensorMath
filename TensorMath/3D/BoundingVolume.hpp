//
// Created by Philip on 10/17/2022.
//

#ifndef TENSORMATH_BOUNDINGVOLUME_HPP
#define TENSORMATH_BOUNDINGVOLUME_HPP
#include "../FixedVector.hpp"
namespace TensorMath {
//class for representing 3d bounding volumes for collisions
    class BoundingVolume {
    public:
        //minimum and maximum values
        Vector3 min;
        Vector3 max;

        //create a bounding box from two points(do not have to be min or max)
        BoundingVolume(Vector3 a, Vector3 b){
            min = a.min(b); //get the maximum and minimum value from both points
            max = a.max(b);
        }

        //create a bounding box from the maxes and minimums of a list of points
        BoundingVolume(std::vector<Vector3> points){
            if(points.empty()){ return;} //no data
            //initialize max and min with first point(zero initialization would cause problems, if the min is greater than 0)
            min = points[0];
            max = points[0];
            for (Vector3 point : points) {
                min = min.min(point); //get the maximum and minimum values of all points
                max = max.max(point);
            }
        }

        //check if two volumes intersect:https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
        bool intersects(const BoundingVolume& other) const{
            return 
            min.x() <= other.max.x() &&
            max.x() >= other.min.x() &&
            min.x() <= other.max.x() &&
            max.x() >= other.min.x() &&
            min.x() <= other.max.x() &&
            max.x() >= other.min.x();
        }

        //Ray intersection with axis aligned bounding box: https://tavianator.com/2015/ray_box_nan.html
        bool intersectsRay(Vector3 origin, Vector3 inverse_direction) { //compute inverse direction beforehand
            double t1 = (min[0] - origin[0])*inverse_direction[0];
            double t2 = (max[0] - origin[0])*inverse_direction[0];
            double t_min = std::min(t1, t2);
            double t_max = std::max(t1, t2);
            for (int i = 1; i < 3; ++i) {
                t1 = (min[i] - origin[i])*inverse_direction[i];
                t2 = (max[i] - origin[i])*inverse_direction[i];
                t_min = std::max(t_min, std::min(std::min(t1, t2), t_max));
                t_max = std::min(t_max, std::max(std::max(t1, t2), t_min));
            }
            return t_max > std::max(t_min, 0.0); //if t max is less than 0, the whole box is behind the ray
        } //some other implementations: https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms




    };

}
#endif //TENSORMATH_BOUNDINGVOLUME_HPP
