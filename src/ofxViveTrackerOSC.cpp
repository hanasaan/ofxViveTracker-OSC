//
//  ofxViveTrackerOSC
//
//  Created by Yuya Hanai on 2017/06/02
//

#include "ofxViveTrackerOSC.h"

namespace ofxViveTracker
{
	OSC::OSC()
	{

	}

	void OSC::update()
	{
		for (auto& obj : objects) {
			obj.second.lost_count++;
			if (obj.second.lost_count > 2) {
				obj.second.b_tracked = false;
			}
		}
		while (hasWaitingMessages()) {
			ofxOscMessage m;
			if (getNextMessage(m) && m.getAddress() == "/vive") {
				auto serial = m.getArgAsString(0);
				auto& obj = objects[serial];
				obj.device_class = (ETrackedDeviceClass) m.getArgAsInt(1);
				obj.serial = serial;
				obj.b_tracked = true;
				obj.lost_count = 0;
				obj.pose.set(
					m.getArgAsFloat(2), m.getArgAsFloat(3), m.getArgAsFloat(4), 0,
					m.getArgAsFloat(5), m.getArgAsFloat(6), m.getArgAsFloat(7), 0,
					m.getArgAsFloat(8), m.getArgAsFloat(9), m.getArgAsFloat(10), 0,
					m.getArgAsFloat(11) * scale, m.getArgAsFloat(12) * scale, m.getArgAsFloat(13) * scale, 1);
			}
		}
	}
	void OSC::debugDraw() const
	{
		ofPushStyle();
		for (const auto& obj : objects) {
			ofPushMatrix();
			ofMultMatrix(obj.second.pose);
			if (obj.second.b_tracked) {
				ofSetColor(0, 255, 0);
			} else {
				ofSetColor(255, 0, 0);
			}
			ofDrawBitmapString(ofToString(obj.second.device_class) + ":" + obj.second.serial, ofVec3f());
			ofSetColor(255);
			ofDrawAxis(10);
			ofPopMatrix();
		}
		ofPopStyle();
	}
	vector<TrackedObject> OSC::getGenericTrackers() const
	{
		vector<TrackedObject> objs;
		
		for (const auto& obj : objects) {
			if (obj.second.device_class == TrackedDeviceClass_GenericTracker) {
				objs.emplace_back(obj.second);
			}
		}
		return objs;
	}
}
