#include <iostream>
#include <climits>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <vector>
// #include <sys>
// #include <sys.h>
// #include <stack>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define HASHING_PRIME 257
#define TEMP_OUT "temp_out.txt"
#define endl '\n'
#define NOT_DEFINED -1
#define print_var(x) cout << #x << ": " << x << endl;
typedef struct tile Tile;

using namespace std;

ifstream input_file;
int TRACE = 1;
// int TOTAL_CHAR = 0;
int TOTAL_VALS = 0;
struct tile
{
    //TODO: Remove char things
    // char tileChar;
    // char upTileChar, downTileChar, leftTileChar, rightTileChar;
    int tileVal;
    int upTileVal, downTileVal, leftTileVal, rightTileVal;
};

int intToASCII(int number){
    return '0' + number;
}

void fillBlankChar(int* uniqueChar){
    for(int i = 0; i < 256; i++){ 
        // uniqueChar[i] = '\0';
        uniqueChar[i] = NOT_DEFINED;
    }
}

// int checkForChar(char* uniqueChar, char inputChar){
//     for(int i = 0; i < TOTAL_CHAR; i++){ 
//         if(uniqueChar[i] == inputChar)
//             return i;
//     }
//     return -1;
// }

int checkForVal(int *uniqueVal, int inputValue){
    for (int i = 0; i < TOTAL_VALS; ++i){
        if (uniqueVal[i] == inputValue)
            return i;
    }
    return NOT_DEFINED;
}

// int checkForCharByInt(char* uniqueChar, int inputChar){
//     for(int i = 0; i < TOTAL_CHAR; i++){ 
//         int carCheck = (int)uniqueChar[i]; 
//         if(carCheck == inputChar)
//             return i;
//     }
//     return -1;
// }

void printArray(char* coefficients, int size){
    for(int i = 0; i < size; i++){
        cout << coefficients[i] << " ";
    }
    cout << endl;
}

void printArray(int* coefficients, int size){
    for(int i = 0; i < size; i++){
        cout << coefficients[i] << " ";
    }
    cout << endl;
}

void printModArray(int* coefficients, int productRowCol, int TOTAL_VALS){
    for(int i = 0; i < productRowCol; i++){
        for(int j = 0; j < TOTAL_VALS; j++){
            if (coefficients[i*TOTAL_VALS + j] != 0)
                printf("%c", coefficients[i*TOTAL_VALS + j]);
        }
        cout<<"|";
    }
    cout << endl;
}

void printModColArray(int* coefficients, int productRowCol, int outputCol, int TOTAL_VALS){
    for(int i = 0; i < productRowCol; i++){
        for(int j = 0; j < TOTAL_VALS; j++){
            if (coefficients[i*TOTAL_VALS + j] != 0)
                printf("%c", coefficients[i*TOTAL_VALS + j]);
        }
        cout<<"|";
        if ((i+1) % outputCol == 0)
            cout << endl;
    }
    cout << endl;
}

void printCharArray(int* coefficients, int size){
    for(int i = 0; i < size; i++){
        printf("%c ", coefficients[i]);
    }
    cout << endl;
}

void printArray(Tile* compatibleMatrix, int inputRow, int inputCol){
    for(int i = 0; i < inputRow; i++){
        for(int j = 0; j < inputCol; j++){
            // cout << compatibleMatrix[i*inputCol + j].tileChar << " ";
            cout << compatibleMatrix[i*inputCol + j].tileVal << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// void getRowAndColAndChar(int &row, int &col, int* uniqueChar, FILE* stream){
void getRowAndColAndVal(int &row, int &col, int *uniqueVal, string path){
    
    // char inputValue;
    // int colFlag = 0;
    // while ((inputValue = getc(stream)) != EOF) {
    //     if(inputValue != '\n'){
    //         if (inputValue != ' ') {
    //             if(!colFlag) col++;
    //             if (checkForChar(uniqueChar, inputValue) == -1) {
    //                 uniqueChar[TOTAL_CHAR] = inputValue;
    //                 TOTAL_CHAR++;
    //             }
    //         }
    //     }
    //     else{
    //         colFlag = 1;
    //         row++;
    //     }
    // }
    // ifstream input_file;
    assert(!input_file.is_open());
    (::input_file).open(path, ios::in);
    assert(input_file.good());
    int inputValue, colFlag;
    string line;
    col = NOT_DEFINED;
    while (input_file.good()){
        getline(input_file, line);
        if (line.size() == 0) continue;
        int temp = count(line.begin(), line.end(), ' ') + 1;
        // print_var(temp);
        // print_var(col);
        // cout << endl;
        if (col == NOT_DEFINED) col = temp;
        else assert(col == temp);
        row++;
    }
    // print_var(row);
    // print_var(col);
    input_file.clear();
    input_file.seekg(0);
    char ch;
    while(input_file.good()){
        input_file >> inputValue;
        // input_file >> ch;
        // inputValue = (int)ch;
        if (checkForVal(uniqueVal, inputValue) == NOT_DEFINED)
            uniqueVal[TOTAL_VALS++] = inputValue;
    }
    input_file.close();
}

// void readInput(Tile* compatibleMatrix, char* uniqueChar, int* charWeight, FILE* stream){
//     char inputValue;
//     int i = 0;
//     while ((inputValue = getc(stream)) != EOF) {
//         if(inputValue != '\n' && inputValue != ' '){
//             compatibleMatrix[i].tileChar = inputValue;
//             i++;
//             charWeight[checkForChar(uniqueChar, inputValue)]++;
//         }
//     }
// }

void readInput(Tile* compatibleMatrix, int *uniqueVal, int *charWeight){
    assert(input_file.is_open());
    int i = 0;
    int val;
    char ch;
    while(input_file.good()){
        input_file >> val;
        // input_file >> ch;
        // val = (int)ch;
        compatibleMatrix[i].tileVal = val;
        ++i;
        charWeight[checkForVal(uniqueVal, val)]++;
    }
}

int validDirection(int maxRow, int maxCol, int curRow, int curCol, int direction){
    if(direction == 0){ //UP
        if(curRow - 1 >= 0)
            return (curRow - 1) * maxCol + curCol;
    }
    else if(direction == 1){ //DOWN
        if(curRow + 1 < maxRow)
            return (curRow + 1) * maxCol + curCol;
    }
    else if(direction == 2){ //LEFT
        if(curCol - 1 >= 0)
            return curRow * maxCol + curCol - 1;
    }
    else if(direction == 3){ //RIGHT
        if(curCol + 1 < maxCol)
            return curRow * maxCol + curCol + 1;
    }
    return NOT_DEFINED;
}

void resolveMatrix(Tile* parseMatrix, int &row, int &col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            Tile* curTile = &parseMatrix[i*col + j];
            int getDirIndex;
            getDirIndex = validDirection(row, col, i, j, 0);
            if (getDirIndex != NOT_DEFINED) curTile->upTileVal = parseMatrix[getDirIndex].tileVal;
            // if (getDirIndex != -1) curTile->upTileChar = parseMatrix[getDirIndex].tileChar;
            // else curTile->upTileChar = '\0';
            else curTile->upTileVal = NOT_DEFINED;

            getDirIndex = validDirection(row, col, i, j, 1);
            if (getDirIndex != NOT_DEFINED) curTile->downTileVal = parseMatrix[getDirIndex].tileVal;
            else curTile->downTileVal = NOT_DEFINED;
            // if (getDirIndex != -1) curTile->downTileChar = parseMatrix[getDirIndex].tileChar;
            // else curTile->downTileChar = '\0';
            
            getDirIndex = validDirection(row, col, i, j, 2);
            if (getDirIndex != NOT_DEFINED) curTile->leftTileVal = parseMatrix[getDirIndex].tileVal;
            else curTile->leftTileVal = NOT_DEFINED;
            // if (getDirIndex != -1) curTile->leftTileChar = parseMatrix[getDirIndex].tileChar;
            // else curTile->leftTileChar = '\0';

            getDirIndex = validDirection(row, col, i, j, 3);
            if (getDirIndex != NOT_DEFINED) curTile-> rightTileVal = parseMatrix[getDirIndex].tileVal;
            else curTile->rightTileVal = NOT_DEFINED;
            // if (getDirIndex != -1) curTile->rightTileChar = parseMatrix[getDirIndex].tileChar;
            // else curTile->rightTileChar = '\0';
        }
    }       
}

// void fillCoeff(int* coefficients, char* uniqueChar, int size){
//     for(int i = 0; i < size; i++){
//         for (int j = 0; j < TOTAL_CHAR; j++) {
//             coefficients[i*TOTAL_CHAR + j] = uniqueChar[j];
//         }
//     }
// }

void fillCoeff(int *coefficients, int *uniqueVal, int size){
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < TOTAL_VALS; j++)
            coefficients[i*TOTAL_VALS + j] = uniqueVal[j];
}

// int getTilesAtIndex(int* coefficients, int index){
//     int sum = 0;
//     for(int i = 0; i < TOTAL_CHAR; i++){
//         if (coefficients[index*TOTAL_CHAR + i] != 0) 
//             sum ++;
//     }
//     return sum;
// }

int getTilesAtIndex(int *coefficients, int index){
    int sum = 0;
    for (int i = 0; i < TOTAL_VALS; ++i)
        if (coefficients[index * TOTAL_VALS + i] != 0) sum++;
    return sum;
}

int isFullyCollapsed(int* isCollapsedArray, int outputSize){
    for(int i = 0; i < outputSize; i++){
        if (isCollapsedArray[i] > 1) return 0;
        if (isCollapsedArray[i] == 0) {
            printf("ERROR: Collapse failure\n");
            
            exit(1);
        }
    }
    return 1;
}

void fillCollapsed(int* isCollapsedArray, int* coefficients, int outputSize){
    for(int i = 0; i < outputSize; i++){
        isCollapsedArray[i] = getTilesAtIndex(coefficients, i);
    }
}

// float shannonEntropy(int* coefficients, int index, int* charWeight, char* uniqueChar) {
//     float sumOfWeights = 0;
//     float sumOfLogWeights = 0;
//     for (int i = 0; i < TOTAL_CHAR; i++) {
//         int currentChar = coefficients[index*TOTAL_CHAR + i];
//         if (currentChar != 0) {
//             int curWeight = charWeight[checkForCharByInt(uniqueChar, currentChar)];
//             sumOfWeights += curWeight;
//             sumOfLogWeights += curWeight * log(curWeight);
//         }
//     }
//     return log(sumOfWeights) - sumOfLogWeights / sumOfWeights;
// }

float shannonEntropy(int* coefficients, int index, int* charWeight, int* uniqueVal) {
    float sumOfWeights = 0;
    float sumOfLogWeights = 0;
    for (int i = 0; i < TOTAL_VALS; i++) {
        int currentChar = coefficients[index*TOTAL_VALS + i];
        if (currentChar != 0) {
            int curWeight = charWeight[checkForVal(uniqueVal, currentChar)];
            sumOfWeights += curWeight;
            sumOfLogWeights += curWeight * log(curWeight);
        }
    }
    return log(sumOfWeights) - sumOfLogWeights / sumOfWeights;
}

int minEntropyIndex(int* coefficients, int* charWeight, int* uniqueVal, int outputSize){
    float minEntropy = INT_MAX;
    int minEntropyIndex = -1;
    for(int i = 0; i < outputSize; i++){
        if (getTilesAtIndex(coefficients, i) == 1)
            continue;
        float entropy = shannonEntropy(coefficients, i, charWeight, uniqueVal);
        if (entropy < minEntropy) { // Use the BattleCode feature here, or add noise
            minEntropy = entropy;
            minEntropyIndex = i;
        }
    }
    return minEntropyIndex;
}

// void collapse(int* coefficients, int index, int* charWeight, char* uniqueChar){
//     float maxweight = -1;
//     int chosenIndex = -1;
//     for (int i = 0; i < TOTAL_CHAR; i++) {
//         int currentChar = coefficients[index*TOTAL_CHAR + i];
//         if (currentChar != 0) {
//             float curWeight = ((double) rand() / (RAND_MAX)) * charWeight[checkForCharByInt(uniqueChar, currentChar)];
//             if (curWeight > maxweight) {
//                 maxweight = curWeight;
//                 chosenIndex = i;
//             }
//         }
//     }    
//     // printf("Chosen index is %d \n", chosenIndex);
//     for (int i = 0; i < TOTAL_CHAR; i++) {
//         if (i != chosenIndex){
//             coefficients[index*TOTAL_CHAR + i] = 0;
//         }
//     }
// }

void collapse(int* coefficients, int index, int* charWeight, int* uniqueVal){
    float maxweight = -1;
    int chosenIndex = -1;
    for (int i = 0; i < TOTAL_VALS; i++) {
        int currentChar = coefficients[index*TOTAL_VALS + i];
        if (currentChar != 0) {
            float curWeight = ((double) rand() / (RAND_MAX)) * charWeight[checkForVal(uniqueVal, currentChar)];
            if (curWeight > maxweight) {
                maxweight = curWeight;
                chosenIndex = i;
            }
        }
    }    
    // printf("Chosen index is %d \n", chosenIndex);
    for (int i = 0; i < TOTAL_VALS; i++) {
        if (i != chosenIndex){
            coefficients[index*TOTAL_VALS + i] = 0;
        }
    }
}

// int checkMatch(Tile* compatibleMatrix, int comRow, int comCol, char firstChar, char secondChar, int direction){
int checkMatch(Tile *compatibleMatrix, int comRow, int comCol, int firstVal, int secondVal, int direction){
    for(int i = 0; i < comRow; i++){
        for(int j = 0; j < comCol; j++){
            Tile* curTile = &compatibleMatrix[i*comCol + j];
            // if (curTile->tileChar != firstChar){
            //     continue;
            // }
            if (curTile->tileVal != firstVal) continue;
            if (direction == 0){ //UP
                // if(curTile->upTileChar == secondChar){
                //     return 1;
                // }
                if (curTile->upTileVal == secondVal) return 1;
            }
            else if(direction == 1){ //DOWN
                if(curTile->downTileVal == secondVal) return 1;
                // if(curTile->downTileChar == secondChar){
                //     return 1;
                // }
            }
            else if(direction == 2){ //LEFT
                if (curTile->leftTileVal == secondVal) return 1;
                // if(curTile->leftTileChar == secondChar){
                //     return 1;
                // }
            }
            else if(direction == 3){ //RIGHT
                if (curTile->rightTileVal == secondVal) return 1;
                // if(curTile->rightTileChar == secondChar){
                //     return 1;
                // }
            }
        }
    }
    return 0;
}

void propagate(Tile* compatibleMatrix, int* isCollapsedArray, int comRow, int comCol, int* coefficients, int* coefficientsCopy, 
    int coeffRow, int coeffCol, int index){
    int stopFlag = 1;
    while(stopFlag > 0){
        stopFlag = 0;
        for (int mainLoop = 0; mainLoop < coeffCol * coeffRow; mainLoop++){
            int curIndex = mainLoop;
            int willPush = 0;
            for (int dir = 0; dir < 4; dir++){ // Iterate through neighbors
                int otherIndex = validDirection(coeffRow, coeffCol, curIndex/coeffCol, curIndex%coeffCol, dir); // Get 2nd tile
                if (otherIndex == -1) continue; // If no tile, continue

                for (int i = 0; i < TOTAL_VALS; i++){ 
                    int curVal = coefficients[curIndex*TOTAL_VALS + i];
                    if (curVal != 0){
                        int removeFlag = 0;
                        for(int j = 0; j < TOTAL_VALS; j++){ //Iterate through enemy possible tiles
                            int otherVal = coefficients[otherIndex*TOTAL_VALS + j]; // Got one of the other's tile
                            // if(TRACE) printf("Enemy char is %c\n", otherChar);
                            if (otherVal == 0){
                                continue;
                            }
                            int newDir;
                            if (dir == 0)
                                newDir = 1;
                            else if (dir == 1)
                                newDir = 0;
                            else if (dir == 2)
                                newDir = 3;
                            else if (dir == 3)
                                newDir = 2;
                            int matchIndex = checkMatch(compatibleMatrix, comRow, comCol, otherVal, curVal, newDir);
                            if (matchIndex != 0){ // Does match with atleast one neighbour, don't remove this character
                                removeFlag = 1;
                            }
                            
                        }
                        if (removeFlag == 0){
                            willPush = 1;
                            coefficientsCopy[curIndex*TOTAL_VALS + i] = 0;    
                        }
                    }
                }
                if (willPush == 1){
                    isCollapsedArray[mainLoop] = 1;
                }
                else{
                    isCollapsedArray[mainLoop] = 0;
                }
            }
        }
        for(int i=0; i < coeffCol * coeffRow; i++){
                stopFlag += isCollapsedArray[i];
        }
        for(int copier=0; copier < coeffCol * coeffRow * TOTAL_VALS; copier++){
            coefficients[copier] = coefficientsCopy[copier];
        }
        // printModColArray(coefficients, coeffRow * coeffCol, coeffCol, TOTAL_VALS);
    }
}

inline int rolling_hash(int r, int g, int b){
    return r + (HASHING_PRIME * g) + (HASHING_PRIME * HASHING_PRIME * b);
}

void get_rgb(int hashed_val, vector<int> &rgb){
    // vector<int> rgb(3, NOT_DEFINED);
    rgb[0] = hashed_val % HASHING_PRIME;
    hashed_val /= HASHING_PRIME;
    rgb[1] = hashed_val % HASHING_PRIME;
    hashed_val /= HASHING_PRIME;
    assert(hashed_val == hashed_val % HASHING_PRIME);
    rgb[2] = hashed_val;
}

inline int get_val(unsigned char *data, int i, int j, int n, int y){
    return rolling_hash((int)data[i*y*n+j*n], (int)data[i*y*n + j*n + 1], (int)data[i * y * n + j * n + 2]);
}

void read_input_image(const char *filename){
    // const char *filename = path.c_str();
    int x, y, n = 4;
    unsigned char *data = stbi_load(filename, &x, &y, &n, 3);
    fstream temp_file;
    temp_file.open(TEMP_OUT, ios::out);
    for (int i = 0; i < y; ++i){
        for (int j = 0; j < x - 1; ++j){
            temp_file << get_val(data, i, j, n, y);
            temp_file << " ";
        }
        temp_file << get_val(data, i, x - 1, n, y);
        temp_file << endl;
    }
    temp_file.close();
    stbi_image_free(data);
}

void write_image(const char *filename, int *coeffs, int total_size, int dim){
    unsigned char * data;
    data = (unsigned char*) malloc(3 * total_size * sizeof(unsigned char));
    int curVal;
    vector<int> rgb(3, NOT_DEFINED);
    int index = 0;
    for (int i = 0; i < total_size; ++i){
        for (int j = 0; j < TOTAL_VALS; ++j){
            if (coeffs[i * TOTAL_VALS + j] != 0){
                curVal = coeffs[i * TOTAL_VALS + j];
                get_rgb(curVal, rgb);
                data[index++] = (unsigned char)(rgb[0]);
                data[index++] = (unsigned char)(rgb[1]);
                data[index++] = (unsigned char)(rgb[2]);
            }
        }
    }
    assert(index == total_size * 3);
    assert(total_size == dim * dim);
    // for (int i = 0; i < x; ++i){
    //     for (int j = 0; j < y; ++j){
    //         curVal = coeffs[i*x + j];
    //         get_rgb(curVal, rgb);
    //         data[i*x*3 + y * 3] = (unsigned char)(rgb[0]);
    //         data[i*x*3 + y * 3 + 1] = (unsigned char)(rgb[1]);
    //         data[i*x*3 + y * 3 + 2] = (unsigned char)(rgb[2]);
    //     }
    // }
    stbi_write_bmp(filename, dim, dim, 3, data);
    free(data);
}
// void printModColArray(int* coefficients, int productRowCol, int outputCol, int TOTAL_CHAR){
//     for(int i = 0; i < productRowCol; i++){
//         for(int j = 0; j < TOTAL_CHAR; j++){
//             if (coefficients[i*TOTAL_CHAR + j] != 0)
//                 printf("%c", coefficients[i*TOTAL_CHAR + j]);
//         }
//         cout<<"|";
//         if ((i+1) % outputCol == 0)
//             cout << endl;
//     }
//     cout << endl;
// }


int main(int argc, char *argv[])
{
    srand(5234);

    // FILE *stream;
    assert(!input_file.is_open());
    // char *filename = argv[1];
    // string filename = argv[1];
    // assert(filename != NULL);
    char *filename2 = argv[1];
    assert(filename2 != NULL);
    string fname = TEMP_OUT;

    const char *filename = fname.c_str();
    read_input_image(filename2);
    // return 0;
    // stream = fopen(filename, "r");
    input_file.open(filename, ios::in);
    if (!input_file.is_open()) {
        perror("ERROR: No input file given");
        exit(EXIT_FAILURE);
    }
    if (TRACE) cout << "Opening file " << filename << endl;
    // printf("Opening file %s\n", filename);

    int inputRow = 0, inputCol = 0; // Size loops
    // char uniqueChar[256]; // Implies 256 char limit on input
    // int charWeight[256] = {0};
    // int uniqueVal[256];
    // int charWeight[256] = {0};
    // char uniqueChar[40000];
    // int charWeight[40000] = {0};

    // int uniqueVal[16908285];
    // int charWeight[16908285] = {0};
    int *uniqueVal = new int[16908285];
    int *charWeight = new int[16908285];
    memset(uniqueVal, NOT_DEFINED, 16908285 * sizeof(int));
    memset(uniqueVal, 0, 16908285 * sizeof(int));
    fillBlankChar(uniqueVal);
    input_file.close();
    getRowAndColAndVal(inputRow, inputCol, uniqueVal, filename);
    // getRowAndColAndChar(inputRow, inputCol, uniqueChar, stream);
    // if (TRACE) printf("File size: %d rows, %d cols\n", inputRow, inputCol);
    if (TRACE) cout << "File size: " << inputRow << " rows, " << inputCol << " cols\n";
    Tile compatibleMatrix[(inputRow + 1) * (inputCol + 1)]; 
    
    // rewind(stream);
    // input_file.clear();
    // input_file.seekg(0);
    input_file.open(filename, ios::in);

    // readInput(compatibleMatrix, uniqueChar, charWeight, stream);
    readInput(compatibleMatrix, uniqueVal, charWeight);

    if (TRACE) {
        printf("Input chars:\n");
        // printArray(uniqueChar, TOTAL_CHAR);
        printArray(uniqueVal, TOTAL_VALS);
        printf("Input chars:\n");
        printArray(charWeight, TOTAL_VALS);
        printf("Input matrix:\n");
        printArray(compatibleMatrix, inputRow, inputCol);
    }

    // fclose(stream);
    input_file.close();

    resolveMatrix(compatibleMatrix, inputRow, inputCol);

    int outputRow = atoi(argv[2]);
    int outputCol = atoi(argv[3]);
    int outputSize = outputRow * outputCol;
    if (TRACE) printf("Output matrix size: (%d,%d)\n", outputRow, outputCol);

    int* coefficients = new int[outputSize * TOTAL_VALS];
    // fillCoeff(coefficients, uniqueChar, outputSize);
    fillCoeff(coefficients, uniqueVal, outputSize);

    // if (TRACE){
    //     printf("Coefficients:\n");
    //     printCharArray(coefficients, outputSize * TOTAL_CHAR);
    //     printf("\n");
    //     // // printModArray(coefficients, outputSize, TOTAL_CHAR);
    //     printModColArray(coefficients, outputSize, outputCol, TOTAL_CHAR);
    // }

    int* isCollapsedArray = new int[outputSize];
    for(int i = 0; i < outputSize; i++){
        isCollapsedArray[i] = 2;
    }

    int* coefficientsCopy = new int[outputSize * TOTAL_VALS];

    // for(int i =0; i < 1; i++){
    while(isFullyCollapsed(isCollapsedArray, outputSize) == 0){
        // printModColArray(coefficients, outputSize, outputCol, TOTAL_CHAR);
        int mEntIndex = minEntropyIndex(coefficients, charWeight, uniqueVal, outputSize);
        if (TRACE) printf("Min entropy Index is %d \n", mEntIndex);
        collapse(coefficients, mEntIndex, charWeight, uniqueVal);
        if (TRACE) printf("After collapse, coefficients:\n");
        if (TRACE) printModColArray(coefficients, outputSize, outputCol, TOTAL_VALS);

        for(int copier=0; copier < outputSize * TOTAL_VALS; copier++){
            coefficientsCopy[copier] = coefficients[copier];
        }

        propagate(compatibleMatrix, isCollapsedArray, inputRow, inputCol, coefficients, coefficientsCopy, outputRow, outputCol, mEntIndex);
        if (TRACE) printf("Propagation is as follows \n");
        if (TRACE) printModColArray(coefficients, outputSize, outputCol, TOTAL_VALS);
        fillCollapsed(isCollapsedArray, coefficients, outputSize);
    //     printf("===========\n");
    }
    char *outfile = argv[4];
    if (outfile == NULL) outfile = "test_output.bmp";
    // printModColArray(coefficients, outputSize, outputCol, TOTAL_VALS);
    write_image(outfile, coefficients, outputSize, outputCol);
    // system("rm -f temp_out.txt");
    // free(uniqueVal);
    // free()
    delete[] uniqueVal;
    delete[] charWeight;
    delete[] coefficients;
    delete[] coefficientsCopy;
    return 0;
}