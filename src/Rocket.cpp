#include "Rocket.h"
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>

Rocket::Rocket(const ngl::Vec3 &_startPos, float _speed, std::shared_ptr<ngl::Obj>_mesh,  const ngl::Mat4 &_view,  const ngl::Mat4 &_project):
m_view(_view),m_project(_project)
{
  m_pos=_startPos;
  m_life=0;
  m_mesh=_mesh;
  m_speed=_speed;
  m_active=true;
  m_maxLife=60;
}

void Rocket::update()
{
  m_pos.m_z-=m_speed;
  if(++m_life >= m_maxLife)
  {
    m_active=false;
  }
}

void Rocket::draw() const
{
  // grab an instance of the shader manager
  ngl::ShaderLib::use("Texture");
  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat4 M;
  ngl::Transformation t;
  t.setPosition(m_pos);
  t.setRotation(0,-90,0);
  MVP= m_project*m_view*t.getMatrix();
  ngl::ShaderLib::setUniform("MVP",MVP);
  m_mesh->draw();
}
