# Multple Queues Added

Single Consumers, Multiple Producers
1. `MotorQueue`
2. `SerialQueue`

| Task | Queue | Producer/Consumer |
|------|-------|--------|
| Accelerometer | SerialQueue | Producer |
|  | PositionQueue | Producer |
| Current Sensor | MotorQueue | Producer |
|   | SerialQueue | Producer (DEBUG ONLY) |
| Offset Encoder | PositionQueue | Producer |
|  | SerialQueue | Producer |
| Serial Port | SerialQueue | Consumer |
| Motor | MotorQueue | Consumer |
| PID | MotorQueue | Producer |
|  | PositionQueue | Consumer |
|  | SerialQueue | Producer (DEBUG ONLY) |
