Fancy Mouse Jiggler
==========
This small Arduino sketch implements a full-featured mouse jiggler to keep a computer awake and active without installing any software on the host, instead utilizing the host's USB HID features. 

Features
----------
-    Power saving. Some chip features not in use are powered down.
-    A proper task scheduler. We sleep using a task scheduler when there's nothing to do.
-    Visual feedback using LED when plugged in and during mouse movement activity. 
-    Watchdog timer automatically resets the device in case of error.
-    Tiny mouse movements do not disturb normal mouse usage (at least not on my system).
-    Dead simple with easy reconfiguration to suit your mouse jiggling needs.

Requirements
----------
-    Arduino Leonardo (I use a mini beetle version with built-in USB connector for ultra-compact design)
-    Arduino software to build and upload the code.
-    May work on other Arduinos that don't use a separate USB chip. 

Dependencies
----------
-    Arduino standard libs.
-    TaskScheduler
