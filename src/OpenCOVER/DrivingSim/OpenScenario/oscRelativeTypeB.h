/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl-2.1.txt.

* License: LGPL 2+ */

#ifndef OSC_RELATIVE_TYPE_B_H
#define OSC_RELATIVE_TYPE_B_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscVariables.h"


namespace OpenScenario {

/// \class This class represents a generic OpenScenario Object
class OPENSCENARIOEXPORT oscRelativeTypeB: public oscObjectBase
{
public:
    oscRelativeTypeB()
    {
        OSC_ADD_MEMBER(refObject);
        OSC_ADD_MEMBER(delta);
    };

    oscString refObject;
    oscDouble delta;
};

typedef oscObjectVariable<oscRelativeTypeB *> oscRelativeTypeBMember;

}

#endif //OSC_RELATIVE_TYPE_B_H
