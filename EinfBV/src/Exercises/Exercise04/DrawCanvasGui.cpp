/** @file   DrawCanvasGui.cpp
    @brief  GUI for drawing primitives onto a canvas and transforming
            them via rotation, translation, and scaling (exercise 4).
    @see    PrimitiveBase, AffineTransform, DrawCanvasGui
    @author esquivel
 */

#include <Graphics2D/Image.hh>
#include <Graphics2D/GuiBase.hh>
#include <Graphics2D/AffineTransform.hh>
#include <Graphics2D/PrimitivePoint.hh>
#include <Graphics2D/PrimitiveLine.hh>
#include <Graphics2D/PrimitivePolygon.hh>
#include <Graphics2D/PrimitiveRectangle.hh>
#include <iostream>
#include <vector>

using namespace std;

/** @class  DrawCanvasGui
    @brief  Implements an image canvas where primitives can be painted
            and transformed.
            Mouse handlers are used to select the vertices to create the
            primitives from. Different colors and drawing modes can be
            selected by the user via keyboard input.
    @see    GuiBase
    @author esquivel
*/
class DrawCanvasGui : public GuiBase
{
public:

  /** @brief Create GUI instance with canvas of given size. */
  DrawCanvasGui(int width, int height)
    : GuiBase("Drawing Canvas", width, height), canvas_(width, height, Image::CM_RGB),
      color_(Color::RED), drawMode_(DRAWMODE_Polygon)
  {
    // Create initial primitives
    primitives_.push_back(new PrimitiveRectangle(Color::BLACK, Float2D(50, 0), Float2D(250, 200)));
    primitives_.push_back(new PrimitiveLine(Color::RED, Float2D(100, 175), Float2D(100, 75)));
    primitives_.push_back(new PrimitiveLine(Color::GREEN, Float2D(100, 75), Float2D(200, 75)));
    primitives_.push_back(new PrimitiveLine(Color::BLUE, Float2D(200, 75), Float2D(200, 175)));
    primitives_.push_back(new PrimitiveLine(Color::YELLOW, Float2D(200, 175), Float2D(100, 175)));
    primitives_.push_back(new PrimitiveLine(Color::MAGENTA, Float2D(100, 175), Float2D(200, 75)));
    primitives_.push_back(new PrimitiveLine(Color::CYAN, Float2D(200, 75), Float2D(150, 25)));
    primitives_.push_back(new PrimitiveLine(Color::MAGENTA, Float2D(150, 25), Float2D(100, 75)));
    primitives_.push_back(new PrimitiveLine(Color::CYAN, Float2D(100, 75), Float2D(200, 175)));
    primitives_.push_back(new PrimitiveRectangle(Color::GREEN, Float2D(0, 175), Float2D(width, 200)));
    vector<Float2D> points;
    points.push_back(Float2D(width/2, height/2));
    points.push_back(Float2D(width/2 - 50, height));
    points.push_back(Float2D(width/2 + 50, height));
    primitives_.push_back(new PrimitivePolygon(Color::BLUE, points));

    // Draw primitives into canvas image and update display
    DrawCanvas_();
  }

  virtual ~DrawCanvasGui()
  {
    for (unsigned int i = 0; i < primitives_.size(); i++) {
      delete primitives_[i];
    }
  }

protected:

  /** @brief Specifies primitive drawing mode for this GUI */
  enum DrawMode {
    DRAWMODE_Point,     ///< draw points
    DRAWMODE_Line,      ///< draw lines
    DRAWMODE_Polygon,   ///< draw polygons
    DRAWMODE_Rectangle  ///< draw rectangles
  };

  /** @brief Draw canvas image and update display. */
  void DrawCanvas_()
  {
    // Clear canvas image with background color
    canvas_.Clear(Color::WHITE);
    // Draw all primitives painted so far
    for (unsigned int i = 0; i < primitives_.size(); i++) {
      primitives_[i]->Draw(canvas_);
    }
    // Draw currently selected vertices
    Color vertexColor(192, 128, 0);
    for (unsigned int i = 0; i < vertices_.size(); i++) {
      PrimitivePoint p(vertexColor, vertices_[i]);
      p.Draw(canvas_);
    }
    // Draw lines between selected vertices
    for (unsigned int i = 0; i+1 < vertices_.size(); i++) {
      PrimitiveLine line(vertexColor, vertices_[i], vertices_[i+1]);
      line.Draw(canvas_);
    }
    // Copy canvas image to window display
    SetImage(canvas_);
    UpdateDisplay();
  }

  /** @brief This handler is called when keys are pressed or released. */
  virtual void KeyboardHandler(int key, bool pressed)
  {
    if (pressed) {
      // Handle user input
      if (key == 'q' || key == 'Q') {
        // Quit application with Q key
        Quit();
      } else if (key == 'd' || key == 'D') {
        // Delete all painted primitives with D key
        if (!primitives_.empty()) {
          primitives_.clear();
          DrawCanvas_();
          cout << "Deleted all primitives from canvas" << endl;
        }
      } else if (key == 'u' || key == 'U') {
        // Undo last painted primitives with U key
        if (!primitives_.empty()) {
          primitives_.pop_back();
          DrawCanvas_();
          cout << "Deleted most recent primitive from canvas" << endl;
        }
      } else if (key == 'h' || key == 'H') {
        // Print help with H key
        cout << "[D]   Delete all primitives" << endl
             << "[Q]   Quit application" << endl
             << "[U]   Undo last primitive" << endl
             << "[V]   Draw points" << endl
             << "[L]   Draw lines" << endl
             << "[P]   Draw polygons (click near first vertex to close polygon)" << endl
             << "[R]   Draw rectangles" << endl
             << "[1-9] Select color (red,green,blue,cyan,magenta,yellow,white,gray,black)" << endl
             << "[Arrows]  Translate canvas left/right/up/down by 16 pixels" << endl
             << "[PgUp/Dn] Rotate canvas left/right by 6 degree" << endl
             << "[+/-] Zoom canvas in and out by 10%" << endl;
      } else if (key == 'v' || key == 'V') {
        cout << "Set draw mode to points" << endl;
        drawMode_ = DRAWMODE_Point;
      } else if (key == 'l' || key == 'L') {
        cout << "Set draw mode to lines" << endl;
        drawMode_ = DRAWMODE_Line;
      } else if (key == 'p' || key == 'P') {
        cout << "Set draw mode to polygons" << endl;
        drawMode_ = DRAWMODE_Polygon;
      } else if (key == 'r' || key == 'R') {
        cout << "Set draw mode to rectangles" << endl;
        drawMode_ = DRAWMODE_Rectangle;
      } else if (key >= '1' && key <= '9') {
        // Select color for next primitives with keys 1 to 9
        cout << "Set current color to ";
        switch (key) {
          case '1': color_ = Color::RED; cout << "red" << endl; break;
          case '2': color_ = Color::GREEN; cout << "green" << endl; break;
          case '3': color_ = Color::BLUE; cout << "blue" << endl; break;
          case '4': color_ = Color::CYAN; cout << "cyan" << endl; break;
          case '5': color_ = Color::MAGENTA; cout << "magenta" << endl; break;
          case '6': color_ = Color::YELLOW; cout << "yellow" << endl; break;
          case '7': color_ = Color::WHITE; cout << "white" << endl; break;
          case '8': color_ = Color::GRAY; cout << "gray" << endl; break;
          default:  color_ = Color::BLACK; cout << "black" << endl;
        }
      }  else if (key == GUI_KEY_LEFT || key == GUI_KEY_RIGHT ||
                  key == GUI_KEY_UP || key == GUI_KEY_DOWN) {
         // Translate all primitives by 16 pixels with arrow keys
         float tx = 0.0f, ty = 0.0f;
         if (key == GUI_KEY_LEFT)
           tx = -16.0f;
         else if (key == GUI_KEY_RIGHT)
           tx = 16.0f;
         else if (key == GUI_KEY_UP)
           ty = -16.0f;
         else if (key == GUI_KEY_DOWN)
           ty = 16.0f;
         AffineTransform T;
         T.MakeTranslation(tx, ty);
         for (unsigned int i = 0; i < primitives_.size(); i++) {
           primitives_[i]->ApplyTransform(T);
         }
         DrawCanvas_();
       } else if (key == GUI_KEY_PGUP || key == GUI_KEY_PGDOWN) {
        // Rotate all primitives by 6 degree around canvas center with page up/down key
        if (!primitives_.empty()) {
          float degree = (key == GUI_KEY_PGUP) ? -6.0f : 6.0f;
          AffineTransform T, T1, T2, T3;
          T1.MakeTranslation(-0.5f * canvas_.GetWidth(), -0.5f * canvas_.GetHeight());
          T2.MakeRotation(degree * (float)M_PI / 180.0f);
          T3.MakeTranslation(0.5f * canvas_.GetWidth(), 0.5f * canvas_.GetHeight());
          T = AffineTransform::Concatenate(T3, AffineTransform::Concatenate(T2, T1));
          for (unsigned int i = 0; i < primitives_.size(); i++) {
            primitives_[i]->ApplyTransform(T);
          }
          DrawCanvas_();
        }
      } else if (key == '+' || key == '-') {
        // Scale all primitives by 110% or 90% w.r.t. canvas center with keys + and -
        if (!primitives_.empty()) {
          float scale = (key == '+') ? 1.1f : 0.9f;
          AffineTransform T, T1, T2, T3;
          T1.MakeTranslation(-0.5f * canvas_.GetWidth(), -0.5f * canvas_.GetHeight());
          T2.MakeScaling(scale, scale);
          T3.MakeTranslation(0.5f * canvas_.GetWidth(), 0.5f * canvas_.GetHeight());
          T = AffineTransform::Concatenate(T3, AffineTransform::Concatenate(T2, T1));
          for (unsigned int i = 0; i < primitives_.size(); i++) {
            primitives_[i]->ApplyTransform(T);
          }
          DrawCanvas_();
        }
      }
    }
  }

  /** @brief This handler is called when mouse buttons are pressed or released. */
  virtual void MouseButtonHandler(int x, int y, int button, bool pressed)
  {
    if (button == GUI_MOUSE_RIGHT && pressed) {
      // Reset currently selected vertices with right mouse button
      vertices_.clear();
      DrawCanvas_();
    } else if (button == GUI_MOUSE_LEFT && pressed) {
      switch (drawMode_)
      {
        case DRAWMODE_Point:
        {
          // Create point primitive from clicked point
          primitives_.push_back(new PrimitivePoint(color_, Float2D(x, y)));
          break;
        }
        case DRAWMODE_Line:
        {
          // Add clicked point to selected vertices or create line primitive
          if (vertices_.empty()) {
            vertices_.push_back(Float2D(x, y));
          } else {
            primitives_.push_back(new PrimitiveLine(color_, vertices_[0], Float2D(x, y)));
            vertices_.clear();
          }
          break;
        }
        case DRAWMODE_Polygon:
        {
          // Add clicked point to selected vertices or create polygon primitive
          if (vertices_.size() < 3) {
            vertices_.push_back(Float2D(x, y));
          } else if (abs((int)vertices_[0][0] - x) <= 4 && abs((int)vertices_[0][1] - y) <= 4) {
            // Create polygon if mouse click appeared close to the first vertex
            primitives_.push_back(new PrimitivePolygon(color_, vertices_));
            vertices_.clear();
          } else {
            // Add clicked point to selected vertices otherwise
            vertices_.push_back(Float2D(x, y));
          }
          break;
        }
        case DRAWMODE_Rectangle:
        {
          // Add clicked point to selected vertices or create rectangle primitive
          if (vertices_.empty()) {
            vertices_.push_back(Float2D(x, y));
          } else {
            primitives_.push_back(new PrimitiveRectangle(color_, vertices_[0], Float2D(x, y)));
            vertices_.clear();
          }
          break;
        }
      }
      // Draw canvas and update display in window
      DrawCanvas_();
    }
  }

  /** @brief This handler is called when the window is resized. */
  virtual void ResizeWindowHandler(int width, int height)
  {
    // Resize canvas image to window size
    canvas_.Init(width, height, Image::CM_RGB);
    DrawCanvas_();
  }

private:

  /** @brief Stores currently selected vertices */
  vector<Float2D> vertices_;
  /** @brief Stores primitives painted onto the canvas */
  vector<PrimitiveBase*> primitives_;
  /** @brief Image used as canvas to display in window */
  Image canvas_;
  /** @brief Currently selected color for drawing */
  Color color_;
  /** @brief Stores current primitive drawing mode */
  DrawMode drawMode_;

};

int main(int argc, char *argv[])
{
  // Read window size from parameter
  int width = (argc > 1) ? atoi(argv[1]) : 800;
  int height = (argc > 2) ? atoi(argv[2]) : ((3 * width) / 4);
  cout << "-- DrawCanvasGui --" << endl;

  // Start GUI
  DrawCanvasGui gui(width, height);
  gui.Start();

  return 0;
}
