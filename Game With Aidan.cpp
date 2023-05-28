#include <iostream>

#include "Game.h"

int main() {
	Character c;
	Potion p;
	Leaderboard l = Leaderboard();
	AncientSpirit a = AncientSpirit();
	Game g = Game();
	Monster m;

	g.StartGame(c, p, m, l, a);

	while (PlayGame) {
		g.KeyPressed(c, m, p, a, l);
	}
}
