# @file
# 
# CMakeLists.txt for covise kernel
#
# @author Blasius Czink

PROJECT(kernel CXX C)

ADD_SUBDIRECTORY(file)

if (NOT XERCESC_FOUND OR COVISE_BUILD_ONLY_FILE)
   return()
endif()

ADD_SUBDIRECTORY(util)
ADD_SUBDIRECTORY(config)
ADD_SUBDIRECTORY(img)
ADD_SUBDIRECTORY(shm)
ADD_SUBDIRECTORY(net)
ADD_SUBDIRECTORY(covise)
ADD_SUBDIRECTORY(do)
ADD_SUBDIRECTORY(appl)
ADD_SUBDIRECTORY(api)
ADD_SUBDIRECTORY(alg)
ADD_SUBDIRECTORY(dmgr)
ADD_SUBDIRECTORY(vrbclient)
ADD_SUBDIRECTORY(reader)
ADD_SUBDIRECTORY(star)
ADD_SUBDIRECTORY(grmsg)
ADD_SUBDIRECTORY(gpu)
ADD_SUBDIRECTORY(wslib)
