#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "Application.h"

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);
	// Destructor that deletes the EBO
	~EBO();

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	
};

#endif