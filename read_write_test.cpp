#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#define endl "\n"
#define print_var(x) cout << #x << ": " << x << endl;

using namespace std;

char * read_input_image(string path, string destination_path){
    const char *filename = path.c_str();
    int x, y, n;
    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
    // print_var(x);
    // print_var(y);
    // for (int i = 0; i < y; ++i){
    //     for (int j = 0; j < x; ++j){
    //         cout << "(" << (int)data[i * y * n + j * n] << ", ";
    //         for (int k =1; k < n-1; ++k){
    //             cout << (int)data[i * y * n + j * n + k] << ", ";
    //         }
    //         cout << (int)data[i * y * n + j * n + n-1] << ") ";
    //     }
    //     cout << endl;
    // }
    // int comp, quality;
    const char * dest_path = destination_path.c_str();
    // stbi_write_png(dest_path, x, y, comp, data, quality);
    // stbi_write_jpg(filename, y, x, comp, data, quality);
    // stbi_write_jpg(dest_path, x, y, 1, data, 100);
    stbi_write_bmp(dest_path, x, y, 3, data);
    
    stbi_image_free(data);
}

void alt_test(string path){
    fstream file;
    file.open(path, ios::in);
    int input;
    char inp2;
    string line;
    vector<int> values;
    while(file.good()){
        getline(file, line);
        print_var(line);
        
        // file >> input;
        // print_var(input);
        // file >> inp2;
        // print_var(inp2);
    }
}

int main(){
    string input_path = "./benchmark/wfc/samples/3bricks.bmp";
    // read_input_image(input_path, "s4.bmp");
    string input_path2 = "./sample.txt";
    alt_test(input_path2);
    return 0;
}