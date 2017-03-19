#pragma once
#include "correspondence.h"

namespace proslam {

  class CorrespondenceCollection: public BaseContext {
  public: EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  //ds object handling
  public:

    //ds ctor
    CorrespondenceCollection(const LocalMap* local_map_query_,
                             const LocalMap* local_map_reference_,
                             const Count& absolute_number_of_matches_,
                             const real& relative_number_of_matches_,
                             const Correspondence::MatchMap& matches_,
                             const CorrespondencePointerVector& correspondences_);

    //ds deep copy ctor
    CorrespondenceCollection(CorrespondenceCollection* collection_);

    //ds dtor
    ~CorrespondenceCollection();

    //ds deep context merging (old element can be deleted)
    void absorb(const CorrespondenceCollection* collection_);

    //ds deep copy helpers
    static const Correspondence::MatchMap getClone(const Correspondence::MatchMap& matches_per_point_) {
      Correspondence::MatchMap matches_per_point_copy;
      for (const Correspondence::MatchMapElement matches_element: matches_per_point_) {
        Correspondence::MatchPtrVector matches_copy(matches_element.second.size());
        for(Index index_match = 0; index_match < matches_element.second.size(); ++index_match) {
          matches_copy[index_match] = new Correspondence::Match(matches_element.second[index_match]);
        }
        matches_per_point_copy.insert(std::make_pair(matches_element.first, matches_copy));
      }
      return matches_per_point_copy;
    }

    static const CorrespondencePointerVector getClone(const CorrespondencePointerVector& correspondences_) {
      CorrespondencePointerVector correspondences_copy(correspondences_.size());
      for(Index index_correspondence = 0; index_correspondence < correspondences_.size(); ++index_correspondence) {
        correspondences_copy[index_correspondence] = new Correspondence(correspondences_[index_correspondence]);
      }
      return correspondences_copy;
    }

    const LocalMap* local_map_query     = 0;
    const LocalMap* local_map_reference = 0;
    const Identifier id_query          = 0;
    const Identifier id_reference      = 0;
    const Count absolute_number_of_matches   = 0;
    const real relative_number_of_matches = 0.0;
    const Correspondence::MatchMap matches_per_point;
    CorrespondencePointerVector correspondences;
    TransformMatrix3D transform_frame_query_to_frame_reference = TransformMatrix3D::Identity();
    real icp_inlier_ratio       = 0.0;
    Count icp_number_of_iterations = 0;
    Count icp_number_of_inliers    = 0;
    bool is_valid              = false;
  };

  typedef std::vector<CorrespondenceCollection*> CorrespondenceCollectionPointerVector;
  typedef std::map<const Identifier, CorrespondenceCollection*> CorrespondenceMap;
  typedef std::pair<const Identifier, CorrespondenceCollection*> CorrespondenceMapElement;
}
