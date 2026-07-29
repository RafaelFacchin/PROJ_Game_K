//-----------------------------------------------------------------------------------------------------
//CLASSE: CNGLBrick
//DESCR: Representa um brick (tijolo) que compõe a layer.
//-----------------------------------------------------------------------------------------------------

#ifndef CNGLBRICK_H
#define CNGLBRICK_H

#include "CNGLObject.h"

class CNGLBrick : public CNGLObject 
{
public:
	//INDICE de imagem no vetor de tiles da cena
	int iImage;

	//INDICE do frame na imagem
	int iFrame;

public:
	//***CONSTRUTOR-PADRAO:
	CNGLBrick();

	//***DESTRUTOR-PADRAO:
	virtual ~CNGLBrick();

	//FUNC: RELEASE
	//DESCR: FINALIZA a classe
	//PARAM1: 
	//RETORNO: verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	bool Release();
};

#endif
