#include <iostream>
#include <climits>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stack>
#include <stb_image.h>

typedef struct tile Tile;

using namespace std;

int TRACE = 0;
int TOTAL_CHAR = 0;

struct tile
{
    char tileChar;
    char upTileChar, downTileChar, leftTileChar, rightTileChar;
};

int intToASCII(int number){
    return '0' + number;
}

void fillBlankChar(char* uniqueChar){
    for(int i = 0; i < 256; i++){ 
        uniqueChar[i] = '\0';
    }
}

int checkForChar(char* uniqueChar, char inputChar){
    for(int i = 0; i < TOTAL_CHAR; i++){ 
        if(uniqueChar[i] == inputChar)
            return i;
    }
    return -1;
}

int checkForCharByInt(char* uniqueChar, int inputChar){
    for(int i = 0; i < TOTAL_CHAR; i++){ 
        int carCheck = (int)uniqueChar[i]; 
        if(carCheck == inputChar)
            return i;
    }
    return -1;
}

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

void printModArray(int* coefficients, int productRowCol, int TOTAL_CHAR){
    for(int i = 0; i < productRowCol; i++){
        for(int j = 0; j < TOTAL_CHAR; j++){
            if (coefficients[i*TOTAL_CHAR + j] != 0)
                printf("%c", coefficients[i*TOTAL_CHAR + j]);
        }
        cout<<"|";
    }
    cout << endl;
}

void printModColArray(int* coefficients, int productRowCol, int outputCol, int TOTAL_CHAR){
    for(int i = 0; i < productRowCol; i++){
        for(int j = 0; j < TOTAL_CHAR; j++){
            if (coefficients[i*TOTAL_CHAR + j] != 0)
                printf("%c", coefficients[i*TOTAL_CHAR + j]);
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
            cout << compatibleMatrix[i*inputCol + j].tileChar << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void getRowAndColAndChar(int &row, int &col, char* uniqueChar, FILE* stream){
    char inputValue;
    int colFlag = 0;
    while ((inputValue = getc(stream)) != EOF) {
        if(inputValue != '\n'){
            if (inputValue != ' ') {
                if(!colFlag) col++;
                if (checkForChar(uniqueChar, inputValue) == -1) {
                    uniqueChar[TOTAL_CHAR] = inputValue;
                    TOTAL_CHAR++;
                }
            }
        }
        else{
            colFlag = 1;
            row++;
        }
    }
}

void readInput(Tile* compatibleMatrix, char* uniqueChar, int* charWeight, FILE* stream){
    char inputValue;
    int i = 0;
    while ((inputValue = getc(stream)) != EOF) {
        if(inputValue != '\n' && inputValue != ' '){
            compatibleMatrix[i].tileChar = inputValue;
            i++;
            charWeight[checkForChar(uniqueChar, inputValue)]++;
        }
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
    return -1;
}

void resolveMatrix(Tile* parseMatrix, int &row, int &col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            Tile* curTile = &parseMatrix[i*col + j];
            int getDirIndex;
            getDirIndex = validDirection(row, col, i, j, 0);
            if (getDirIndex != -1) curTile->upTileChar = parseMatrix[getDirIndex].tileChar;
            else curTile->upTileChar = '\0';

            getDirIndex = validDirection(row, col, i, j, 1);
            if (getDirIndex != -1) curTile->downTileChar = parseMatrix[getDirIndex].tileChar;
            else curTile->downTileChar = '\0';
            
            getDirIndex = validDirection(row, col, i, j, 2);
            if (getDirIndex != -1) curTile->leftTileChar = parseMatrix[getDirIndex].tileChar;
            else curTile->leftTileChar = '\0';

            getDirIndex = validDirection(row, col, i, j, 3);
            if (getDirIndex != -1) curTile->rightTileChar = parseMatrix[getDirIndex].tileChar;
            else curTile->rightTileChar = '\0';
        }
    }       
}

void fillCoeff(int* coefficients, char* uniqueChar, int size){
    for(int i = 0; i < size; i++){
        for (int j = 0; j < TOTAL_CHAR; j++) {
            coefficients[i*TOTAL_CHAR + j] = uniqueChar[j];
        }
    }
}

int getTilesAtIndex(int* coefficients, int index){
    int sum = 0;
    for(int i = 0; i < TOTAL_CHAR; i++){
        if (coefficients[index*TOTAL_CHAR + i] != 0) 
            sum ++;
    }
    return sum;
}

int isFullyCollapsed(int* coefficients, int outputSize){
    for(int i = 0; i < outputSize; i++){
        int count = getTilesAtIndex(coefficients, i);
        if (count > 1) return 0;
        if (count == 0) {
            printf("ERROR: Collapse failure\n");
            exit(1);
        }
    }
    return 1;
}

float shannonEntropy(int* coefficients, int index, int* charWeight, char* uniqueChar) {
    float sumOfWeights = 0;
    float sumOfLogWeights = 0;
    for (int i = 0; i < TOTAL_CHAR; i++) {
        int currentChar = coefficients[index*TOTAL_CHAR + i];
        if (currentChar != 0) {
            int curWeight = charWeight[checkForCharByInt(uniqueChar, currentChar)];
            sumOfWeights += curWeight;
            sumOfLogWeights += curWeight * log(curWeight);
        }
    }
    return log(sumOfWeights) - sumOfLogWeights / sumOfWeights;
}

int minEntropyIndex(int* coefficients, int* charWeight, char* uniqueChar, int outputSize){
    float minEntropy = INT_MAX;
    int minEntropyIndex = -1;
    for(int i = 0; i < outputSize; i++){
        if (getTilesAtIndex(coefficients, i) == 1)
            continue;
        float entropy = shannonEntropy(coefficients, i, charWeight, uniqueChar) - 0.1 * ((double) rand() / (RAND_MAX));
        if (entropy < minEntropy) { // Use the BattleCode feature here, or add noise
            minEntropy = entropy;
            minEntropyIndex = i;
        }
    }
    return minEntropyIndex;
}

void collapse(int* coefficients, int index, int* charWeight, char* uniqueChar){
    float maxweight = -1;
    int chosenIndex = -1;
    for (int i = 0; i < TOTAL_CHAR; i++) {
        int currentChar = coefficients[index*TOTAL_CHAR + i];
        if (currentChar != 0) {
            float curWeight = ((double) rand() / (RAND_MAX)) * charWeight[checkForCharByInt(uniqueChar, currentChar)];
            if (curWeight > maxweight) {
                maxweight = curWeight;
                chosenIndex = i;
            }
        }
    }    
    // printf("Chosen index is %d \n", chosenIndex);
    for (int i = 0; i < TOTAL_CHAR; i++) {
        if (i != chosenIndex){
            coefficients[index*TOTAL_CHAR + i] = 0;
        }
    }
}

int checkMatch(Tile* compatibleMatrix, int comRow, int comCol, char firstChar, char secondChar, int direction){
    for(int i = 0; i < comRow; i++){
        for(int j = 0; j < comCol; j++){
            Tile* curTile = &compatibleMatrix[i*comCol + j];
            if (curTile->tileChar != firstChar){
                continue;
            }
            if (direction == 0){ //UP
                if(curTile->upTileChar == secondChar){
                    return 1;
                }
            }
            else if(direction == 1){ //DOWN
                if(curTile->downTileChar == secondChar){
                    return 1;
                }
            }
            else if(direction == 2){ //LEFT
                if(curTile->leftTileChar == secondChar){
                    return 1;
                }
            }
            else if(direction == 3){ //RIGHT
                if(curTile->rightTileChar == secondChar){
                    return 1;
                }
            }
        }
    }
    return 0;
}

void propagate(Tile* compatibleMatrix, int comRow, int comCol, int* coefficients, int coeffRow, int coeffCol, int index){
    stack<int> tilesToPropagate;
    tilesToPropagate.push(index);
    while(!tilesToPropagate.empty()){
        int curIndex = tilesToPropagate.top();
        tilesToPropagate.pop();
        for (int dir=0; dir< 4; dir++){ // Get direction
            int otherIndex = validDirection(coeffRow, coeffCol, curIndex/coeffCol, curIndex%coeffCol, dir); // Get 2nd tile
            if (otherIndex == -1) continue; // If no tile, continue

            // if(TRACE) printf("Checking direction %d and other index %d\n", dir, otherIndex);
            int willPush = 0;
            for(int j = 0; j < TOTAL_CHAR; j++){
                char otherChar = coefficients[otherIndex*TOTAL_CHAR + j]; // Got one of the other tile's chars
                // if(TRACE) printf("Enemy char is %c\n", otherChar);
                if (otherChar != 0){
                    int removeFlag = 0;
                    for (int i = 0; i < TOTAL_CHAR; i++){ // Check if completely illegal
                        char curChar = coefficients[curIndex*TOTAL_CHAR + i];
                        if (curChar == 0){
                            continue;
                        }
                        // if(TRACE) printf("Friendly char is %c\n", curChar);
                        int matchIndex = checkMatch(compatibleMatrix, comRow, comCol, curChar, otherChar, dir);
                        // if(TRACE) printf("Match index is %d\n", matchIndex);
                        if (matchIndex != 0){ // Does match with atleast one neighbour, don't remove this character
                            removeFlag = 1;
                        }
                    }
                    if (removeFlag == 0){
                        willPush = 1;
                        coefficients[otherIndex*TOTAL_CHAR + j] = 0;    
                    }
                }
            }
            if (willPush == 1){
                tilesToPropagate.push(otherIndex);
            }
        }
        // printModColArray(coefficients, coeffRow * coeffCol, coeffCol, TOTAL_CHAR);
    }
}


// char * read_input_image(string path){
//     const char *filename = path.c_str();
//     int x, y, n = 4;
//     unsigned char *data = stbi_load(filename, &x, &y, &n, 3);

//     stbi_image_free(data);
// }


int main(int argc, char *argv[])
{
    srand(5234);

    FILE *stream;
    char *filename = argv[1];
    assert(filename != NULL);
    stream = fopen(filename, "r");
    if (stream == NULL) {
        perror("ERROR: No input file given");
        exit(EXIT_FAILURE);
    }
    if (TRACE) printf("Opening file %s\n", filename);

    int inputRow = 0, inputCol = 0; // Size loops
    char uniqueChar[256]; // Implies 256 char limit on input
    int charWeight[256] = {0};
    fillBlankChar(uniqueChar);
    getRowAndColAndChar(inputRow, inputCol, uniqueChar, stream);
    if (TRACE) printf("File size: %d rows, %d cols\n", inputRow, inputCol);
    Tile compatibleMatrix[(inputRow + 1) * (inputCol + 1)]; 
    
    rewind(stream);

    readInput(compatibleMatrix, uniqueChar, charWeight, stream);

    if (TRACE) {
        printf("Input chars:\n");
        printArray(uniqueChar, TOTAL_CHAR);
        printf("Input chars:\n");
        printArray(charWeight, TOTAL_CHAR);
        printf("Input matrix:\n");
        printArray(compatibleMatrix, inputRow, inputCol);
    }

    fclose(stream);

    resolveMatrix(compatibleMatrix, inputRow, inputCol);

    int outputRow = atoi(argv[2]);
    int outputCol = atoi(argv[3]);
    int outputSize = outputRow * outputCol;
    if (TRACE) printf("Output matrix size: (%d,%d)\n", outputRow, outputCol);

    int* coefficients = new int[outputSize * TOTAL_CHAR];
    fillCoeff(coefficients, uniqueChar, outputSize);

    if (TRACE){
        printf("Coefficients:\n");
        printCharArray(coefficients, outputSize * TOTAL_CHAR);
        printf("\n");
        // // printModArray(coefficients, outputSize, TOTAL_CHAR);
        printModColArray(coefficients, outputSize, outputCol, TOTAL_CHAR);
    }

    // for(int i =0; i < 1; i++){
    while(!isFullyCollapsed(coefficients, outputSize)){
        // printModColArray(coefficients, outputSize, outputCol, TOTAL_CHAR);
        int mEntIndex = minEntropyIndex(coefficients, charWeight, uniqueChar, outputSize);
        if (TRACE) printf("Min entropy Index is %d \n", mEntIndex);
        collapse(coefficients, mEntIndex, charWeight, uniqueChar);
        if (TRACE) printf("After collapse, coefficients:\n");
        if (TRACE) printModColArray(coefficients, outputSize, outputCol, TOTAL_CHAR);
        propagate(compatibleMatrix, inputRow, inputCol, coefficients, outputRow, outputCol, mEntIndex);
        if (TRACE) printf("Propagation is as follows \n");
        if (TRACE) printModColArray(coefficients, outputSize, outputCol, TOTAL_CHAR);
    //     printf("===========\n");
    }

    printModColArray(coefficients, outputSize, outputCol, TOTAL_CHAR);
    delete[] coefficients;
    return 0;
}