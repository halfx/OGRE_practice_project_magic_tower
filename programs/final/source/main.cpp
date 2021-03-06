#include "GameEngine.h"
#include "Stage.h"



GameEngine::GameEngine(void) {
	this->mTotalScore = 0;
	this->enableDefaultInput(true);
	mStages.push_back(new Introduction(this));
	mStages.push_back(new Stage1(this));
	mStages.push_back(new Stage2(this));
	mStages.push_back(new Stage3(this));
	mStages.push_back(new Title(this));
	currentStage = mStages[4];
}



//int main(int argc, char *argv[]) {

int WINAPI WinMain(HINSTANCE hinstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   int nCmdShow){

	GameEngine app;
	app.go();
	return 0;
}
