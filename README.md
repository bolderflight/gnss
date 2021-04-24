# gnss
Defines a common interface for our Global Navigation Satellite System (GNSS) receivers.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

# Description
This library abstracts away GNSS hardware specifics by defining common configuration and data sturctures and an interface class defining common methods for GNSS receivers. This enables the designer of higher-level software to reference this class, rather than individual sensor drivers, and have a fixed interface to design against.

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

This will build the library. Notice that the *cmake* command includes a define specifying the microcontroller the code is being compiled for. This is required to correctly configure the code, CPU frequency, and compile/linker options. The available MCUs are:
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

**struct GnssConfig** defines a structure used to configure the sensor. The data fields are:

| Name | Description |
| --- | --- |
| int32_t baud | The GNSS receiver baudrate |
| int32_t period_ms | The GNSS sampling period, ms |

The sampling period is how often the GNSS receiver should provide new data - typically between 1000 (1 Hz) and 100 (10 Hz).

**struct GnssData** defines a structure of data returned from the sensor. The data fields are:

| Name | Description |
| --- | --- |
| bool new_data | Whether new data was received |
| bool healthy | Whether the GNSS receiver is healthy |
| GnssFix fix | The GNSS fix status |
| int8_t num_sats | The number of satellites used in the solution |
| int16_t week | The GNSS week number |
| float alt_wgs84_m | Altitude above the WGS84 ellipsoid, m |
| float alt_msl_m | Altitude above Mean Sea Level (MSL) |
| float horz_acc_m | Horizontal position accuracy, m |
| float vert_acc_m | Vertical position accuracy, m |
| float vel_acc_mps | Velocity accuracy, m/s |
| float hdop | Horizontal Dilution of Precision |
| float vdop | Vertical Dilution of Precision |
| Eigen::Vector3f ned_vel_mps | North, east down (NED) velocity, m/s |
| double lat_rad | Latitude, rad |
| double lon_rad | Longitude, rad |
| double tow_s | GNSS time of week, s |

GnssFix is defined by:

| Enum | Value | Description |
| --- | --- | --- |
| FIX_NONE | 1 | No GNSS fix |
| FIX_2D | 2 | 2D fix |
| FIX_3D | 3 | 3D fix |
| FIX_DGNSS | 4 | DGPS/SBAS/CORS aided 3D position |
| FIX_RTK_FLOAT | 5 | RTK fix with floating integer ambiguities |
| FIX_RTK_FIXED | 6 | RTK fix with fixed integer ambiguities |

**Gnss** The *Gnss* class defines a common interface to IMU sensors. It is templated with the object implementing this interface for the desired sensor. For example, the uBlox implementation may be:

```C++
bfs::Gnss<bfs::Ublox> gnss(&Serial1);
```

Similar to how a pure virtual class can be used to define an interface using dynamic polymorphism, this approach uses static polymorphism.

**Gnss(HardwareSerial &ast;bus)** creates a Gnss object; a pointer to the Serial bus object is passed.

**bool Init(const GnssConfig &ref)** initializes communication with the sensor and configures it. Returns true if communication is established and configuration was successful.

**bool Read(GnssData &ast; const ptr)** reads data from the sensor. Returns true if new data was received.
