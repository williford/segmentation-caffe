#ifndef CAFFE_ELTWISE_ACCURACY_LAYERS_HPP_
#define CAFFE_ELTWISE_ACCURACY_LAYERS_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"
//#include "caffe/common.hpp"

namespace caffe {

/**
 * @brief Computes the segmentation accuracy for a pixel-wise one-of-many
 *        classification task.
 */
template <typename Dtype>
class EltwiseAccuracyLayer : public Layer<Dtype> {
 public:
  /**
   * @param param provides EltwiseAccuracyParameter eltwise_accuracy_param,
   *     with EltwiseAccuracyLayer options:
   *   - top_k (\b optional, default 1).
   *     Sets the maximum rank @f$ k @f$ at which a prediction is considered
   *     correct.  For example, if @f$ k = 5 @f$, a prediction is counted
   *     correct if the correct label is among the top 5 predicted labels.
   */
  explicit EltwiseAccuracyLayer(const LayerParameter& param)
      : Layer<Dtype>(param) {}
  virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual inline const char* type() const { return "EltwiseAccuracy"; }

  virtual inline int ExactNumBottomBlobs() const { return 2; }
  virtual inline int ExactNumTopBlobs() const { return 1; }

 protected:
  /**
   * TODO: add comment for eltwise accuracy layer 
   */
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);


  /// @brief Not implemented -- EltwiseAccuracyLayer cannot be used as a loss.
  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
    for (int i = 0; i < propagate_down.size(); ++i) {
      if (propagate_down[i]) { NOT_IMPLEMENTED; }
    }
  }

  int top_k_;
  /// Whether to ignore instances with a certain label.
  bool has_ignore_label_;
  /// The label indicating that an instance should be ignored.
  int ignore_label_;

  /// Whether to use only instance with given label.
  bool has_use_label_;
  /// The label indicating that the an instance should be used
  int use_label_;

};

}  // namespace caffe

#endif  // CAFFE_ELTWISE_ACCURACY_LAYERS_HPP_
