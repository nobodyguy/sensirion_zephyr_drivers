/*
 * Copyright (c) 2023 Jan Gnip
 * Copyright (c) 2021 Advanced Climate Systems
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>
#include <zephyr/logging/log.h>

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#include <sensor/scd30/scd30.h>

#define SCD30_SAMPLE_TIME_SECONDS 5U

#if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_scd30)
#error "No sensirion,scd30 compatible node found in the device tree"
#endif

void main(void)
{
	const struct device *dev = DEVICE_DT_GET_ANY(sensirion_scd30);
	struct sensor_value sample_period = {
		.val1 = SCD30_SAMPLE_TIME_SECONDS,
	};

	if (!device_is_ready(dev))
	{
		LOG_ERR("Could not get SCD30 device");
		return;
	}

	int rc = sensor_attr_set(dev, SENSOR_CHAN_ALL,
							 SCD30_SENSOR_ATTR_SAMPLING_PERIOD, &sample_period);
	if (rc != 0)
	{
		LOG_ERR("Failed to set sample period. (%d)", rc);
		return;
	}

	while (true)
	{
		struct sensor_value co2_concentration;

		rc = sensor_sample_fetch(dev);
		if (rc == 0)
		{
			rc = sensor_channel_get(dev, SENSOR_CHAN_CO2, &co2_concentration);
		}

		if (rc == -ENODATA)
		{
			LOG_INF("%s: no new measurment yet.", dev->name);
			LOG_INF("Waiting for 1 second and retrying...");
			k_sleep(K_SECONDS(1));
			continue;
		}
		else if (rc != 0)
		{
			LOG_INF("%s channel get: failed: %d", dev->name, rc);
			break;
		}

		LOG_INF("%s: %d ppm", dev->name, co2_concentration.val1);

		k_sleep(K_SECONDS(SCD30_SAMPLE_TIME_SECONDS));
	}
}
