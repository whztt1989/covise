/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#ifndef _DLab_NODE_PLUGIN_H
#define _DLab_NODE_PLUGIN_H

#include <util/common.h>

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

#include <cover/VRViewer.h>
#include <cover/coVRPluginSupport.h>
#include <cover/coVRMSController.h>
#include <cover/coVRPluginSupport.h>
#include <cover/coVRFileManager.h>
#include <config/CoviseConfig.h>
#include <util/byteswap.h>
#include <net/covise_connect.h>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>


#include <util/coTypes.h>

#include <vrml97/vrml/config.h>
#include <vrml97/vrml/VrmlNodeType.h>
#include <vrml97/vrml/coEventQueue.h>
#include <vrml97/vrml/MathUtils.h>
#include <vrml97/vrml/System.h>
#include <vrml97/vrml/Viewer.h>
#include <vrml97/vrml/VrmlScene.h>
#include <vrml97/vrml/VrmlNamespace.h>
#include <vrml97/vrml/VrmlNode.h>
#include <vrml97/vrml/VrmlSFBool.h>
#include <vrml97/vrml/VrmlMFFloat.h>
#include <vrml97/vrml/VrmlSFInt.h>
#include <vrml97/vrml/VrmlMFInt.h>
#include <vrml97/vrml/VrmlNodeChild.h>
#include <vrml97/vrml/VrmlScene.h>

using namespace vrml;
using namespace opencover;
using namespace covise;

class PLUGINEXPORT VrmlNodeDLab : public VrmlNodeChild
{
public:
    // Define the fields of DLab nodes
    static VrmlNodeType *defineType(VrmlNodeType *t = 0);
    virtual VrmlNodeType *nodeType() const;

    VrmlNodeDLab(VrmlScene *scene = 0);
    VrmlNodeDLab(const VrmlNodeDLab &n);
    virtual ~VrmlNodeDLab();

    virtual VrmlNode *cloneMe() const;

    virtual VrmlNodeDLab *toDLab() const;

    virtual ostream &printFields(ostream &os, int indent);

    virtual void setField(const char *fieldName, const VrmlField &fieldValue);
    const VrmlField *getField(const char *fieldName);

    void eventIn(double timeStamp, const char *eventName,
                 const VrmlField *fieldValue);

    virtual void render(Viewer *);

    bool isEnabled()
    {
        return d_enabled.get();
    }

private:
    // Fields
    VrmlSFBool d_enabled;

    // eventOuts
    VrmlMFFloat d_floats;
    VrmlMFInt d_ints;
};

class DLabPlugin : public coVRPlugin
{
public:
    DLabPlugin();
    ~DLabPlugin();
    bool init();
    SimpleClientConnection *conn;
    Host *serverHost;
    Host *localHost;
    int port;
    double oldTime;
    int numFloats;
    int numInts;
    float *floatValues;
    int *intValues;
    static DLabPlugin *plugin;
    osg::Geode *geode;
    void createGeometry();
    osg::MatrixTransform *targetTransform;

    // this will be called in PreFrame
    void preFrame();
    bool readVal(void *buf, unsigned int numBytes);

private:
};
#endif
