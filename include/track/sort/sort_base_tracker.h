#ifndef __BASE_TRACKER_H__
#define __BASE_TRACKER_H__
#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace sort{

#define USE_DEEP 1
#define MAX_MISS_TIME 15

#define STATE_NEW 0
#define STATE_TRACKED 1
#define STATE_LOST 2
#define STATE_REMOVE 3

class Tracker{

    private:
        static int id;
        int m_id;
        int m_state;
        int m_time_since_update;
        int m_label;
        bool m_activate;
        cv::Mat m_measurement;
        cv::KalmanFilter m_kalman_filter;
        cv::Rect_<float> m_box;
        std::vector<float> m_feature;

    public:
        Tracker(cv::Rect_<float> init_box, int label);
        Tracker(cv::Rect_<float> init_box, int label, std::vector<float> features);
        
        static int reset_static_id();

        int init_kalman_filter();
        bool is_activate();
        int predict();
        int update(cv::Rect_<float>);
        int update(cv::Rect_<float>, std::vector<float>);

        int get_id();
        int get_state();
        int get_label();
        std::vector<float> get_features();
        cv::Rect_<float> get_box();
        int get_miss_time();
        cv::Rect_<float> get_rect_box(float, float, float, float);

        int reset_kf_update(cv::Rect_<float> det_result, std::vector<float> features);

        int mark_lost();
        int mark_removed();


};

};

#endif