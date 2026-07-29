#include "CNGLAnimation.h"
#include "CNGLMain.h"
#include ".\nglanimation.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLAnimation(void)
// Desc: CONSTRUTOR-PADRAO
// Pams: nenhum
//----------------------------------------------------------------------------
CNGLAnimation::CNGLAnimation() 
{
	bRepeat          = false;
	iCurrentframe    = 0;
	iframesPerSecond = 1;
	pr_Main          = NULL;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLAnimation(void)
// Desc: DESTRUTOR-PADRAO
// Pams: nenhum
//----------------------------------------------------------------------------
CNGLAnimation::~CNGLAnimation() 
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza a animação
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLAnimation::Release() 
{
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Ended(void)
// Desc: retorna verdadeiro se a animação acabou
// Pams: nenhum
//----------------------------------------------------------------------------
bool CNGLAnimation::Ended()
{
	return (bRepeat)? false : iCurrentFrame >= (char)Frames.size();
}

//---------------------------------------------------------------------------- 
// Nome: Update(void)
// Desc: Atualiza a animação
// Pams: nenhum
//----------------------------------------------------------------------------
void CNGLAnimation::Update() 
{
	if (pr_Main) 
	{
		//ATUALIZA o acumulador de tempo
		TimeAccum.Update();

		//SE o acumulador eh maior que o intervalo entre quadros
		if (TimeAccum.Ended()) 
		{
			//CAPTURA o intervalo entre os quadros
			unsigned int uiFrameInterval = (iFramesPerSecond) ? 1000 / iFramesPerSecond : 1;

			//CALCULA a quantidade de quadros que se passaram
			int iSum = (int)(TimeAccum.uiTimeAccum / uiFrameInterval);

			//SOMA os quadros ao quadro corrente
			if (bRepeat) 
			{
				//TROCA P/ O PROXIMO QUADRO
				iCurrentFrame += iSum;
				//**OBS: Neste caso o próximo quadro é calculado como uma fila circular.
				//Caso iCurrentFrame seja igual ao número total de quadros, então
				//o próximo quadro será ZERO.
				iCurrentFrame %= Frames.size();
			}
			else 
			{
				//TROCA p/ o proximo quadro
				iCurrentFrame += (iCurrentFrame < (char)Frames.size()) ? iSum : 0;
			}
			//RECOMECA o acumulador
			TimeAccum.Restart();
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: GetCurrentFrame(void)
// Desc: Retorna o quadro corrente da animação
// Pams: nenhum
//----------------------------------------------------------------------------
int CNGLAnimation::GetCurrentFrame() 
{
	return (iCurrentFrame >= 0 && iCurrentFrame < (int)Frames.size()) ? Frames[iCurrentFrame] : Frames[Frames.size() - 1];
}

//---------------------------------------------------------------------------- 
// Nome: Reset(void)
// Desc: Reinicia a animação
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLAnimation::Reset() 
{
	TimeAccum.Init(&pr_Main->TimeHandler, (iFramesPerSecond) ? 1000 / iFramesPerSecond : 1);
	iCurrentFrame = 0;
}

//---------------------------------------------------------------------------- 
// Nome: GetClone(void)
// Desc: retorna um clone da animação
// Pams: 
//----------------------------------------------------------------------------
CNGLAnimation* CNGLAnimation::GetClone() 
{
	CNGLAnimation* p_Clone = new CNGLAnimation();
	if (p_Clone) 
	{
		p_Clone->bRepeat = bRepeat;
		p_Clone->iCurrentFrame = iCurrentFrame;
		p_Clone->pr_Main = pr_Main;
		p_Clone->SetFrameInterval(iframesPerSecond, TimeAccum.uiTimeAccum);

		int iSize = (int)Frames.size();
		for (int 1 = 0; i < iSize; i++)
		{
			p_Clone->Frames.push_back(Frames[i]);
		}
		return p_Clone;
	}
	return NULL;
}

//---------------------------------------------------------------------------- 
// Nome: SetFrameInterval(int iFrameInterval)
// Desc: Configura o intervalo de tempo entre os quadros (em FPS).
// Pams: Intervalo de tempo, tempo inicial do acumulador de tempo
//----------------------------------------------------------------------------
void CNGLAnimation::SetFrameInterval(int iFrameInterval, unsigned int uiTimeAccum) 
{
	iFramesPerSecond = iFrameInterval;
	TimeAccum.Init(&pr_Main->TimeHandler, (iFramesPerSecond) ? 1000 / iFramesPerSecond : 1);
	TimeAccum.uiTimeAccum = uiTimeAccum;
}
