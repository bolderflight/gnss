/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef INCLUDE_GNSS_GNSS_H_
#define INCLUDE_GNSS_GNSS_H_

#include "Eigen/Core"
#include "Eigen/Dense"
#include "core/core.h"

namespace bfs {

enum class GnssFix : int8_t {
  FIX_NONE = 1,
  FIX_2D = 2,
  FIX_3D = 3,
  FIX_DGNSS = 4,
  FIX_RTK_FLOAT = 5,
  FIX_RTK_FIXED = 6
};
struct GnssConfig {
  int32_t baud;
  int32_t period_ms;
};
struct GnssData {
  bool new_data;
  bool healthy;
  bool rel_pos_avail;
  GnssFix fix;
  int8_t num_sats;
  int16_t week;
  float alt_wgs84_m;
  float alt_msl_m;
  float horz_acc_m;
  float vert_acc_m;
  float vel_acc_mps;
  float hdop;
  float vdop;
  Eigen::Vector3f ned_vel_mps;
  Eigen::Vector3f rel_pos_m;
  Eigen::Vector3f rel_acc_m;
  double lat_rad;
  double lon_rad;
  double tow_s;
};
template<class Impl>
class Gnss {
 public:
  Imu(HardwareSerial *bus) : impl_(bus) {}
  bool Init(const GnssConfig &ref) {return impl_.Init(ref);}
  bool Read(GnssData * const ptr) {return impl_.Read(ptr);}

 private:
  Impl impl_;
};

}  // namespace bfs

#endif  // INCLUDE_GNSS_GNSS_H_
