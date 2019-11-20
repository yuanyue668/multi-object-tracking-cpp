#ifndef _BASE_TRACKER_H_
#define _BASE_TRACKER_H_

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "kalman_tracker_v2.h"

enum tracker_state {
    /*
    Enumeration type for the single target state.
    Newly created tracks are classified as `tentative` until enough evidence
    has been collected. Then, the track state is changed to `confirmed`. Trackers
    that are no longer alive are classified as `deleted` to mark them for removal
    from the set of active trackers.
    */
   Tentative = 1,
   Confirmed = 2,
   Deleted = 3
};

const int n_init = 3;
const int max_age = 30;
const double max_iou_distance = 0.3;

class BaseTracker{

    private:
        cv::Mat m_mean;
        cv::Mat m_covariance;

        int m_id;
        int m_hits;
        int m_age;
        int m_time_since_update;

        int m_label;

        tracker_state m_state;
        std::vector<std::vector<float>> m_feature;

    public:
        BaseTracker(cv::Mat, cv::Mat, int, int, std::vector<float>);
        int predict(KalmanTrackerV2);
        int update(KalmanTrackerV2, cv::Rect_<float>, std::vector<float>);
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
        std::vector<std::vector<float>> get_features();

        void clear_features();
};

#endif