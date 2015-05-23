#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <cmath>

#include <boost/lexical_cast.hpp>

//some useful constants
const double PI                 = 3.1415926535;

const double TO_RAD             = 0.0174532925;
const double TO_DEG             = 57.295779513;

const double TO_PXL             = 30.0;
const double TO_MTR             = 1.0f / TO_PXL;

//functions
//convert types
template<typename T1, typename T2>
T1 convert(T2 t2)
{
    return boost::lexical_cast<T1> (t2);
}

enum game_state{null_state, menu, play, pause_state, level_win, game_over, quit};
enum button_state{button_general, button_select, button_down};
enum shape{rectangle, circle, triangle};
enum type{static_body, kinematic_body, dynamic_body};

#endif // GLOBALS_HPP
