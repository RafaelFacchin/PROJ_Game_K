#include "CNGLMain.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLMain(void)
// Desc: ***CONSTRUTOR-PADRAO
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLMain::CNGLMain()
{
	pr_CurrentScene = NULL;
	pr_Wnd = NULL;
	pr_Inst = NULL;
	bEnded = false;
	bPaused = false;
	VideoManager.pr_Main = this;
	InputManager.pr_Main = this;
	SoundManager.pr_Main = this;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLMain(void)
// Desc: ***DESTRUTOR-PADRAO
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLMain::~CNGLMain()
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: FINALIZA a NGL Main 
// Pams: nenhum
//----------------------------------------------------------------------------
bool CNGLMain::Release()
{
	//setando cena corrente como nula
	if (pr_CurrentScene)
	{
		pr_CurrentScene->Release();
		pr_CurrentScene = NULL;
	}

	//liberando video
	VideoManager.Release();

	//liberando entradas
	InputManager.Release();

	//liberando som
	SoundManager.Release();

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize()
// Desc: INICIALIZA os dispositivos da NGL: gráficos, teclado, mouse e som. Ajusta a primeira cena como corrente.
// Pams: nenhum
//----------------------------------------------------------------------------

bool CNGLMain::Initialize()
{
	//inicializando video
	if (!VideoManager.Initialize())
	{
		return false;
	}

	//inicializando entradas
	if (!InputManager.Initialize())
	{
		return false;
	}

	//inicializa o som
	SoundManager.Initialize();

	//ajusta a primeira cena como corrente, caso nenhuma esteja ajustada
	if (!pr_CurrentScene)
	{
		SetCurrentScene(0);
	}

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: ExitNGL()
// Desc: FINALIZA a execução da NGL
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLMain::ExitNGL()
{
	bEnded = true;
}

//---------------------------------------------------------------------------- 
// Nome: Ended()
// Desc: RETORNA verdadeiro se a NGL terminou sua execução
// Pams: nenhum
//----------------------------------------------------------------------------
bool CNGLMain::Ended()
{
	if (bEnded)
	{
		Release();
	}

	return bEnded;
}

//---------------------------------------------------------------------------- 
// Nome: Loop(void)
// Desc: LACO principal do jogo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLMain::Loop()
{
	//LEH as entradas
	InputManager.Read();

	//ATUALIZA o tempo
	TimeHandler.Update();

	//ATUALIZA o som (STREAMING)
	SoundManager.Update();

	//LIMPA o backbuffer
	VideoManager.BackBuffer.Clear(RGB(255, 255, 255));

	//DESENHA a cena
	if(pr_CurrentScene)
	{
		pr_CurrentScene->Draw();

		//somente atualiza o jogo se ele não estiver pausado
		if (!bPaused)
		{
			pr_CurrentScene->Update();
			pr_CurrentScene->Execute();
		}
	}

	//mostra imagens
	VideoManager.Present();
}

//---------------------------------------------------------------------------- 
// Nome: AddScene(CNGLScene* pr_NewScene)
// Desc: ADICIONA uma cena à NGL.
// Pams: ponteiro para a nova cena
//----------------------------------------------------------------------------
void CNGLMain::AddScene(CNGLScene* pr_NewScene)
{
	if (pr_NewScene)
	{
		//adiciona a cena à lista
		Scenes.push_back(pr_NewScene);
	}
}

//---------------------------------------------------------------------------- 
// Nome: SetCurrentScene(int iIndex)
// Desc: ATRIBUI uma nova cena corrente da NGL, de acordo com o índice. Caso já exista uma cena corrente configurada, 
//			ela é liberada e a nova é inicializada.
// Pams: índice da nova cena
//---------------------------------------------------------------------------- 
void CNGLMain::SetCurrentScene(int iIndex)
{
	if (iIndex < (int)Scenes.size())
	{
		//pega a nova cena a ser ajustada
		CNGLScene *pr_NewScene = Scenes[iIndex];
		if (pr_NewScene)
		{
			//se já existia uma cena ativa, então libera ela.
			if (pr_CurrentScene)
			{
				pr_CurrentScene->Release();
				pr_CurrentScene = NULL;
			}

			//atribui a nova cena corrente
			pr_CurrentScene = pr_NewScene;

			//atribui o main à cena
			pr_CurrentScene->pr_Main = this;

			//inicializa a nova cena
			if (!pr_CurrentScene->Initialize())
			{
				pr_CurrentScene->Release();
				pr_CurrentScene = NULL;
			}
			TimeHandler.Reset();
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: Pause(void)
// Desc: PAUSA o jogo
// Pams: nenhum
//----------------------------------------------------------------------------
void CNGLMain::Pause()
{
	bPaused = true;
}

//---------------------------------------------------------------------------- 
// Nome: Resume(void)
// Desc: CONTINUA o jogo após uma pausa.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLMain::Resume()
{
	if (bPaused)
	{
		TimeHandler.Reset();
		bPaused = false;
	}
}