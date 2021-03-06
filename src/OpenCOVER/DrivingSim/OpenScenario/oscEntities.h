/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl-2.1.txt.

* License: LGPL 2+ */

#ifndef OSC_ENTITIES_H
#define OSC_ENTITIES_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscObjects.h"
#include "oscUserDataList.h"


namespace OpenScenario {

/// \class This class represents a generic OpenScenario Object
class OPENSCENARIOEXPORT oscEntities: public oscObjectBase
{
public:
    oscEntities()
    {
        OSC_OBJECT_ADD_MEMBER(objects, "oscObjects");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(userDataList, "oscUserDataList");
    };

    oscObjectsArrayMember objects;
    oscUserDataListArrayMember userDataList;
};

typedef oscObjectVariable<oscEntities *> oscEntitiesMember;

}

#endif //OSC_ENTITIES_H
