#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class Pawn{


private:
    string team_;
    int id_;


public:

    Pawn(string team, int id)
    {
        team_ = team;
        id_ = id;
  	}



    string getTeam()
    {
        return team_;
    }

    int getId()
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
                    else (tablero_[i][j]->getTeam() == "Blanco"){
                        blancas++;
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
                        blanco_se_puede_mover == blanco_se_puede_mover || canMoveForward(i, j) || canKillLeft(i, j) || canKillRight(i, j)
                    }else{
                        negro_se_puede_mover == negro_se_puede_mover || canMoveForward(i, j) || canKillLeft(i, j) || canKillRight(i, j)
                    }
                }
            }
        }
        if (!blanco_se_puede_mover || !negro_se_puede_mover){
            return true;
        }

        return false;
    }

    string getWinnerTeam()
    {
        for (size_t i = 0; i < count; i++) {
            /* code */
        }
    }



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

    bool canKillLeft(){
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

    bool moveForward(int i, int j)
    {

        if(!canMoveForward((i, j)){
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

    bool killRight()
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

    bool killLeft()
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
    }












};

void initializeBoard(Pawn*** tablero)
{
	for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(i == 0){
                tablero[i][j] = new Pawn ("Blanco", j);
            }
            if(i == 1){
                tablero[i][j] = NULL;
            }
            if(i == 2){
                tablero[i][j] = new Pawn ("Negro", j);
            }
        }
    }
}

void printTablero(Pawn*** tablero)
{
    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (!tablero[i][j]) {
                cout<<"  0  , ";
            }
            else{
                cout<<tablero[i][j]->getTeam()<<" "<<tablero[i][j]->getId()<<", ";
            }
        }
        cout<<'\n';
    }
}

int main()
{
    Pawn*** tablero;

	tablero = (Pawn***)calloc(3, sizeof(Pawn**));

	for (int i = 0; i < 3; i++){
		tablero[i] = (Pawn**)calloc(3, sizeof(Pawn*));
        for(int j = 0; j < 3; j++){
        	tablero[i][j] = (Pawn*)calloc(1,sizeof(Pawn));
        }
    }

	initializeBoard(tablero);



    // game logic
    printTablero(tablero);



    printTablero(tablero);






	for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
        	free(tablero[i][j]);
        }
        free(tablero[i]);
    }
	free(tablero);

}
