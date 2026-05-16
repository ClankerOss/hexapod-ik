# hexapod-ik

Robotic hexapod leg with a full 3-DOF inverse kinematics solver,
running on an Arduino in C.

Type a target coordinate (X, Y, Z) over Serial and the leg tip
moves precisely to that position — joint angles solved in real time.

## Hardware

| Component | Details |
|-----------|---------|
| Microcontroller | Arduino |
| Servos | MG995 (× 3) — provided by ETH Student Project House |
| Material | PETG (3D printed, chosen for structural stability) |
| Joints | Coaxial · Femur · Tibia |

## Link lengths

| Segment | Length |
|---------|--------|
| Coaxial (l) | 50 mm |
| Femur (a) | 100 mm |
| Tibia (b) | 150 mm |

## CAD files

All parts designed for 3D printing in PETG.

| File | Description |
|------|-------------|
| `Connector_to_body.stl` | Mounts the leg assembly to the body |
| `Connector_to_Servo2.stl` | Interface between coaxial and femur servo |
| `Foot.stl` | Leg tip / contact point |
| `Joint_1_to_2.stl` | Coaxial to femur joint |
| `Joint_2_to_3.stl` | Femur to tibia joint |
| `Torque_1_to_2.stl` | Torque transfer coaxial → femur |
| `Torque_2_to_3.stl` | Torque transfer femur → tibia |

## Arduino files

### `InverseKinematics.ino`
Base IK solver. Reads X Y Z from Serial, computes joint angles
using 3-DOF geometric inverse kinematics, and drives all three
servos. Angles clamped to physical servo limits (0–180°).

### `InverseKinematicsConst.ino`
Extended version with mechanical constraint handling. Adds
dynamic range adjustment for the femur servo (servo2) when
the tibia angle exceeds 90° — prevents physical collision
between leg segments. Prints a warning to Serial when a
constraint is triggered.

## Usage

1. Flash either `.ino` to your Arduino
2. Open Serial Monitor at 9600 baud
3. Enter coordinates: `100 50 -80`
4. The leg moves to that position

## Built with

C · Arduino · Servo.h · Geometric IK · PETG · MG995
