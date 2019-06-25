#include "Game.h"
#include <ngl/ShaderLib.h>
#include <ngl/NGLInit.h>
#include <algorithm>

Game::Game()
{
  ngl::NGLInit::instance();
  m_maxRockets=200;
  m_activeRockets=0;
  // Now set the initial GLWindow attributes to default values
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);


  // now to load the shader and set the values
  // grab an instance of shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  // we are creating a shader called Texture
  shader->createShaderProgram("Texture");
  // now we are going to create empty shaders for Frag and Vert
  shader->attachShader("TextureVertex",ngl::ShaderType::VERTEX);
  shader->attachShader("TextureFragment",ngl::ShaderType::FRAGMENT);
  // attach the source
  shader->loadShaderSource("TextureVertex","shaders/TextureVertex.glsl");
  shader->loadShaderSource("TextureFragment","shaders/TextureFragment.glsl");
  // compile the shaders
  shader->compileShader("TextureVertex");
  shader->compileShader("TextureFragment");
  // add them to the program
  shader->attachShaderToProgram("Texture","TextureVertex");
  shader->attachShaderToProgram("Texture","TextureFragment");

  // now we have associated this data we can link the shader
  shader->linkProgramObject("Texture");
  // and make it active ready to load values
  (*shader)["Texture"]->use();
  // Now we will create a basic Camera from the graphics library
  // This is a static camera so it only needs to be set once
  // First create Values for the camera position
  ngl::Vec3 from(0,0,30);
  ngl::Vec3 to(0,0,0);
  ngl::Vec3 up(0,1,0);
  // now load to our new camera
  m_view=ngl::lookAt(from,to,up);
  // set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10
  m_project=ngl::perspective(45.0f,720.0f/576.0f,0.05f,350.0f);
  m_shipMesh = std::make_unique<ngl::Obj>("models/SpaceShip.obj","textures/spaceship.bmp");
  m_shipMesh->createVAO();

  m_rocket = std::make_unique<ngl::Obj>("models/rocket.obj","textures/rockets.bmp");
  m_rocket->createVAO();
  m_starmap = std::make_unique<StarMap>("textures/starmap.png","textures/PlanetMap.tif",m_view,m_project);


}

Game::~Game()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void Game::resize(int _w, int _h)
{
  glViewport(0,0,_w,_h);
  // now set the camera size values as the screen size has changed
  m_project=ngl::perspective(45,static_cast<float>(_w)/_h,0.05f,350.0f);
}

void Game::move(float _dx, float _dy, float _dz)
{
  m_modelPos.m_x+=_dx;
  m_modelPos.m_y+=_dy;
  m_modelPos.m_z+=_dz;
}

void Game::draw()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // grab an instance of the shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["Texture"]->use();

  // Rotation based on the mouse position for our global transform
  m_transform.reset();
  {
    m_transform.setPosition(m_modelPos);
    m_transform.setRotation(0,-90,0);
    loadMatricesToShader();
    m_shipMesh->draw();
  }
  m_transform.reset();
  {
    m_transform.setPosition(m_modelPos);

    m_transform.addPosition(-5,-0.6f,2);
    m_transform.setRotation(0,-90,0);
    loadMatricesToShader();
    m_rocket->draw();
  }
  m_transform.reset();
  {
    m_transform.setPosition(m_modelPos);

    m_transform.addPosition(5.0f,-0.6f,2.0f);
    m_transform.setRotation(0.0f,-90.0f,0.0f);
    loadMatricesToShader();
    m_rocket->draw();
  }

  // now draw the rockets
  for(auto &rocket : m_rockets)
  {
    rocket->draw();
  }
  m_starmap->draw();

}


void Game::update()
{
  for(auto &rocket : m_rockets)
  {
    rocket->update();
  }
  // now check the list and call the isActive method and remove if false

 // std::remove_if(std::begin(m_rockets),std::end(m_rockets),std::not1(std::mem_fun(&Rocket::isActive)));
  // update the size of the active rockets
  m_activeRockets=m_rockets.size();
}

void Game::fireLeft(float _speed)
{
  if( m_activeRockets !=m_maxRockets )
  {
    ngl::Vec3 p=m_modelPos;
    p.m_x+=-5.0f;
    p.m_y+=-0.6f;
    p.m_z+=2.0f;
    m_rockets.emplace_back(std::make_unique<Rocket>(p,_speed,m_rocket,m_view,m_project));
    ++m_activeRockets;
  }
}

void Game::fireRight(float _speed)
{
  if( m_activeRockets !=m_maxRockets )
  {
    ngl::Vec3 p=m_modelPos;
    p.m_x+=5;
    p.m_y+=-0.6f;
    p.m_z+=2;
    m_rockets.emplace_back(std::make_unique<Rocket>(p,_speed,m_rocket,m_view,m_project));
    ++m_activeRockets;
  }

}

void Game::loadMatricesToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  ngl::Mat4 MVP;
  MVP= m_project*m_view*m_transform.getMatrix();
  shader->setUniform("MVP",MVP);
}
