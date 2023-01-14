/*
 * Copyright (c) 2023 Jan Gnip
 * Copyright (c) 2022 Stephen Oliver
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>
#include <zephyr/logging/log.h>

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#include <sensor/scd4x/scd4x.h>

LOG_MODULE_REGISTER(main);

#if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_scd4x)
#error "No sensirion,scd4x compatible node found in the device tree"
#endif

void main(void)
{
	const struct device *scd = DEVICE_DT_GET_ANY(sensirion_scd4x);
	struct sensor_value temp, hum, co2;

	if (!device_is_ready(scd))
	{
		LOG_ERR("Device %s is not ready", scd->name);
		return;
	}

	while (true)
	{
		if (sensor_sample_fetch(scd))
		{
			LOG_ERR("Failed to fetch sample from %s device", scd->name);
			return;
		}

		sensor_channel_get(scd, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		sensor_channel_get(scd, SENSOR_CHAN_HUMIDITY, &hum);
		sensor_channel_get(scd, SENSOR_CHAN_CO2, &co2);

		double temperature = sensor_value_to_double(&temp);
		if (IS_ENABLED(CONFIG_APP_USE_FAHRENHEIT))
		{
			temperature = ((9.0 / 5.0) * temperature) + 32;
		}

		LOG_INF("%s Temperature: %.2f°, Humidity: %0.2f%%, CO2: %0.0f ppm",
				scd->name,
				temperature,
				sensor_value_to_double(&hum),
				sensor_value_to_double(&co2));

		k_sleep(K_MSEC(5000));
	}
}
