#pragma once
#include "base/prediction_set.h"
#include <string>
#include <vector>

class Clusterizator {
public:
  Clusterizator() {}
  
  virtual void load_company_names(const std::vector<std::string>& company_names) = 0;
  virtual PredictionSet prediction_set() = 0;
  virtual const std::string& name() const = 0;
};
