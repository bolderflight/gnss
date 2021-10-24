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
cmake ..
make
```

This will build the library and an example called *example*, which has source code located in *examples/example.cc*.

## Namespace
This library is within the namespace *bfs*.

## Class / Methods

**enum GnssFix** specifies GNSS fix information for the receiver.

| Enum | Value (int8_t) | Description |
| --- | --- | --- |
| FIX_NONE | 1 | No GNSS fix |
| FIX_2D | 2 | 2D GNSS fix |
| FIX_3D | 3 | 3D GNSS fix |
| FIX_DGNSS | 4 | 3D GNSS fix with differential GNSS corrections applied |
| FIX_RTK_FLOAT | 5 | 3D GNSS fix with RTK float integer ambiguity |
| FIX_RTK_FIXED | 6 | 3D GNSS fix with RTK fixed integer ambiguity |

**struct GnssData** defines a structure of data returned from the receiver. The data fields are:

| Name | Description |
| --- | --- |
| bool new_data | Whether new data was received |
| bool healthy | Whether the receiver is healthy |
| int8_t fix | The GNSS fix type |
| int8_t num_sats | Number of satellites used in the solution |
| int16_t week | GNSS week number |
| int32_t tow_ms | GNSS time of week, s |
| float alt_wgs84_m | Altitude above the WGS84 ellipsoid, m |
| float alt_msl_m | Altitude above Mean Sea Level, m |
| float hdop | Horizontal dilution of precision |
| float vdop | Vertical dilution of precision |
| float track_rad | Ground track, rad |
| float spd_mps | Ground speed, m/s |
| float horz_acc_m | Horizontal position accuracy estimate, m |
| float vert_acc_m | Vertical position accuracy estimate, m |
| float vel_acc_mps | Velocity accuracy estimate, m/s |
| float track_acc_rad | Ground track accuracy, rad |
| float ned_vel_mps[3] | Velocity in a North-East-Down (NED) sense, m/s |
| double lat_rad | Latitude, rad |
| double lon_rad | Longitude, rad |

Health is determined by whether the sensor fails to read 5 times in a row at the expected sampling rate.

**Gnss** Concepts are used to define what an *Gnss* compliant object looks like and provide a means to templating against an *Gnss* interface. The required methods are:

**bool Config(const GnssConfig &ref)** This method should receive a *GnssConfig* struct and setup the sensor driver configuration. Note that the configuration should be applied in the *Init* method, this simply checks the configuration for validity and sets up the sensor driver object. True is returned if the config is valid, otherwise false if returned.

**GnssData gnss_data()** This method returns the *GnssData* from the last successful *Read*.
