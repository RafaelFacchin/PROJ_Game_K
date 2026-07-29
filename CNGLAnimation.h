//-----------------------------------------------------------------------------------------------------
//CLASSE: CNGLAnimation
//DESCR: Uma seqüência de animação de um sprite.
//-----------------------------------------------------------------------------------------------------

#ifndef CNGLANIMATION_H
#define CNGLANIMATION_H

#include "CNGLTimeAccumulator.h"
#include "CNGLStlFiles.h"

//PROTOTIPO
class CNGLMain;

class CNGLAnimation : public CNGLObject 
{
private:
	//!Acumulator de tempo (usado para trocar quadros de animação).
	CNGLTimeAccumulator TimeAccum;

	//!Número de quadros por segundo na animação.
	int iFramesPerSecond;

public:
	//!Indica se a animação deve reiniciar quando terminar (contínua ou finita).
	bool bRepeat;

	//!Índices dos quadros de animação na imagem.
	vector<int> Frames;

	//!Índice do quadro atual no vetor de quadros.
	int iCurrentFrame;

	//PONTEIRO p/ o MAIN CNGL
	CNGLMain *pr_Main;

public:
	//***CONSTRUTOR-PADRAO
	CNGLAnimation();

	//***DESTRUTOR-PADRAO
	virtual ~CNGLAnimation();

	//FUNC: RELEASE
	//DESCR: FINALIZA a classe.
	//PARAM1: 
	//RETORNO: vazio
	bool Release();

	//FUNC: ENDED
	//DESCR: RETORNA se a animação terminou.
	//PARAM1: 
	//RETORNO: verdadeiro se a animação acabou. Para animações em loop; o retorno eh sempre FALSO
	bool Ended();

	//FUNC: UPDATE
	//DESCR: Atualiza a animação
	//PARAM1: 
	//RETORNO: vazio
	void Update();

	//FUNC: GETCURRENTFRAME
	//DESCR: Retorna o índice do quadro corrente na imagem.
	//PARAM1: 
	//RETORNO: Índice do quadro corrente na imagem.
	int GetCurrentFrame();

	//FUNC: RESET
	//DESCR: Reinicia a animação.
	//PARAM1: 
	//RETORNO: vazio
	void Reset();

	//FUNC: GETCLONE
	//DESCR:	Cria um clone da animação atual. Essa função aloca um objeto CNGLAnimation e retorna
	//			um ponteiro para a mesma.Para deletar esse ponteiro, deve ser chamado o delete do C++.
	//PARAM1: 
	//RETORNO: Ponteiro para uma animação clonada.
	CNGLAnimation *GetClone();

	//FUNC: SETFRAMEINTERVAL
	//DESCR:	Configura o intervalo de tempo entre os quadros (em FPS).
	//PARAM1 iFrameInterval: intervalo de tempo.
	//PARAM2 uiTimeAccum: Tempo acumulado no acumulador de tempo.
	//RETORNO:
	void SetFrameInterval(int iFrameInterval, unsigned int uiTimeAccum = 0);
};

#endif
