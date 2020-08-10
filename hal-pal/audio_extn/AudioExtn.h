/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of The Linux Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AUDIOEXTN_H
#define AUDIOEXTN_H
#include <cutils/str_parms.h>
#include <set>
#include "PalDefs.h"
#include "audio_defs.h"
#include <log/log.h>
#include "battery_listener.h"

typedef void (*batt_listener_init_t)(battery_status_change_fn_t);
typedef void (*batt_listener_deinit_t)();
typedef bool (*batt_prop_is_charging_t)();
typedef bool (*audio_device_cmp_fn_t)(audio_devices_t);

class AudioDevice;
//HFP
typedef int audio_usecase_t;
typedef void(*hfp_init_t)();
typedef bool(*hfp_is_active_t)(std::shared_ptr<AudioDevice> adev);
typedef audio_usecase_t(*hfp_get_usecase_t)();
typedef int(*hfp_set_mic_mute_t)(bool state);
typedef void(*hfp_set_parameters_t)(std::shared_ptr<AudioDevice> adev, struct str_parms *parms);
typedef int(*hfp_set_mic_mute2_t)(std::shared_ptr<AudioDevice> adev, bool state);

class AudioExtn
{
public:
    static int audio_extn_parse_compress_metadata(struct audio_config *config_, pal_snd_dec_t *pal_snd_dec, str_parms *parms, uint32_t *sr, uint16_t *ch);
    static int get_controller_stream_from_params(struct str_parms *parms, int *controller, int *stream);
    static void battery_listener_feature_init(bool is_feature_enabled);
    static void battery_properties_listener_init(battery_status_change_fn_t fn);
    static void battery_properties_listener_deinit();
    static bool battery_properties_is_charging();

    //HFP
    static int hfp_feature_init(bool is_feature_enabled);
    static bool audio_extn_hfp_is_active(std::shared_ptr<AudioDevice> adev);
    audio_usecase_t audio_extn_hfp_get_usecase();
    static int audio_extn_hfp_set_mic_mute(bool state);
    static void audio_extn_hfp_set_parameters(std::shared_ptr<AudioDevice> adev, struct str_parms *parms);
    static int audio_extn_hfp_set_mic_mute2(std::shared_ptr<AudioDevice> adev, bool state);

    /* start device utils */
    static bool audio_devices_cmp(const std::set<audio_devices_t>&, audio_device_cmp_fn_t);
    static bool audio_devices_cmp(const std::set<audio_devices_t>&, audio_devices_t);
    static audio_devices_t get_device_types(const std::set<audio_devices_t>&);
    static bool audio_devices_empty(const std::set<audio_devices_t>&);
    /* end device utils */
};

#endif /* AUDIOEXTN_H */
