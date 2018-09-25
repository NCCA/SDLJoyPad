#ifndef STARMAP_H_
#define STARMAP_H_
#include <ngl/Mat4.h>
#include <string>

class StarMap
{
  public :
    StarMap(std::string _texture,std::string _texture2, const ngl::Mat4 &_view, const ngl::Mat4 &_project);
    ~StarMap()=default;
    void draw();
  private :
    GLuint m_texID;
    GLuint m_texID2;
    const ngl::Mat4 &m_view;
    const ngl::Mat4 &m_project;
};

#endif
