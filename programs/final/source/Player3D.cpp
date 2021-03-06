#include "Player3D.h"
#include "Stage.h"
#include "Weapon3D.h"


Player3D::Player3D(Stage *stage): Sprite3D(stage){
}


void Player3D::walkLeft(const Ogre::FrameEvent& evt){
	Ogre::Camera* mCamera = mStage->mSceneMgr->getCamera("playerCam");
	mDirection = mCamera->getRealDirection();

	Ogre::Vector3 direction = rotateY(mDirection, -90);
	Ogre::Vector3 d = direction * mVelocity * evt.timeSinceLastFrame;
	mSceneNode->translate(d);

	Ogre::Vector3 pos = mSceneNode->getPosition();

	bool flgPos = mStage->projectScenePointOntoTerrain_PosDirection(pos);

	if(flgPos){
		mSceneNode->setPosition(pos + d);
	} 		

	if(flgPos){
		Ogre::Vector3 e = mDirection * 20;
		mCamera->setPosition(pos+mEyePosition+e);
	}


	
}

void Player3D::walkRight(const Ogre::FrameEvent& evt){

	Ogre::Camera* mCamera = mStage->mSceneMgr->getCamera("playerCam");

	mDirection = mCamera->getRealDirection();
	Ogre::Vector3 direction = rotateY(mDirection, 90);
	Ogre::Vector3 d =  direction * mVelocity * evt.timeSinceLastFrame;
	mSceneNode->translate(d);

	Ogre::Vector3 pos = mSceneNode->getPosition();
	bool flgPos = mStage->projectScenePointOntoTerrain_PosDirection(pos);

	if(flgPos){
		mSceneNode->setPosition(pos + d);
	} 		

	
	if(flgPos){
		Ogre::Vector3 e = direction * 20;
		mCamera->setPosition(pos+mEyePosition+e);
	}

}

void Player3D::walkForward(const Ogre::FrameEvent& evt){
	
	Ogre::Camera* mCamera = mStage->mSceneMgr->getCamera("playerCam");

	mDirection = mCamera->getRealDirection();
	Ogre::Vector3 direction = mDirection;
	direction.y = 0;
	Ogre::Vector3 d = direction * mVelocity * evt.timeSinceLastFrame;
	mSceneNode->translate(d);

	Ogre::Vector3 pos = mSceneNode->getPosition();

	bool flgPos = mStage->projectScenePointOntoTerrain_PosDirection(pos);

	if(flgPos){
		mSceneNode->setPosition(pos + d);
	} 		


	if(flgPos){
		Ogre::Vector3 e = direction * 20;
		mCamera->setPosition(pos+mEyePosition+e);
	}
}



void Player3D::walkBackward(const Ogre::FrameEvent& evt){
	Ogre::Camera* mCamera = mStage->mSceneMgr->getCamera("playerCam");

	mDirection = mCamera->getRealDirection();
	Ogre::Vector3 d = mDirection * mVelocity *evt.timeSinceLastFrame;
	mSceneNode->translate(-d);
	Ogre::Vector3 pos = mSceneNode->getPosition();

	bool flgPos = this->mStage->projectScenePointOntoTerrain_PosDirection(pos);

	if(flgPos){
		mSceneNode->setPosition(pos);
	}


	if(flgPos){
		Ogre::Vector3 e = mDirection*20;
		mCamera->setPosition(pos+mEyePosition+e);
	}
}



void Player3D::update(const Ogre::FrameEvent& evt){
	Sprite3D::update(evt);


	//cout << mJumpForce << endl;

	
}




void Player3D::updateViewDirection(Camera* camera, Ogre::Vector3 direction, Ogre::Vector3 offset, Ogre::Radian yawRadian){
	if(mSceneNode){
		Ogre::Vector3 p = mSceneNode->getPosition();

		mSceneNode->lookAt(p - direction*10, Node::TS_WORLD);
		//mSceneNode->yaw(Radian(-3.14159*0.5));
		Ogre::Vector3 e = direction * 20;

		//Ogre::Vector3 offset(100, 0, 100);
		offset = offset * -direction;//camera永遠在player的後面
		camera->setPosition(p+ mEyePosition + e + offset);
		mSceneNode->yaw(yawRadian);//model的方向轉
		
	}
}








