#include "GameEngine.h"
#include "Stage.h"

using namespace Ogre;




/*

void AIEngine::runTo(DEPSprite* spr, float theta){
	float radians = theta * 3.14159f / 180.0f; //使用於sin & cos 函數
	spr->x +=  spr->getVelocityX()*cos(radians);
	spr->y +=  spr->getVelocityY()*sin(radians); 
}

*/


/*

void StageControl::setBulletDestination(GUN *gun, float destx, float desty){
	float distanceX;
	float distanceY;
	float x, y;
	float theta;
	Bullet* bullet;
	int i;
	for(i = 0; i < gun->getBulletAmount(); i++){
		bullet = gun->getBullet(i);
		x = bullet->x;
		y = bullet->y;
	    distanceX = destx - x;
		distanceY = desty - y;
		if( distanceX == 0.0 ) {distanceX = 1;};
		theta = (atan(distanceY/distanceX) * 180.0f) / 3.14159f;   //nway
		if( distanceX >= 0 && theta >= 0 ) {theta = theta ;};//1
		if( distanceX <= 0 && theta >= 0 ) {theta =  theta + 180.0f;};//2
		if( distanceX >= 0 && theta <= 0 ) {theta =  theta + 360.0f;};//4
		if( distanceX <= 0 && theta <= 0 ) {theta =  theta + 180.0f;};//3
		bullet->setDirection(theta);
	}
	
}*/

/*
void ThetaBullet::run(){
	dt += hge->Timer_GetDelta();
	radians = theta * PI / 180.0f; //使用於sin & cos 函數
	
	y +=  speed *sin(radians); 
	x +=  speed *cos(radians);

}*/

/*
x = radius * cos(angle)
y = radius * sin(angle)

angle = atan(y/x)
radius = sqrt(x*x+y*y)  

atan : 反正切
sqrt : 平方根值

帶入以上公式即可作兩個座標系之轉換
*/


//沒有目標，沒辦法決定方向，因此用極座標來決定

void Stage1::chooseScene(){
	Stage::chooseScene();
	if(mSceneMgr == NULL){
		mSceneMgr = mEngine->mRoot->createSceneManager(Ogre::ST_EXTERIOR_CLOSE, "primary");
	}
}


bool Stage1::doLoadingScript(){
	Stage::doLoadingScript();
	cout << "loading Stage1" << endl;
	this->mScriptMode = SM_BATTLE;
	//this->mScriptMode = SM_STORY;
	this->mEngine->enableDefaultInput(true);
	mTime = 0;
	return true;
}


bool Stage1::doBattleScript(){
	Stage::doBattleScript();

	environment();
	//cout << "Stage1 BATTLE" << endl;
	//cout << "stage1 battle" << endl;

	Ogre::Vector3 pos = mPlayerSpr->getPosition();
	//gScreenText.print(0.1, 0.05, "Position:%.0f ,%.0f, %.0f", pos.x, pos.y, pos.z);

	if(mTime < 4){
		static float alpha = 1;
		gScreenText.setColour(ColourValue(1, 1, 1, alpha));
		gScreenText.print(0.4, 0.3, 2, L"Stage1: 危機！");
		alpha -= evt.timeSinceLastFrame * 0.1;
	}

	if(mTime > 3 && mTime < 24){
		bool triggerFlg = true;
		for(int i = 0; i < 3; i++){
			String name;
			genNameUsingIndex("robot", i, name);
			Sprite3D* p = mMonsterMgr->getSprite(name);
			if(p){
				if(p->isAlive()){
					triggerFlg = false;
				}

			}
		}

		if(triggerFlg){
			setEvent1();
		}

	}


	//=======================================



	if((int)mTime == 5){
		setEvent2();
	}





	if((int)mTime == 10){
		setEvent3();
	}


	if((int)mTime == 20){
		setEvent4();
	}


	
	if((int)mTime == 30){
		setEvent5();
	}


	if((int)mTime == 35){
		setEvent6();
		
	}


	if(mTime > 40 && mTime < 45){
		static float alpha = 1;
		gScreenText.setColour(ColourValue(1, 0, 0, alpha));
		gScreenText.print(0.4, 0.1, 2, L"警告!警告! 敵人主力即將出現!");
		alpha -= evt.timeSinceLastFrame;
	}





	//==============boss=======================
	
	if((int)mTime == 50){
		setEvent7();
	}

	


	doEvent1(); //robot
	doEvent2(); //fish
	doEvent3(); //penguin
	doEvent4(); //ogrehead
	doEvent5(); //penguin2
	doEvent6(); //ogrehead2



	
	if(mTime > 50){
		Sprite3D* p = mMonsterMgr->getSprite("boss1");
		if(p){
			if(p->getHealth() >= 1400){
				doEvent7();

			}

		}
		

	}


	if(mTime > 50){
		Sprite3D* p = mMonsterMgr->getSprite("boss1");
		if(p){
			if(p->getHealth() >= 1200 && p->getHealth() < 1400){
				doEvent8();
			}
		}

	}

	
	if(mTime > 50){
		Sprite3D* p = mMonsterMgr->getSprite("boss1");
		if(p){
			if(p->getHealth() >= 600 && p->getHealth() < 1200){
				doEvent9();
				
			}
		}

	}


	if(mTime > 50){
		Sprite3D* p = mMonsterMgr->getSprite("boss1");
		if(p){
			if(p->getHealth() < 600){
				doEvent10();
				
			}
		}

	}


	if(mTime > 50){
		Sprite3D* p = mMonsterMgr->getSprite("boss1");
		if(p){
			if(!p->isAlive()){
				mEngine->mFaderMap["stage1_win"]->startFadeOut(10, 1, 0);
				mScriptMode = SM_GAME_WIN;
			}
		}
	
	}


	/*if((int)mTime == 5){
		setEvent2();
		//mTime++;
	}
	doEvent2();


	if((int)mTime == 2){
		setEvent3();
		mTime++;
	}
	doEvent3();*/
	return true;

}


bool Stage1::doStoryScript(){
	Stage::doStoryScript();

	if(mTime == 0){
	}

	if(mTime == 1){

	//	gScreenText.print(0.2, 0.2, "good luck!");
	
	
	}
	return true;

}



bool Stage1::doGameWinScript(){
	bool faderRunning = mEngine->mFaderMap["stage1_win"]->fade(evt.timeSinceLastFrame);


	if(mPlayerSpr){
		mPlayerSpr->update(evt);
	}
	mParticleMgr->update(evt);

	return true;

}

bool Stage1::doFinishScript(){
	Stage::doFinishScript();
	cout << "do stage1 finish" << endl;
	mEngine->mFaderMap["stage1_win"]->hide();
	mEngine->currentStage = mEngine->mStages[2];
	return true;

}