#include "schema/o_schema.hpp"
#include "schema/constants.hpp"
#include <sstream>
#include <glog/logging.h>
#include <algorithm>

namespace mldb {

OSchema::OSchema(const OSchemaProto& proto) : proto_(proto) { }

std::pair<std::string,std::string> OSchema::GetName(BigInt feature_id) const {
  auto high = std::upper_bound(proto_.family_offsets().cbegin(),
      proto_.family_offsets().cend(), feature_id);
  auto idx = high - proto_.family_offsets().cbegin();
  if (high == proto_.family_offsets().cend()) {
    idx = proto_.family_names_size() - 1;
  }
  return std::make_pair(proto_.family_names(idx),
      proto_.feature_names(feature_id));
}

std::string OSchema::ToString() const {
  BigInt num_families = proto_.family_names_size();
  BigInt num_features = proto_.feature_names_size();

  if (num_families == 0) {
    return "(empty OSchema)";
  }

  BigInt family_idx = 0;
  BigInt family_end = family_idx == num_families - 1 ?
    num_features : proto_.family_offsets(family_idx + 1);

  std::stringstream ss;
  ss << "[" << proto_.feature_names_size() << "]";
  ss << " |" << proto_.family_names(family_idx);
  for (BigInt i = 0; i < proto_.feature_names_size(); ++i) {
    if (i == family_end) {
      // Advance family_idx
      ++family_idx;
      family_end = (family_idx == num_families - 1 ?
          num_features : proto_.family_offsets(family_idx + 1));
      ss << " |" << proto_.family_names(family_idx);
    }
    ss << " " << proto_.feature_names(i);
  }
  return ss.str();
}

}  // namespace mldb
