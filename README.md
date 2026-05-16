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
| Screws | M4 × 20mm hex socket cap screws (Allen head) |

## Link lengths

| Segment | Length |
|---------|--------|
| Coaxial (l) | 50 mm |
| Femur (a) | 100 mm |
| Tibia (b) | 150 mm |

## Repository structure

hexapod-ik/
├── CAD/
│   ├── Connector_to_body.stl
│   ├── Connector_to_Servo2.stl
│   ├── Foot.stl
│   ├── Joint_1_to_2.stl
│   ├── Joint_2_to_3.stl
│   ├── Torque_1_to_2.stl
│   ├── Torque_2_to_3.stl
│   └── Assembly.stl
├── Arduino/
│   ├── InverseKinematics.ino
│   ├── InverseKinematicsConst.ino
│   └── ServoSweepTest.ino
└── README.md

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
| `Assembly.stl` | Full assembled leg — shows how all parts fit together and what the finished leg should look like |

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

### `ServoSweepTest.ino`
Calibration and testing utility. Sweeps all three servos
smoothly through their full range of motion (min → max → min)
in a continuous loop. Use this to verify that all servos are
correctly wired and that the leg moves freely through its
full range without mechanical interference. Set `set_pos = 0`
to park all servos at 90° (neutral) for assembly alignment.

## Assembly notes

Most fasteners are M4 × 20mm hex socket cap screws (Allen head).
Have an M4 Allen key available before assembly. The PETG parts
are designed to accept the screws directly — no inserts required.

## Usage

1. Flash either `.ino` to your Arduino
2. Open Serial Monitor at 9600 baud
3. Enter coordinates: `100 50 -80`
4. The leg moves to that position

## Built with

C · Arduino · Servo.h · Geometric IK · PETG · MG995
