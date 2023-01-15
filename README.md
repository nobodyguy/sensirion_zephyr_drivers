# Sensirion Zephyr drivers
SCD4X and SCD30 sensor drivers for Zephyr RTOS.\
Based on an awesome work of [Stephen Oliver](https://github.com/steveatinfincia) (SCD4X driver) and [
Joep Buruma](https://github.com/burumaj) (SCD30 driver).

## Supported Zephyr versions
* 3.2.0 (September 2022)

## Usage
### Module installation
Add this project to your `west.yml` manifest:
```yaml
- name: sensirion_drivers
  path: modules/sensirion_drivers
  url: https://github.com/nobodyguy/sensirion_zephyr_drivers
  revision: main
```

So your projects should look something like this:
```yaml
manifest:
  projects:
    - name: zephyr
      url: https://github.com/zephyrproject-rtos/zephyr
      revision: refs/tags/zephyr-v3.2.0
      import: true
    - name: sensirion_drivers
      path: modules/sensirion_drivers
      url: https://github.com/nobodyguy/sensirion_zephyr_drivers
      revision: main
```

This will import the module and allow you to use the drivers in your code.

Additionally make sure that you run `west update` when you've added this entry to your `west.yml`.

### Driver usage
Please check the samples in `./samples/` directory.