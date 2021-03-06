/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl-2.1.txt.

* License: LGPL 2+ */

#ifndef OSC_SPEED_H
#define OSC_SPEED_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscSpeedDynamics.h"
#include "oscRelativeTypeC.h"
#include "oscAbsoluteTypeB.h"


namespace OpenScenario {

/// \class This class represents a generic OpenScenario Object
class OPENSCENARIOEXPORT oscSpeed: public oscObjectBase
{
public:
    oscSpeed()
    {
        OSC_OBJECT_ADD_MEMBER(dynamics, "oscSpeedDynamics");
        OSC_OBJECT_ADD_MEMBER_CHOICE(relativeSpeed, "oscRelativeTypeC");
        OSC_OBJECT_ADD_MEMBER_CHOICE(absoluteSpeed, "oscAbsoluteTypeB");
    };

    oscSpeedDynamicsMember dynamics;
    oscRelativeTypeCMember relativeSpeed;
    oscAbsoluteTypeBMember absoluteSpeed;
};

typedef oscObjectVariable<oscSpeed *> oscSpeedMember;

}

#endif //OSC_SPEED_H
