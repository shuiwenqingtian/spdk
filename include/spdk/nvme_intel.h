/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2015 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SPDK_NVME_INTEL_H
#define SPDK_NVME_INTEL_H

#include <stdint.h>
#include <stddef.h>

/**
 * \file
 *
 * reference:
 * http://www.intel.com/content/dam/www/public/us/en/documents/product-specifications/
 * ssd-dc-p3700-spec.pdf
 */

enum nvme_intel_feature {
	NVME_INTEL_FEAT_MAX_LBA				= 0xC1,
	NVME_INTEL_FEAT_NATIVE_MAX_LBA			= 0xC2,
	NVME_INTEL_FEAT_POWER_GOVERNOR_SETTING		= 0xC6,
	NVME_INTEL_FEAT_SMBUS_ADDRESS			= 0xC8,
	NVME_INTEL_FEAT_LED_PATTERN			= 0xC9,
	NVME_INTEL_FEAT_RESET_TIMED_WORKLOAD_COUNTERS	= 0xD5,
	NVME_INTEL_FEAT_LATENCY_TRACKING		= 0xE2,
};

enum nvme_intel_log_page {
	NVME_INTEL_LOG_PAGE_DIRECTORY		= 0xC0,
	NVME_INTEL_LOG_READ_CMD_LATENCY		= 0xC1,
	NVME_INTEL_LOG_WRITE_CMD_LATENCY	= 0xC2,
	NVME_INTEL_LOG_TEMPERATURE		= 0xC5,
	NVME_INTEL_LOG_SMART			= 0xCA,
};

enum nvme_intel_smart_attribute_code {
	NVME_INTEL_SMART_PROGRAM_FAIL_COUNT			= 0xAB,
	NVME_INTEL_SMART_ERASE_FAIL_COUNT			= 0xAC,
	NVME_INTEL_SMART_WEAR_LEVELING_COUNT			= 0xAD,
	NVME_INTEL_SMART_E2E_ERROR_COUNT			= 0xB8,
	NVME_INTEL_SMART_CRC_ERROR_COUNT			= 0xC7,
	NVME_INTEL_SMART_MEDIA_WEAR				= 0xE2,
	NVME_INTEL_SMART_HOST_READ_PERCENTAGE			= 0xE3,
	NVME_INTEL_SMART_TIMER					= 0xE4,
	NVME_INTEL_SMART_THERMAL_THROTTLE_STATUS		= 0xEA,
	NVME_INTEL_SMART_RETRY_BUFFER_OVERFLOW_COUNTER		= 0xF0,
	NVME_INTEL_SMART_PLL_LOCK_LOSS_COUNT			= 0xF3,
	NVME_INTEL_SMART_NAND_BYTES_WRITTEN			= 0xF4,
	NVME_INTEL_SMART_HOST_BYTES_WRITTEN			= 0xF5,
};

struct nvme_intel_rw_latency_page {
	uint16_t		major_revison;
	uint16_t		minor_revison;
	uint32_t		buckets_32us[32];
	uint32_t		buckets_1ms[31];
	uint32_t		buckets_32ms[31];
};
_Static_assert(sizeof(struct nvme_intel_rw_latency_page) == 380, "Incorrect size");

struct nvme_intel_temperature_page {
	uint64_t		current_temperature;
	uint64_t		shutdown_flag_last;
	uint64_t		shutdown_flag_life;
	uint64_t		highest_temperature;
	uint64_t		lowest_temperature;
	uint64_t		reserved[5];
	uint64_t		specified_max_op_temperature;
	uint64_t		reserved2;
	uint64_t		specified_min_op_temperature;
	uint64_t		estimated_offset;
};
_Static_assert(sizeof(struct nvme_intel_temperature_page) == 112, "Incorrect size");

struct nvme_intel_smart_attribute {
	uint8_t			code;
	uint8_t			reserved[2];
	uint8_t			normalized_value;
	uint8_t			reserved2;
	uint8_t			raw_value[6];
	uint8_t			reserved3;
};

struct __attribute__((packed)) nvme_intel_smart_information_page {
	struct nvme_intel_smart_attribute	nvme_intel_smart_attributes[13];
};
_Static_assert(sizeof(struct nvme_intel_smart_information_page) == 156, "Incorrect size");

#endif