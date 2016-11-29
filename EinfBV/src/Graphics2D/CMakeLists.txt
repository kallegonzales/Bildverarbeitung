# Build Graphics2D library
SET(Graphics2D_SOURCE
    Color.cpp Color.hh
    Image.cpp Image.hh
    ImageIO.cpp ImageIO.hh
    Vectors.cpp Vectors.hh
    Matrices.cpp Matrices.hh
    Lines.cpp Lines.hh
    AffineTransform.cpp AffineTransform.hh
    PrimitiveBase.cpp PrimitiveBase.hh
    PrimitivePoint.cpp PrimitivePoint.hh
    PrimitiveLine.cpp PrimitiveLine.hh
    PrimitivePolygon.cpp PrimitivePolygon.hh
    PrimitiveRectangle.cpp PrimitiveRectangle.hh
    ColorConversion.cpp ColorConversion.hh
)

SET(Graphics2D_LINKEDLIBS)

IF(USE_FreeImage)
  LIST(APPEND Graphics2D_LINKEDLIBS ${FreeImage_LIBRARIES})
ENDIF()

IF(USE_OPENGL)
  LIST(APPEND Graphics2D_SOURCE GuiBase.cpp GuiBase.hh)
  LIST(APPEND Graphics2D_LINKEDLIBS ${OPENGL_LIBRARIES})
ENDIF()

ADD_LIBRARY(Graphics2D STATIC ${Graphics2D_SOURCE})
TARGET_LINK_LIBRARIES(Graphics2D ${Graphics2D_LINKEDLIBS})
