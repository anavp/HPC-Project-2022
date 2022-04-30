#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define print_var(x) cout << #x << ": " << x << endl;

using namespace std;

char * read_input_image(string path, string destination_path){
    const char *filename = path.c_str();
    int x, y, n = 4;
    unsigned char *data = stbi_load(filename, &x, &y, &n, 3);
    print_var(x);
    print_var(y);
    for (int i = 0; i < y; ++i){
        for (int j = 0; j < x; ++j){
            cout << data[i * y + j] << " ";
        }
        cout << endl;
    }
    // int comp, quality;
    // const char * dest_path = destination_path.c_str();
    // stbi_write_png(dest_path, x, y, comp, data, quality);
    // stbi_write_jpg(filename, y, x, comp, data, quality);
    
    stbi_image_free(data);
}

int main(){
    string input_path = "./benchmark/wfc/samples/3bricks.bmp";
    read_input_image(input_path, "nothing");

    return 0;
}