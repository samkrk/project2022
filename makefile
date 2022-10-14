sam: main.cpp
	g++ main.cpp Player.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_1/include -L/opt/homebrew/Cellar/sfml/2.5.1_1/lib -lsfml-window -lsfml-system -lsfml-graphics

mitch: 
	@g++ main2.cpp Coin.cpp Enemy.cpp Spring.cpp Platform.cpp Object.cpp Bullet.cpp Entity.cpp Player.cpp Game.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_1/include -L/opt/homebrew/Cellar/sfml/2.5.1_1/lib -lsfml-window -lsfml-system -lsfml-graphics
	@./a.out