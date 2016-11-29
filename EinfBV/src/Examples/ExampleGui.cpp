/** @file   ExampleGui.cpp
    @brief  Example for basic GUI interface.
    @see    GuiBase, ExampleGui
    @author esquivel
 */

#include <Graphics2D/Image.hh>
#include <Graphics2D/ImageIO.hh>
#include <Graphics2D/GuiBase.hh>
#include <iostream>
#include <sstream>

using namespace std;

/** @class  ExampleGui
    @brief  Example for usage of GuiBase. Implements a simple image viewer.
            Mouse handlers are used to show image information and draw lines
            into the window.
    @see    GuiBase
    @author esquivel
 */
class ExampleGui : public GuiBase
{
public:

  /** @brief Create GUI instance. Set given image as background image. */
  ExampleGui(const Image &image) : GuiBase("Image Viewer", image)
  {
    leftButtonDown_ = false;
    scaleX_ = scaleY_ = 1.0f;
    image_ = image;
  }

  virtual ~ExampleGui()
  {
  }

protected:

  /** @brief This handler is called when keys are pressed or released. */
  virtual void KeyboardHandler(int key, bool pressed)
  {
    if (pressed) {
      // Show pressed key
      if (key >= 32 && key < 128)
        cout << "Pressed key " << key << " = '" << (char)key << "'" << endl;
      else
        cout << "Pressed key " << key << endl;
      // Handle user input
      if (key == 'q' || key == 'Q') {
        Quit();
      }
    }
  }

  /** @brief This handler is called when mouse buttons are pressed or released. */
  virtual void MouseButtonHandler(int x, int y, int button, bool pressed)
  {
    if (pressed) {
      // Show pressed mouse button
      cout << "Pressed mouse button " << button << " at " << x << ", " << y << endl;
    }
    if (button == GUI_MOUSE_LEFT) {
      leftButtonDown_ = pressed;
      if (!leftButtonDown_) {
        // Clear status text and reset image
        SetStatusText("");
        SetImage(image_);
        UpdateDisplay();
      } else {
        // Show image information and cross-hair
        MouseMotionHandler(x, y);
      }
    }
  }

  /** @brief This handler is called when mouse is moved while a button is pressed. */
  virtual void MouseMotionHandler(int x, int y)
  {
    if (leftButtonDown_) {
      // Get position in image from position in window
      x = (int)(scaleX_ * x);
      y = (int)(scaleY_ * y);
      // Get color at current position
      Color color;
      image_.GetPixel(x, y, color);
      // Set status text
      ostringstream text;
      text << "XY = [ " << x << ", " << y << " ], RGB = [ " << (int)color.red
           << ", " << (int)color.green << ", " << (int)color.blue << " ]";
      SetStatusText(text.str());
      // Draw cross-hair into window using copy of background image
      Image tmpImage = image_;
      if (y >= 0 && y < image_.GetHeight()) {
        for (int i = 0; i < image_.GetWidth(); i++)
          tmpImage.SetPixel(i, y, Color::RED);
      }
      if (x >= 0 && x < image_.GetWidth()) {
        for (int i = 0; i < image_.GetHeight(); i++)
          tmpImage.SetPixel(x, i, Color::RED);
      }
      SetImage(tmpImage);
      UpdateDisplay();
    }
  }

  /** @brief This handler is called when the window is resized. */
  virtual void ResizeWindowHandler(int width, int height)
  {
    // Update scale factor between window and image
    scaleX_ = image_.GetWidth() / (float)width;
    scaleY_ = image_.GetHeight() / (float)height;
  }

private:

  bool leftButtonDown_;   ///< stores if left mouse button is down
  float scaleX_, scaleY_; ///< stores scale factor between window and image
  Image image_;           ///< stores original background image

};

int main(int argc, char *argv[])
{
  // Read parameters
  if (argc < 2) {
    cout << "Usage: ExampleGui <input image>" << endl;
    return 0;
  }
  cout << "-- ExampleGui --" << endl;

  // Load background image
  Image image;
  const string inputFilename = argv[1];
  if (!ImageIO::Load(inputFilename, image)) {
    cerr << "Failed to load image from file " << inputFilename << "!" << endl;
    return -1;
  }
  if (image.GetColorModel() == Image::CM_HSV) {
    cout << "Expected RGB color format instead of HSV! Image might look strange..." << endl;
  }

  // Start GUI
  ExampleGui gui(image);
  gui.Start();

  return 0;
}
