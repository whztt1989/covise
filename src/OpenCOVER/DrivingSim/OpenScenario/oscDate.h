/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl-2.1.txt.

* License: LGPL 2+ */

#ifndef OSC_DATE_H
#define OSC_DATE_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscVariables.h"


namespace OpenScenario {

/// \class This class represents a generic OpenScenario Object
class OPENSCENARIOEXPORT oscDate: public oscObjectBase
{
public:
    oscDate()
    {
        OSC_ADD_MEMBER(day);
        OSC_ADD_MEMBER(month);
        OSC_ADD_MEMBER(year);
    };

    oscUInt day;
    oscUInt month;
    oscUInt year;
};

typedef oscObjectVariable<oscDate *> oscDateMember;

}

#endif //OSC_DATE_H
