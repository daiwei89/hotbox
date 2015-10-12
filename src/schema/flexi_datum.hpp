#pragma once

#include <vector>
#include <cstdint>
#include "schema/constants.hpp"
#include "schema/proto/schema.pb.h"
#include <utility>
#include <cmath>

namespace mldb {

// Store datum in either dense or sparse representation.
class FlexiDatum {
public:
  FlexiDatum();

  // Initialize sparse store.
  FlexiDatum(std::vector<BigInt>&& feature_ids,
      std::vector<float>&& vals, BigInt feature_dim,
      float label = std::nanf(""), float weight = 1.);

  // Initialize dense store.
  FlexiDatum(std::vector<float>&& vals,
      float label = std::nanf(""), float weight = 1.);

  // Move semantics
  FlexiDatum(FlexiDatum&& other) noexcept;  // move c'tor
  FlexiDatum& operator=(FlexiDatum&& other);  // move assignment
  FlexiDatum& operator=(const FlexiDatum&& other);  // copy assignment

  // Move accessors can only be called once.
  const std::vector<float>& GetDenseStore() const;
  const std::vector<BigInt>& GetSparseIdx() const;
  const std::vector<float>& GetSparseVals() const;

  // Move accessors can only be called once.
  std::vector<float>&& MoveDenseStore();
  std::vector<BigInt>&& MoveSparseIdx();
  std::vector<float>&& MoveSparseVals();

  std::string ToString() const;

private:
  // Dense or Sparse. store_type_ can only be set in constructor.
  OutputStoreType store_type_;

  BigInt feature_dim_;
  float label_;
  float weight_;

  std::vector<BigInt> sparse_idx_;
  std::vector<float> sparse_vals_;
  std::vector<float> dense_vals_;
};

}  // namespace mldb