#pragma once
#include "Defines.h"

namespace NDR
{
    typedef int NDRButtonAction;
    
    typedef int NDRMouseButton;
    typedef int NDRKey;
}

// from glfw3.h
#define NDR_BUTTON_DOWN             GLFW_PRESS
#define NDR_BUTTON_UP               GLFW_RELEASE

#define NDR_MOUSEBUTTON_LEFT        GLFW_MOUSE_BUTTON_LEFT
#define NDR_MOUSEBUTTON_RIGHT       GLFW_MOUSE_BUTTON_RIGHT
#define NDR_MOUSEBUTTON_MIDDLE      GLFW_MOUSE_BUTTON_MIDDLE

/* The unknown key */
#define NDR_KEY_UNKNOWN            -1

/* Printable keys */
#define NDR_KEY_SPACE              32
#define NDR_KEY_APOSTROPHE         39  /* ' */
#define NDR_KEY_COMMA              44  /* , */
#define NDR_KEY_MINUS              45  /* - */
#define NDR_KEY_PERIOD             46  /* . */
#define NDR_KEY_SLASH              47  /* / */
#define NDR_KEY_0                  48
#define NDR_KEY_1                  49
#define NDR_KEY_2                  50
#define NDR_KEY_3                  51
#define NDR_KEY_4                  52
#define NDR_KEY_5                  53
#define NDR_KEY_6                  54
#define NDR_KEY_7                  55
#define NDR_KEY_8                  56
#define NDR_KEY_9                  57
#define NDR_KEY_SEMICOLON          59  /* ; */
#define NDR_KEY_EQUAL              61  /* = */
#define NDR_KEY_A                  65
#define NDR_KEY_B                  66
#define NDR_KEY_C                  67
#define NDR_KEY_D                  68
#define NDR_KEY_E                  69
#define NDR_KEY_F                  70
#define NDR_KEY_G                  71
#define NDR_KEY_H                  72
#define NDR_KEY_I                  73
#define NDR_KEY_J                  74
#define NDR_KEY_K                  75
#define NDR_KEY_L                  76
#define NDR_KEY_M                  77
#define NDR_KEY_N                  78
#define NDR_KEY_O                  79
#define NDR_KEY_P                  80
#define NDR_KEY_Q                  81
#define NDR_KEY_R                  82
#define NDR_KEY_S                  83
#define NDR_KEY_T                  84
#define NDR_KEY_U                  85
#define NDR_KEY_V                  86
#define NDR_KEY_W                  87
#define NDR_KEY_X                  88
#define NDR_KEY_Y                  89
#define NDR_KEY_Z                  90
#define NDR_KEY_LEFT_BRACKET       91  /* [ */
#define NDR_KEY_BACKSLASH          92  /* \ */
#define NDR_KEY_RIGHT_BRACKET      93  /* ] */
#define NDR_KEY_GRAVE_ACCENT       96  /* ` */
#define NDR_KEY_WORLD_1            161 /* non-US #1 */
#define NDR_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define NDR_KEY_ESCAPE             256
#define NDR_KEY_ENTER              257
#define NDR_KEY_TAB                258
#define NDR_KEY_BACKSPACE          259
#define NDR_KEY_INSERT             260
#define NDR_KEY_DELETE             261
#define NDR_KEY_RIGHT              262
#define NDR_KEY_LEFT               263
#define NDR_KEY_DOWN               264
#define NDR_KEY_UP                 265
#define NDR_KEY_PAGE_UP            266
#define NDR_KEY_PAGE_DOWN          267
#define NDR_KEY_HOME               268
#define NDR_KEY_END                269
#define NDR_KEY_CAPS_LOCK          280
#define NDR_KEY_SCROLL_LOCK        281
#define NDR_KEY_NUM_LOCK           282
#define NDR_KEY_PRINT_SCREEN       283
#define NDR_KEY_PAUSE              284
#define NDR_KEY_F1                 290
#define NDR_KEY_F2                 291
#define NDR_KEY_F3                 292
#define NDR_KEY_F4                 293
#define NDR_KEY_F5                 294
#define NDR_KEY_F6                 295
#define NDR_KEY_F7                 296
#define NDR_KEY_F8                 297
#define NDR_KEY_F9                 298
#define NDR_KEY_F10                299
#define NDR_KEY_F11                300
#define NDR_KEY_F12                301
#define NDR_KEY_F13                302
#define NDR_KEY_F14                303
#define NDR_KEY_F15                304
#define NDR_KEY_F16                305
#define NDR_KEY_F17                306
#define NDR_KEY_F18                307
#define NDR_KEY_F19                308
#define NDR_KEY_F20                309
#define NDR_KEY_F21                310
#define NDR_KEY_F22                311
#define NDR_KEY_F23                312
#define NDR_KEY_F24                313
#define NDR_KEY_F25                314
#define NDR_KEY_KP_0               320
#define NDR_KEY_KP_1               321
#define NDR_KEY_KP_2               322
#define NDR_KEY_KP_3               323
#define NDR_KEY_KP_4               324
#define NDR_KEY_KP_5               325
#define NDR_KEY_KP_6               326
#define NDR_KEY_KP_7               327
#define NDR_KEY_KP_8               328
#define NDR_KEY_KP_9               329
#define NDR_KEY_KP_DECIMAL         330
#define NDR_KEY_KP_DIVIDE          331
#define NDR_KEY_KP_MULTIPLY        332
#define NDR_KEY_KP_SUBTRACT        333
#define NDR_KEY_KP_ADD             334
#define NDR_KEY_KP_ENTER           335
#define NDR_KEY_KP_EQUAL           336
#define NDR_KEY_LEFT_SHIFT         340
#define NDR_KEY_LEFT_CONTROL       341
#define NDR_KEY_LEFT_ALT           342
#define NDR_KEY_LEFT_SUPER         343
#define NDR_KEY_RIGHT_SHIFT        344
#define NDR_KEY_RIGHT_CONTROL      345
#define NDR_KEY_RIGHT_ALT          346
#define NDR_KEY_RIGHT_SUPER        347
#define NDR_KEY_MENU               348

#define NDR_KEY_LAST               NDR_KEY_MENU