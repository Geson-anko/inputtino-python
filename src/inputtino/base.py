from typing import Self
from dataclasses import dataclass

from . import _core


@dataclass(frozen=True)
class DeviceDefinition:
    """A class representing a virtual device definition.

    This class wraps the C++ DeviceDefinition class and provides a more Pythonic interface.

    Args:
        name: Device name
        vendor_id: Vendor ID for the device
        product_id: Product ID for the device
        version: Device version
        device_phys: Optional physical device path
        device_uniq: Optional unique device identifier
    """

    name: str
    vendor_id: int
    product_id: int
    version: int
    device_phys: str = ""
    device_uniq: str = ""

    def to_core(self) -> _core.DeviceDefinition:
        """Convert to C++ DeviceDefinition object.

        Returns:
            A C++ DeviceDefinition object used by the core library
        """
        definition = _core.DeviceDefinition()
        definition.name = self.name
        definition.vendor_id = self.vendor_id
        definition.product_id = self.product_id
        definition.version = self.version
        definition.device_phys = self.device_phys
        definition.device_uniq = self.device_uniq
        return definition

    @classmethod
    def from_core(cls, core_definition: _core.DeviceDefinition) -> Self:
        """Create a DeviceDefinition from a C++ DeviceDefinition object.

        Args:
            core_definition: C++ DeviceDefinition object

        Returns:
            A new DeviceDefinition instance
        """
        return cls(
            name=core_definition.name,
            vendor_id=core_definition.vendor_id,
            product_id=core_definition.product_id,
            version=core_definition.version,
            device_phys=core_definition.device_phys,
            device_uniq=core_definition.device_uniq,
        )
