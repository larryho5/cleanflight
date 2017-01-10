/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <platform.h>

#include "io/motors.h"

#include "sensors/battery.h"

#include "config/config_master.h"
#include "config/feature.h"
#include "io/ledstrip.h"
#include "drivers/pwm_output.h"

void targetApplyDefaultLedStripConfig(ledConfig_t *ledConfigs)   
{
    const ledConfig_t defaultLedStripConfig[] = {
        DEFINE_LED( 0,   0,     6,  0,        LF(COLOR), 0,   0 ),
        DEFINE_LED( 1,   0,     6,  0,        LF(COLOR), 0,   0 ),
        DEFINE_LED( 1,  15,     6,  0,        LF(COLOR), 0,   0 ),
        DEFINE_LED( 0,  15,     6,  0,        LF(COLOR), 0,   0 ),
    };
    memcpy(ledConfigs, &defaultLedStripConfig, MIN(LED_MAX_STRIP_LENGTH, sizeof(defaultLedStripConfig)));
}

// alternative defaults settings for COLIBRI RACE targets
void targetConfiguration(master_t *config)
{
    config->motorConfig.minthrottle = 1045;
    config->motorConfig.maxthrottle = 1980;
    config->motorConfig.mincommand = 980;
    config->servoConfig.servoCenterPulse = 1500;

    config->batteryConfig.vbatmaxcellvoltage = 45;
    config->batteryConfig.vbatmincellvoltage = 30;
    config->batteryConfig.vbatwarningcellvoltage = 35;

    config->flight3DConfig.deadband3d_low = 1406;
    config->flight3DConfig.deadband3d_high = 1514;
    config->flight3DConfig.neutral3d = 1460;
    config->flight3DConfig.deadband3d_throttle = 0;
    
    config->failsafeConfig.failsafe_procedure = 1;
    config->failsafeConfig.failsafe_throttle_low_delay = 10;

    config->gyroConfig.gyro_sync_denom = 2;
    config->pidConfig.pid_process_denom = 1;
    config->blackboxConfig.rate_num = 1;
    config->blackboxConfig.rate_denom = 1;

    config->rcControlsConfig.deadband = 5;
    config->rcControlsConfig.yaw_deadband = 5;

    config->failsafeConfig.failsafe_delay = 10;

    config->telemetryConfig.telemetry_inversion = 1;

    config->profile[0].pidProfile.vbatPidCompensation = 1;

    config->profile[0].pidProfile.P8[ROLL] = 47;     // new PID with preliminary defaults test carefully
    config->profile[0].pidProfile.I8[ROLL] = 74;
    config->profile[0].pidProfile.D8[ROLL] = 23;
    config->profile[0].pidProfile.P8[PITCH] = 50;
    config->profile[0].pidProfile.I8[PITCH] = 110;
    config->profile[0].pidProfile.D8[PITCH] = 25;
    config->profile[0].pidProfile.P8[YAW] = 96;
    config->profile[0].pidProfile.I8[YAW] = 63;
    config->profile[0].pidProfile.D8[YAW] = 50;

    config->profile[0].controlRateProfile[0].rates[FD_ROLL] = 80;
    config->profile[0].controlRateProfile[0].rates[FD_PITCH] = 80;
    config->profile[0].controlRateProfile[0].rates[FD_YAW] = 80;

    config->motorConfig.motorPwmProtocol = PWM_TYPE_MULTISHOT;

    targetApplyDefaultLedStripConfig(config->ledStripConfig.ledConfigs);

}
