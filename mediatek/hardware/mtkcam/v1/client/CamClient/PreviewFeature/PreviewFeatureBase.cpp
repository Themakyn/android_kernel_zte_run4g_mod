/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */

#define LOG_TAG "MtkCam/CamClient/PREFEATUREBASE"
//

#include "camera/MtkCamera.h"
#include "MAVClient.h"
#include "PanoramaClient.h"
#ifdef MTK_MOTION_TRACK_SUPPORTED
#include "MotionTrackClient.h"
#endif
#include "utility_hal_base.h"
#include "PreviewFeatureBase.h"
#include "mtkcam/exif/IBaseCamExif.h"

using namespace NSCamClient;
using namespace NSPREFEATUREABSE;
//
/******************************************************************************
*
*******************************************************************************/
#define ENABLE_LOG_PER_FRAME        (1)
PREFEATUREABSE* BasObj;
halUTILITYBase* UtilityObj;

//#define MOTIONTRACK_DEBUG

/******************************************************************************
*
*******************************************************************************/
#define MY_LOGV(fmt, arg...)        CAM_LOGV("(%d)[%s] "fmt, ::gettid(), __FUNCTION__, ##arg)
#define MY_LOGD(fmt, arg...)        CAM_LOGD("(%d)[%s] "fmt, ::gettid(), __FUNCTION__, ##arg)
#define MY_LOGI(fmt, arg...)        CAM_LOGI("(%d)[%s] "fmt, ::gettid(), __FUNCTION__, ##arg)
#define MY_LOGW(fmt, arg...)        CAM_LOGW("(%d)[%s] "fmt, ::gettid(), __FUNCTION__, ##arg)
#define MY_LOGE(fmt, arg...)        CAM_LOGE("(%d)[%s] "fmt, ::gettid(), __FUNCTION__, ##arg)
#define MY_LOGA(fmt, arg...)        CAM_LOGA("(%d)[%s] "fmt, ::gettid(), __FUNCTION__, ##arg)
#define MY_LOGF(fmt, arg...)        CAM_LOGF("(%d)[%s] "fmt, ::gettid(), __FUNCTION__, ##arg)
//
#define MY_LOGV_IF(cond, ...)       do { if ( (cond) ) { MY_LOGV(__VA_ARGS__); } }while(0)
#define MY_LOGD_IF(cond, ...)       do { if ( (cond) ) { MY_LOGD(__VA_ARGS__); } }while(0)
#define MY_LOGI_IF(cond, ...)       do { if ( (cond) ) { MY_LOGI(__VA_ARGS__); } }while(0)
#define MY_LOGW_IF(cond, ...)       do { if ( (cond) ) { MY_LOGW(__VA_ARGS__); } }while(0)
#define MY_LOGE_IF(cond, ...)       do { if ( (cond) ) { MY_LOGE(__VA_ARGS__); } }while(0)
#define MY_LOGA_IF(cond, ...)       do { if ( (cond) ) { MY_LOGA(__VA_ARGS__); } }while(0)
#define MY_LOGF_IF(cond, ...)       do { if ( (cond) ) { MY_LOGF(__VA_ARGS__); } }while(0)

/******************************************************************************
 *
 ******************************************************************************/
#include <fcntl.h>
#include <sys/stat.h>
bool
dumpBufToFile(char const*const fname, MUINT8 *const buf, MUINT32 const size)
{
    int nw, cnt = 0;
    uint32_t written = 0;

    CAM_LOGD("(name, buf, size) = (%s, %x, %d)", fname, buf, size);
    CAM_LOGD("opening file [%s]\n", fname);
    int fd = ::open(fname, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if (fd < 0) {
        CAM_LOGE("failed to create file [%s]: %s", fname, ::strerror(errno));
        return false;
    }

    CAM_LOGD("writing %d bytes to file [%s]\n", size, fname);
    while (written < size) {
        nw = ::write(fd,
                     buf + written,
                     size - written);
        if (nw < 0) {
            CAM_LOGE("failed to write to file [%s]: %s", fname, ::strerror(errno));
            break;
        }
        written += nw;
        cnt++;
    }
    CAM_LOGD("done writing %d bytes to file [%s] in %d passes\n", size, fname, cnt);
    ::close(fd);
    return true;
}

/******************************************************************************
 *
 ******************************************************************************/
sp<IPREFEATUREClient>
IPREFEATUREClient::
createInstance(sp<IParamsManager> pParamsMgr)
{
    return new PREFEATUREABSE(pParamsMgr);
}

/******************************************************************************
 *
 ******************************************************************************/
sp<IFeatureClient>
IFeatureClient::
createInstance(PreFeatureObject_e eobject,int ShotNum)
{
    MY_LOGD("IFeatureClient ShotNum %d", ShotNum);

    if (eobject == PRE_MAV_OBJ_NORMAL) {
         return  new MAVClient(ShotNum);
    }
    else if (eobject == PRE_PANO_OBJ_NORMAL) {
        return  new PanoramaClient(ShotNum);
    }
    else if (eobject == PRE_PANO3D_OBJ_NORMAL) {
    	  return 0;
    }
#ifdef MTK_MOTION_TRACK_SUPPORTED
    else if (eobject == PRE_MOTIONTRACK_OBJ_NORMAL) {
        return  new MotionTrackClient(ShotNum);
    }
#endif

    return  0;
}

/******************************************************************************
 *
 ******************************************************************************/
PREFEATUREABSE::
PREFEATUREABSE(sp<IParamsManager> pParamsMgr)
    : isDoMerge(0)
    , mCmdQue()
    , mCmdQueMtx()
    , mCmdQueCond()
    , mi4ThreadId(0)
    //
    , mModuleMtx()
    , mpCamMsgCbInfo(new CamMsgCbInfo)
    , mpParamsMgr(pParamsMgr)
    , mIsMsgEnabled(0)
    //
    , mi4CallbackRefCount(0)
    , mi8CallbackTimeInMs(0)
    , mClientCbCookie(NULL)
    , mfpRequestMemory(NULL)
    //
    , mpImgBufQueue(NULL)
    , mpImgBufPvdrClient(NULL)
    , mIsFeatureStarted(0)
    //
{
    MY_LOGD("+ this(%p)", this);
    BasObj = this;
}


/******************************************************************************
 *
 ******************************************************************************/
PREFEATUREABSE::
~PREFEATUREABSE()
{
    MY_LOGD("-");
}


/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
init()
{
    MY_LOGD("+");
    bool ret = true;
    //
    mpImgBufQueue = new ImgBufQueue(IImgBufProvider::eID_GENERIC, "PrvFeatureBuf@ImgBufQue");
    if  ( mpImgBufQueue == 0 )
    {
        MY_LOGE("Fail to new ImgBufQueue");
        ret = false;
        goto lbExit;
    }
    //
lbExit:
    MY_LOGD("-");
    return  ret;
}


/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
uninit()
{
    MY_LOGD("+");
    //
    //
    if  ( 0 != mi4CallbackRefCount )
    {
        int64_t const i8CurrentTimeInMs = getTimeInMs();
        MY_LOGW(
            "Preview Callback: ref count(%d)!=0, the last callback before %lld ms, timestamp:(the last, current)=(%lld ms, %lld ms)",
            mi4CallbackRefCount, (i8CurrentTimeInMs-mi8CallbackTimeInMs), mi8CallbackTimeInMs, i8CurrentTimeInMs
        );
    }
    //
    //
    if  ( mpImgBufPvdrClient != 0 )
    {
        mpImgBufPvdrClient = NULL;
    }
    //
    //
    sp<IImgBufQueue> pImgBufQueue;
    {
        Mutex::Autolock _l(mModuleMtx);
        pImgBufQueue = mpImgBufQueue;
    }
    //
    if  ( pImgBufQueue != 0 )
    {
        pImgBufQueue->pauseProcessor();
        pImgBufQueue->flushProcessor(); // clear "TODO"
        pImgBufQueue->stopProcessor();
        pImgBufQueue = NULL;
    }
    //
    //
    MY_LOGD("-");
    return  true;
}

/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
setImgBufProviderClient(sp<IImgBufProviderClient>const& rpClient)
{
    bool ret = false;
    //
    MY_LOGD("+ ImgBufProviderClient(%p)", rpClient.get());
    //
    //
    if  ( rpClient == 0 )
    {
        MY_LOGE("NULL ImgBufProviderClient");
        goto lbExit;
    }
    //
    if  ( mpImgBufQueue == 0 )
    {
        MY_LOGE("NULL ImgBufQueue");
        goto lbExit;
    }
    //
    //if  ( ! rpClient->onImgBufProviderCreated(mpImgBufQueue) )
    //{
    //    goto lbExit;
    //}
    mpImgBufPvdrClient = rpClient;
    //
    //
    ret = true;
lbExit:
    MY_LOGD("-");
    return  ret;
}

/******************************************************************************
 * Set the notification and data callbacks
 ******************************************************************************/
void
PREFEATUREABSE::
setCallbacks(sp<CamMsgCbInfo> const& rpCamMsgCbInfo)
{
    Mutex::Autolock _l(mModuleMtx);
    //
    //  value copy
    MY_LOGD("setCallbacks + ");
    *mpCamMsgCbInfo = *rpCamMsgCbInfo;
}


/******************************************************************************
 *
 ******************************************************************************/
void
PREFEATUREABSE::
enableMsgType(int32_t msgType)
{
    ::android_atomic_or(msgType, &mpCamMsgCbInfo->mMsgEnabled);
}


/******************************************************************************
 *
 ******************************************************************************/
void
PREFEATUREABSE::
disableMsgType(int32_t msgType)
{
    ::android_atomic_and(~msgType, &mpCamMsgCbInfo->mMsgEnabled);
 }


/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
isMsgEnabled()
{
    return  CAMERA_MSG_PREVIEW_METADATA == (CAMERA_MSG_PREVIEW_METADATA & ::android_atomic_release_load(&mpCamMsgCbInfo->mMsgEnabled));
}

/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
onStateChanged()
{
    bool ret = true;
    //
    MY_LOGD("isEnabledState(%d) +", isEnabledState());
    //
    if  ( isEnabledState() )
    {
        status_t status = run();
        if  ( OK != status )
        {
            MY_LOGE("Fail to run thread, status[%s(%d)]", ::strerror(-status), -status);
            ret = false;
            goto lbExit;
        }

        postCommand(Command::eID_WAKEUP);
    }
    else
    {
        if  ( mpImgBufQueue != 0 )
        {
            mpImgBufQueue->pauseProcessor();
        }

        MY_LOGD("getThreadId(%d), getStrongCount(%d), this(%p)", getThreadId(), getStrongCount(), this);
        //requestStop();
    }
    //
lbExit:
    return ret;
}

/******************************************************************************
 *
 ******************************************************************************/
status_t
PREFEATUREABSE::
sendCommand(int32_t cmd, int32_t arg1, int32_t arg2)
{
    bool ret = false;

    MY_LOGD("cmd(%d) +", cmd);

    filename = mpParamsMgr->getStr(MtkCameraParameters::KEY_CAPTURE_PATH).string();
    switch  (cmd)
    {
        case CAMERA_CMD_START_MAV:
            ret = startMAV(arg1);
            break;

        case CAMERA_CMD_STOP_MAV:
            ret = stopFeature(arg1);
            break;

        case CAMERA_CMD_START_AUTORAMA:
            MY_LOGD("cmd(0x%x) CAMERA_CMD_START_AUTORAMA", CAMERA_CMD_START_AUTORAMA);
            ret = startPanorama(arg1);
            break;

        case CAMERA_CMD_STOP_AUTORAMA:
            MY_LOGD("cmd(%d) CAMERA_CMD_STOP_AUTORAMA", CAMERA_CMD_STOP_AUTORAMA);
            ret = stopFeature(arg1);
            break;
#ifdef MTK_MOTION_TRACK_SUPPORTED
        case CAMERA_CMD_START_MOTIONTRACK:
            MY_LOGD("cmd(0x%x) CAMERA_CMD_START_MOTIONTRACK", CAMERA_CMD_START_MOTIONTRACK);
            ret = startMotionTrack(arg1);
            break;

        case CAMERA_CMD_STOP_MOTIONTRACK:
            MY_LOGD("cmd(%d) CAMERA_CMD_STOP_MOTIONTRACK", CAMERA_CMD_STOP_MOTIONTRACK);
            ret = stopFeature(1);
            break;
#endif
        default:
            break;
    }

    MY_LOGD("-");

    return ret? OK : INVALID_OPERATION;
}


/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::stopPreview()
{
    bool ret = true;

    // in case AP set stopPreview but no stopFeature
    if ( isEnabledState() )
    {
        ret =  stopFeature(0);
    }

    return ret;
}


/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
startMAV(int32_t ShotNum)
{
    MY_LOGD("startMAV +");
    Mutex::Autolock _l(mModuleMtx);
    mobject = PRE_MAV_OBJ_NORMAL;
    mShotNum = ShotNum;
    if  ( mpImgBufPvdrClient != 0 && ! mpImgBufPvdrClient->onImgBufProviderCreated(mpImgBufQueue) )
    {
        MY_LOGE("startMAV onImgBufProviderCreated failed");
        return false;
    }
    mpParamsMgr->getPreviewSize(&bufWidth, &bufHeight);
    FeatureClient = IFeatureClient::createInstance(PRE_MAV_OBJ_NORMAL,ShotNum);
    MY_LOGD("create done +");
    FeatureClient->init(bufWidth, bufHeight);
    FeatureClient->setImgCallback(handleMAVImgCallBack);
    MY_LOGD("startMAV init done");
    //
    if ( !isEnabledState() )
    {
        MY_LOGD("isEnabledState in");
        ::android_atomic_write(1, &mIsFeatureStarted);
        onStateChanged();
    }
    return true;
}

/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
stopFeature(int32_t Cancel)
{
    Mutex::Autolock _l(mModuleMtx);
    MY_LOGD("+");
    int err;
    isDoMerge = Cancel;
    //
    MY_LOGD("isDoMerge %d Cancel %d",isDoMerge,Cancel);
    if ( isEnabledState() )
    {
        ::android_atomic_write(0, &mIsFeatureStarted);
        onStateChanged();
    }
    if(FeatureClient==NULL)
    {
    	 return true;
    }
    FeatureClient->stopFeature(isDoMerge);

    if(isDoMerge)
    {
        err = FeatureClient->mHalCamFeatureCompress();
        if (err != NO_ERROR)
        {
            MY_LOGE("  mHalCamFeatureCompress fail");
            return false;
        }
    }

    requestExit();
    status_t status = join();
    if  ( OK != status )
    {
        MY_LOGW("Not to wait thread(tid:%d), status[%s(%d)]", getThreadId(), ::strerror(-status), -status);
    }

    err = FeatureClient->uninit();
    FeatureClient = NULL;
    MY_LOGD("uninit done %d",err);

    if  ( mpImgBufPvdrClient != 0 )
    {
        mpImgBufPvdrClient->onImgBufProviderDestroyed(mpImgBufQueue->getProviderId());
    }
    MY_LOGD("join() exit");
    return true;
}

/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
startPanorama(int32_t ShotNum)
{
    MY_LOGD("  startPanorama ShotNum %d",ShotNum);
    Mutex::Autolock _l(mModuleMtx);
    mShotNum = ShotNum;
    mobject = PRE_PANO_OBJ_NORMAL;
    if  ( mpImgBufPvdrClient != 0 && ! mpImgBufPvdrClient->onImgBufProviderCreated(mpImgBufQueue) )
    {
        MY_LOGE("startPanorama onImgBufProviderCreated failed");
        return false;
    }    

    mpParamsMgr->getPreviewSize(&bufWidth, &bufHeight);
    FeatureClient = IFeatureClient::createInstance(PRE_PANO_OBJ_NORMAL, mShotNum);
    FeatureClient->init(bufWidth, bufHeight);
    FeatureClient->setImgCallback(handlePanoImgCallBack);

    //
    if ( !isEnabledState() )
    {
        MY_LOGD("isEnabledState in");
        ::android_atomic_write(1, &mIsFeatureStarted);
        onStateChanged();
    }
    return true;
}

#ifdef MTK_MOTION_TRACK_SUPPORTED
/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
startMotionTrack(int32_t ShotNum)
{
    MY_LOGD("  startMotionTrack ShotNum %d",ShotNum);
    Mutex::Autolock _l(mModuleMtx);
    mShotNum = ShotNum;
    mobject = PRE_MOTIONTRACK_OBJ_NORMAL;
    if  ( mpImgBufPvdrClient != 0 && ! mpImgBufPvdrClient->onImgBufProviderCreated(mpImgBufQueue) )
    {
        MY_LOGE("startMotionTrack onImgBufProviderCreated failed");
      return false;
    }

    mpParamsMgr->getPreviewSize(&bufWidth, &bufHeight);
    FeatureClient = IFeatureClient::createInstance(PRE_MOTIONTRACK_OBJ_NORMAL, mShotNum);
    FeatureClient->init(bufWidth, bufHeight);
    FeatureClient->setImgCallback(handleMotionTrackImgCallBack);

    //
    if ( !isEnabledState() )
    {
        MY_LOGD("isEnabledState in");
        ::android_atomic_write(1, &mIsFeatureStarted);
        onStateChanged();
    }
    return true;
}
#endif

/******************************************************************************
 *
 ******************************************************************************/
 /*
bool
PREFEATUREABSE::
stopPanorama(int Cancel)
{
    int err;
    Mutex::Autolock _l(mModuleMtx);
    MY_LOGD("  stopPanorama isDoMerge %d",Cancel);
    isDoMerge = Cancel;
    //
    if (isEnabledState() )
    {
        ::android_atomic_write(0, &mIsFeatureStarted);
        onStateChanged();
    }
    else
    {
        MY_LOGW("Panorama was not running");
        return false;
    }


    if(isDoMerge)
    {
        err = FeatureClient->mHalCamFeatureCompress();
        if (err != NO_ERROR)
        {
            MY_LOGE("  mHalCamFeatureCompress fail");
            return false;
        }
    }
    requestExit();
    status_t status = join();
    if  ( OK != status )
    {
        MY_LOGW("Not to wait thread(tid:%d), status[%s(%d)]", getThreadId(), ::strerror(-status), -status);
    }

    err = FeatureClient->uninit();
    MY_LOGD("uninit done %d",err);

    if  ( mpImgBufPvdrClient != 0 )
    {
        mpImgBufPvdrClient->onImgBufProviderDestroyed(mpImgBufQueue->getProviderId());
    }
    MY_LOGD("join() exit");

    return true;
}
*/
/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
isEnabledState()
{
    return  0 != ::android_atomic_release_load(&mIsFeatureStarted);
}


/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
performCallback(int32_t mvX, int32_t mvY, int32_t mStitchDir, MBOOL isShot, MBOOL isSound)
{
    bool ret = true;
    //MY_LOGD("performCallback: mvX (%d), mvY(%d), isMsgEnabled(%d) mStitchDir (%d) isShot (%d)", mvX, mvY, isMsgEnabled(),mStitchDir,isShot);
    if(mobject==PRE_MAV_OBJ_NORMAL)
    {
        if(isShot)
        {
            MY_LOGD("performCallback MAV capture");
            mpCamMsgCbInfo->mNotifyCb(MTK_CAMERA_MSG_EXT_NOTIFY, MTK_CAMERA_MSG_EXT_NOTIFY_MAV, 0, mpCamMsgCbInfo->mCbCookie);
        }
    }
    else if(mobject==PRE_PANO_OBJ_NORMAL)
    {
        camera_memory* pmem = mpCamMsgCbInfo->mRequestMemory(-1, 5*sizeof(int32_t), 1, NULL);
        uint32_t*const pCBData = reinterpret_cast<uint32_t*>(pmem->data);

        if (isSound)
        {
            if(isShot)
            {
                // Shutter sound callback:
                //mpCamMsgCbInfo->mNotifyCb(CAMERA_MSG_SHUTTER, 0, 0, mpCamMsgCbInfo->mCbCookie);
                // Capture sound callback:
                pCBData[0] = MTK_CAMERA_MSG_EXT_DATA_AUTORAMA;
                pCBData[1] = 1;
                pCBData[2] = 1;
                pCBData[3] = 50;
                mpCamMsgCbInfo->mDataCb(
                     MTK_CAMERA_MSG_EXT_DATA,
                     pmem,
                     0,
                     NULL,
                     mpCamMsgCbInfo->mCbCookie
                );
            }
            else
            {
                // Capture no sound callback:
                pCBData[0] = MTK_CAMERA_MSG_EXT_DATA_AUTORAMA;
                pCBData[1] = 0;
                pCBData[2] = mvX;
                pCBData[3] = mvY;
                pCBData[4] = mStitchDir;
                mpCamMsgCbInfo->mDataCb(
                     MTK_CAMERA_MSG_EXT_DATA,
                     pmem,
                     0,
                     NULL,
                     mpCamMsgCbInfo->mCbCookie
                );
            }
        }
        else
        {
            MY_LOGD("capture done call back");
            pCBData[0] = MTK_CAMERA_MSG_EXT_DATA_AUTORAMA;
            pCBData[1] = 1;
            pCBData[2] = 0;
            pCBData[3] = 50;
            mpCamMsgCbInfo->mDataCb(
                 MTK_CAMERA_MSG_EXT_DATA,
                 pmem,
                 0,
                 NULL,
                 mpCamMsgCbInfo->mCbCookie
            );
        }

        pmem->release(pmem);
    }
#ifdef MTK_MOTION_TRACK_SUPPORTED
    else if(mobject==PRE_MOTIONTRACK_OBJ_NORMAL)
    {
        if (isSound)
        {
            if (isShot)
            {
                // Shutter sound callback:
                //mpCamMsgCbInfo->mNotifyCb(CAMERA_MSG_SHUTTER, 0, 0, mpCamMsgCbInfo->mCbCookie);
            }

            camera_memory* pmem = mpCamMsgCbInfo->mRequestMemory(-1, 5*sizeof(int32_t), 1, NULL);
            uint32_t*const pCBData = reinterpret_cast<uint32_t*>(pmem->data);

            // Capture no sound callback:
            pCBData[0] = MTK_CAMERA_MSG_EXT_DATA_MOTIONTRACK;
            pCBData[1] = 0;
            pCBData[2] = mvX;
            pCBData[3] = mvY;
            pCBData[4] = 0;
            mpCamMsgCbInfo->mDataCb(
                 MTK_CAMERA_MSG_EXT_DATA,
                 pmem,
                 0,
                 NULL,
                 mpCamMsgCbInfo->mCbCookie
            );
            pmem->release(pmem);
        }
        else
        {
            MUINT32* pSrcData = (MUINT32*) mvX;

            if ((pSrcData[1] == 1) || (pSrcData[1] == 2))
            {
                camera_memory* pmem;
                uint32_t* pCBData;

                if ((pSrcData[1] != 2) || (pSrcData[3] != 0))
                {
                  /* Callback on captured or blended image */
                MUINT8* puExifHeaderBuf = (MUINT8*) mvY;
                MUINT8* puJpegBuf = (MUINT8*) mStitchDir;
                MUINT32 u4ExifHeaderSize = pSrcData[4];
                MUINT32 u4JpegSize = pSrcData[5];
                    pmem = mpCamMsgCbInfo->mRequestMemory(-1, ((sizeof(MUINT32[6]) + u4ExifHeaderSize + u4JpegSize) + 0x3) & ~0x3, 1, NULL);
                    pCBData = reinterpret_cast<uint32_t*>(pmem->data);

                memcpy((void*) pCBData, (void*) pSrcData, 4 * (sizeof(MUINT32)));
                pCBData[4] = u4ExifHeaderSize + u4JpegSize;
                memcpy((void*) &(pCBData[5]) , puExifHeaderBuf, u4ExifHeaderSize);
                memcpy((void*) (((MUINT32) &(pCBData[5])) + u4ExifHeaderSize), (void*) puJpegBuf, u4JpegSize);

#ifdef MOTIONTRACK_DEBUG
                char sourceFiles[80];
                sprintf(sourceFiles, "%s_%02d.jpg", (pCBData[1] == 1)? "/sdcard/frame": "/sdcard/blend", pCBData[2]);
                dumpBufToFile((char *)sourceFiles, (uint8_t*)&(pCBData[5]), u4JpegSize + u4ExifHeaderSize);
#endif
                }
                else
                {
                    /* Callback with no blended image */
                    pmem = mpCamMsgCbInfo->mRequestMemory(-1, sizeof(MUINT32[5]), 1, NULL);
                    pCBData = reinterpret_cast<uint32_t*>(pmem->data);

                    memcpy((void*) pCBData, (void*) pSrcData, 4 * (sizeof(MUINT32)));
                }

                MY_LOGD("[performCallback] + byte(%d,%d,%d,%d,%d)", pCBData[0], pCBData[1], pCBData[2], pCBData[3], pCBData[4]);
                // Capture sound callback:
                mpCamMsgCbInfo->mDataCb(
                     MTK_CAMERA_MSG_EXT_DATA,
                     pmem,
                     0,
                     NULL,
                     mpCamMsgCbInfo->mCbCookie
                );

                pmem->release(pmem);
            }
            else if (pSrcData[1] == 3)
            {
                /* Callback on intermediate data */
                camera_memory* pmem = mpCamMsgCbInfo->mRequestMemory(-1, sizeof(MUINT32[2]) + pSrcData[2], 1, NULL);
                uint32_t*const pCBData = reinterpret_cast<uint32_t*>(pmem->data);

                memcpy((void*) pCBData, (void*) pSrcData, 2 * (sizeof(MUINT32)));
                memcpy((void*) &(pCBData[2]) , (void*) pSrcData[3], pSrcData[2]);

#ifdef MOTIONTRACK_DEBUG
                char sourceFiles[80];
                sprintf(sourceFiles, "/sdcard/intermediatedata");
                dumpBufToFile((char *)sourceFiles, (uint8_t*)&(pCBData[2]), pSrcData[2]);
#endif

                MY_LOGD("[performCallback] + byte(%d,%d)", pCBData[0], pCBData[1]);
                // Capture sound callback:
                mpCamMsgCbInfo->mDataCb(
                     MTK_CAMERA_MSG_EXT_DATA,
                     pmem,
                     0,
                     NULL,
                     mpCamMsgCbInfo->mCbCookie
                );

                pmem->release(pmem);
            }
        }
    }
#endif
    else
    {
        ret = false;
        MY_LOGW_IF(ENABLE_LOG_PER_FRAME, "No Motion CB: mvX (%d), mvY(%d), isMsgEnabled(%d)", mvX, mvY, isMsgEnabled());
    }

    return ret;
}


/******************************************************************************
 *
 ******************************************************************************/
bool
PREFEATUREABSE::
captureDoneCallback(int32_t message, int32_t id, int32_t bufferAddr, int32_t bufferSize)
{
    MY_LOGD("+");
    bool ret = true;

    // for debug
	char value[PROPERTY_VALUE_MAX] = {'\0'};
	property_get("mediatek.previewfeature.dump", value, "0");
	bool dump = atoi(value);
    if(dump) {
        dumpBufToFile("/sdcard/previewfeature.mpo", (MUINT8*)bufferAddr, (MUINT32)bufferSize);
    }


    camera_memory* pmem = mpCamMsgCbInfo->mRequestMemory(-1
                                                        , bufferSize+2*sizeof(int32_t)
                                                        , 1
                                                        , NULL);
    uint32_t*const pCBData = reinterpret_cast<uint32_t*>(pmem->data);
    uint8_t* pImage = reinterpret_cast<uint8_t*>(&pCBData[2]);

    pCBData[0] = message;   //MTK_CAMERA_MSG_EXT_DATA_AUTORAMA
    pCBData[1] = id;        //2
    memcpy(pImage, (void*)bufferAddr, bufferSize);  //pCBData[2]
    mpCamMsgCbInfo->mDataCb(MTK_CAMERA_MSG_EXT_DATA
                            , pmem
                            , 0
                            , NULL
                            , mpCamMsgCbInfo->mCbCookie
                            );

    pmem->release(pmem);
    MY_LOGD("-");
    return ret;
}

/*******************************************************************************
*
********************************************************************************/
MBOOL
PREFEATUREABSE::
createMPO(MPImageInfo * pMPImageInfo, MUINT32 num, char* file, MUINT32 MPOType)
{
    MINT32 err = NO_ERROR;
    MBOOL ok;
    MpoEncoder* mpoEncoder = new MpoEncoder();
    if (mpoEncoder) {
        ok = mpoEncoder->setJpegSources(TYPE_Disparity, pMPImageInfo, num);

        if (!ok) {
            MY_LOGE("  mpoEncoder->setJpegSources fail \n");
            err = 1;
            goto mHalCamMAVMakeMPO_EXIT;
        }

        ok = mpoEncoder->encode(file, MPOType);

        if (!ok) {
            MY_LOGE("  mpoEncoder->encode fail \n");
            err = 1;
            goto mHalCamMAVMakeMPO_EXIT;
        }

        MY_LOGD("[mHalCamMAVMakeMPO] Done, %s \n", file);
    }
    else
    {
        MY_LOGD("new MpoEncoder() fail");
        return false;
    }

mHalCamMAVMakeMPO_EXIT:
    delete mpoEncoder;
    if(err!=NO_ERROR)
        return false;
    else
        return true;
}


/*******************************************************************************
*
********************************************************************************/
MBOOL
PREFEATUREABSE::
createMPOInMemory(MPImageInfo * pMPImageInfo, MUINT32 num, MUINT32 MPOType, MUINT8* mpoBuffer)
{
    MINT32 err = NO_ERROR;
    MBOOL ok;
    MpoEncoder* mpoEncoder = new MpoEncoder();
    if (mpoEncoder) {
        ok = mpoEncoder->setJpegSources(TYPE_Disparity, pMPImageInfo, num);

        if (!ok) {
            MY_LOGE("  mpoEncoder->setJpegSources fail \n");
            err = 1;
            goto mHalCamMAVMakeMPO_EXIT;
        }

        if(!mpoBuffer) {
            MY_LOGE("  malloc fail\n");
            err = 1;
            goto mHalCamMAVMakeMPO_EXIT;
        }

        ok = mpoEncoder->encodeToMemory(mpoBuffer, MPOType);
        //dumpBufToFile("/sdcard/test.mpo", mem, mpoSize);


        if (!ok) {
            MY_LOGE("  mpoEncoder->encode fail \n");
            err = 1;
            goto mHalCamMAVMakeMPO_EXIT;
        }

        MY_LOGD("[createMPOInMemory] Done\n");
    }
    else
    {
        MY_LOGD("new MpoEncoder() fail");
        return false;
    }

mHalCamMAVMakeMPO_EXIT:
    delete mpoEncoder;
    if(err!=NO_ERROR)
        return false;
    else
        return true;
}


/*******************************************************************************
*
********************************************************************************/
MBOOL
PREFEATUREABSE::
queryMpoSize(MPImageInfo * pMPImageInfo, MUINT32 num, MUINT32 MPOType, MUINT32 &mpoSize)
{
    MINT32 err = NO_ERROR;
    MBOOL ok;
    MpoEncoder* mpoEncoder = new MpoEncoder();
    if (mpoEncoder) {
        ok = mpoEncoder->setJpegSources(TYPE_Disparity, pMPImageInfo, num);

        if (!ok) {
            MY_LOGE("  mpoEncoder->setJpegSources fail \n");
            err = 1;
            goto mHalCamMAVMakeMPO_EXIT;
        }

        mpoSize = mpoEncoder->getBufferSize();

        MY_LOGD("mpoSize %d", mpoSize);
    }
    else
    {
        MY_LOGD("new MpoEncoder() fail");
        return false;
    }

mHalCamMAVMakeMPO_EXIT:
    delete mpoEncoder;
    if(err!=NO_ERROR)
        return false;
    else
        return true;
}

/******************************************************************************
*
*******************************************************************************/
MBOOL 
PREFEATUREABSE::   
createJpegImg(MVOID* pMPImageInfo 
              , MVOID* Srcbuf
              , int u4SrcWidth
              , int u4SrcHeight
              , MUINT32     Jpgbufsize
              , MINT32      JpgbufmemID
              , MUINT32     JpgbufvirtAddr
              , MUINT32     JpgbufphyAddr
              , MUINT32     &u4JpegSize)
{
	  MBOOL ret = true;
    UtilityObj = halUTILITYBase::createInstance();
    ret=UtilityObj->createPanoJpegImg(pMPImageInfo
                                  ,Srcbuf
                                  ,u4SrcWidth,u4SrcHeight
                                  ,Jpgbufsize,JpgbufmemID,JpgbufvirtAddr,JpgbufphyAddr
                                  ,u4JpegSize,mpParamsMgr->getInt(CameraParameters::KEY_JPEG_QUALITY));
    
    if(UtilityObj)    
    	UtilityObj->destroyInstance();
    //delete UtilityObj;
    return ret;
    
}
   
/******************************************************************************
*
*******************************************************************************/
MBOOL 
PREFEATUREABSE:: 
makeExifHeader(MUINT32 const u4CamMode,
    			     MUINT8* const puThumbBuf,
				       MUINT32 const u4ThumbSize,
				       MUINT8* puExifBuf,
				       MUINT32 &u4FinalExifSize,
				       MUINT32 const Width,
				       MUINT32 const Height,
				       MUINT32 u4ImgIndex,
				       MUINT32 u4GroupId)
{
	  MBOOL ret = true;
    UtilityObj = halUTILITYBase::createInstance();                                  	
    ret=UtilityObj->makeExifHeader(u4CamMode, puThumbBuf, u4ThumbSize, puExifBuf, u4FinalExifSize, Width, Height, u4ImgIndex, u4GroupId, (MVOID*)&mpParamsMgr);
    
    if(UtilityObj)    
    	UtilityObj->destroyInstance();
    //delete UtilityObj; 
    return ret;	
}       
/******************************************************************************
*
*******************************************************************************/
MBOOL
PREFEATUREABSE::
handlePanoImgCallBack(MVOID* const puJpegBuf, int u4SrcWidth, int u4SrcHeight)
{
    MY_LOGD("[handleJpegCallBack] + (puJpgBuf, u4SrcWidth, u4SrcHeight) = (%p, %d , %d)", puJpegBuf, u4SrcWidth, u4SrcHeight);

    String8 const format =  String8(MtkCameraParameters::PIXEL_FORMAT_YUV420SP);

    IImageBufferAllocator* allocator = IImageBufferAllocator::getInstance();
                                            
    IImageBufferAllocator::ImgParam imgParam(((u4SrcWidth * u4SrcHeight * 2) + DBG_EXIF_SIZE), 0);
    sp<IImageBuffer> jpegBuf = allocator->alloc("PanoJpg", imgParam);
    jpegBuf->syncCache(eCACHECTRL_INVALID);
    if  ( jpegBuf.get() == 0 )
    {
        MY_LOGE("NULL Buffer\n");
        return MFALSE;
    }
    
    if ( !jpegBuf->lockBuf( "PanoJpg", (eBUFFER_USAGE_HW_CAMERA_READWRITE | eBUFFER_USAGE_SW_MASK) ) )
    {
        MY_LOGE("lock Buffer failed\n");
        return MFALSE;
    }
    
    MUINT32 u4JpegSize;
    MPImageInfo pMPImageInfo;
    BasObj->createJpegImg((MVOID*)&pMPImageInfo
                          ,(MVOID*)puJpegBuf
                          ,u4SrcWidth,u4SrcHeight
                          ,jpegBuf->getBufSizeInBytes(0),(MINT32)jpegBuf->getFD(0),(MUINT32)jpegBuf->getBufVA(0),(MUINT32)jpegBuf->getBufPA(0)
                          ,u4JpegSize);
        
    //save final image
    MY_LOGD("[handlePanoImgCallBack] u4JpegSize %d",u4JpegSize);
    MUINT8 *puExifHeaderBuf = new MUINT8[DBG_EXIF_SIZE];
    MUINT32 u4ExifHeaderSize = 0;

    BasObj->makeExifHeader(eAppMode_PhotoMode, NULL, 0, puExifHeaderBuf, u4ExifHeaderSize, u4SrcWidth, u4SrcHeight);
    MY_LOGD("[handleJpegData] (exifHeaderBuf, size) = (%p, %d)", puExifHeaderBuf, u4ExifHeaderSize);

    memcpy((void*)pMPImageInfo.imageBuf , puExifHeaderBuf, u4ExifHeaderSize);
    memcpy((void*)(pMPImageInfo.imageBuf +u4ExifHeaderSize), (void*)jpegBuf->getBufVA(0), u4JpegSize);
    
    delete [] puExifHeaderBuf;	
    
    if( !jpegBuf->unlockBuf( "PanoBuffer" ) )
    {
        CAM_LOGE("unlock Buffer failed\n");
        return MFALSE;
    }
	  allocator->free(jpegBuf.get());
	  
    BasObj->captureDoneCallback(MTK_CAMERA_MSG_EXT_DATA_AUTORAMA
                                , 2
                                , (int32_t)pMPImageInfo.imageBuf
                                , u4JpegSize + u4ExifHeaderSize
                                );
    BasObj->performCallback(0, 0, 0, 0, 0);
    MY_LOGD("[handleJpegData] -");

    return MTRUE;

}

#ifdef MTK_MOTION_TRACK_SUPPORTED
/******************************************************************************
*
*******************************************************************************/
MBOOL
PREFEATUREABSE::
handleMotionTrackImgCallBack(MVOID* const puJpegBuf, int u4SrcWidth, int u4SrcHeight)
{
    MUINT32 trueJpegBuf = ((MUINT32*) puJpegBuf)[4];
    MY_LOGD("[handleJpegCallBack] + integer(%d,%d,%d) (puJpgBuf, u4SrcWidth, u4SrcHeight) = (%p, %d , %d)", ((MUINT32*) puJpegBuf)[0], ((MUINT32*) puJpegBuf)[1], ((MUINT32*) puJpegBuf)[2], trueJpegBuf, u4SrcWidth, u4SrcHeight);

    if ((((MUINT32*) puJpegBuf)[0] == 3) || /* Callback on intermediate data */
        ((((MUINT32*) puJpegBuf)[0] == 2) && /* Callback with no blended image */
         (((MUINT32*) puJpegBuf)[2] == 0)))
    {
        MUINT32 CBData[4];
        CBData[0] = MTK_CAMERA_MSG_EXT_DATA_MOTIONTRACK;
        CBData[1] = ((MUINT32*) puJpegBuf)[0];
        CBData[2] = ((MUINT32*) puJpegBuf)[1];
        CBData[3] = ((MUINT32*) puJpegBuf)[2];

        BasObj->performCallback((int32_t) CBData, 0, 0, 0, 0);
        return MTRUE;
    }

    String8 const format =  String8(MtkCameraParameters::PIXEL_FORMAT_YUV420SP);

    IImageBufferAllocator* allocator = IImageBufferAllocator::getInstance();
                                            
    IImageBufferAllocator::ImgParam imgParam(((u4SrcWidth * u4SrcHeight * 2) + DBG_EXIF_SIZE), 0);
    sp<IImageBuffer> jpegBuf = allocator->alloc("MTJpg", imgParam);
    jpegBuf->syncCache(eCACHECTRL_INVALID);
    if  ( jpegBuf.get() == 0 )
    {
        MY_LOGE("NULL Buffer\n");
        return MFALSE;
    }
    
    if ( !jpegBuf->lockBuf( "PanoJpg", (eBUFFER_USAGE_HW_CAMERA_READWRITE | eBUFFER_USAGE_SW_MASK) ) )
    {
        MY_LOGE("lock Buffer failed\n");
        return MFALSE;
    }
    
    MUINT32 u4JpegSize;
    MPImageInfo pMPImageInfo;
    BasObj->createJpegImg((MVOID*)&pMPImageInfo
                          ,(MVOID*)trueJpegBuf
                          ,u4SrcWidth,u4SrcHeight
                          ,jpegBuf->getBufSizeInBytes(0),(MINT32)jpegBuf->getFD(),(MUINT32)jpegBuf->getBufVA(0),(MUINT32)jpegBuf->getBufPA(0)
                          ,u4JpegSize);
                          	
    //save final image
    MY_LOGD("[handleMotionTrackImgCallBack] Jpeg buffer %X, size %d", jpegBuf->getBufVA(0), u4JpegSize);
    MUINT8 *puExifHeaderBuf = new MUINT8[DBG_EXIF_SIZE];
    MUINT32 u4ExifHeaderSize = 0;

    BasObj->makeExifHeader(eAppMode_PhotoMode, NULL, 0, puExifHeaderBuf, u4ExifHeaderSize, u4SrcWidth, u4SrcHeight);
    MY_LOGD("[handleMotionTrackImgCallBack] Exif header buffer %X, size %d", puExifHeaderBuf, u4ExifHeaderSize);
       
    /* Start to callback */
    MUINT32 CBData[6];
    CBData[0] = MTK_CAMERA_MSG_EXT_DATA_MOTIONTRACK;
    CBData[1] = ((MUINT32*) puJpegBuf)[0];
    CBData[2] = ((MUINT32*) puJpegBuf)[1];
    CBData[3] = ((MUINT32*) puJpegBuf)[2];
    CBData[4] = u4ExifHeaderSize;
    CBData[5] = u4JpegSize;

    BasObj->performCallback((int32_t) CBData, (int32_t) puExifHeaderBuf, (int32_t) jpegBuf->getBufVA(0), 0, 0);

    delete [] puExifHeaderBuf;
    if( !jpegBuf->unlockBuf( "MTJpg" ) )
    {
        CAM_LOGE("unlock Buffer failed\n");
        return MFALSE;
    }
    allocator->free(jpegBuf.get());

    MY_LOGD("[handleJpegData] -");
    return MTRUE;
}
#endif

/******************************************************************************
*
*******************************************************************************/
MBOOL
PREFEATUREABSE::
handleMAVImgCallBack(MVOID* const puJpegBuf, int u4SrcWidth, int u4SrcHeight)
{
    MY_LOGD("[handleJpegCallBack] + (puJpgBuf, u4SrcWidth, u4SrcHeight) = (%p, %d , %d)", puJpegBuf, u4SrcWidth, u4SrcHeight);
    IImageBufferAllocator* allocator = IImageBufferAllocator::getInstance();
    IImageBufferAllocator::ImgParam imgParam(((u4SrcWidth * u4SrcHeight * 2) + DBG_EXIF_SIZE), 0);
    sp<IImageBuffer> jpegBuf = allocator->alloc("MavJpg", imgParam);
    jpegBuf->syncCache(eCACHECTRL_INVALID);
    if  ( jpegBuf.get() == 0 )
    {
        MY_LOGE("NULL Buffer\n");
        return MFALSE;
    }
    
    if ( !jpegBuf->lockBuf( "MAVJpg", (eBUFFER_USAGE_HW_CAMERA_READWRITE | eBUFFER_USAGE_SW_MASK) ) )
    {
        MY_LOGE("lock Buffer failed\n");
        return MFALSE;
    }
    
    MUINT32 u4JpegSize;
    MUINT32 u4SrcJpegSize;
    MPImageInfo * pMPImageInfo = new MPImageInfo[BasObj->mShotNum + 1];
    MUINT8 *puExifHeaderBuf = new MUINT8[DBG_EXIF_SIZE];
    MUINT32 u4ExifHeaderSize = 0;
    sp<IImageBuffer> *srcBuf = ((sp<IImageBuffer>*)puJpegBuf);
    
    BasObj->makeExifHeader(eAppMode_PhotoMode, NULL, 0, puExifHeaderBuf, u4ExifHeaderSize, u4SrcWidth, u4SrcHeight);
    MY_LOGD("[handleJpegData] (exifHeaderBuf, size) = (%p, %d)", puExifHeaderBuf, u4ExifHeaderSize);  
     
    //char sourceFiles[80]; 
    //for (MUINT8 i = 0; i< BasObj->mShotNum; i++) {
    //sprintf(sourceFiles, "%s%d_%dx%d.nv21_yvu", "/sdcard/JpgIn",i,u4SrcWidth,u4SrcHeight);
    //dumpBufToFile((char *) sourceFiles, (MUINT8 *)srcBuf[i]->getBufVA(0), u4SrcWidth*u4SrcHeight*3>>1);
    //}     
    srcBuf[0]->syncCache(eCACHECTRL_FLUSH);
    BasObj->createJpegImg((MVOID*)&pMPImageInfo[0]
                          ,(MVOID*)srcBuf[0]->getBufVA(0)
                          ,u4SrcWidth,u4SrcHeight
                          ,jpegBuf->getBufSizeInBytes(0),(MINT32)jpegBuf->getFD(0),(MUINT32)jpegBuf->getBufVA(0),(MUINT32)jpegBuf->getBufPA(0)
                          ,u4SrcJpegSize);
    jpegBuf->syncCache(eCACHECTRL_INVALID);                     	                                 	    
    for (MUINT8 i = 1; i< BasObj->mShotNum; i++) {
       MY_LOGD("[handleJpegData] srcBuf[i].getBufVA(0) 0x%x srcBuf[i-1].getBufVA(0) 0x%x", srcBuf[i]->getBufVA(0), srcBuf[i-1]->getBufVA(0));
       srcBuf[i]->syncCache(eCACHECTRL_FLUSH);
       BasObj->createJpegImg((MVOID*)&pMPImageInfo[i]
                             ,(MVOID*)srcBuf[i]->getBufVA(0)
                             ,u4SrcWidth,u4SrcHeight
                             ,srcBuf[i-1]->getBufSizeInBytes(0),(MINT32)srcBuf[i-1]->getFD(0),(MUINT32)srcBuf[i-1]->getBufVA(0),(MUINT32)srcBuf[i-1]->getBufPA(0)
                             ,u4JpegSize);
       srcBuf[i-1]->syncCache(eCACHECTRL_INVALID);                       	                                 	
       pMPImageInfo[i].imageBuf = (char*)srcBuf[i-1]->getBufVA(0);
       pMPImageInfo[i].imageSize = u4JpegSize ;
       pMPImageInfo[i].sourceType = SOURCE_TYPE_BUF;   	
    }
    
    
   
    for (MUINT8 i = (BasObj->mShotNum - 1); i > 0 ; i--) {  	  
        memcpy((void*)pMPImageInfo[i].imageBuf , puExifHeaderBuf, u4ExifHeaderSize);
        memcpy((void*)(pMPImageInfo[i].imageBuf +u4ExifHeaderSize), (void*)pMPImageInfo[i-1].imageBuf, pMPImageInfo[i-1].imageSize);
        pMPImageInfo[i].imageSize = pMPImageInfo[i-1].imageSize + u4ExifHeaderSize;
        //pMPImageInfo[i-1].imageBuf = pMPImageInfo[i].imageBuf;
        //pMPImageInfo[i-1].imageSize = pMPImageInfo[i-1].imageSize + u4ExifHeaderSize;
        MY_LOGD("MAV JPG: %d Adr 0x%x size %d", i, (MUINT32)pMPImageInfo[i].imageBuf,pMPImageInfo[i-1].imageSize);
        //sprintf(sourceFiles, "%s%d.jpg", "/sdcard/MPO",i);
        //dumpBufToFile((char *) sourceFiles, (MUINT8 *)pMPImageInfo[i].imageBuf, pMPImageInfo[i-1].imageSize);
    }
      
    memcpy((void*)pMPImageInfo[0].imageBuf , puExifHeaderBuf, u4ExifHeaderSize);
    memcpy((void*)(pMPImageInfo[0].imageBuf +u4ExifHeaderSize), (void*)jpegBuf->getBufVA(0), u4SrcJpegSize);
    pMPImageInfo[0].sourceType = SOURCE_TYPE_BUF;
    pMPImageInfo[0].imageSize = u4SrcJpegSize + u4ExifHeaderSize;
    
    //sprintf(sourceFiles, "%s.jpg", "/sdcard/MPO0");
    //dumpBufToFile((char *) sourceFiles, (MUINT8 *)pMPImageInfo[0].imageBuf, pMPImageInfo[0].imageSize);
      
    // encode MPO to memory
    MUINT8 *mpoBuffer = NULL;
    MUINT32 mpoSize = 0;
    BasObj->queryMpoSize(pMPImageInfo, BasObj->mShotNum, MTK_TYPE_MAV, mpoSize);
    mpoBuffer = (MUINT8*)malloc(mpoSize);
    if(!mpoBuffer) {
        MY_LOGE("alloc mpoBuffer fail");
        goto lbExit;
    }
    if(!BasObj->createMPOInMemory(pMPImageInfo, BasObj->mShotNum, MTK_TYPE_MAV, mpoBuffer)) {
        MY_LOGE("createMPOInMemory fail");
        goto lbExit;
    }

    // send MPO to AP
    BasObj->captureDoneCallback(MTK_CAMERA_MSG_EXT_DATA_MAV
                                , 2
                                , (MINT32)mpoBuffer
                                , (MINT32)mpoSize
                                );
lbExit:
	  if( !jpegBuf->unlockBuf( "MAVBuffer" ) )
    {
        CAM_LOGE("unlock Buffer failed\n");
        return MFALSE;
    }
	  allocator->free(jpegBuf.get());
	  
    if(!mpoBuffer)
        free(mpoBuffer);
    BasObj->performCallback(0, 0, 0, 1, 0);
    delete [] pMPImageInfo;
    delete [] puExifHeaderBuf;

    MY_LOGD("[handleJpegData] -");

    return MTRUE;
}
