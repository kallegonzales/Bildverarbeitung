#include "GuiBase.hh"
#include <GL/glut.h>
#include <iostream>
#include <cstring>

using namespace std;

GuiBase* g_instance = NULL; // static pointer to GUI instance is needed for GLUT

GuiBase::GuiBase(const std::string &title, const Image &image, int x, int y)
  : windowId_(0), textureId_(0), mouseX_(0), mouseY_(0), width_(0), height_(0)
{
  InitializeWindow_(title, image.GetWidth(), image.GetHeight(), x, y);
  SetImage(image);
}

GuiBase::GuiBase(const std::string &title, int width, int height, int x, int y)
  : windowId_(0), textureId_(0), mouseX_(0), mouseY_(0), width_(0), height_(0)
{
  InitializeWindow_(title, width, height, x, y);
}

GuiBase::~GuiBase()
{
}

void GuiBase::Start()
{
  // Register callbacks
  g_instance = this;
  glutDisplayFunc(GL_Display);
  glutReshapeFunc(GL_ResizeWindow);
  glutKeyboardFunc(GL_KeyPressed);
  glutKeyboardUpFunc(GL_KeyReleased);
  glutSpecialFunc(GL_SpecialKeyPressed);
  glutSpecialUpFunc(GL_SpecialKeyReleased);
  glutMouseFunc(GL_MouseButton);
  glutMotionFunc(GL_MouseMotion);
  glutPassiveMotionFunc(GL_MouseMotion);

  // Start main loop
  glutMainLoop();
}

void GuiBase::GetWindowPosition(int &x, int &y)
{
  x = glutGet(GLUT_WINDOW_X);
  y = glutGet(GLUT_WINDOW_Y);
}

void GuiBase::GetWindowSize(int &width, int &height)
{
  width = width_;
  height = height_;
}

void GuiBase::SetWindowPosition(int x, int y)
{
  glutPositionWindow(x, y);
}

void GuiBase::SetWindowSize(int width, int height)
{
  glutReshapeWindow(width, height);
}

void GuiBase::SetWindowTitle(const string &title)
{
  glutSetWindowTitle(title.c_str());
}

void GuiBase::GetMousePosition(int &x, int &y)
{
  x = mouseX_;
  y = mouseY_;
}

void GuiBase::SetImage(const Image &image)
{
  // Create texture
  if (textureId_ == 0) {
    GLuint texId = 0;
    glGenTextures(1, &texId);
    textureId_ = (int)texId;
    if (textureId_ > 0) {
      glBindTexture(GL_TEXTURE_2D, (GLuint)textureId_);
#if defined(GL_TEXTURE_BASE_LEVEL) && defined(GL_TEXTURE_MAX_LEVEL)
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
#endif
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }
  // Copy image data to texture
  if (textureId_ > 0) {
    glBindTexture(GL_TEXTURE_2D, (GLuint)textureId_);
    int w = image.GetWidth(), h = image.GetHeight();
    if (image.IsEmpty()) {
      // Image is empty, fill texture with black
      unsigned char *tmpData = new unsigned char[w*h*3];
      memset(tmpData, 0, w*h*3);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
                   0, GL_RGB, GL_UNSIGNED_BYTE, tmpData);
      delete[] tmpData;
    } else if (image.GetColorModel() == Image::CM_Gray) {
      // Image has gray values, convert to RGB texture data
      unsigned char *tmpData = new unsigned char[w*h*3];
      const unsigned char *srcPtr = image.GetData();
      unsigned char *dstPtr = tmpData;
      for (int i = 0; i < w * h; i++, srcPtr++, dstPtr += 3) {
        dstPtr[0] = *srcPtr; dstPtr[1] = *srcPtr; dstPtr[2] = *srcPtr;
      }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
                   0, GL_RGB, GL_UNSIGNED_BYTE, tmpData);
      delete[] tmpData;
    } else {
      // Image has color values, assume that image is already in RGB format
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.GetWidth(), image.GetHeight(),
                   0, GL_RGB, GL_UNSIGNED_BYTE, image.GetData());
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    //glutPostRedisplay();
  }
}

void GuiBase::SetStatusText(const std::string &text)
{
  statusText_ = text;
}

void GuiBase::UpdateDisplay()
{
  glutPostRedisplay();
}

void GuiBase::Quit()
{
  // Unregister callbacks
  glutReshapeFunc(NULL);
  glutKeyboardFunc(NULL);
  glutKeyboardUpFunc(NULL);
  glutSpecialFunc(NULL);
  glutSpecialUpFunc(NULL);
  glutMouseFunc(NULL);
  glutMotionFunc(NULL);
  glutPassiveMotionFunc(NULL);
  g_instance = NULL;

  // Release texture
  if (textureId_ > 0) {
    GLuint texId = (GLuint)textureId_;
    glDeleteTextures(1, &texId);
    textureId_ = 0;
  }

  // Destroy window
  glutDestroyWindow(windowId_);
  windowId_ = 0;
}

void GuiBase::InitializeWindow_(const string &title, int width, int height, int x, int y)
{
  // Initialize GLUT
  int argc = 1;
  char *argv[1];
  char buffer[8] = "GuiBase";
  argv[0] = buffer;
  glutInit(&argc, argv);

  // Create window
  GLenum type = GLUT_RGB | GLUT_DOUBLE; // GLUT_SINGLE;
  glutInitDisplayMode(type);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(x, y);
  windowId_ = glutCreateWindow(title.c_str());
  width_ = glutGet(GLUT_WINDOW_WIDTH);
  height_ = glutGet(GLUT_WINDOW_HEIGHT);
  statusText_ = "";

  // Set GL parameters
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void GuiBase::GL_Display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  if (g_instance) {
    // Draw background image
    if (g_instance->textureId_ > 0) {
      glBindTexture(GL_TEXTURE_2D, (GLuint)g_instance->textureId_);
      glBegin(GL_QUADS);
      glColor3f(1.0f, 1.0f, 1.0f);
      glTexCoord2f(0.0f, 0.0f);
      glVertex2f(-1.0f, 1.0f);
      glTexCoord2f(1.0f, 0.0f);
      glVertex2f(1.0f, 1.0f);
      glTexCoord2f(1.0f, 1.0f);
      glVertex2f(1.0f, -1.0f);
      glTexCoord2f(0.0f, 1.0f);
      glVertex2f(-1.0f, -1.0f);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    // Draw status text
    if (!g_instance->statusText_.empty()) {
      glDisable(GL_TEXTURE_2D);
      glColor3f(1.0f, 1.0f, 1.0f);
      glRasterPos2f(-1.0f, -1.0f);
      const string &text = g_instance->statusText_;
      for (unsigned int i = 0 ; i < text.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
      glEnable(GL_TEXTURE_2D);
    }
  }
  glPopMatrix();
  glutSwapBuffers();
  //glFlush();
}

void GuiBase::GL_ResizeWindow(int width, int height)
{
  glViewport(0, 0, width, height);
  if (g_instance) {
    g_instance->width_ = width;
    g_instance->height_ = height;
    g_instance->ResizeWindowHandler(width, height);
  }
}

void GuiBase::GL_KeyPressed(unsigned char key, int x, int y)
{
  if (g_instance) {
    if (key == GUI_KEY_ESCAPE)
      g_instance->Quit();
    else
      g_instance->KeyboardHandler((int)key, true);
  }
}

void GuiBase::GL_KeyReleased(unsigned char key, int x, int y)
{
  if (g_instance) {
    if (key != GUI_KEY_ESCAPE)
      g_instance->KeyboardHandler((int)key, false);
  }
}

void GuiBase::GL_SpecialKeyPressed(int key, int x, int y)
{
  if (g_instance) {
    key = ConvertSpecialKey_(key);
    if (key >= 0)
      g_instance->KeyboardHandler(key, true);
  }
}

void GuiBase::GL_SpecialKeyReleased(int key, int x, int y)
{
  if (g_instance) {
    key = ConvertSpecialKey_(key);
    if (key >= 0)
      g_instance->KeyboardHandler(key, false);
  }
}

void GuiBase::GL_MouseButton(int button, int state, int x, int y)
{
  if (g_instance) {
    button = ConvertMouseButton_(button);
    if (button >= 0) {
      g_instance->MouseButtonHandler(x, y, button, state == GLUT_DOWN);
    }
  }
}

void GuiBase::GL_MouseMotion(int x, int y)
{
  if (g_instance) {
    g_instance->mouseX_ = x;
    g_instance->mouseY_ = y;
    g_instance->MouseMotionHandler(x, y);
  }
}

int GuiBase::ConvertSpecialKey_(int key)
{
  switch (key) {
    case GLUT_KEY_F1: key = GUI_KEY_F1; break;
    case GLUT_KEY_F2: key = GUI_KEY_F2; break;
    case GLUT_KEY_F3: key = GUI_KEY_F3; break;
    case GLUT_KEY_F4: key = GUI_KEY_F4; break;
    case GLUT_KEY_F5: key = GUI_KEY_F5; break;
    case GLUT_KEY_F6: key = GUI_KEY_F6; break;
    case GLUT_KEY_F7: key = GUI_KEY_F7; break;
    case GLUT_KEY_F8: key = GUI_KEY_F8; break;
    case GLUT_KEY_F9: key = GUI_KEY_F9; break;
    case GLUT_KEY_F10: key = GUI_KEY_F10; break;
    case GLUT_KEY_F11: key = GUI_KEY_F11; break;
    case GLUT_KEY_F12: key = GUI_KEY_F12; break;
    case GLUT_KEY_LEFT: key = GUI_KEY_LEFT; break;
    case GLUT_KEY_UP: key = GUI_KEY_UP; break;
    case GLUT_KEY_RIGHT: key = GUI_KEY_RIGHT; break;
    case GLUT_KEY_DOWN: key = GUI_KEY_DOWN; break;
    case GLUT_KEY_PAGE_UP: key = GUI_KEY_PGUP; break;
    case GLUT_KEY_PAGE_DOWN: key = GUI_KEY_PGDOWN; break;
    case GLUT_KEY_HOME: key = GUI_KEY_HOME; break;
    case GLUT_KEY_END: key = GUI_KEY_END; break;
    case GLUT_KEY_INSERT: key = GUI_KEY_INSERT; break;
    case 0x6D: key = GUI_KEY_NUMLOCK;
    case 0x70: key = GUI_KEY_LSHIFT; break;
    case 0x71: key = GUI_KEY_RSHIFT; break;
    case 0x72: key = GUI_KEY_LCTRL; break;
    case 0x73: key = GUI_KEY_RCTRL; break;
    case 0x74: key =  GUI_KEY_ALT; break;
    default: key = -1;
  }
  return key;
}

int GuiBase::ConvertMouseButton_(int button)
{
  switch (button) {
    case GLUT_LEFT_BUTTON: button = GUI_MOUSE_LEFT; break;
    case GLUT_MIDDLE_BUTTON: button = GUI_MOUSE_MIDDLE; break;
    case GLUT_RIGHT_BUTTON: button = GUI_MOUSE_RIGHT; break;
    default: button = -1;
  }
  return button;
}

void GuiBase::GetViewportCoordinates_(int x, int y, float &u, float &v) const
{
  u = x / (0.5f * width_) - 1.0f;
  v = 1.0f - y / (0.5f * height_);
}

void GuiBase::GetPixelCoordinates_(float u, float v, int &x, int &y) const
{
  x = (int)((u + 1.0f) * (0.5f * width_));
  y = (int)((1.0f - v) * (0.5f * height_));
}

void GuiBase::CloseWindowHandler()
{
}

void GuiBase::ResizeWindowHandler(int width, int height)
{
}

void GuiBase::KeyboardHandler(int key, bool pressed)
{
}

void GuiBase::MouseButtonHandler(int x, int y, int button, bool pressed)
{
}

void GuiBase::MouseMotionHandler(int x, int y)
{
}
