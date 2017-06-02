import openvr
import time
import sys
import argparse
from pythonosc import osc_message_builder
from pythonosc import udp_client

# Initialize OpenVR in the 
vr = openvr.init(openvr.VRApplication_Other)

parser = argparse.ArgumentParser()
parser.add_argument("--ip", default="127.0.0.1", help="The ip of the OSC server")
parser.add_argument("--port", type=int, default=5005, help="The port the OSC server is listening on")
parser.add_argument("--fps", type=int, default=60, help="Target FPS")
args = parser.parse_args()
client = udp_client.SimpleUDPClient(args.ip, args.port)
interval = 1.0/args.fps
 
print("OSC client is set to {0}:{1} at {2} fps".format(args.ip, args.port, args.fps))

if interval:
	while(True):
		start = time.time()
		sleep_time = interval-(time.time()-start)
		poses = vr.getDeviceToAbsoluteTrackingPose(openvr.TrackingUniverseStanding, 0, openvr.k_unMaxTrackedDeviceCount)
		for i in range(openvr.k_unMaxTrackedDeviceCount):
			if poses[i].bPoseIsValid:
				device_class = vr.getTrackedDeviceClass(i)
				serial = vr.getStringTrackedDeviceProperty(i, openvr.Prop_SerialNumber_String).decode('utf-8')
				m = poses[i].mDeviceToAbsoluteTracking
				values = [serial, int(device_class),  
							m[0][0], m[1][0], m[2][0], 
							m[0][1], m[1][1], m[2][1],
							m[0][2], m[1][2], m[2][2],  
							m[0][3], m[1][3], m[2][3]  
							]
				client.send_message("/vive", values)
		print("\r{0}".format(start), end="")
		if sleep_time>0:
			time.sleep(sleep_time)
