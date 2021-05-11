# Changelog

## v2.3.0
- Moved from Eigen and Enum to plain old data types to ease integration with Simulink autocode

## v2.2.0
- Added back in MSL altitude.
- Added ground track, ground speed, and ground track accuracy.
- Added HDOP and VDOP.
- Re-ordered config to optimize struct packing.
- Changed time of week to uin32_t ms

## v2.1.0
- Updated README
- Removed MSL altitude for now, this is easy enough to estimate post-flight and not estimated super accurately on the GNSS receiver. For instance, the uBlox receivers use EGM96 with a 10m x 10m grid and maybe some linear fitting to estimate MSL altitude, leading to a few meter mis-match from what's expected.

## v2.0.0
- Updated to use concepts to define the interface

## v1.2.1
- Fixed a README typo

## v1.2.0
- Updated period_ms to sampling_period_ms to make it more clear what the value is defining.

## v1.1.0
- Added relative position data
- Fixed typo in class definition
- Marked constructor as explicit

## v1.0.0
- Initial baseline
