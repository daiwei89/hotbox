#pragma once

#include "schema/proto/schema.pb.h"

namespace mldb {

// Identify a feature (or a family) in the schema.
struct FeatureFinder {
  std::string family_name;

  // if true, ignore feature_name and family_idx.
  bool all_family = false;

  // At most one of the following should be set.
  std::string feature_name;
  int family_idx = -1;
};

struct TypedFeatureFinder : public FeatureFinder {
  TypedFeatureFinder(const FeatureFinder& finder, const FeatureType& t);

  FeatureType type;
};

}  // namespace mldb