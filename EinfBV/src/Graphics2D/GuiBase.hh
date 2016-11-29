#ifndef __GuiBase_hh__
#define __GuiBase_hh__

#ifndef BUILD_WITH_OPENGL
#  error Build project with USE_OPENGL to enable GUI classes!
#endif

// Define constants for mouse buttons
#define GUI_MOUSE_LEFT    0x00
#define GUI_MOUSE_MIDDLE  0x01
#define GUI_MOUSE_RIGHT   0x02

// Define constants for common keys
#define GUI_KEY_BACKSPACE 0x08
#define GUI_KEY_TAB       0x09
#define GUI_KEY_ENTER     0x0D
#define GUI_KEY_ESCAPE    0x1B
#define GUI_KEY_SPACE     0x20
#define GUI_KEY_DELETE    0x7F

// Define constants for special keys
#define GUI_KEY_F1        0x101
#define GUI_KEY_F2        0x102
#define GUI_KEY_F3        0x103
#define GUI_KEY_F4        0x104
#define GUI_KEY_F5        0x105
#define GUI_KEY_F6        0x106
#define GUI_KEY_F7        0x107
#define GUI_KEY_F8        0x108
#define GUI_KEY_F9        0x109
#define GUI_KEY_F10       0x10A
#define GUI_KEY_F11       0x10B
#define GUI_KEY_F12       0x10C
#define GUI_KEY_LEFT      0x164
#define GUI_KEY_UP        0x165
#define GUI_KEY_RIGHT     0x166
#define GUI_KEY_DOWN      0x167
#define GUI_KEY_PGUP      0x168
#define GUI_KEY_PGDOWN    0x169
#define GUI_KEY_HOME      0x16A
#define GUI_KEY_END       0x16B
#define GUI_KEY_INSERT    0x16C
#define GUI_KEY_NUMLOCK   0x16D
#define GUI_KEY_LSHIFT    0x170
#define GUI_KEY_RSHIFT    0x171
#define GUI_KEY_LCTRL     0x172
#define GUI_KEY_RCTRL     0x173
#define GUI_KEY_ALT       0x174

#include "Image.hh"
#include <string>

/** @class  GuiBase
    @brief  Abstract base class for image GUIs implemented with OpenGL/GLUT.
            Derived classes can overload the event handler methods like
            KeyboardHandler(int, bool) or MouseHandler(int, int, int, bool)
            to add user interaction.
    @author esquivel
 */
class GuiBase
{
public:

  /** @brief Destructor. Release dynamically allocated memory. */
  virtual ~GuiBase();

  /** @brief Start GUI. Terminates main program when window is closed. */
  void Start();

protected:

  /** @brief Create GUI instance with given background image.
             Call SetImage(const Image&) to change the background image. */
  GuiBase(const std::string &title, const Image &image, int x = -1, int y = -1);

  /** @brief Create GUI with given window size without background image.
             Call SetImage(const Image&) to set the background image later. */
  GuiBase(const std::string &title, int width, int height, int x = -1, int y = -1);

  /** @brief Retrieve window position (coordinates of top left corner). */
  void GetWindowPosition(int &x, int &y);

  /** @brief Retrieve window size. */
  void GetWindowSize(int &width, int &height);

  /** @brief Set window position (coordinates of top left corner). */
  void SetWindowPosition(int x, int y);

  /** @brief Set window size. */
  void SetWindowSize(int width, int height);

  /** @brief Set window title. */
  void SetWindowTitle(const std::string &title);

  /** @brief Retrieve position of mouse cursor within window. */
  void GetMousePosition(int &x, int &y);

  /** @brief Set background image for window. Image must be 1-channel gray
             image or 3-channel RGB image. Call UpdateDisplay() afterwards
             to show the background image. */
  void SetImage(const Image &image);

  /** @brief Set status text to display at the bottom of the window. Call
             UpdateDisplay() afterwards to update status text in display. */
  void SetStatusText(const std::string &text);

  /** @brief Update window display. */
  void UpdateDisplay();

  /** @brief Close window and terminate GUI. */
  void Quit();

  /** @brief This handler is called when the window is closed.
             Does nothing by default. Overload this for custom event handling. */
  virtual void CloseWindowHandler();

  /** @brief This handler is called when the window is resized.
             Does nothing by default. Overload this for custom event handling. */
  virtual void ResizeWindowHandler(int width, int height);

  /** @brief This handler is called when keys are pressed or released.
             Does nothing by default. Overload this for custom event handling. */
  virtual void KeyboardHandler(int key, bool pressed);

  /** @brief This handler is called when mouse buttons are pressed or released.
             Does nothing by default. Overload this for custom event handling. */
  virtual void MouseButtonHandler(int x, int y, int button, bool pressed);

  /** @brief This handler is called when mouse is moved while a button is pressed.
             Does nothing by default. Overload this for custom event handling. */
  virtual void MouseMotionHandler(int x, int y);

private:

  /** @brief ID of OpenGL window */
  int windowId_;

  /** @brief ID of OpenGL texture */
  int textureId_;

  /** @brief Stores window size */
  int width_, height_;

  /** @brief Stores coordinates of mouse cursor */
  int mouseX_, mouseY_;

  /** @brief Stores status text that is displayed at the bottom of the window */
  std::string statusText_;

  /** @brief Create window and initialize GL/GLUT stuff internally. */
  void InitializeWindow_(const std::string &title, int width, int height, int x, int y);

  // The following methods are used internally for GL/GLUT window handling

  static void GL_Display();

  static void GL_ResizeWindow(int width, int height);

  static void GL_KeyPressed(unsigned char key, int x, int y);

  static void GL_KeyReleased(unsigned char key, int x, int y);

  static void GL_SpecialKeyPressed(int key, int x, int y);

  static void GL_SpecialKeyReleased(int key, int x, int y);

  static void GL_MouseButton(int button, int state, int x, int y);

  static void GL_MouseMotion(int x, int y);

  static int ConvertSpecialKey_(int key);

  static int ConvertMouseButton_(int button);

  void GetViewportCoordinates_(int x, int y, float &u, float &v) const;

  void GetPixelCoordinates_(float u, float v, int &x, int &y) const;

};

#endif // __GuiBase_hh__
