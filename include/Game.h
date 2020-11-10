#ifndef GAME_H_
#define GAME_H_

#include <ngl/Transformation.h>
#include <SDL2/SDL.h>
#include <ngl/Obj.h>
#include <list>
#include <memory>
#include "Rocket.h"
#include "StarMap.h"

class Game
{
  public :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor this will have a valid OpenGL context so we can create gl stuff
    //----------------------------------------------------------------------------------------------------------------------
    Game();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor used to remove any NGL stuff created
    //----------------------------------------------------------------------------------------------------------------------
    ~Game();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief resize our screen and set the camera aspect ratio
    /// @param[in] _w the new width
    /// @param[in] _h the new height
    //----------------------------------------------------------------------------------------------------------------------
    void resize(int _w, int _h);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draw the scene
    //----------------------------------------------------------------------------------------------------------------------
    void draw();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief move the ship by offset _dx/y/z
    /// @param [in] _dx the cange in x
    /// @param [in] _dy the cange in y
    /// @param [in] _dz the cange in z
    //----------------------------------------------------------------------------------------------------------------------
    void move(float _dx, float _dy, float _dz);

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief reset the ship to the origin
    //----------------------------------------------------------------------------------------------------------------------
    inline void resetPosition(){m_modelPos.set(0,0,0); }
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief fire rockets from the left
    /// @param[in] _speed the velocity of the rocket
    //----------------------------------------------------------------------------------------------------------------------
    void fireLeft(float _speed);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief fire rockets from the right
    /// @param[in] _speed the velocity of the rocket
    //----------------------------------------------------------------------------------------------------------------------
    void fireRight(float _speed);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this updates the rocket list and removes any dead ones
    //----------------------------------------------------------------------------------------------------------------------
    void update();


  private :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief method to load transform data to the shaders
    //----------------------------------------------------------------------------------------------------------------------
    void loadMatricesToShader();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Our Camera
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Mat4 m_view;
    ngl::Mat4 m_project;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief transformation stack for the gl transformations etc
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Transformation m_transform;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the model position for mouse movement
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 m_modelPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the spaceship model
    //----------------------------------------------------------------------------------------------------------------------
    std::shared_ptr<ngl::Obj> m_shipMesh;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the rocket model
    //----------------------------------------------------------------------------------------------------------------------
    std::shared_ptr<ngl::Obj> m_rocket;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief max rockets to be fired
    //----------------------------------------------------------------------------------------------------------------------
    size_t m_maxRockets;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief max rockets to be fired
    //----------------------------------------------------------------------------------------------------------------------
    size_t m_activeRockets;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief our rocket list we use a list so we can use some algorithms
    //----------------------------------------------------------------------------------------------------------------------
    std::vector <std::unique_ptr<Rocket>> m_rockets;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief starmap
    //----------------------------------------------------------------------------------------------------------------------
    std::unique_ptr<StarMap>m_starmap;


};


#endif
