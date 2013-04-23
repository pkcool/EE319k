
typedef enum {
	CROSS,
	LINE,
	CORNER,
	START,
	END,
	OBSTACLE
} PieceType;

typedef struct {
	PieceType type;
  int x, y, a;
} Piece;

char (*sprites)[6*12*12/2*4];

Piece newPiece(PieceType type, int x, int y, int direction) {
  Piece a;
  a.x = x;
  a.y = y;
	a.a = direction;
  return a;
}


void GameInit(void) {
	
	
}

