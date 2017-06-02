//
//  ofxViveTrackerOSC
//
//  Created by Yuya Hanai on 2017/06/02
//
#pragma once

#include "ofxOsc.h"

namespace ofxViveTracker
{
	// from OpenVR SDK
	// https://github.com/ValveSoftware/openvr
	enum ETrackedDeviceClass
	{
		TrackedDeviceClass_Invalid = 0,				// the ID was not valid.
		TrackedDeviceClass_HMD = 1,					// Head-Mounted Displays
		TrackedDeviceClass_Controller = 2,			// Tracked controllers
		TrackedDeviceClass_GenericTracker = 3,		// Generic trackers, similar to controllers
		TrackedDeviceClass_TrackingReference = 4,	// Camera and base stations that serve as tracking reference points
		TrackedDeviceClass_DisplayRedirect = 5,		// Accessories that aren't necessarily tracked themselves, but may redirect video output from other tracked devices
	};


	struct TrackedObject
	{
		string serial;
		ETrackedDeviceClass device_class = TrackedDeviceClass_Invalid;
		bool b_tracked = false;
		ofMatrix4x4 pose;
		int lost_count = 0;
	};

	class OSC : public ofxOscReceiver
	{
		map<string, TrackedObject> objects;
		float scale = 100;
	public:
		OSC();

		void update();

		void debugDraw() const;

		const map<string, TrackedObject>& getTrackedObjects() const { return objects; }
		vector<TrackedObject> getGenericTrackers() const;

		void setScale(float f) { scale = f; }
		float getScale() const { return scale;  }
	};
}

