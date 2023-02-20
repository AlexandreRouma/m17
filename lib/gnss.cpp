#include "gnss.h"
#include <math.h>

namespace M17 {
    void GNSS::encode(const GNSS& gnss, uint8_t* data) {
        data[0] = gnss.dataSource;
        data[1] = gnss.stationType;

        // Split latitude
        uint16_t latitudeSign = (gnss.latitude < 0);
        double latitudeAbs = fabs(gnss.latitude);
        uint8_t latitudeWhole = floor(latitudeAbs);
        uint16_t latitudeDec = round((latitudeAbs - (double)latitudeWhole) * 65535.0);

        // Split logitude
        uint16_t longitudeSign = (gnss.longitude < 0);
        double longitudeAbs = fabs(gnss.longitude);
        uint8_t longitudeWhole = floor(longitudeAbs);
        uint16_t longitudeDec = round((longitudeAbs - (double)longitudeWhole) * 65535.0);

        // Split bearing and speed if valid
        uint8_t altitudeValid = (gnss.altitude != NAN);
        uint8_t bearingAndSpeedValid = (gnss.bearing != NAN && gnss.speed != NAN);
        
        // Encode latitude and longitude
        data[2] = latitudeWhole;
        data[3] = (latitudeDec >> 8) & 0xFF;
        data[4] = latitudeDec & 0xFF;
        data[5] = longitudeWhole;
        data[6] = (longitudeDec >> 8) & 0xFF;
        data[7] = longitudeDec & 0xFF;
        data[8] = (bearingAndSpeedValid << 3) | (altitudeValid << 2) | (longitudeSign << 1) | latitudeSign;

        // TODO
    }

    void GNSS::decode(const uint8_t* data, GNSS& gnss) {
        // TODO
    }
}