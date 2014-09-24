#ifndef STARMAP_H__
#define STARMAP_H__

#include <ngl/Camera.h>
#include <string>

class StarMap
{
  public :
    StarMap(std::string _texture,std::string _texture2, ngl::Camera *_cam);
    ~StarMap();
    void draw();
  private :
    GLuint m_texID;
    GLuint m_texID2;
    ngl::Camera *m_camera;
};

#endif
