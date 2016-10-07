#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

class Interactable {
public:
	Interactable();
	virtual ~Interactable() {};
	
	virtual void setDirection(float, float) = 0;
};

#endif