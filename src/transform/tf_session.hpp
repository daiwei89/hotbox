#pragma once
#ifdef USE_TF
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/platform/env.h"
#include <cstdint>
#include <string>
#include <vector>

namespace hotbox {

struct TfSessionConfig {
  std::vector<std::string> output_vars;
  std::string graph_path;
  std::string weight_path;
  int input_dim;
};

class TfSession {
public:
  TfSession(const TfSessionConfig& config);

  std::vector<float> Transform(const std::vector<float>& v);

  // Do an evaluation on one datum to get the output dim.
  int GetOutputDim() const;

  ~TfSession();

private:
  // Use shared_ptr to support copy constructor.
  std::shared_ptr<tensorflow::Session> session_;
  int input_dim_{0};
  int output_dim_{0};
  std::vector<std::string> output_vars_;
};

}  // namespace hotbox
#endif
