#include <Graphics2D/Image.hh>
#include <Graphics2D/ImageIO.hh>
#include <Graphics2D/Color.hh>

#include <Graphics2D/ColorConversion.hh>

#include <iostream>

using namespace std;

int main() {

    Image in;

    if(!ImageIO::Load("monalisa.ppm", in)) {
        cerr<<"Failed to load image."<<endl;
        return -1;
    }

    Image out(in.GetWidth(), in.GetHeight(), Image::CM_RGB);

    ColorConversion::RGBToGray(in, out);

    if(ImageIO::Save("mona-gray.png", out)) {
        cout << "Image saved successfully!" << endl;
    } else {
        cerr << "That did not :(" << endl;
        return -1;
    }

    /*
    Color test(255,42,0);

    Color gray;

    ColorConversion::ColorRGBToGray(test,gray);

    cout << (short)gray.red << " " << (short)gray.green << " " << (short)gray.blue <<endl;*/


    return 0;
}
