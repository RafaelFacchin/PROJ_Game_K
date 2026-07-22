//---------------------------------------------------------------------------- 
// Nome: CNGLTimeHandler(void)
// Desc: construtor padrão
// Pams: nenhum
//----------------------------------------------------------------------------

#include "CNGLTimeHandler.h"
#include <windows.h>

CNGLTimeHandler::CNGLTimeHandler() 
{
	bPreventLowdown = true;
	Initialize();
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLTimeHandler(void)
// Desc: construtor padrão
// Pams: nenhum
//----------------------------------------------------------------------------
CNGLTimeHandler::~CNGLTimeHandler()
{
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: Finaliza o TimeHandler
// Pams: nenhum
//----------------------------------------------------------------------------
bool CNGLTimeHandler::Release() 
{
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initializa(void)
// Desc: Inicializa o TimeHandler
// Pams: nenhum
//----------------------------------------------------------------------------
void CNGLTimeHandler::Initialize() 
{
	uiLastTime  = GetTickCount();
	fFrameTime  = 0.0f;
	iFrameTime  = 0;
	iFPS        = 0;
	iFrameCount = 0;
	iTimeAcum   = 0;
}

//---------------------------------------------------------------------------- 
// Nome: Update()
// Desc: Atualiza o tempo;***OBS:Este método deve ser chamado a cada quadro da aplicação.
// Pams: nenhum 
//---------------------------------------------------------------------------- 
#define NGLMINFRAMEINTERVAL 5
#define NGLMAXFRAMEINTERVAL 50
void CNGLTimeHandler::Update() 
{
	iFrameTime = 0;
	unsigned int uiCurrentTime;

	do 
	{
		uiCurrentTime = GetTickCount();
		iFrameTime    = (uiCurrentTime > uiLastTime) ? uiCurrentTime - uiLastTime : 0;
		uiLastTime    = (uiCurrentTime >= uiLastTime) ? uiLastTime : uiCurrentTime;
	} while (!(iFrameTime >= NGLMAXFRAMEINTERVAL));

	if(bPreventLowdown && (iFrameTime > NGLMAXFRAMEINTERVAL)) 
	{
		iFrameTime = NGLMAXFRAMEINTERVAL;
	}

	iTimeAcum += iFrameTime;
	iFrameCount++;
	fFrameTime = (float)iFrameTime * 0.001f;

	if (iTimeAcum >= 1000) 
	{
		iFPS        = iFrameCount;
		iFrameCount = 0;
		iTimeAcum   = 0;
	}

	uiLastTime = uiCurrentTime;
}

//---------------------------------------------------------------------------- 
// Nome: GetFPS()
// Desc: RETORNAo número de quadros por segundo
// Pams: nenhum
//----------------------------------------------------------------------------
int CNGLTimeHandler::GetFPS() 
{
	return iFPS;
}

//---------------------------------------------------------------------------- 
// Nome: Reset()
// Desc: RECOMECA a contagem de tempo
// Pams: nenhum
//----------------------------------------------------------------------------
void CNGLTimeHandler::Reset() 
{
	uiLastTime = GetTickCount();
}