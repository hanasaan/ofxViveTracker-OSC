# ofxViveTracker-OSC
I wanna use vive tracker as rigid body.

- Python OSC client streams Vive trackers' transforms.
- It might be simpler than using ofxOpenVR if you do not want to use Vive as HMD...

### How to Use
- Tested on Windows 10 only.
- Setup HTC Vive.
- Install [Anaconda Package](https://www.anaconda.com/products/individual) for Python 3.6
  - Although this addon does not depend on [triad_openvr](https://github.com/TriadSemi/triad_openvr), [this instruction](http://www.roadtovr.com/how-to-use-the-htc-vive-tracker-without-a-vive-headset/) is also applicable to disable HMD requirement, 
```
pip install openvr
pip install python-osc
```
- Run Anaconda Prompt and go to ```ofxViveTracker-OSC/client``` directory, then
```
python vivetracker_osc.py --host [HOST] --port [PORT] --fps [FPS]
```

### Tested Environment
- OF0.9.8 + VS2015 on Windows 10
