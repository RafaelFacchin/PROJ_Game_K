//CABECALHO Character - CLASSE P/ CRIACAO de personagens
//CLASSE: responsavel p/ tratar movimentacao/gravidade/colisao e morte

#ifndef CHARACTER_H
#define CHARACTER_H

//INCLUDE CLASSES
#include "CNGLObject.h"

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

public:
	//POSICAO do personagem NO LACO ANTERIOR DO JOGO
	CNGLVector lastPos;

	//SPRITE com as ANIMACOES do personagem
	CNGLSprite *p_Sprite;

	//REF. p/ a classe "CLevel"
	CLevel *pr_Level;

	//***CONSTRUTOR-PADRAO
	CCharacter();

	//DESTRUTOR-PADRAO
	virtual ~CCharacter();

	//OBS: finaliza  classe, loiberando sprite do personagem
	//"return = true" SE a operacao for bem sucedida!
	bool Release();

	//METODO que devera ser reescrito pelo inimigo ou jogador p/ inicia-lo (SPRITES, ANIMACOES e POSICAO)
	//param InitPos: POSICAO INICIAL do personagem
	//"return = true" se bem sucedido
	virtual bool Initialize(CNGLVector InitPos) = 0;

	//ATUALIZA gravidade; tratamento de colisoes com bricks; atualiza posicao do personagem' ajuste de animacoes do personagem
	virtual void Execute();

	//RETORNA um "CNGLFrame" contendo o quadro de Sprote do personagem;
	//return CNGLFRAME COM O QUADRO DE PERSONAGENS
	CNGLFrame GetFrame();

	//FAZ o personagem ATIRAR, DEVENDO ser reescrita nas classes filhas
	virtual void Shot();

			//METODO QUE DEVE SER REESCRITO pelas classes que herdam desta, para saber se o jogador eh bom ou inimigo
	virtual bool IsPlayer() = 0;

	//MATA o personagem
	//"return = true", SE o personagem esta morrendo
	bool IsDieing();
};

#endif