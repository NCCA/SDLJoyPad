#include "StarMap.h"
#include <ngl/VAOPrimitives.h>
#include <ngl/Texture.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
StarMap::StarMap(std::string _texture, std::string _texture2, const ngl::Mat4 &_view, const ngl::Mat4 &_project) :
  m_view(_view),m_project(_project)
{

  ngl::Texture t(_texture);
  m_texID=t.setTextureGL();
  ngl::Texture t2(_texture2);
  m_texID2=t2.setTextureGL();

  ngl::VAOPrimitives::createSphere("starmap",300,20);
}

void StarMap::draw()
{
  static float rot=0.0;

  glEnable (GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  ngl::ShaderLib::use("Texture");
  ngl::Transformation t;
  t.setRotation(rot,0,0);
  rot+=0.01f;
  ngl::Mat4 MVP;

  MVP=m_project*m_view*t.getMatrix();
  ngl::ShaderLib::setUniform("MVP",MVP);
  glBindTexture(GL_TEXTURE_2D,m_texID);
  ngl::VAOPrimitives::draw("starmap");

  t.setRotation(0,rot*8,0);
  t.setScale(0.91f,0.91f,0.91f);
  glBindTexture(GL_TEXTURE_2D,m_texID2);

  MVP=m_project*m_view*t.getMatrix();
  ngl::ShaderLib::setUniform("MVP",MVP);
  ngl::VAOPrimitives::draw("starmap");
  glDisable(GL_BLEND);

}
