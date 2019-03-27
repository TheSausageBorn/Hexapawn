#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class Pawn{


private:
    string team_;
    int id_;


public:

    // constructor de objetos Pawn
    Pawn(string team = "none", int id = 0)
    {
        team_ = team;
        id_ = id;
  	}

    Pawn(Pawn const &pawn)
    {
        team_ = pawn.getTeam();
        id_ = pawn.getId();
  	}



    string getTeam() const
    {
        return team_;
    }

    int getId() const
    {
        return id_;
    }

    void setTeam(string team)
    {
        team_ = team;
    }

    void setId(int id)
    {
        id_ = id;
    }

};


class Board {
private:
    Pawn*** tablero_;

public:

    // constructor del objeto Board
    Board ()
    {
        // crea el tablero (memoria)
        tablero_ = (Pawn***)calloc(3, sizeof(Pawn**));

    	for (int i = 0; i < 3; i++){
    		tablero_[i] = (Pawn**)calloc(3, sizeof(Pawn*));
            for(int j = 0; j < 3; j++){
            	tablero_[i][j] = (Pawn*)calloc(1,sizeof(Pawn));
            }
        }

        // mete las fichas en el tablero (llena la memoria)
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(i == 0){
                    tablero_[i][j] = new Pawn ("Blanco", j);
                }
                if(i == 1){
                    tablero_[i][j] = NULL;
                }
                if(i == 2){
                    tablero_[i][j] = new Pawn ("Negro", j);
                }
            }
        }
    }


    // destructor del objeto Board
    ~Board ()
    {
        for (int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
            	free(tablero_[i][j]);
            }
            free(tablero_[i]);
        }
    	free(tablero_);
    }


    // calcula si alguien ha ganado
    bool isWinScenario()
    {
        // condicion de solo quedan negras o blancas

        int blancas = 0;
        int negras = 0;

        for (int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++)
            {

                if (tablero_[i][j] != NULL) {
                    if (tablero_[i][j]->getTeam() == "Negro"){
                        negras++;
                    }
                    else{
                        if(tablero_[i][j]->getTeam() == "Blanco"){
                        blancas++;
                        }
                    }
                }

            }
        }

        if(negras == 0 || blancas == 0){
            return true;
        }



        // condicion de que las blancas o las negras lleguen al borde el otro

        for (int j = 0; j < 3; j++) {
            if (tablero_[2][j] != NULL && tablero_[2][j]->getTeam() == "Blanco") {
                return true;
            }
            if (tablero_[0][j] != NULL && tablero_[0][j]->getTeam() == "Negro") {
                return true;
            }
        }

        // condicion de que las blancas o las negras no tienen movimientos posibles

        bool blanco_se_puede_mover = false;
                bool negro_se_puede_mover = false;

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if(tablero_[i][j] != NULL){
                            if(tablero_[i][j]->getTeam() == "Blanco"){
                                blanco_se_puede_mover = blanco_se_puede_mover || canMoveForward(i, j) || canKillLeft(i, j) || canKillRight(i, j);
                            }else{
                                negro_se_puede_mover = negro_se_puede_mover || canMoveForward(i, j) || canKillLeft(i, j) || canKillRight(i, j);
                            }
                        }
                    }
                }
                if (!blanco_se_puede_mover || !negro_se_puede_mover){
                    return true;
                }
        return false;
    }

    // en caso de que alguien haya ganado devuelve el equipo ganador
    string getWinnerTeam()
    {
        int blancas = 0;
        int negras = 0;

        for (int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++)
            {

                if (tablero_[i][j] != NULL) {
                    if (tablero_[i][j]->getTeam() == "Negro"){
                        negras++;
                    }
                    else (tablero_[i][j]->getTeam() == "Blanco");{
                        blancas++;
                    }
                }

            }
        }

        if(negras == 0){
            return "Las blancas han ganado!";
        }
        else{
            return "Las negras han ganado!";
        }



        // condicion de que las blancas o las negras lleguen al borde el otro

        for (int j = 0; j < 3; j++) {
            if (tablero_[2][j] != NULL && tablero_[2][j]->getTeam() == "Blanco") {
                return "Las blancas han ganado!";
            }
            if (tablero_[0][j] != NULL && tablero_[0][j]->getTeam() == "Negro") {
                return "Las negras han ganado!";
            }
        }

        // condicion de que las blancas o las negras no tienen movimientos posibles

        bool blanco_se_puede_mover = false;
        bool negro_se_puede_mover = false;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(tablero_[i][j] != NULL){
                    if(tablero_[i][j]->getTeam() == "Blanco"){
                        blanco_se_puede_mover == blanco_se_puede_mover || canMoveForward(i, j) || canKillLeft(i, j) || canKillRight(i, j);
                    }else{
                        negro_se_puede_mover == negro_se_puede_mover || canMoveForward(i, j) || canKillLeft(i, j) || canKillRight(i, j);
                    }
                }
            }
        }
        if (!blanco_se_puede_mover){
            return "Las blancas han ganado!";
        }
        else{
            return "Las negras han ganado!";
        }


    }



    // calcula si la pieza seleccionada pueder mover hacia delante
    bool canMoveForward(int i, int j){
        if(tablero_[i][j]->getTeam() == "Blanco"){ // logica directa
            if(tablero_[i+1][j] == NULL && i < 2){
                return true;
            }
        }else{ //logica invertida
            if(tablero_[i-1][j] == NULL && i > 0){
                return true;
            }
        }


        return false;
    }

    // calcula si la pieza seleccionada puede matar hacia la derecha
    bool canKillRight(int i, int j){
        if(tablero_[i][j]->getTeam() == "Blanco"){
            if(tablero_[i+1][j+1]->getTeam() == "Negro"){
                return true;
            }
        }
        else{
            if(tablero_[i-1][j+1]->getTeam() == "Blanco"){
                return true;
            }
        }

        return false;
    }

    // calcula si la pieza seleccionada puede matar hacia la izquierda
    bool canKillLeft(int i, int j){
        if(tablero_[i][j]->getTeam() == "Blanco"){
            if(tablero_[i+1][j-1]->getTeam() == "Negro"){
                return true;
            }
        }
        else{
            if(tablero_[i-1][j-1]->getTeam() == "Blanco"){
                return true;
            }
        }

            return false;
    }


    // mueve la pieza seleccionada hacia delante
    bool moveForward(int i, int j)
    {

        if(!canMoveForward(i, j)){
            return false;
        }

        if(tablero_[i][j]->getTeam() == "Blanco"){ // logica directa
            tablero_[i+1][j] = tablero_[i][j];
            tablero_[i][j] = NULL;
        }
        else{ //logica invertida
          tablero_[i-1][j] = tablero_[i][j];
          tablero_[i][j] = NULL;
        }


        return true;
    }

    // mueve la pieza seleccionada comiendo hacia la derecha
    bool killRight(int i, int j)
    {
        if(!canKillRight(i, j)){
            return false;
        }

        if(tablero_[i][j]->getTeam() == "Blanco"){
            tablero_[i+1][j+1] = tablero_[i][j];
            tablero_[i][j] = NULL;
        }
        else{
            tablero_[i-1][j+1] = tablero_[i][j];
            tablero_[i][j] = NULL;
        }

        return true;
    }

    // mueve la pieza seleccionada comiendo hacia la izquierda
    bool killLeft(int i, int j)
    {
        if(!canKillLeft(i, j)){
            return false;
        }

        if(tablero_[i][j]->getTeam() == "Blanco"){
            tablero_[i+1][j-1] = tablero_[i][j];
            tablero_[i][j] = NULL;
        }
        else{
            tablero_[i-1][j-1] = tablero_[i][j];
            tablero_[i][j] = NULL;
        }

        return true;
    };

    Pawn& getPawn(int i, int j) const
    {
        if (tablero_[i][j] != NULL){
            return *new Pawn(*tablero_[i][j]);
        }
        else{
            return *new Pawn();
        }
    }


    void printTablero()
    {
        for (int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if (!tablero_[i][j]) {
                    cout<<"  0  , ";
                }
                else{
                    cout<<tablero_[i][j]->getTeam()<<" "<<tablero_[i][j]->getId()<<", ";
                }
            }
            cout<<'\n'<< endl;
        }
    }


    void userMove()
    {
        int i;
        int j;
        bool moveOk = false;
        bool optionOk = false;
        int option;

        cout<<"Selecciona las coordenadas de la ficha que quieres mover\n\ti: ";
        cin>>i;
        cout<<"\tj: ";
        cin>>j;

        cout<<"\nSelecciona que movimiento quieres realizar: \n";
        cout << "[1] mover hacia delante" << '\n';
        cout << "[2] comer hacia la derecha" << '\n';
        cout << "[3] comer hacia la izquerda" << '\n';
        cout << "introduzca su jugada: ";
        cin >> option;

        if(tablero_[i][j] != NULL && option <= 3 && option >=1){
            optionOk = true;
        }
        else{
            cout << endl << endl << "Ese movimiento es ilegal, repita su jugada." << endl << endl << endl;
        }

        while (!moveOk)
        {
            while(!optionOk)
            {
                cout<<"\nSelecciona las coordenadas de la ficha que quieres mover\n\ti: ";
                cin>>i;
                cout<<"\tj: ";
                cin>>j;

                cout<<"\nSelecciona que movimiento quieres realizar: \n";
                cout << "[1] mover hacia delante" << '\n';
                cout << "[2] comer hacia la derecha" << '\n';
                cout << "[3] comer hacia la izquerda" << '\n';
                cout << "introduzca su jugada: ";
                cin >> option;
                cout << endl << endl;

                if(tablero_[i][j]->getTeam() == "Blanco" && option <= 3 && option >=1){
                    optionOk = true;
                }
                else{
                    cout << endl << endl << "Ese movimiento es ilegal, repita su jugada." << endl << endl << endl;
                    printTablero();
                }
            }

            if(option == 1)
            {
                if(canMoveForward(i, j)){
                    moveForward(i, j);
                    moveOk = true;
                }
            }

            if(option == 2)
            {
                if(canKillRight(i, j)){
                    killRight(i, j);
                    moveOk = true;
                }
            }


            if(option == 3)
            {
                if(canKillLeft(i, j)){
                    killLeft(i, j);
                    moveOk = true;
                }
            }

        }
    }

};


// imprime el tablero


// selecciona un movimiento


int main()
{
    Board board;

    // game logic
    board.printTablero();

    while(!board.isWinScenario())
    {
        board.userMove();

        board.printTablero();
    }

    return 0;
}
