/***********************************************
* Project            : Doodle Jump Game
* Author             : Joon Young Sun
* Student Number     : 101216511
* Description        : Doodle Jump Game
* Last modified      : 20/11/08
|***********************************************/

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreFont.h"
#include "OgreTrays.h"
#include <iostream>
#include <string>
#include "Platform.h"
#include "Player.h"
#include "Physics.h"


class Game : public OgreBites::ApplicationContext, public OgreBites::InputListener {

private: 

    int m_FpsNum;
    int m_ThrottleFPSChange;
    int m_ThrottleTPUChange;
    int m_TpuNum;
    int m_PlayerScore = 0;

    Ogre::Root* m_Root;
   
    OgreBites::TrayManager* m_TrayMgr;
    OgreBites::TrayListener m_MyTrayListener;

    //Labels and Fps
    OgreBites::Label* m_pTpuLabel;
    OgreBites::Label* m_pTpu;
    OgreBites::Label* m_pFpsLabel;
    OgreBites::Label* m_pFps; 
    OgreBites::Label* m_PlayerLabel;
    OgreBites::Label* m_playerScene;


    //Rectangle Nodes
    Ogre::Rectangle2D* m_Rectangle;
    Ogre::SceneNode* m_RectangleNode;

    //Player
    Player* m_Player;

    //Platforms
    Platform* m_FloorPlatform;
    Platform* m_FirstPlatform;
    Platform* m_SecondPlatform;
    Platform* m_TotalPlatforms[3];

    //Materials
    Ogre::MaterialPtr m_BackgroundMaterial;
    Ogre::MaterialPtr m_PlayerMaterial;
    Ogre::MaterialPtr m_PlatformMaterial;

    //Physics
    Physics* m_Physics;


public:
    Game();
    ~Game();
   // virtual ~Game() {}


    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    void run();
    void update();
};
