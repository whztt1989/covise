/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl-2.1.txt.

* License: LGPL 2+ */

#ifndef OSC_WEATHER_H
#define OSC_WEATHER_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscVariables.h"
#include "oscLight.h"
#include "oscFog.h"
#include "oscPrecipitation.h"


namespace OpenScenario {

class OPENSCENARIOEXPORT cloudStateType: public oscEnumType
{
public:
    static cloudStateType *instance(); 
private:
    cloudStateType();
    static cloudStateType *inst;
};

/// \class This class represents a generic OpenScenario Object
class OPENSCENARIOEXPORT oscWeather: public oscObjectBase
{
public:
    oscWeather()
    {
        OSC_OBJECT_ADD_MEMBER(sun, "oscLight");
        OSC_OBJECT_ADD_MEMBER(fog, "oscFog");
        OSC_OBJECT_ADD_MEMBER(precipitation, "oscPrecipitation");
        OSC_ADD_MEMBER(cloudState);

        cloudState.enumType = cloudStateType::instance();
    };

    oscLightMember sun;
    oscFogMember fog;
    oscPrecipitationMember precipitation;
    oscEnum cloudState;

    enum cloudState
    {
        sky_off,
        free,
        cloudy,
        overcast,
        rainy,
    };
};

typedef oscObjectVariable<oscWeather *> oscWeatherMember;

}

#endif //OSC_WEATHER_H
