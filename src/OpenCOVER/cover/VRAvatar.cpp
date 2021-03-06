/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#include <util/byteswap.h>
#include "VRAvatar.h"
#include "VRSceneGraph.h"
#include "coVRCollaboration.h"
#include "coVRPluginSupport.h"
#include "coVRCommunication.h"
#include "coVRFileManager.h"
#include "coBillboard.h"
#include <osg/MatrixTransform>
#include <osg/Texture2D>

using namespace opencover;
using namespace covise;
VRAvatarList *VRAvatarList::instance()
{
    static VRAvatarList *singleton = NULL;
    if (!singleton)
        singleton = new VRAvatarList;
    return singleton;
}

VRAvatar::VRAvatar(const char *name)
{
    thisnum = num++;
    hostname = new char[strlen(name) + 1];
    strcpy(hostname, name);
    handTransform = new osg::MatrixTransform;
    brilleTransform = new osg::MatrixTransform;
    schuheTransform = new osg::MatrixTransform;
    avatarNodes = new osg::Group;
    avatarNodes->addChild(schuheTransform);
    avatarNodes->addChild(brilleTransform);
    avatarNodes->addChild(handTransform);
    char *NodeName = new char[strlen(name) + 100];
    sprintf(NodeName, "Avatar %s", name);
    avatarNodes->setName(NodeName);
    osg::StateSet *ss = avatarNodes->getOrCreateStateSet();
    for (int i = 0; i < cover->getNumClipPlanes(); i++)
    {
        ss->setAttributeAndModes(cover->getClipPlane(i), osg::StateAttribute::OFF);
    }

    delete[] NodeName;
    brilleNode = coVRFileManager::instance()->loadIcon("brille");
    handNode = coVRFileManager::instance()->loadIcon("hand");
    schuheNode = coVRFileManager::instance()->loadIcon("schuhe");
    char *hostIcon = new char[6 + strlen(name) + 4];
    strcpy(hostIcon, "hosts/");
    strcat(hostIcon, name);
    hostIconNode = coVRFileManager::instance()->loadIcon(hostIcon);
    if (hostIconNode == NULL)
    {
        cerr << "Hosticon not found " << hostIcon << endl;
    }
    if (brilleNode)
    {
        brilleTransform->addChild(brilleNode);
    }
    if (handNode)
    {
        handTransform->addChild(handNode);
    }
    if (schuheNode)
    {
        schuheTransform->addChild(schuheNode);
    }
    coBillboard *bb = new coBillboard;
    schuheTransform->addChild(bb);
    if (hostIconNode)
    {
        bb->addChild(hostIconNode);
    }
    if (coVRCollaboration::instance()->showAvatar)
    {
        cover->getObjectsRoot()->addChild(avatarNodes.get());
    }
    VRAvatarList::instance()->add(this);
}

VRAvatar::~VRAvatar()
{
    thisnum = num++;
    delete[] hostname;
    cover->getObjectsRoot()->removeChild(avatarNodes.get());
}

void VRAvatar::show()
{
    if (avatarNodes->getNumParents() == 0)
    {
        cover->getObjectsRoot()->addChild(avatarNodes.get());
    }
}

void VRAvatar::hide()
{
    if (avatarNodes->getNumParents() == 1)
    {
        cover->getObjectsRoot()->removeChild(avatarNodes.get());
    }
}

void VRAvatar::updateData(VRAvatarData &ad)
{

    osg::Matrix handmat;
    osg::Matrix headmat;
    osg::Matrix feetmat;
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            handmat(i, j) = ad.handMat[i][j];
            headmat(i, j) = ad.headMat[i][j];
            feetmat(i, j) = ad.feetMat[i][j];
        }
    handTransform->setMatrix(handmat);
    brilleTransform->setMatrix(headmat);
    schuheTransform->setMatrix(feetmat);
}

VRAvatar *VRAvatarList::get(const char *name)
{
    int i;
    for (i = 0; i < num; i++)
    {
        if (strcmp(name, avatars[i]->hostname) == 0)
            return avatars[i];
    }
    return NULL;
}

void VRAvatarList::show()
{
    int i;
    for (i = 0; i < num; i++)
    {
        avatars[i]->show();
    }
    visible = true;
}

void VRAvatarList::hide()
{
    int i;
    for (i = 0; i < num; i++)
    {
        avatars[i]->hide();
    }
    visible = false;
}

VRAvatarList::VRAvatarList()
{
    num = 0;
    visible = true;
}

bool VRAvatarList::isVisible()
{
    return visible;
}

void VRAvatarList::add(VRAvatar *a)
{
    avatars[num] = a;
    num++;
    if (num > 0)
    {
        coVRCollaboration::instance()->showCollaborative(true);
    }
    //cerr << num << " AddAvatars" << endl;
}

void VRAvatarList::remove(VRAvatar *a)
{
    int i;
    for (i = 0; i < num; i++)
    {
        if (avatars[i] == a)
        {
            i++;
            while (i < num)
            {
                avatars[i - 1] = avatars[i];
                i++;
            }
            num--;
            delete a;
            break;
        }
    }
}

void VRAvatarList::sendMessage()
{
    // all data is in object Coordinates

    int len = strlen(coVRCommunication::instance()->getHostaddress()) + 1;
    len += 8 - (len % 8);
    char *buf = new char[len + sizeof(VRAvatarData)];
    strncpy(buf, coVRCommunication::instance()->getHostaddress(), len);
    //fprintf(stderr, "send %s\n",buf);
    VRAvatarData ad;
    ad.convert();
    memcpy(buf + len, &ad, sizeof(VRAvatarData));
    cover->sendBinMessage("AvatarX", buf, len + sizeof(VRAvatarData));
    delete[] buf;
}

void VRAvatarList::receiveMessage(const char *messageData)
{
    VRAvatar *av = get(messageData);
    if (av == NULL)
    {
        av = new VRAvatar(messageData);
    }
    int len = strlen(messageData) + 1;
    len += 8 - (len % 8);
    //fprintf(stderr, "receive %s\n",messageData);
    VRAvatarData ad(messageData + len);
    ad.convert();
    av->updateData(ad);
}

VRAvatarData::VRAvatarData()
{
    // all data is in object Coordinates
    osg::Matrix invbase = cover->getInvBaseMat();
    osg::Matrix handmat = cover->getPointerMat();
    handmat *= invbase;
    osg::Matrix headmat = cover->getViewerMat();
    osg::Vec3 toFeet;
    toFeet = headmat.getTrans();
    toFeet[2] = VRSceneGraph::instance()->floorHeight();
    osg::Matrix feetmat;
    feetmat.makeTranslate(toFeet[0], toFeet[1], toFeet[2]);
    headmat *= invbase;
    feetmat *= invbase;
    //handmat.print(0,1,"handPrepare",stderr);
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            handMat[i][j] = handmat(i, j);
            headMat[i][j] = headmat(i, j);
            feetMat[i][j] = feetmat(i, j);
        }
    //fprintf(stderr,"sendworld%f %f %f\n",toFeet[0],toFeet[1],toFeet[2]);
    //fprintf(stderr,"toFeetObj%f %f %f\n",toFeetObj[0],toFeetObj[1],toFeetObj[2]);
}

VRAvatarData::VRAvatarData(const char *buf)
{
    memcpy(this, buf, sizeof(VRAvatarData));
}

void VRAvatarData::convert()
{
#ifdef BYTESWAP
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            byteSwap(handMat[i][j]);
            byteSwap(headMat[i][j]);
            byteSwap(feetMat[i][j]);
        }
    }
#endif
}

int VRAvatar::num = 0;
float VRAvatar::rc[10] = { 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.5, 0.2, 0.1, 0.2 };
float VRAvatar::gc[10] = { 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.5, 0.4, 0.4, 0.0 };
float VRAvatar::bc[10] = { 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.1, 0.6, 0.7, 0.7 };
