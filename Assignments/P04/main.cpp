#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

#define CELLSIZE 10

using namespace std;
using namespace sf;

/**
 * lifeCell : A single instance of a cell in a Game of Life array
 * @Extends:
 *   sf::Drawable
 * @Data-Elements:
 *     RectangleShape rect;    // sfml rectangle type
 *     bool alive;        // is cell alive or not
 * @Methods:
 *     void draw(RenderTarget& target, RenderStates state) const
 */
struct lifeCell : public Drawable {
    RectangleShape rect;
    bool alive;
    int neighborCount;
protected:
    /**
     * void draw: draws an SFML shape to an SFML window.
     */
    void draw(RenderTarget& target, RenderStates state) const // means this method won't change
    // anything...
    {
        target.draw(rect);
    }
};

/**
 * Starter class to represent game of life
 */
class gameOfLife {
private:
    lifeCell **World;                // double pointer to a lifeCell (defined above)
    int Rows;                    // num rows in game board
    int Cols;                    // num cols in game board
    RenderWindow &WindowRef;    // reference to sfml window so we can draw to it.
    string line;

//    /**
//     * Creates the game board, resets it (0's it out), then randomly populates it.
//     */
//    void init() {
//
//        World = new lifeCell *[Rows];
//
//        for (int i = 0; i < Rows; i++) {
//            World[i] = new lifeCell[Cols];
//        }
//
//        resetBoard();
//    }
    
public:
//    /**
//     * GameOfLife Constructor extends sfml WindowRef
//     * @param:
//     *    RenderWindow : a reference to our sfml window
//     *
//     */
    gameOfLife(RenderWindow &thatWindow,ifstream &infile) : WindowRef(thatWindow) {
        initBoard(infile);
    }

//    /**
//     * GameOfLife Constructor extends sfml WindowRef
//     * @param:
//     *    RenderWindow : a reference to our sfml window
//     *    int rows : num of rows in board
//     *    int cols : num of cols in board
//     *
//     */
    gameOfLife(RenderWindow &thatWindow, int rows, int cols,ifstream &infile) : WindowRef(thatWindow) {
        initBoard(infile);
    }
    
    void print(){
        for(int i = 0; i < Rows; i++){
            for(int j = 0; j < Cols; j++){
                cout << World[i][j].alive;
            }
            cout << endl;
        }
    }
    //    /**
    //     * Function: rulse
    //     *     Runs the rules GOL:
    //     *        less than two the cell dies
    //     *        more than three the cell dies
    //     *        two or three the cell lives
    //     *
    //     *
    //     * @param:
    //     *    None
    //     * @returns:
    //     *       True or false
    //     */
    
    void rules(){
        for(int i = 0; i < Rows; i++){
            for(int j = 0; j < Cols; j++){
                if(World[i][j].neighborCount < 2){
                    World[i][j].alive = 0;
                }
                 if(World[i][j].neighborCount > 3){
                    World[i][j].alive = 0;
                }
                 if(World[i][j].neighborCount == 2 ||World[i][j].neighborCount == 3){
                    World[i][j].alive = 1;
                }
            }
        }
        
        
    }
    //    /**
    //     * Function: onWorld
    //     *     Tests if World[i][j] is on the board
    //     * @param:
    //     *    None
    //     * @returns:
    //     *       True or false
    //     */
    
    bool onWorld(int i,int j){
        return (i >=0 && i < Rows && j >= 0 && j < Cols);
    }
    
    //    /**
    //     * Function: neighborCount
    //     *     Cheks to see if neighbors are on the world and if the cell is alive
    //     *     increases the neighborcount
    //     * @param:
    //     *    None
    //     * @returns:
    //     *       None
    //     */
    
    void neighborCount(){
        for(int i = 0; i < Rows; i++){
            for(int j = 0; j < Cols; j++){
                    if(onWorld(i+1,j+1) && World[i+1][j+1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                    if(onWorld(i+1,j) && World[i+1][j].alive == 1){
                        World[i][j].neighborCount++;
                    }
                    if(onWorld(i,j+1) && World[i][j+1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                    if(onWorld(i-1,j-1) && World[i-1][j-1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                    if(onWorld(i-1,j) && World[i-1][j].alive == 1){
                        World[i][j].neighborCount++;
                    }
                    if(onWorld(i,j-1) && World[i][j-1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                    if(onWorld(i-1,j+1) && World[i-1][j+1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                    if(onWorld(i+1,j-1) && World[i+1][j-1].alive == 1){
                        World[i][j].neighborCount++;
                    }
            }
        }
    }
    
    
//    /**
//     * Function: resetBoard
//     *     Sets the size of each rectangle to CELLSIZE (necessary?)
//     *       Also sets each cell to NOT alive
//     * @param:
//     *    None
//     * @returns:
//     *       None
//     */
    void resetBoard() {
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                World[i][j].rect.setSize(Vector2f(CELLSIZE, CELLSIZE));
                World[i][j].alive = 0;
                World[i][j].rect.setPosition((i + 1)*CELLSIZE, (j + 1)*CELLSIZE);
            }
        }
    }
    
//    /**
//     * Function: randomlyPopulate
//     *     Sets max_life number of cells to alive
//     * @param:
//     *    int max_life
//     * @returns:
//     *       None
//     */
    void randomlyPopulate(int max_life = 30) {
        int count = 0;
        int r, c;
        while (count < max_life) {
            r = rand() % Rows;
            c = rand() % Cols;
            if (World[r][c].alive == 0) {
                World[r][c].alive = 1;
                World[r][c].rect.setFillColor(Color::Green);
                count++;
            }
        }
    }
    
//    /**
//     * Function: initBoard
//     *     Prints board to an sfml window
//     * @param:
//     *    None
//     * @returns:
//     *       None
//     */
    void initBoard(ifstream &infile){
        World = new lifeCell*[Rows];
        infile >> Rows >> Cols;
        for(int i=0;i< Rows;i++){
            World[i] = new lifeCell[Cols];
        }
        
        
        for(int i = 0; i < Rows; i++){
            infile >> line;
            cout << line;
            for(int j = 0; j < Cols; j++){
                World[i][j].alive = line[j] - 48;
            }
            cout << endl;
            
        }
    }
    //    /**
    //     * Function: printBoard
    //     *     Prints board to an sfml window
    //     * @param:
    //     *    None
    //     * @returns:
    //     *       None
    //     */
    
    void printBoard() {
        int x = 0;
        int y = 0;
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                if (World[i][j].alive == 1) {
                    y = (i) * CELLSIZE;
                    x = (j) * CELLSIZE;
                    std::cout << x << "," << y << std::endl;
                    World[i][j].rect.setSize(Vector2f(CELLSIZE, CELLSIZE));
                    World[i][j].rect.setPosition((i)*CELLSIZE, (j)*CELLSIZE);
                    World[i][j].rect.setFillColor(Color::Green);
                    WindowRef.draw(World[i][j].rect);
                }
            }
        }
    }
};


/**
 * directionType : A single instance of a cell in a Game of Life array
 * Data-Elements:
 *     int x;    // x direction (positive = right)
 *     int y;    // y direction (positive = down)
 * Methods:
 *     None
 */
struct directionType {
    int x;
    int y;
    directionType() {
        x = 1;
        y = 1;
    }
};

///**
// * directionType direction:
// * @params:
// *    int rows - number of rows in 2D array
// *    int cols - numberof cols in 2D array
// * @returns: **RectangleShape (pointer)
// */
directionType direction(CircleShape shape, Vector2u winSize) {
    Vector2f position = shape.getPosition();
    
    directionType d;
    
    if (position.x >= winSize.x) {
        d.x = -1;
    }
    if (position.y >= winSize.y) {
        d.y = -1;
    }
    
    if (position.x <= 0) {
        d.x = 1;
    }
    if (position.y <= 0) {
        d.y = 1;
    }
    
    return d;
}


int main() {
    ifstream infile;
    infile.open("gen_zero.txt");
    RenderWindow window(VideoMode(600, 600), "Game of Life");
    
    int frameRate = 1;
    int frameCount = 0;
    
    Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;
    gameOfLife Gol(window, width / CELLSIZE, height / CELLSIZE,infile);
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();

        
        Gol.neighborCount();
        Gol.rules();
        Gol.print();


        if (frameCount % frameRate == 0) {
            window.display();
        }

        frameCount++;
    }
    return 0;
}
