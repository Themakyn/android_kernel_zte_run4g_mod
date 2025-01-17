# Copyright Statement:
#
# This software/firmware and related documentation ("MediaTek Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to MediaTek Inc. and/or its licensors.
# Without the prior written permission of MediaTek inc. and/or its licensors,
# any reproduction, modification, use or disclosure of MediaTek Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.

# MediaTek Inc. (C) 2010. All rights reserved.
#
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
# RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
# AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
# SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
# CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
# AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
# OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
#
# The following software/firmware and/or related documentation ("MediaTek Software")
# have been modified by MediaTek Inc. All revisions are subject to any receiver's
# applicable license agreements with MediaTek Inc.

################################################################################

LOCAL_PATH := $(call my-dir)

################################################################################
#
################################################################################
include $(CLEAR_VARS)

#-----------------------------------------------------------
MY_CUST_FTABLE_PATH := $(LOCAL_PATH)/config/matv
MY_CUST_FTABLE_PATH += $(MTK_PATH_CUSTOM)/hal/imgsensor
MY_CUST_FTABLE_PATH += $(MTK_PATH_CUSTOM)/hal/flashlight
MY_CUST_FTABLE_PATH += $(MTK_PATH_CUSTOM)/hal/camerashot
MY_CUST_FTABLE_PATH += $(MTK_PATH_CUSTOM)/hal/senindepfeature

#-----------------------------------------------------------
#
define my-all-config.ftbl-under
$(patsubst ./%,%, \
  $(shell find $(1)  -maxdepth 1 \( -name "config.ftbl.*.h" \) -and -not -name ".*") \
 )
endef
#
# custom feature table file list
MY_CUST_FTABLE_FILE_LIST := $(call my-all-config.ftbl-under, $(MY_CUST_FTABLE_PATH))

#-----------------------------------------------------------
LOCAL_SRC_FILES += $(call all-c-cpp-files-under, .)

#-----------------------------------------------------------
LOCAL_C_INCLUDES += $(MTKCAM_C_INCLUDES)
LOCAL_C_INCLUDES += $(PARAMSMGR_C_INCLUDES)
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/include
#
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/frameworks/av/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES += $(LOCAL_PATH)/config/matv
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_CUSTOM)/hal/imgsensor
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_CUSTOM)/hal/flashlight
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_CUSTOM)/hal/camerashot
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_CUSTOM)/hal/senindepfeature
LOCAL_C_INCLUDES += $(MTK_PATH_CUSTOM)/hal/inc/aaa

#-----------------------------------------------------------
LOCAL_CFLAGS += $(MTKCAM_CFLAGS)

#====== VSS ======
ifeq ($(MTK_CAM_VSS_SUPPORT),yes)
	LOCAL_CFLAGS += -DVSS_SUPPORTED=1
endif

#====== EIS ======
ifeq ($(MTK_CAM_EIS_SUPPORT),yes)
	LOCAL_CFLAGS += -DEIS_SUPPORTED=1
endif

#====== VHDR ======
ifeq ($(MTK_CAM_VHDR_SUPPORT),yes)
	LOCAL_CFLAGS += -DVHDR_SUPPORTED=1
endif

#====== HDR ======
ifeq ($(MTK_CAM_HDR_SUPPORT),yes)
	LOCAL_CFLAGS += -DHDR_SUPPORTED=1
endif

#====== 3DNR ======
ifeq ($(MTK_CAM_NR3D_SUPPORT),yes)
	LOCAL_CFLAGS += -DNR3D_SUPPORTED=1
endif

#====== cFB ======
ifeq ($(MTK_CAM_FACEBEAUTY_SUPPORT),yes)
	LOCAL_CFLAGS += -DFACEBEAUTY_SUPPORTED=1
endif

#
$(info "PARAMSMGR_VERSION=$(PARAMSMGR_VERSION)")
#
LOCAL_CFLAGS += -DCUSTOM_FLASHLIGHT_TYPE_$(CUSTOM_KERNEL_FLASHLIGHT)
$(info "CUSTOM_FLASHLIGHT_TYPE_$(CUSTOM_KERNEL_FLASHLIGHT)")

PLATFORM_VERSION_MAJOR := $(word 1,$(subst .,$(space),$(PLATFORM_VERSION)))
LOCAL_CFLAGS += -DPLATFORM_VERSION_MAJOR=$(PLATFORM_VERSION_MAJOR)

#-----------------------------------------------------------
LOCAL_WHOLE_STATIC_LIBRARIES += 
#
LOCAL_STATIC_LIBRARIES += 

#-----------------------------------------------------------
LOCAL_MODULE := libcam.paramsmgr.feature.custom
LOCAL_MODULE_CLASS := STATIC_LIBRARIES
INTERMEDIATES := $(call local-intermediates-dir)
# custom feature table all-in-one file
MY_CUST_FTABLE_FINAL_FILE := $(INTERMEDIATES)/custgen.config.ftbl.h
LOCAL_GENERATED_SOURCES += $(MY_CUST_FTABLE_FINAL_FILE)
$(MY_CUST_FTABLE_FINAL_FILE): $(MY_CUST_FTABLE_FILE_LIST)
	@mkdir -p $(dir $@)
	@echo '//this file is auto-generated; do not modify it!' > $@
	@echo '#define MY_CUST_VERSION "$(shell date) $(PARAMSMGR_VERSION)"' >> $@
	@echo '#define MY_CUST_FTABLE_FILE_LIST "$(MY_CUST_FTABLE_FILE_LIST)"' >> $@
	@echo '#define MY_CUST_FTABLE_FINAL_FILE "$(MY_CUST_FTABLE_FINAL_FILE)"' >> $@
	@for x in $(MY_CUST_FTABLE_FILE_LIST); do echo "#include <`basename $$x`>" >> $@; done

#-----------------------------------------------------------
include $(BUILD_STATIC_LIBRARY)


################################################################################
#
################################################################################
#include $(CLEAR_VARS)
#include $(call all-makefiles-under,$(LOCAL_PATH))

