#pragma once

#include <iostream>
#include <cmath>
#include <string>

// Визначення перерахувань для типів шахових фігур та кольорів
enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };

class Square
{
	Piece piece;
	Color color;
	int x, y;
public:
	
	// Встановлює простір на основі іншого простору
	
	void setSpace(Square*);
	
	// Встановлює порожній простір
	
	void setEmpty();
	
	// Встановлює фігуру та колір простору
	
	void setPieceAndColor(Piece, Color);
	
	// Повертає фігуру простору
	
	Piece getPiece();
	
	// Повертає колір простору
	
	Color getColor();
	
	// Встановлює значення x
	
	void setX(int ex) { x = ex; }
	
	// Встановлює значення y
	
	void setY(int why) { y = why; }
	
	// Повертає значення x
	
	int getX() { return x; }
	
	// Повертає значення y
	
	int getY() { return y; }
	
	// Конструктор
	
	Square();
};

class Board
{
	Square square[8][8];
	Color turn = WHITE;
	
	// Перевіряє можливість ходу для короля
	
	bool moveKing(Square* thisKing, Square* thatSpace);
	
	// Перевіряє можливість ходу для ферзя
	
	bool moveQueen(Square* thisQueen, Square* thatSpace);
	
	// Перевіряє можливість ходу для слона
	
	bool moveBishop(Square* thisBishop, Square* thatSpace);
	
	// Перевіряє можливість ходу для коня
	
	bool moveKnight(Square* thisKnight, Square* thatSpace);
	
	// Перевіряє можливість ходу для тура
	
	bool moveRook(Square* thisRook, Square* thatSpace);
	
	// Перевіряє можливість ходу для пішака
	
	bool movePawn(Square* thisPawn, Square* thatSpace);
	
	// Виконує хід з позиції (x1, y1) на позицію (x2, y2)
	
	bool makeMove(int x1, int y1, int x2, int y2);
	
	// Виводить дошку на екран
	
	void printBoard();
public:
	
	// Повертає простір за позицією (x, y)
	
	Square* getSquare(int x, int y) {
		return &square[x][y];
	}
	
	// Встановлює простір на позицію (x, y)
	
	void setSquare(Square* s, int x, int y) {
		square[x][y] = *s;
	}
	
	// Виконує хід
	
	bool doMove();
	
	// Ініціалізує дошку
	
	void setBoard();
	
	// Починає гру
	
	bool playGame();
};
