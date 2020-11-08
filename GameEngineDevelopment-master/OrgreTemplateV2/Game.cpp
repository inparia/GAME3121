/***********************************************
* Project            : Doodle Jump Game
* Author             : Joon Young Sun
* Student Number     : 101216511
* Description        : Doodle Jump Game
* Last modified      : 20/11/08
|***********************************************/

#include "Game.h"
#include "OgreRectangle2D.h"


using namespace std::chrono;

Game::Game() : OgreBites::ApplicationContext("Doodle Jump Game"){

}

Game::~Game()
{
	if (m_Root)
	{
		delete[] m_Root;
		m_Root = 0;
	}
	if (m_Rectangle)
	{
		delete[] m_Rectangle;
		m_Rectangle = 0;
	}
	if (m_FirstPlatform && m_SecondPlatform)
	{
		delete[] m_FirstPlatform;
		delete[] m_SecondPlatform;
		m_FirstPlatform = 0;
		m_SecondPlatform = 0;
	}
	if (m_Player)
	{
		delete[] m_Player;
		m_Player = 0;
	}
	if (m_TrayMgr)
	{
		delete[] m_TrayMgr;
		m_TrayMgr = 0;
	}
	
}


void Game::setup(){
	// call the base first.
	OgreBites::ApplicationContext::setup();
	
	//register for input events.
	addInputListener(this);

	//get a pointer to the already created root.
	m_Root = getRoot();
	Ogre::SceneManager* scnMgr = m_Root->createSceneManager();

	// Register our scxene with RTSS
	Ogre::RTShader::ShaderGenerator* shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(scnMgr);

	scnMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	//without light we would just get a black screen.
	Ogre::Light* light = scnMgr->createLight("Mainlight");
	Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(0, 0, 15);
	lightNode->attachObject(light);

	//need to tell where we are.
	Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 0, 20);
	camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_WORLD);
	
	
	// create the camera
	Ogre::Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	
	
	// and tell it to render into the main window
	Ogre::Viewport* vp = getRenderWindow()->addViewport(cam);


	scnMgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

	///Background Material
	m_BackgroundMaterial = Ogre::MaterialManager::getSingleton().create("Background", "General");
	m_BackgroundMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("background.png");
	m_BackgroundMaterial->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	m_BackgroundMaterial->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	m_BackgroundMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);

	//Platform Material
	m_PlatformMaterial = Ogre::MaterialManager::getSingleton().create("platform", "General");
	m_PlatformMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("platform.png");
	m_PlatformMaterial->getTechnique(0)->getPass(0)->setAlphaRejectSettings(Ogre::CMPF_GREATER_EQUAL, 128, true);
	m_PlatformMaterial->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	m_PlatformMaterial->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	m_PlatformMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(true);

	m_Rectangle = new Ogre::Rectangle2D(true);
	m_Rectangle->setCorners(-1.0, 1.0, 1.0, -1.0);
	m_Rectangle->setMaterial(m_BackgroundMaterial);

	// Render the background before everything else
	m_Rectangle->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);

	// Attach background to the scene
	m_RectangleNode = scnMgr->getRootSceneNode()->createChildSceneNode("Background");
	m_RectangleNode->attachObject(m_Rectangle);
	
	//Player Material
	m_PlayerMaterial = Ogre::MaterialManager::getSingleton().create("doodle", "Player");
	m_PlayerMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("doodle.png");
	m_PlayerMaterial->getTechnique(0)->getPass(0)->setAlphaRejectSettings(Ogre::CMPF_GREATER_EQUAL, 128, true);
	m_PlayerMaterial->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	m_PlayerMaterial->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	m_PlayerMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(true);

	// Intialize game stats.
	
	m_ThrottleFPSChange = 0;
	m_ThrottleTPUChange = 0;

	

	// Instantiate Platforms.
	Ogre::Vector3 floorPos = Ogre::Vector3(0, -5, 0);
	m_FloorPlatform = new Platform(scnMgr, floorPos, m_PlatformMaterial, 0.2, 0.003);
	
	Ogre::Vector3 paddlePos = Ogre::Vector3(0, -2, 0);
	m_FirstPlatform = new Platform(scnMgr, paddlePos, m_PlatformMaterial, 0.02, 0.003);
	
	Ogre::Vector3 paddlePos1 = Ogre::Vector3(2, 2, 0);
	m_SecondPlatform = new Platform(scnMgr, paddlePos1, m_PlatformMaterial, 0.02, 0.003);

	//Instantiate Player Character.

	Ogre::Vector3 playerPos = Ogre::Vector3(0, 0, 0);
	m_Player = new Player(scnMgr, playerPos, m_PlayerMaterial);

	m_TotalPlatforms[0] = m_FloorPlatform;
	m_TotalPlatforms[1] = m_FirstPlatform;
	m_TotalPlatforms[2] = m_SecondPlatform;
	// Instantiate game stats.

	m_TrayMgr = new OgreBites::TrayManager("UI", getRenderWindow());
	scnMgr->addRenderQueueListener(Game::getOverlaySystem());

	m_pFpsLabel = m_TrayMgr->createLabel(OgreBites::TrayLocation::TL_TOPLEFT, "FPS", "FPS:", 100);
	m_pFps = m_TrayMgr->createLabel(OgreBites::TrayLocation::TL_TOPLEFT, "fps", "59", 50);
	m_pTpuLabel = m_TrayMgr->createLabel(OgreBites::TrayLocation::TL_TOPLEFT, "Time/Update", "Time/Update:", 100);
	m_pTpu = m_TrayMgr->createLabel(OgreBites::TrayLocation::TL_TOPLEFT, "tpu", "0", 50);

	m_PlayerLabel = m_TrayMgr->createLabel(OgreBites::TrayLocation::TL_TOPRIGHT, "score", "Score: ", 100);
	m_playerScene = m_TrayMgr->createLabel(OgreBites::TrayLocation::TL_TOPRIGHT, "Score","Score: ", 100);

}

bool Game::keyPressed(const OgreBites::KeyboardEvent &evt)
{
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}

	if (evt.keysym.sym == OgreBites::SDLK_LEFT)
	{
		m_Player->MoveLeft();
	}

	if (evt.keysym.sym == OgreBites::SDLK_RIGHT)
	{
		m_Player->MoveRight();
	}

	if (evt.keysym.sym == OgreBites::SDLK_SPACE)
	{
		m_Player->Jump();
	}
	return true;
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

	m_FpsNum = 1 / evt.timeSinceLastFrame;
	m_ThrottleFPSChange++;
	if (m_ThrottleFPSChange > 240)
	{
		m_pFps->setCaption(Ogre::StringConverter::toString(m_FpsNum));
		m_ThrottleFPSChange = 0;
	}
	run();
	return true;
}


void Game::run(){
	
	update();
}

void Game::update(){

	auto start = high_resolution_clock::now();

	// update stuff
	
	m_playerScene->setCaption(Ogre::StringConverter::toString(m_PlayerScore));

	m_Player->Update();

	for (Platform* tempPlatform : m_TotalPlatforms)
	{
		if (m_Physics->AABBCheck(m_Player, tempPlatform))
		{
			m_Player->setIsFalling(false);
		}
		else
		{
			m_Player->setIsFalling(true);
		}
	}


	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	m_TpuNum = duration.count();
	m_ThrottleTPUChange++;
	if (m_ThrottleTPUChange > 240)
	{

		m_pTpu->setCaption(Ogre::StringConverter::toString(m_TpuNum));
		m_ThrottleTPUChange = 0;
	}
}


int main(int argc, char *argv[])
{
	try 
	{
		Game app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	}

	catch(const std::exception& e ) 
	{
		std::cerr << "Error occured during execution: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
