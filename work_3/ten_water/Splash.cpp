#include "Splash.h"
#include <iostream>

void Splash::buildMap() {
	char tmp;
	tmp = getchar();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tmp = getchar();
			if (tmp == '1' || tmp == '2' || tmp == '3') {
				this->map[i][j] = new Water(tmp - '0', i, j, this);
			}
			else if (tmp == '#') {
				this->map[i][j] = new Void(i, j, this);
			}
			else if (tmp == '*') {
				this->map[i][j] = new Barrier(i, j, this);
			}
			else if (tmp == '-') {
				tmp = getchar();
				this->map[i][j] = new Toxic(tmp - '0', i, j, this);
			}
			getchar();
		}
	}
}

void Splash::actAt(int x, int y) {
	Object *obj = map[x][y];
	score += obj->act(NONE, PLAYER);
	// std::cout << "score:" << score << std::endl ;
	if(obj != map[x][y]) delete obj;
	//当map中的指针和传入的不一样时，说明发生了类对象的变化，则将原来的指针删除
	//这里很重要，一定要注意在obj的成员函数中不能删除obj指针
	return;
}
