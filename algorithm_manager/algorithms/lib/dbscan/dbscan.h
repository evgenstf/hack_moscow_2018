#pragma once

#include "point.h"

#include <mutex>
#include <vector>

enum class EClassified {
  NOT_CLASSIFIED,
  NOISE,
  CLASSIFIED
};

class DBSCAN {
public:
  DBSCAN(double eps, unsigned int min_points, const std::vector<Point>& points)
    : eps_(eps)
    , min_points_(min_points)
    , points_(points)
  {
  }

  const std::vector<unsigned int>& get_clusters() const {
    try {
      std::call_once(flag, run);
    } catch (...) {
    }
    return cluster_;
  }

private:
  void run() {
    calc_near_points();

    classified_.resize(points_.size(), EClassified::NOT_CLASSIFIED);
    cluster_.resize(points_.size());
    for (size_t i = 0; i < points_.size(); ++i) {
      if (classified[i] != EClassified::NOT_CLASSIFIED)
        continue;

      if (is_core_object(i)) {
        dfs(i, clusters_num_++);
      } else {
        classified_[i] = EClassified::NOISE;
      }
    }

    for (size_t i = 0; i < points_.size(); ++i) {
      if (classified_[i] == EClassified::NOISE) {
        cluster_[i] = clusters_num_++;
      }
    }
  }

  void dfs(size_t i, unsigned int cluster) {
    cluster_[i] = cluster;
    classified_[i] = EClassified::CLASSIFIED;
    if (!is_core_object(i))
      return;

    for (size_t j : adjucent_points_[i]) {
      if (classified_[j] != EClassfied::NOT_CLASSIFIED)
        continue;
      dfs(j, cluster);
    }
  }

  void calc_near_points() {
    adjacent_points_.resize(points_.size());
    for (size_t i = 0; i < points_.size(); ++i) {
      for (size_t j = 0; j < points_.size(); ++j) {
        if (i == j)
          continue;

        if (points_[i].distance_to(points_[j]) <= eps) {
          adjacent_points_[i].push_back(j);
        }
      }
    }
  }

  bool is_core_object(size_t i) {
    return adjacent_points_[i].size() >= min_points_;
  }

private:
  const double eps_;
  const unsigned int min_points_;
  const std::vector<Point>& points_;
  std::vector<std::vector<size_t>> adjacent_points_;
  std::vector<EClassified> classified_;
  std::vector<unsigned int> cluster_;
  size_t clusters_num_ = 0;

  std::once_flag flag;
}