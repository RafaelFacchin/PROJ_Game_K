//CABECALHO Character - CLASSE P/ CRIACAO de personagens
//CLASSE: responsavel p/ tratar movimentacao/gravidade/colisao e morte

#ifndef CHARACTER_H
#define CHARACTER_H

//INCLUDE CLASSES
#include "NGLObject.h"

class Clevel;

class CCharacter : public CNGLObject 
{
private:
	//TRATAMENTO DA COLISAO c/ o cenario na esquerda e na direita do personagem (eixo X)
	void HandleCollisionLeftRight(void);

	//TRATAMENTO DA COLISAO c/ o cenario na esquerda e na direita do personagem (eixo Y)
	void HandleCollisionUpDown(void);

protected:
	//!!! INDICA se o personagem esta pulando ou caindo no momento
	bool bJump;
	// INDICA se a gravidade vai agir sobre o personagem
	bool bUseGravity;

	//METODO que deve ser reescrito pelo inimigo ou jogador p/ tratar a morte do personagem

	virtual void Die(void) = 0;
	//!!! INDICA se o personagem esta morrendo
	bool bIsDieing;
	//! VELOCIDADE atual do personagem
	CNGLVector CurrentSpeed;
	//VELOCIDADE padrao de deslocamento e queda do personagem
	CNGLVector defaultSpeed;
	//CONTEM O VALOR de GRAVIDADE do personagem
	float fGravity;


};

#endif