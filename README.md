# overkill_interceptor
CAN BUS interception infrastructure for teensy

This was me messing around with cpp maps for the purpose of working with a long list of CANBUS signals and messages in order to intercept and modify particular signals.  I wanted the ease of use of openpilot canbus interception implemented in cpp for the teensy. Never ended up using this since it became overkill for my purposes and I didn't realize that in dbc format you can have multiple signals with the same name on a different address. So in order to use this you would need to add another pair in the signal maps.
