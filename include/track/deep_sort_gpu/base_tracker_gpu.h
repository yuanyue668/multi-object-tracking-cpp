#ifndef _BASE_TRACKER_GPU_H_
#define _BASE_TRACKER_GPU_H_

#include <iostream>
#include <queue>
#include <opencv2/core/core.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "kalman_tracker_v2.h"
#include "tracker_param.h"
#include "util.h"

class BaseTrackerGPU{

    private:
        cv::Mat m_mean;
        cv::Mat m_covariance;

        int m_id;
        int m_hits;
        int m_age;
        int m_time_since_update;

        int m_label;

        tracker_state m_state;
        
        // Use `queue` is not convience in `get feature()`;
        // std::queue<float*> m_free_d_memory;
        // std::queue<float*> m_feature;
        size_t size;
        std::vector<float*> m_free_d_memory;
        std::vector<float*> m_feature;

    public:
        BaseTrackerGPU(cv::Mat, cv::Mat, int, int, float*);
        int predict(KalmanTrackerV2);
        int update(KalmanTrackerV2, cv::Rect_<float>, float*);
        cv::Rect_<float> to_rect();
        int mark_missed();
        int is_tentative();
        int is_confirmed();
        int is_deleted();

        int get_id();
        int get_hits();
        int get_age();
        int get_label();
        int get_time_since_update();

        cv::Mat get_mean();
        cv::Mat get_covariance();
        std::vector<float*> get_features();

        void clear_features();
        void release_memory();
};

#endif