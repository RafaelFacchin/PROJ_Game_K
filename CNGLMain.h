//CLASSE MAIN da biblioteca NGL
//!!!esta classe eh responsavel por iniciar o jogo a partir de uma janela windows!!!

#ifndef CNGLMAIN_H
#define CNGLMAIN_H

#include "CNGLInputManager.h"
#include "CNGLObject.h"
#include "CNGLScene.h"
#include "CNGLSoundManager.h" 
#include "CNGLTimeHandler.h"
#include "CNGLVideoManager.h"

class CNGLMain : public CNGLObject 
{
private:

	//INDICAa fnalizacao da NGL
	bool bEnded;

	//LISTA de cenas do jogo
	vector <CNGLScene *> Scenes;

	//!REFERENCIA p/ a cena corrente do jogo
	CNGLScene *pr_CurrentScene;

	//INDICA se o jogo esta pausado
	bool bPaused;

public:

	//REFERENCIA p/ a janela WINDOWS
	void *pr_Wnd;

	//REFERENCIA p/ a instancia da aplicacao WINDOWS
	void* pr_Inst;

	//GERENCIADOR de video
	CNGLVideoManager VideoManager;

	//!GERENCIADOR DE disp. de entrada
	CNGLInputManager InputManager;

	//GERENCIADOR de SOM
	CNGLSoundManager SoundManager;

	//GERENCIADOR de tempo da NGL
	CNGLTimeHandler TimeHandler;

public:

	//!!!INFORMA se a NGL ja finalizou sua execucao
	//OBS: "return true" se ja finalizou, senao mantem falso
	bool Ended();

	//ENCERRA o uso da NGL
	void ExitNGL();

	/*Inicializa os dispositivos da NGL: gráficos, teclado, mouse e som. Ajusta a primeira cena como corrente.
	\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.*/
	bool Initialize();

	//**CONSTRUTOR-PADRAO
	CNGLMain();

	//DESTRUTOR-PADRAO
	virtual ~CNGLMain();

	/*
	Finaliza a classe.
	\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Release();

	//LOOP principal do jogo: CHAMAR essa rotina em cada laco de repeticao
	void Loop();

	/*
	Adiciona uma cena à NGL.
	\param pr_Scene: Ponteiro da nova cena corrente.
	*/
	void AddScene(CNGLScene* pr_scene);

	/*!
	Atribui uma nova cena corrente da NGL, de acordo com o índice. Caso já exista uma cena corrente configurada, ela é liberada e a nova é inicializada.
	\param iIndex: Índice da nova cena.
		*/
	void SetCurrentScene(int iIndex);

	/*!
	Retorna a cena corrente do jogo.
	\return Ponteiro para a cena corrente.
	*/
	inline CNGLScene* GetCurrentScene() { return pr_CurrentScene; };

	/*!
	Pausa o jogo. A pausa tranca a execução do jogo, mas não a renderização.
	*/
	void Pause(void);

	/*!
	Continua o jogo após uma pausa.
	*/
	void Resume(void);

	/*!
	Retorna se o jogo está pausado.
	\return verdadeiro se o jogo estiver pausado, senão retorna falso.
	*/
	inline bool IsPaused(void) { return bPaused; };
};

#endif
