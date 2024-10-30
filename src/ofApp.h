#pragma once

#include "ofMain.h"
#include "particle.hpp";
#include "vector"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//std::unique_ptr<BaseParticle> arr[40][40];
		vector < vector<std::unique_ptr<BaseParticle>>> v;
		vector<std::unique_ptr<BaseParticle>> v1;
		//vector<BaseParticle*> v1;
		//BaseParticle *p = new Sand()
		//vector < vector<bool*>> v;
		
};
