//-----------------------------------------------------------------------------------------------------
//CLASSE: CNGLTimeHandler
//DESCR: Controla o relogio do jogo
//-----------------------------------------------------------------------------------------------------

#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

#include "CNGLObject.h"
#include "CNGLStlFiles.h"

class CNGLTimeHandler : public CNGLObject 
{
private:

	//ARMAZENA o ultimo tempo obtido (milesegundos)
	unsigned int uiLastTime;

	//ACUMULO de tempo desde o ultimo tempo obtido (milesegundos)
	int iTimeAcum;

	//NUMERO DE QUADROS que se passaram durante este periodo; ou o numero de chamadas da rotina "Update()"
	int iFrameCount;

	//NUMERO DE QUADROS P/ SEGUNDO
	int iFPS;

public:

	//ACIONA esta FLAG p/ previnir SLOWDOWN
	bool bPreventLowdown;

	//ARMAZENA o tempo passado desde o ultimo quadro (milisegundos)
	int iFrameTime;

	//ARMAZENA  o tempo passado desde o ultimo quadro (segundos)
	float fFrameTime;

	//RECOMECA a contagem do tempo
	void Reset();

	//RETORNA  o numero de frames/sec
	int GetFPS();

	//ATUALIZA o tempo;***OBS: este metodo devera ser chamado a cada quadro da aplicacao
	void Update();

	//INICIALIZA as variaveis internas
	void Initialize();

	//FINALIZA a classe; ***OBS: retorna "TRUE" se a op. for bem sucedida
	bool Release(void);

	//***CONSTRUTOR-PADRAO
	CNGLTimeHandler();

	//***DESTRUTOR-PADRAO
	virtual ~CNGLTimeHandler();
};

#endif
