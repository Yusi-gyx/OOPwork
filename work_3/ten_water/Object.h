#pragma once

class Splash;

#include <iostream>

using namespace std;


enum Direction {NONE, LEFT, RIGHT, UP, DOWN};
enum Actor {PLAYER, WATER, TOXIC};

class Object {
protected:
	Splash* splash;
	int x, y;
public:
	Object(int _x, int _y, Splash* _splash):splash(_splash), x(_x), y(_y) {}
	virtual int act(Direction fromwhere, Actor fromwho) = 0;
	virtual ~Object() {}
};

class Water : public Object {
	int weight = 0 ;
public:
	Water(int w, int _x, int _y, Splash* splash): Object(_x, _y, splash), weight(w) {}
	~Water() {}
	int act(Direction fromwhere, Actor fromwho) ;
};

class Void : public Object {
public:
	Void(int _x, int _y, Splash* _splash): Object(_x, _y, _splash) {}
	~Void() {}
	int act(Direction fromwhere, Actor fromwho) ;
};

class Barrier : public Object {
public:
	Barrier(int _x, int _y, Splash* _splash): Object(_x, _y, _splash) {}
	~Barrier() {}
	int act(Direction fromwhere, Actor fromwho) ;
};

class Toxic : public Object {
	int weight = 0 ;
public:
	Toxic(int w, int _x, int _y, Splash* _splash): Object(_x, _y, _splash), weight(w) {}
	~Toxic() {}
	int act(Direction fromwhere, Actor fromwho) ;
};
