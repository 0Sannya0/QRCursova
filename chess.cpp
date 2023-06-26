#include "chess.h"

Square::Square()
{
	// Конструктор класу Square, ініціалізує значення фігури і кольору як порожні
	
	piece = EMPTY;
	color = NONE;
}

void Square::setSpace(Square* space)
{
	// Встановлює значення фігури та кольору на основі іншого простору
	
	color = space->getColor();
	piece = space->getPiece();
}

void Square::setEmpty()
{
	// Встановлює значення фігури та кольору на порожнє значення
	
	color = NONE;
	piece = EMPTY;
}

Piece Square::getPiece()
{
	// Повертає значення фігури простору
	
	return piece;
}

Color Square::getColor()
{
	// Повертає значення кольору простору
	
	return color;
}

void Square::setPieceAndColor(Piece p, Color c)
{
	// Встановлює значення фігури та кольору простору
	
	piece = p;
	color = c;
}

void Board::printBoard() {
	
	using namespace std;
	// Виводить дошку на екран
	
	cout << "   y: 0  1  2  3  4  5  6  7 " << endl << "x:" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << " " << i << "   ";
		for (int j = 0; j < 8; j++)
		{
			Piece p = square[i][j].getPiece();
			Color c = square[i][j].getColor();

			switch (p)
			{
			case KING: (c == WHITE) ? cout << " K " : cout << " k ";
				break;
			case QUEEN: (c == WHITE) ? cout << " Q " : cout << " q ";
				break;
			case BISHOP: (c == WHITE) ? cout << " B " : cout << " b ";
				break;
			case KNIGHT: (c == WHITE) ? cout << " H " : cout << " h ";
				break;
			case ROOK: (c == WHITE) ? cout << " R " : cout << " r ";
				break;
			case PAWN: (c == WHITE) ? cout << " P " : cout << " p ";
				break;
			case EMPTY: cout << " " << "\21" << " ";
				break;
			default: cout << "XXX";
				break;
			}
		}
		cout << endl;
	}
}
     //Просить гравця ввести свій хід у вигляді чотирьох символів із координатами
bool Board::doMove() {
	using namespace std;
	string move;
	int x1, x2, y1, y2;
	bool stop = false;
	while (!stop)
	{
		(turn == WHITE) ? cout << "Хід білих" << endl : cout << "Хід чорних" << endl;
		cout << "Введіть свій хід у вигляді одного рядка з чотирьох символів. Спочатку в кожній парі використовуйте координати x." << endl;
		cin >> move;
		x1 = move[0] - 48;
		y1 = move[1] - 48;
		x2 = move[2] - 48;
		y2 = move[3] - 48;
		if (getSquare(x1, y1)->getColor() == turn)
		{
			if (makeMove(x1, y1, x2, y2) == false)
			{
				cout << "Недійсний хід, повторіть спробу." << endl;
			}
			else
				stop = true;
		}
		else
			cout << "Це не твоя фігура, спробуйте ще раз." << endl;
	}
	if (getSquare(x2, y2)->getPiece() == KING)
		if (getSquare(x1, y1)->getColor() == WHITE)
		{
			cout << "Білі перемогли" << endl;
			return false;
		}
		else
		{
			cout << "Чорні перемогли" << endl;
			return false;
		}
	if (turn == BLACK)
		turn = WHITE;
	else
		turn = BLACK;
	return true;
}

void Board::setBoard()
{
	// Ініціалізує початкову позицію фігур на дошці
	
	square[0][0].setPieceAndColor(ROOK, WHITE);
	square[1][0].setPieceAndColor(KNIGHT, WHITE);
	square[2][0].setPieceAndColor(BISHOP, WHITE);
	square[3][0].setPieceAndColor(QUEEN, WHITE);
	square[4][0].setPieceAndColor(KING, WHITE);
	square[5][0].setPieceAndColor(BISHOP, WHITE);
	square[6][0].setPieceAndColor(KNIGHT, WHITE);
	square[7][0].setPieceAndColor(ROOK, WHITE);

	square[0][7].setPieceAndColor(ROOK, BLACK);
	square[1][7].setPieceAndColor(KNIGHT, BLACK);
	square[2][7].setPieceAndColor(BISHOP, BLACK);
	square[3][7].setPieceAndColor(QUEEN, BLACK);
	square[4][7].setPieceAndColor(KING, BLACK);
	square[5][7].setPieceAndColor(BISHOP, BLACK);
	square[6][7].setPieceAndColor(KNIGHT, BLACK);
	square[7][7].setPieceAndColor(ROOK, BLACK);

	for (int i = 0; i < 8; i++)
	{
		square[i][1].setPieceAndColor(PAWN, WHITE);
		square[i][6].setPieceAndColor(PAWN, BLACK);
	

    // Ініціалізація дошки шахів із порожніми квадратами
    // Проходимо по рядках 2-5 та стовпцях 0-7 і встановлюємо кожному квадрату порожній стан та відсутність фігури на ньому.
	}
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[j][i].setPieceAndColor(EMPTY, NONE);
     
	 // Встановлюємо координати кожного квадрата на дошці.
	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}

}
    // Функція playGame відповідає за початок гри.
    // Очищуємо екран, виводимо дошку на екран та викликаємо функцію doMove().
    // Повертається результат функції doMove().

bool Board::playGame()
{
	system("cls");
	printBoard();
	return doMove();

}    //Функція moveKing відповідає за переміщення короля на дошці
     // Якщо умова виконується, король переміщується на цільовий квадрат, а поточний квадрат стає порожнім.
     // Повертається значення true, якщо переміщення вдалося.
     // Якщо умови не виконуються, повертається значення false.
bool Board::moveKing(Square* thisKing, Square* thatSpace) {
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	if (abs(thatSpace->getX() - thisKing->getX()) == 1)
		if (abs(thatSpace->getY() - thisKing->getY()) == 1)
		{
			thatSpace->setSpace(thisKing);
			thisKing->setEmpty();
			return true;
		}
		else return false;
	else return false;
}
bool Board::moveQueen(Square* thisQueen, Square* thatSpace) { 
         // Функція moveQueen відповідає за переміщення ферзя на дошці.
		 // Якщо умови виконуються, ферзь переміщується на цільовий квадрат, а поточний квадрат стає порожнім.
         // Повертається значення true, якщо переміщення вдалося.
         // Якщо умови не виконуються, повертається значення false.

	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	std::cout << "this";
	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (queenX != thatX || queenY != thatY)
	{

		if (queenX == thatX)
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{
             
			// Перевірка, чи на шляху ферзя немає інших фігур.
				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
				// Перевірка, чи на шляху ферзя немає інших фігур.
					
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
				// Перевірка, чи цільовий квадрат відрізняється від поточного ферзя по діагоналі.
				
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
						
						// Перевірка, чи на шляху ферзя немає інших фігур.
					{
						std::cout << "It got here somehow";
						if (square[queenX + xIncrement*i][queenY + yIncrement*i].getColor() != NONE)
							return false;

					}
				}
				else
					return false;
		
	}


    // Переміщення ферзя на цільовий квадрат
	if (invalid == false)
	{
		thatSpace->setSpace(thisQueen);
		thisQueen->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}
   // Функція moveBishop відповідає за переміщення слона на дошці.
   // Якщо умови виконуються, слон переміщується на цільовий квадрат, а поточний квадрат стає порожнім.
   // Повертається значення true, якщо переміщення вдалося.
   // Якщо умови не виконуються, повертається значення false.
   
bool Board::moveBishop(Square* thisBishop, Square* thatSpace) { 
	int bishopX = thisBishop->getX();
	int bishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	Square *s;
	
	// Перевірка, чи рух слона можливий по діагоналі.
	
	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
		int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
		int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

		for (int i = 1; i < abs(bishopX - thatX); i++)
			
		{ // Перевірка, чи на шляху слона немає інших фігур.
		
			std::cout << "Там хтось є";
			if (square[bishopX + xIncrement*i][bishopY + yIncrement*i].getColor() != NONE)
				return false;

		}
	}
	else
		return false; 
	
     // Переміщення слона на цільовий квадрат.
	
	if (invalid == false)
	{
		thatSpace->setSpace(thisBishop);
		thisBishop->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}
bool Board::moveKnight(Square* thisKnight, Square* thatSpace)
{
	// Перевірка чи координати входять в межі дошки відбувається в іншому місці перед цим
	// Перевірка чи на квадраті знаходиться фігура того ж кольору відбувається в іншому місці перед цим
	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

    	// Рух коня дозволений тільки на відстань 2 в одному напрямку і 1 у іншому напрямку, або 1 в одному напрямку і 2 у іншому напрямку

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
	{
		thatSpace->setSpace(thisKnight);
		thisKnight->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::moveRook(Square* thisRook, Square* thatSpace)
{
	// Перевірка чи координати входять в межі дошки відбувається в іншому місці перед цим
	// Перевірка чи на квадраті знаходиться фігура того ж кольору відбувається в іншому місці перед цим
	int rookX = thisRook->getX();
	int rookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	
	// Рух тури можливий тільки по горизонталі або вертикалі
	
	if (rookX != thatX || rookY != thatY)
	{

		if (rookX == thatX)
		{
			int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
			for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
			{

            // Перевірка чи всі проміжні квадрати між початковим і кінцевим пусті

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (rookY == thatY)
			{

				int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
				for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
				{
					// Перевірка чи всі проміжні квадрати між початковим і кінцевим пусті
								
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				return false;
	}
	if (invalid == false)
	{
		thatSpace->setSpace(thisRook);
		thisRook->setEmpty();
		return true;
	}
	else
	{//Return some erorr or something. Probably return false;
		std::cout << "That is an invalid move for rook";
		return false;
	}
}

bool Board::movePawn(Square* thisPawn, Square* thatSpace) {
	
	// Перевірка чи координати входять в межі дошки відбувається в іншому місці перед цим
	// Перевірка чи на квадраті знаходиться фігура того ж кольору відбувається в іншому місці перед цим
	
	using namespace std;
	bool invalid = false;
	int pawnX = thisPawn->getX();
	int pawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();


	if (thisPawn->getColor() == WHITE)
	{
		
        		// Білий пішак може рухатися вперед на 1 квадрат, якщо там немає фігури
				
		if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getColor() == NONE)
		{
			thatSpace->setSpace(thisPawn);
			thisPawn->setEmpty();
			return true;
		}
		
				// Білий пішак може бити по діагоналі вперед на 1 квадрат, якщо там є чорна фігура
				
		else
			if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY  && thatSpace->getColor() == BLACK)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				return true;
			}
			else
				return false;
	}
	else
		if (thisPawn->getColor() == BLACK)
		{
			// Чорний пішак може рухатися вперед на 1 квадрат, якщо там немає фігури
					
			if (pawnX == thatX && thatY == pawnY - 1 && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				return true;
			}
			
					// Чорний пішак може бити по діагоналі вперед на 1 квадрат, якщо там є біла фігура
			
			else
				if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY  && thatSpace->getColor() == WHITE)
				{
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					return true;
				}
				else
					return false;
		}
		else
			return false;
}
bool Board::makeMove(int x1, int y1, int x2, int y2) {
	// Перевірка чи координати входять в межі дошки відбувається в іншому місці перед цим
	using namespace std;
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		std::cout << "Одним із ваших вхідних даних була межою" << std::endl;
		return false;
	}
	Square* src = getSquare(x1, y1);
	Square* dest = getSquare(x2, y2);

	if (src->getColor() == dest->getColor() && dest->getColor() != NONE)
	{
		std::cout << "Недійсний хід: не можна розмістити на власну фігуру" << std::endl;
		return false;
	}
	
		// Рух фігури залежно від її типу
		
	switch (src->getPiece())
	{
	case KING: return moveKing(src, dest);
		break;
	case QUEEN: return moveQueen(src, dest);
		break;
	case BISHOP: return moveBishop(src, dest);
		break;
	case KNIGHT: return moveKnight(src, dest);
		break;
	case ROOK: return moveRook(src, dest);
		break;
	case PAWN: return movePawn(src, dest);
		break;
	case EMPTY: std::cout << "Ви не можете розмістити тут" << std::endl;  return false;
		break;
	default: std::cerr << "Щось пішло не так у операторі switch у makeMove()" << std::endl;
		break;
	}
	return false;
}
