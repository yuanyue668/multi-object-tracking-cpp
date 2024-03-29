/***************************************************************************
Copyright(C)：AVS
  *FileName:  // multiple-object-tracking-cpp/include
  *Author:  // Li Haoying
  *Version:  // 2
  *Date:  //2019-10-16
  *Description:  //*Operations of detected result and beginning to track
                   *inference:inference of detect result and beginning of tracking
                   *Pre-selects the detect result, excluding the overlaps
                   *gating:Updates the tracking tree family by gating
                   *sovle_mwis:choses an MWIS method
                   *pruning:pruns the unselected routes combining the ICH theory
                   *sentResult:confirms tracking results
                   *backTraversal:post traverse a tree
                   *TreeToGraph:transfers tree to graph
                   *computeDistance:computes the cost_matrix of Hunguarian Algorithm
                   *get functions: return the tree list
****************************************************************************/
#ifndef _MHT_TRACKER_H_
#define _MHT_TRACKER_H_

#include <iostream>
#include <math.h>
#include <opencv2/core/core.hpp>
#include "mht_tree.h"
#include "mht_graph.h"
#include "util.h"
#include "byavs.h"
#include "kalman_tracker.h"
#include "hungarian.h"
class MHT_tracker {
 private:
  std::vector<Tree> tree_list;
  //time window
  int N = 10;
  int miss_time_thrd = N+10;
  // DEPRECATED, no longer used to calculate missing
  //int hit_time_thrd =  N-(N/2); 

 public: 
  bool init(const std::string& model_dir, 
            const byavs::TrackeParas& pas, 
            const int gpu_id);

  int inference(std::vector<cv::Rect_<float>>, std::vector<float>, 
                byavs::TrackeObjectCPUs&);

  std::vector<cv::Rect_<float>> NMS(std::vector<cv::Rect_<float>>, 
                                    std::vector<float>);
  int gating(std::vector<cv::Rect_<float>>);
  int backTraversal(treeNode, std::shared_ptr<treeNode>, std::vector<int>&, 
                    std::vector<float>&, std::vector<std::vector<int>>&, 
                    std::vector<std::vector<float>>&, int);
  int TreeToGraph(Graph&);
  int sovle_mwis(Graph, std::map<int, std::vector<int>>&);
  int pruning(std::map<int, std::vector<int>>);

  int sentResult(byavs::TrackeObjectCPUs&);
  std::vector<std::vector<double>> computeDistance(std::vector<cv::Rect_<float>> , 
                                                std::vector<cv::Rect_<float>>);

  //get function
  std::vector<Tree> get_tree_list();
};

#endif
