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
