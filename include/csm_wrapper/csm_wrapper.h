//
// Created by waxz on 18-3-25.
//

#ifndef CSM_WRAPPER_CSM_WRAPPER_H
#define CSM_WRAPPER_CSM_WRAPPER_H

#include <string>
#include <vector>
#include <valarray>

#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>


//
#include <csm/csm_all.h>  // csm defines min and max, but Eigen complains

#undef min
#undef max
#define Pi 3.141592653589793
using namespace std;
namespace gm=geometry_msgs;
namespace sm=sensor_msgs;

//
class Csm_Wrapper {
public:
    Csm_Wrapper(ros::NodeHandle nh, ros::NodeHandle nh_private);

    double csm_fit(vector<double> &res);

    int find_match_point(const sm::LaserScan &map_scan, const sm::LaserScan &sensor_scan);

    double get_base_pose(const sm::LaserScan &map_scan, const sm::LaserScan &sensor_scan, gm::Pose &init_pose,
                         const tf::Transform &base_laser_tf, int &corr_valid_cnt);

    void init_params();


private:
    // **** ros
    ros::NodeHandle nh_, nh_private_;

    // input scan_1, scan_2, pose_guess
    // return pose
    double offset_degree_, offset_cnt_;

    LDP map_ldp_, scan_ldp_;
    // after match how many point get correspondens point
    int corr_valid_cnt_;
    // after match corresponse point distance error
    double corr_match_error_;

    // **** input feed to csm
    sm_params input_;
    sm_result output_;



    int sm_debug_write_flag;

    void scan_to_ldp(const sm::LaserScan &scan, LDP &ldp, double offset);


    void set_tf(double x, double y, double yaw, tf::Transform &t);


};



#endif //CSM_WRAPPER_CSM_WRAPPER_H
