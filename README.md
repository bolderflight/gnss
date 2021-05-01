# gnss
Defines a common interface for our GNSS receivers.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

# Description
This library defines what a *Gnss* interface should look like, enabling higher level code to abstract out GNSS receiver specifics and design against this interface.

## Installation
CMake is used to build this library, which is exported as a library target called *gnss*. The header is added as:

```
#include "gnss/gnss.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake .. -DMCU=MK66FX1M0
make
```

This will build the library and an example called *example*, which has source code located in *examples/example.cc*. Notice that the *cmake* command includes a define specifying the microcontroller the code is being compiled for. This is required to correctly configure the code, CPU frequency, and compile/linker options. The available MCUs are:
   * MK20DX128
   * MK20DX256
   * MK64FX512
   * MK66FX1M0
   * MKL26Z64
   * IMXRT1062_T40
   * IMXRT1062_T41

These are known to work with the same packages used in Teensy products. Also switching packages is known to work well, as long as it's only a package change.

## Namespace
This library is within the namespace *bfs*.

## Class / Methods

**enum class GnssFix** specifies GNSS fix information for the receiver.

| Enum | Value | Description |
| --- | --- | --- |
| FIX_NONE | 1 | No GNSS fix |
| FIX_2D | 2 | 2D GNSS fix |
| FIX_3D | 3 | 3D GNSS fix |
| FIX_DGNSS | 4 | 3D GNSS fix with differential GNSS corrections applied |
| FIX_RTK_FLOAT | 5 | 3D GNSS fix with RTK float integer ambiguity |
| FIX_RTK_FIXED | 6 | 3D GNSS fix with RTK fixed integer ambiguity |

**struct GnssConfig** defines a structure used to configure the GNSS receiver. The data fields are:

| Name | Description |
| --- | --- |
| HardwareSerial *bus | A pointer to the serial port to the communicate with the receiver |
| int32_t baud | The baud rate for communicating with the receiver. |
| int16_t sampling_period_ms | The sampling period for the receiver, used for health and status monitoring, ms. Typically 100 - 1000 ms (1 - 10 Hz) |

**struct GnssData** defines a structure of data returned from the receiver. The data fields are:

| Name | Description |
| --- | --- |
| bool new_data | Whether new data was received |
| bool healthy | Whether the receiver is healthy |
| GnssFix fix | The GNSS fix type |
| int8_t num_sats | Number of satellites used in the solution |
| int16_t week | GNSS week number |
| float alt_wgs84_m | Altitude above the WGS84 ellipsoid, m |
| float horz_acc_m | Horizontal position accuracy estimate, m |
| float vert_acc_m | Vertical position accuracy estimate, m |
| float vel_acc_mps | Velocity accuracy estimate, m/s |
| Eigen::Vector3f ned_vel_mps | Velocity in a North-East-Down (NED) sense, m/s |
| double lat_rad | Latitude, rad |
| double lon_rad | Longitude, rad |
| double tow_s | GNSS time of week, s |

Health is determined by whether the sensor fails to read 5 times in a row at the expected sampling rate.

**Gnss** Concepts are used to define what an *Gnss* compliant object looks like and provide a means to templating against an *Gnss* interface. The two required methods are:

**bool Init(const GnssConfig &ref)** This method should receive an *GnssConfig* struct and should establish communication with the GNSS receiver. True is returned on successfully establishing communication with the receiver.

**bool Read(GnssData &ast; const ptr)** This method should get new data from the receiver and return it using a pointer to the *GnssData* struct. True is returned if new data is received.
