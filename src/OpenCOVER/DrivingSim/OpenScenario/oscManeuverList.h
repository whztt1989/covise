/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl-2.1.txt.

* License: LGPL 2+ */
#ifndef OSC_MANEUVER_LIST_H
#define OSC_MANEUVER_LIST_H
#include <oscExport.h>
#include <oscObjectBase.h>
#include <oscObjectVariable.h>
#include <oscVariables.h>

namespace OpenScenario {

class OpenScenarioBase;

/// \class This class represents a generic OpenScenario Object
class OPENSCENARIOEXPORT oscManeuverList: public oscObjectBase
{
public:
    oscManeuverList()
    {
       
    };
    
};

typedef oscObjectVariable<oscManeuverList *>oscManeuverListMember;

}

#endif //OSC_MANEUVER_LIST_H