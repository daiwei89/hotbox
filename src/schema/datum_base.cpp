#include <sstream>
#include <string>
#include <cstdint>
#include <glog/logging.h>
#include "schema/constants.hpp"
#include "schema/datum_base.hpp"
#include "schema/schema_util.hpp"

namespace hotbox {

DatumBase::DatumBase(DatumProto* proto,
    StatCollector* stat_collector) : proto_(proto),
  stat_collector_(stat_collector) {
    CheckInOrder();
  }

DatumBase::DatumBase(const DatumBase& other) :
  proto_(new DatumProto(*other.proto_)),
  stat_collector_(other.stat_collector_) { }

DatumProto* DatumBase::Release() {
  return proto_.release();
}

float DatumBase::GetLabel(const FeatureFamily& internal_family) const {
  return GetFeatureVal(internal_family.GetFeature(kLabelFamilyIdx));
}

float DatumBase::GetWeight(const FeatureFamily& internal_family) const {
  float weight = GetFeatureVal(internal_family.GetFeature(kWeightFamilyIdx));
  return weight == 0 ? 1 : weight;
}

/*
float DatumBase::GetFeatureVal(const Schema& schema,
    const std::string& feature_desc) const {
  auto finders = ParseFeatureDesc(feature_desc);
  CHECK_EQ(1, finders.size());
  const auto& finder = finders[0];
  const auto& family = schema.GetFamily(finder.family_name);
  CHECK(!finder.all_family);
  FeatureLocator loc;
  if (!finder.feature_name.empty()) {
    loc = family.GetFeature(finder.feature_name).loc();
  } else {
    loc = family.GetFeature(finder.family_idx).loc();
  }
  return GetFeatureVal(loc);
}
*/

//Nov 2 get feature value for string
//
float DatumBase::GetFeatureVal(const Feature& f) const {
  CHECK_NOTNULL(proto_.get());
  CHECK(IsNumber(f));
  BigInt store_offset = f.store_offset();
  switch (f.store_type()) {
    case FeatureStoreType::DENSE_CAT:
      return static_cast<float>(proto_->dense_cat_store(store_offset));
    case FeatureStoreType::DENSE_NUM:
      return proto_->dense_num_store(store_offset);
    case FeatureStoreType::SPARSE_CAT:
      {
        /*
        const auto& it = proto_->sparse_cat_store().find(store_offset);
        if (it != proto_->sparse_cat_store().cend()) {
          return static_cast<float>(it->second);
        }
        return 0.;
        */
        // Binary search to find store_offset in idx.
        const auto& idxs = proto_->sparse_cat_store_idxs();
        const auto low = std::lower_bound(idxs.cbegin(),
            idxs.cend(), store_offset);
        auto found = low - idxs.cbegin();
        if (low == idxs.cend() ||
            proto_->sparse_cat_store_idxs(found) != store_offset) {
          // Not found.
          return 0;
        }
        return proto_->sparse_cat_store_vals(found);
      }
    case FeatureStoreType::SPARSE_NUM:
      {
        const auto& idxs = proto_->sparse_num_store_idxs();
        const auto low = std::lower_bound(idxs.cbegin(),
            idxs.cend(), store_offset);
        auto found = low - idxs.cbegin();
        if (low == idxs.cend() ||
            proto_->sparse_num_store_idxs(found) != store_offset) {
          // Not found.
          return 0;
        }
        return proto_->sparse_num_store_vals(found);
      }
    default:
      LOG(FATAL) << "Unrecognized store_type: " << f.store_type();
    }
  }
  return 0.;
}

void DatumBase::SetFeatureVal(const Feature& f, float val) {
  CHECK_NOTNULL(proto_.get());
  CHECK(IsNumber(f));
  BigInt store_offset = f.store_offset();
  if (stat_collector_ != nullptr) {
    stat_collector_->UpdateStat(f, val);
  }
  switch (f.store_type()) {
    case FeatureStoreType::DENSE_CAT:
      SetDenseCatFeatureVal(store_offset, static_cast<int32_t>(val));
      return;
    case FeatureStoreType::DENSE_NUM:
      SetDenseNumFeatureVal(store_offset, val);
      return;
    case FeatureStoreType::SPARSE_CAT:
      SetSparseCatFeatureVal(store_offset, static_cast<int32_t>(val));
      return;
    case FeatureStoreType::SPARSE_NUM:
      SetSparseNumFeatureVal(store_offset, val);
      return;
      default:
      LOG(FATAL) << "Unrecognized store_type: " << f.store_type();
    }
  }
  
//Oct 20  dense and sparse string set value
void DatumBase::SetFeatureValString(const Feature& f,const  char* str, int length){
    BigInt offset = f.store_offset();
    switch (f.store_type()) {
      case FeatureStoreType::DENSE_BYTES:
      SetDenseStrFeatureVal(offset, str, length);
      return;
      case FeatureStoreType::SPARSE_BYTES:
      SetSparseStrFeatureVal(offset, str, length);
      return;
      
      default:
      LOG(FATAL) << "Unrecognized store_type: " << f.store_type();
    }
}
  
//Oct 20 set sparse string val
void DatumBase::SetDenseStrFeatureVal(BigInt offset,const char* str_val,int length){
    CHECK_LT(offset, proto_->dense_bytes_store_size());
    for(int i = 0 ;i < length ; i++){
      proto_->set_dense_bytes_store(offset+i, &(str_val[i]));
    }
}
  
//Oct 20 set sparse string val
void DatumBase::SetSparseStrFeatureVal(BigInt offset,const char* str_val,int length){
    for(int i = 0 ;i < length ; i++){
      (*(proto_->mutable_sparse_bytes_store()))[offset+i] = str_val[i];
    }
  }
  

void DatumBase::SetDenseCatFeatureVal(BigInt store_offset, int val) {
  CHECK_LT(store_offset, proto_->dense_cat_store_size());
  proto_->set_dense_cat_store(store_offset, val);
}

// Directly set in sparse_cat_store()
void DatumBase::SetSparseCatFeatureVal(BigInt store_offset, int val) {
  proto_->add_sparse_cat_store_idxs(store_offset);
  proto_->add_sparse_cat_store_vals(val);
  //(*(proto_->mutable_sparse_cat_store()))[store_offset] = val;
}

// Directly set in dense_num_store()
void DatumBase::SetDenseNumFeatureVal(BigInt store_offset, float val) {
  CHECK_LT(store_offset, proto_->dense_num_store_size());
  proto_->set_dense_num_store(store_offset, val);
}

// Directly set in sparse_num_store()
void DatumBase::SetSparseNumFeatureVal(BigInt store_offset, float val) {
  proto_->add_sparse_num_store_idxs(store_offset);
  proto_->add_sparse_num_store_vals(val);
  //(*(proto_->mutable_sparse_num_store()))[store_offset] = val;
}

std::string DatumBase::ToString() const {
  CHECK_NOTNULL(proto_.get());
  std::stringstream ss;
  ss << "dense_cat:";
  for (int i = 0; i < proto_->dense_cat_store_size(); ++i) {
    ss << " " << i << ":" << proto_->dense_cat_store(i);
  }
  ss << " | sparse_cat:";
  for (int i = 0; i < proto_->sparse_cat_store_idxs_size(); ++i) {
    ss << " " << proto_->sparse_cat_store_idxs(i) << ":" <<
      proto_->sparse_cat_store_vals(i);
  }
  //for (const auto& pair : proto_->sparse_cat_store()) {
  //  ss << " " << pair.first << ":" << pair.second;
  //}
  ss << " | dense_num:";
  for (int i = 0; i < proto_->dense_num_store_size(); ++i) {
    ss << " " << i << ":" << proto_->dense_num_store(i);
  }
  ss << " | sparse_num:";
  //for (const auto& pair : proto_->sparse_num_store()) {
  //  ss << " " << pair.first << ":" << pair.second;
  //}
  for (int i = 0; i < proto_->sparse_num_store_idxs_size(); ++i) {
    ss << " " << proto_->sparse_num_store_idxs(i) << ":" <<
      proto_->sparse_num_store_vals(i);
  }
  ss << " | dense_bytes:";
  for (int i = 0; i < proto_->dense_bytes_store_size(); ++i) {
    ss << " " << i << ":" << proto_->dense_bytes_store(i);
  }
  ss << " | sparse_bytes:";
  //for (const auto& pair : proto_->sparse_bytes_store()) {
  //  ss << " " << pair.first << ":" << pair.second;
  //}
  for (int i = 0; i < proto_->sparse_bytes_store_idxs_size(); ++i) {
    ss << " " << proto_->sparse_bytes_store_idxs(i) << ":" <<
      proto_->sparse_bytes_store_vals(i);
  }
  return ss.str();
}

std::string DatumBase::ToString(const Schema& schema) const {
  CHECK_NOTNULL(proto_.get());
  std::stringstream ss;
  const auto& families = schema.GetFamilies();
  ss << GetLabel(schema.GetFamily(kInternalFamily));
  float weight = GetWeight(schema.GetFamily(kInternalFamily));
  if (weight != 1) {
    ss << " " << weight;
  }
  for (const auto& pair : families) {
    const std::string& family_name = pair.first;
    ss << " |" << family_name;
    const auto& feature_seq = pair.second.GetFeatures();
    for (int i = 0; i < feature_seq.GetNumFeatures(); ++i) {
      const auto& f = feature_seq.GetFeature(i);
      std::string feature_name = (f.name().empty() ?
          std::to_string(i) : f.name());
      ss << " " << feature_name << ":" << GetFeatureVal(f);
    }
    /*
    const std::vector<Feature>& features = pair.second.GetFeatures();
    for (int i = 0; i < features.size(); ++i) {
      //if (!features[i].initialized()) {
      //  continue;
      //}
      std::string feature_name = (features[i].name().empty() ?
          std::to_string(i) : features[i].name());
      ss << " " << feature_name << ":" << GetFeatureVal(features[i]);
    }
    */
  }
}

  
DatumProto* DatumBase::ReleaseProto() {
  return proto_.release();
}
  

std::string DatumBase::Serialize() const {
  std::string serialized;
  proto_->SerializeToString(&serialized);
  return serialized;
}

void DatumBase::CheckInOrder() const {
  CHECK_NOTNULL(proto_.get());
  BigInt prev_idx = -1;
  for (int i = 0; i < proto_->sparse_cat_store_idxs_size(); ++i) {
    BigInt curr_idx = proto_->sparse_cat_store_idxs(i);
    CHECK_GT(curr_idx, prev_idx);
    prev_idx = curr_idx;
  }
  prev_idx = -1;
  for (int i = 0; i < proto_->sparse_num_store_idxs_size(); ++i) {
    BigInt curr_idx = proto_->sparse_num_store_idxs(i);
    CHECK_GT(curr_idx, prev_idx);
    prev_idx = curr_idx;
  }
  prev_idx = -1;
  for (int i = 0; i < proto_->sparse_bytes_store_idxs_size(); ++i) {
    BigInt curr_idx = proto_->sparse_bytes_store_idxs(i);
    CHECK_GT(curr_idx, prev_idx);
    prev_idx = curr_idx;
  }
}

}  // namespace hotbox
