from inputtino import _core
from inputtino.base import DeviceDefinition


def test_device_definition_creation():
    definition = DeviceDefinition(
        name="Test Device",
        vendor_id=0x1234,
        product_id=0x5678,
        version=1,
        device_phys="/dev/input/test",
        device_uniq="unique_id",
    )
    assert definition.name == "Test Device"
    assert definition.vendor_id == 0x1234
    assert definition.product_id == 0x5678
    assert definition.version == 1
    assert definition.device_phys == "/dev/input/test"
    assert definition.device_uniq == "unique_id"


def test_device_definition_to_core():
    definition = DeviceDefinition(
        name="Test Device",
        vendor_id=0x1234,
        product_id=0x5678,
        version=1,
        device_phys="/dev/input/test",
        device_uniq="unique_id",
    )
    core_def = definition.to_core()

    assert isinstance(core_def, _core.DeviceDefinition)
    assert core_def.name == definition.name
    assert core_def.vendor_id == definition.vendor_id
    assert core_def.product_id == definition.product_id
    assert core_def.version == definition.version
    assert core_def.device_phys == definition.device_phys
    assert core_def.device_uniq == definition.device_uniq


def test_device_definition_from_core():
    core_def = _core.DeviceDefinition()
    core_def.name = "Test Device"
    core_def.vendor_id = 0x1234
    core_def.product_id = 0x5678
    core_def.version = 1
    core_def.device_phys = "/dev/input/test"
    core_def.device_uniq = "unique_id"

    definition = DeviceDefinition.from_core(core_def)

    assert isinstance(definition, DeviceDefinition)
    assert definition.name == core_def.name
    assert definition.vendor_id == core_def.vendor_id
    assert definition.product_id == core_def.product_id
    assert definition.version == core_def.version
    assert definition.device_phys == core_def.device_phys
    assert definition.device_uniq == core_def.device_uniq
