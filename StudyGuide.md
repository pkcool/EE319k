EE319k Study Guide
==================

GPIO Registers
--------------

| Register | Name                      | Description                                         |
| -------- | ----                      | -----------                                         |
| `DATA`   | Data                      | values of the GPIO port pins                        |
| `DIR`    | Direction                 | set direction to input / output                     |
| `IS`     | Interrupt Sense           | detect on edge / levels                             |
| `IBE`    | Interrupt Both Edges      | set to detect rising & falling edge (overrides IEV) |
| `IEV`    | Interrupt Event           | detect falling / rising edge                        |
| `IM`     | Interrupt Mask            | set bits to trigger interrupt on corresponding pins |
| `RIS`    | Raw Interrupt Status      | contains raw data from interrupt (before mask)      |
| `MIS`    | Masked Interrupt Status   | contains masked data from interrupt                 |
| `ICR`    | Interrupt Clear           | write a 1 to ACK the interrupt                      |
| `AFSEL`  | Alternate Function Select | write a 1 to any bit to select hardware control     |
| `PUR`    | Pull-Up Select            | enables a weak pull-up resistor (overrides PDR)     |
| `PDR`    | Pull-Down Select          | enables a weak pull-down resistor (overrides PUR)   |
| `DEN`    | Digital Enable            | allow bin voltage into the GPIO port                |

Timer Registers
---------------

`Period = Δt * (reload + 1) * (prescale + 1)`

| Register   | Name            | Description                              |
| --------   | ----            | -----------                              |
| `CFG`      | Configuration   | 0x1 for 32-bit, 0x4 for 16-bit           |
| `T[AB]MR`  | Timer Mode      | 0x1 for One-Shot, 0x2 for Periodic       |
| `CTL`      | Control         | holds a lot of flags, just set `T[AB]EN` |
| `IMR`      | Interrupt Mask  | enables interrupt (set `T[AB]TOIM`)      |
| `ICR`      | Interrupt Clear | set `T[AB]TOCINT` to ACK interrupt       |
| `T[AB]ILR` | Interval Load   | reload value                             |
| `T[AB]PR`  | Prescale        | used to extend the range in 16-bit mode  |

ADC
---

| Register | Name | Description |
| -------- | ---- | ----------- |
|          |      |             |

