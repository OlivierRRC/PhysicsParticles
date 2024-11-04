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

		void resizeVector();
		void placeParticle(int x, int y, int button);
		void gatherNeighbours(int x, int y);

		bool shiftDown = false;

		vector<vector<std::shared_ptr<BaseParticle>>> v;

		glm::vec2 windowSize;

		ofSoundPlayer bgMusic;

		int unitSize = 10;
		
};
