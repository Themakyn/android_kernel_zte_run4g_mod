/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.mediatek.common.telephony;

import android.os.Bundle;
import java.util.List;
import android.telephony.NeighboringCellInfo;
import android.telephony.CellInfo;

import android.os.Message;


/**
 * Interface used to interact with the phone.  Mostly this is used by the
 * TelephonyManager class.  A few places are still using this directly.
 * Please clean them up if possible and use TelephonyManager insteadl.
 *
 * {@hide}
 */
interface ITelephonyEx {

    Bundle queryNetworkLock(int category, int simId);
    int supplyNetworkDepersonalization(String strPasswd, int simId);
    
    /**
     * This function is used to get SIM phonebook storage information
     * by sim id.
     *
     * @param simId Indicate which sim(slot) to query
     * @return int[] which incated the storage info
     *         int[0]; // # of remaining entries
     *         int[1]; // # of total entries
     *         int[2]; // # max length of number
     *         int[3]; // # max length of alpha id
     *
     * @internal
     */ 
    int[] getAdnStorageInfo(int simId);
    
    /**
     * This function is used to check if the SIM phonebook is ready
     * by sim id.
     *
     * @param simId Indicate which sim(slot) to query
     * @return true if phone book is ready. 
     * @internal      
     */    
    boolean isPhbReady(int simId);

    int getSmsDefaultSim();  
    String getScAddressGemini(in int simId);
    void setScAddressGemini(in String scAddr, in int simId);

    /**
     * This function is used to set line1 number (EF_MSISDN)
     * by sim id.
     *
     * This function is a blocking function, please create a thread to run it.
     *
     * @param alphaTag: The description of the number. 
     *            If the input alphaTag is null we will use the current alphaTag.
     *            If current alphaTag is null, we will give a default alphaTag.
     *
     * @param number: The number which to set.
     * @param simId: Indicate which sim(slot) to set
     * @return int: Set MSISDN result
     *            1: Success.
     *            0: Fail
     * @internal      
     */   
    int setLine1Number(String alphaTag, String number, int simId);

    /**
     * This function is used to check if fdn of the icc is enable.
     * @param simId: Indicate which sim(slot) to set
     * @return true if phone Fdn is enable
     * @internal
     */
    boolean isFdnEnabled(int simId);

   /**
     * Query if icc card is existed or not.
     * @param simId Indicate which sim(slot) to query
     * @return true if exists an icc card in given slot.
     * @internal
     */
    boolean hasIccCard(int simId);

   /**
     * Get Icc Card Type
     * @param simId which sim(slot) to query
     * @return "SIM" for SIM card or "USIM" for USIM card.
     * @internal
     */
    String getIccCardType(int simId); 


     /*Add by mtk80372 for Barcode number*/
   /**
     * Get phone barcode number
     * @return serial number.
     * @internal
     */
    String getSerialNumber();

    /**
     * Get Icc Card is a test card or not.
     * @param simId Indicate which sim(slot) to query
     * @return ture if the ICC card is a test card.
     * @internal
     */
    boolean isTestIccCard(int simId);

    // NFC SEEK start
   /**
     * This function is used to send an APDU command to a logical channel
     *
     * @param simSlotId Indicate which sim(slot) to send
     * @return the response APDU for a command APDU sent to a logical channel
     * @internal
     */
    String transmitIccLogicalChannel(int cla, int command, int channel,
            int p1, int p2, int p3, String data, int simSlotId);

   /**
     * This function is used to send an APDU command to the basic channel
     *
     * @param simSlotId Indicate which sim(slot) to send
     * @return the response APDU for a command APDU sent to the basic channel
     * @internal
     */
    String transmitIccBasicChannel(int cla, int command,
            int p1, int p2, int p3, String data, int simSlotId);

   /**
     * This function is used to open a logical channel.
     *
     * @param AID Indicate the channel which to open
     * @param simSlotId Indicate which sim(slot) to open
     * @return the channel id of the logical channel, 
     *             0 on error.
     * @internal
     */
    int openIccLogicalChannel(String AID, int simSlotId);

   /**
     * This function is used to close a logical channel.
     *
     * @param channel Indicate the channel which to close
     * @param simSlotId Indicate which sim(slot) to close
     * @return true if logical channel was closed successfully
     * @internal
     */
    boolean closeIccLogicalChannel(int channel, int simSlotId);

   /**
     * This function is used to get the error code of the last error occured .
     * Currently only used for openIccLogicalChannel
     *
     * @param simSlotId Indicate which sim(slot) to query
     * @return int for error code.
     * @internal
     */
    int getLastError(int simSlotId);
   
   /**
     * This function is used to send an APDU command through SIM_IO
     *
     * @param simSlotId Indicate which sim(slot) to send
     * @return the response APDU for a command APDU sent through SIM_IO
     * @internal
     */
    byte[] transmitIccSimIO(int fileID, int command,
                                      int p1, int p2, int p3, String filePath, int simSlotId);

   /**
     * This function is used to send an APDU command through SIM_IO for Gemini-Card
     *
     * @param simSlotId Indicate which sim(slot) to send
     * @return the response APDU for a command APDU sent through SIM_IO
     * @internal
     */
    byte[] transmitIccSimIoEx(int fileID, int command,
                                      int p1, int p2, int p3, String filePath, String data, String pin2, int simId);
     
   /**
     * This function is used to get SIM's ATR
     *
     * @param simSlotId Indicate which sim(slot) to query
     * @return SIM's ATR in hex format.
     * @internal
     */
    String getIccAtr(int simSlotId);

   /**
     * This function is used to open a logical channel.
     *
     * @param simSlotId Indicate which sim(slot) to open
     * @return the channel id of the logical channel, sw1, and sw2,
     *             0 on error.
     * @internal
     */
    byte[] openIccLogicalChannelWithSw(String AID, int simSlotId);
    // NFC SEEK end

    /**
    * Query the international card type.
    * @param simId Indicate which sim(slot) to query
    * @return the queried international card type.
    */
    int getInternationalCardType(int simId);

    /**
    * Set international network mode only for Engineer Mode of testing CDMA RF for VIA.
    * @param networkMode Cdma only or Wcdma(Gsm) only or international mode.
    */
    void setInternationalNetworkMode(int networkMode);

    /**
    * Get international network mode only for Engineer Mode of testing CDMA RF for VIA..
    * @return the queried international mode.
    */
    int getInternationalNetworkMode(); 

    /**
     * Modem SML change feature.
     * This function will query the SIM state of the given slot. And broadcast 
     * ACTION_UNLOCK_SIM_LOCK if the SIM state is in network lock.
     * 
     * @param simId: Indicate which sim(slot) to query
     * @param needIntent: The caller can deside to broadcast ACTION_UNLOCK_SIM_LOCK or not
     *                              in this time, because some APs will receive this intent (eg. Keyguard).
     *                              That can avoid this intent to effect other AP.
     */
    void repollIccStateForNetworkLock(int simId, boolean needIntent); 
    
    
    /**
     * This function will check if phone can enter airplane mode right now
     *      
     * @return boolean: return phone can enter flight mode
     *                true: phone can enter flight mode
     *                false: phone cannot enter flight mode
     */
    boolean isAirplanemodeAvailableNow();

     /**
     * This function is used to report whether data connectivity is possible.
     * by sim id.
     *
     * @param simId Indicate which sim(slot) to query
     * @return true if phone book is ready. 
     * @internal      
     */    
    boolean isDataConnectivityPossibleGemini(int simId);

    // TODO: need to be removed by Edward, Data LEGO API [start]
     /**
     * Gemini (ToDo)
     * Returns a constant indicating the current data connection state
     * (cellular).
     *
     * @see #DATA_DISCONNECTED
     * @see #DATA_CONNECTING
     * @see #DATA_CONNECTED
     * @see #DATA_SUSPENDED
     * @hide
     */    
    int getDataStateGemini(int simId) ;

    /**
     * Returns a constant indicating the type of activity on a data connection
     * (cellular).
     *
     * @param simId sim slot
     * @see #DATA_ACTIVITY_NONE
     * @see #DATA_ACTIVITY_IN
     * @see #DATA_ACTIVITY_OUT
     * @see #DATA_ACTIVITY_INOUT
     * @see #DATA_ACTIVITY_DORMANT
     * @hide
     */
    int getDataActivityGemini(int simId);

    /**
     * Gemini (ToDo)
     * Returns void
     * (cellular).  
     *
     * @param enable boolean (true/false)
     * @param simId sim slot
     * @hide
     * @internal
     */
    void setDataRoamingEnabledGemini(boolean enable, int simId);
    // TODO: need to be removed by Edward, Data LEGO API [End]

	/**
     * Gemini (ToDo)
     * Returns a constant indicating the current data connection state
     * (cellular).
     *
     * @see #DATA_DISCONNECTED
     * @see #DATA_CONNECTING
     * @see #DATA_CONNECTED
     * @see #DATA_SUSPENDED
     * @hide
     */    
    int getDataState(int simId) ;

    /**
     * Returns a constant indicating the type of activity on a data connection
     * (cellular).
     *
     * @param simId sim slot
     * @see #DATA_ACTIVITY_NONE
     * @see #DATA_ACTIVITY_IN
     * @see #DATA_ACTIVITY_OUT
     * @see #DATA_ACTIVITY_INOUT
     * @see #DATA_ACTIVITY_DORMANT
     * @hide
     */
    int getDataActivity(int simId);

    /**
     * Gemini (ToDo)
     * Returns void
     * (cellular).  
     *
     * @param enable boolean (true/false)
     * @param simId sim slot
     * @hide
     * @internal
     */
    void setDataRoamingEnabled(boolean enable, int simId);

    /**
     * refer to getCallState();
     */
     int getCallState(int simId);

   /**
     * get the network service state for specified SIM
     * @param simId Indicate which sim(slot) to query
     * @return service state.
     *
    */ 
    Bundle getServiceState(int simId);

    boolean handlePinMmi(String dialString, int simId);
    int getSimIndicatorState(int simId);
    String getSimCountryIso(int simId);
    
    /**
     * Get current 3G capability SIM. 
     * (PhoneConstants.GEMINI_SIM_1, PhoneConstants.GEMINI_SIM_2, ...)
     * 
     * @return the SIM slot where 3G capability at. (@see PhoneConstants)
     * @internal
     * @deprecated
     */
    int get3GCapabilitySIM();
    
    /**
     * Set 3G capability to specified SIM. 
     * 
     * @param simId sim slot 
     * @return the result of issuing 3g capability set operation (true or false)
     * @internal
     * @deprecated
     */
    boolean set3GCapabilitySIM(int simId);
    
    /**
     * To acquire 3G switch lock 
     * (to protect from multi-manipulation to 3g switch flow)
     * 
     * @return the acquired lock Id
     * @internal
     * @deprecated
     */
    int aquire3GSwitchLock();
    
    /**
     * To release the acquired 3G switch lock (by lock Id)
     * 
     * @param lockId thd lock Id
     * @return true if the lock Id is released
     * @internal
     * @deprecated
     */
    boolean release3GSwitchLock(int lockId);
    
    /**
     * Check 3G switch lock status
     * 
     * @return true if 3G switch lock is locked
     * @internal
     * @deprecated
     */
    boolean is3GSwitchLocked();
    
    /**
     * To Check if 3G Switch Manual Control Mode Enabled. 
     * 
     * @return true if 3G Switch manual control mode is enabled, else false;
     * @internal
     * @deprecated
     */
    boolean is3GSwitchManualEnabled();
    
    /**
     * Check if 3G Switch allows Changing 3G SIM Slot in Manual Control Mode.  
     * 
     * @return true if 3G Switch allows Changing 3G SIM Slot in manual control mode, else false;
     * @internal
     * @deprecated
     */
    boolean is3GSwitchManualChange3GAllowed();
    
    /**
     * To Get 3G Switch Allowed 3G SIM Slots.
     * 
     * Returns an integer showing allowed 3G SIM Slots bitmasks. 
     *   Bit0 for SIM1; Bit1 for SIM2.  
     *   0 for disallowed; 1 for allowed. 
     * 
     * Examples as below: 
     *   0x00000001b: SIM1 is allowed. 
     *   0x00000010b: SIM2 is allowed.
     *   0x00000011b: SIM1, SIM2 are allowed.
     *   0:           no SIM is allowed. 
     * 
     * @return the allowed 3G SIM Slots bitmasks
     * @internal
     * @deprecated
     */
    int get3GSwitchAllowed3GSlots();

    /**
     * To config sim switch mode(for dsda).
     * 
     * @return true if config sim switch mode successful, or return false
     * @internal
     */
    boolean configSimSwitch(boolean toSwapped);

    /**
     * To check sim switch mode is swapped or not(for dsda).
     * 
     * @return true if swapped, or return false
     * @internal
     */
    boolean isSimSwitchSwapped();

    /**
     * Get the SIM slot which has the specified capability. 
     * (PhoneConstants.GEMINI_SIM_1, PhoneConstants.GEMINI_SIM_2, ...)
     * 
     * @param capability the target capability (@see TelephonyCapabilities)
     * @return the SIM slot where specified capability at. (@see PhoneConstants)
     *         -1 if the capability not supported currently. 
     * @internal
     */
    int getCapabilitySIM(int capability);

    /**
     * Get the high speed SIM slot which has the 3G or 34G capability.
     * (api to select capability automatically)
     * 
     */
    int getHsCapabilitySIM();

    /**
     * Set capability to specified SIM. 
     * 
     * @param capability the target capability (@see TelephonyCapabilities)
     * @param simId sim slot (@see PhoneConstants)
     * @return the result of capability set operation (true or false)
     * @internal
     */
    boolean setCapabilitySIM(int capability, int simId);

    /**
     * To acquire SIM Switch lock 
     * (to protect from multi-manipulation to 3g switch flow)
     * 
     * @return the acquired lock Id
     * @internal
     */
    int aquireSimSwitchLock();

    /**
     * To release the acquired Sim switch lock (by lock Id)
     * 
     * @param lockId thd lock Id
     * @return true if the lock Id is released
     * @internal
     */
    boolean releaseSimSwitchLock(int lockId);

    /**
     * Check Sim switch lock status
     * 
     * @return true if Sim switch lock is locked
     * @internal
     */
    boolean isSimSwitchLocked();

    /**
     * To Check if Sim Switch Manual Control Mode Enabled. 
     * 
     * @return true if Sim Switch manual control mode is enabled, else false;
     * @internal
     */
    boolean isSimSwitchManualModeEnabled();

    /**
     * Check if Sim Switch allows Changing capability sim slot in Manual Control Mode.  
     * 
     * @return true if Sim Switch allows Changing capability sim slot in manual control mode, else false;
     * @internal
     */
    boolean isSimSwitchManualChangeSlotAllowed();

    /**
     * To Get Sim Switch Allowed capability slots.
     * 
     * Returns an integer showing allowed capability slots bitmasks. 
     *   Bit0 for SIM1; Bit1 for SIM2; Bit2 for SIM3; Bit3 for SIM4;
     *   0 for disallowed; 1 for allowed. 
     * 
     * Examples as below: 
     *   0x00000001b: SIM1 is allowed. 
     *   0x00000010b: SIM2 is allowed.
     *   0x00000011b: SIM1, SIM2 are allowed.
     *   0:           no SIM is allowed. 
     * 
     * @return the allowed capability slots bitmasks
     * @internal
     */
    int getSimSwitchAllowedSlots();
    
    /**
     * Gemini (ToDo)
     * Check to see if the radio is on or not.
     * @return returns true if the radio is on.
     * (cellular).  
     *
     * @param simId sim slot   
     * @hide     
     * @internal     
     */
    boolean isRadioOn(int simId);    

    /**
     * Gemini (ToDo)
     * Returns the neighboring cell information of the device.
     * @return the neighboring cell information of the device.
     * (cellular).  
     *
     * @param simId sim slot   
     * @hide     
     * @internal     
     */
    List<NeighboringCellInfo> getNeighboringCellInfo(String callingPkg, int simId);

    /**
     * Gemini (ToDo)
     * Returns the Cell Location information of the device.
     * @return the Cell Location information of the device.
     * (cellular).  
     *
     * @param simId sim slot   
     * @hide     
     * @internal     
     */
    Bundle getCellLocation(int simId);

    List<CellInfo> getAllCellInfo(int simId);

    void setCellInfoListRate(int rateInMillis,int simId);

    /**
     * Gemini (ToDo)
     * Returns the network type
     * @return the network type.
     * (cellular).  
     *
     * @param simId sim slot   
     * @hide     
     * @internal     
     */
    int getNetworkType(int simId);

    /**
     * Returns a constant indicating the radio technology (network type)
     * currently in use on the device for data transmission.
     * @return the network type
     *
     * @see #NETWORK_TYPE_UNKNOWN
     * @see #NETWORK_TYPE_GPRS
     * @see #NETWORK_TYPE_EDGE
     * @see #NETWORK_TYPE_UMTS
     * @see #NETWORK_TYPE_HSDPA
     * @see #NETWORK_TYPE_HSUPA
     * @see #NETWORK_TYPE_HSPA
     * @see #NETWORK_TYPE_CDMA
     * @see #NETWORK_TYPE_EVDO_0
     * @see #NETWORK_TYPE_EVDO_A
     * @see #NETWORK_TYPE_EVDO_B
     * @see #NETWORK_TYPE_1xRTT
     * @see #NETWORK_TYPE_IDEN
     * @see #NETWORK_TYPE_LTE
     * @see #NETWORK_TYPE_EHRPD
     * @see #NETWORK_TYPE_HSPAP
     *
     * @hide
     */
    int getDataNetworkType(int simId);

    /**
     * Returns the NETWORK_TYPE_xxxx for voice
     *
     * @hide
     */
    int getVoiceNetworkType(int simId);

    /**
     * Gemini (ToDo)
     * Gets the unique subscriber ID, for example, the IMSI for a GSM phone.
     * @return Unique subscriber ID, for example, the IMSI for a GSM phone.
     *             Null is returned if it is unavailable.
     * (cellular).  
     *
     * @param simId sim slot   
     * @hide     
     * @internal     
     */
    String getSubscriberId(int simId);    
    
    /**
     * refer to getActivePhoneType();
     */
    int getActivePhoneType(int simId);  

   /**
     * Check if phone is hiding network temporary out of service state.
     * @param simId Indicate which sim(slot) to query
     * @return if phone is hiding network temporary out of service state.
    */    
    int getNetworkHideState(int simId);

    int getActiveModemType();

    /**
     * Returns SimId for connectivity feature user
     * @return : Sim Slot Id
     *
     * @internal 
     */
    int dataConnectivityDecideSimId();

     /**
     * notify modem, if mobile data service on/off
     * @return : none
     *
     * @internal 
     */
    void setDataOnToMD(boolean enable);

   /**
     * To get located PLMN from sepcified SIM modem  protocol      
     * Returns current located PLMN string(ex: "46000") or null if not availble (ex: in flight mode or no signal area or this SIM is turned off)
     * @hide
     * @internal 
     */
    String getLocatedPlmn(int simId);

   /**
     * For Lte Dc feature
     * get the network service state for Lte DC (3/4G)
     * @return service state.
     *
    */ 
    Bundle getServiceStateLte();

    /**
     * For Lte Dc feature
     * Requests to set the preferred network type for searching and registering
     * (CS/PS domain, RAT, and operation mode)
     * @param networkType one of  NT_*_TYPE
     * @param response is callback message
     */
    void setPreferredNetworkTypeLteDc(int networkType, in Message response);

    /**
     *  For Lte Dc feature
     *  Query the preferred network type setting
     *
     * @param response is callback message to report one of  NT_*_TYPE
     */
    void getPreferredNetworkTypeLteDc(in Message response);
   
    /**
     * Lte Dc
     * Returns the numeric name (MCC+MNC) of current registered operator.
     * <p>
     * Availability: Only when user is registered to a network. Result may be
     * unreliable on CDMA networks (use {@link #getPhoneType()} to determine if
     * on a CDMA network).
     */
    String getNetworkOperatorLteDc(); 

    /**
     * For Lte Dc feature   
     * Returns the alphabetic name of current registered operator.
     * <p>
     * Availability: Only when user is registered to a network. Result may be
     * unreliable on CDMA networks (use {@link #getPhoneType()} to determine if
     * on a CDMA network).
     */
    String getNetworkOperatorNameLteDc();

    /**
     * For Lte Dc feature 
     * Returns true if the device is considered roaming on the current
     * network, for GSM purposes.
     * <p>
     * Availability: Only when user registered to a network.
     */
    boolean isNetworkRoamingLteDc();

    /**
     * For Lte Dc feature       
     * Returns the ISO country code equivalent of the current registered
     * operator's MCC (Mobile Country Code).
     * <p>
     * Availability: Only when user is registered to a network. Result may be
     * unreliable on CDMA networks (use {@link #getPhoneType()} to determine if
     * on a CDMA network).
     */
    String getNetworkCountryIsoLteDc();

    void setImsEnable(int simId, boolean enable);
    int getImsState(int simId);
    void registerForImsDisableDone(int simId, IBinder binder, int what);
    void unregisterForImsDisableDone(int simId, IBinder binder);
}

