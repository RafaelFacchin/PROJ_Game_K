//CLASSE MAIN - refatoracao e atualizacao de jogo KANGOO - by Copyright (C) 2003, Nology Softwares. Todos os direitos reservados

#ifndef MAIN_CPP
#define MAIN_CPP

#include <windows.h>

#include "CNGLMain.h"
#include "NGL/NGLLevel.h"
#include "NGL/NGLPresentation.h"

//VAR global que indica se a janela do jogo esta ativa
bool g_bActive = true;
//PONTEIRO global p/ a classe principal da NGL_LIB ()usado pela rotina ""WindowProc)
CNGLMain *g_pr_Main = NULL;

//-----------------------------------------------------------------------------------------------------------------------------
//NOME: WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//DESC: essa funcao trata as mensagens do Windows recebidas pela aplicacao
//-----------------------------------------------------------------------------------------------------------------------------
static LRESULT CALLBACK Windowproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
		case WM_ERASEBKGND:
		case WM_NCPAINT:
		case WM_SYNCPAINT:
		{
			if (g_pr_Main->VideoManager.bFullScreen)
			{
				//SE estiver em tela cheia, retorna 0 p/ essas 3 mensagens
				//Evita o "FLICK/ TREMEDEIRA" NO JOGO EM TELA CHEIA
				return 0;
			}
			break;
		}
		case WM_MOVE:
		{
			//SE a janela foi movida, atualizar o FRAME DO VIDEO
			(g_pr_Main) ? g_pr_Main->VideoManager.UpdateFrame() : 0;
			break;
		}
		case WM_PAINT:
		{
			//SE a janela nao esta ativa
			if (g_pr_Main && !g_bActive)
			{
				//PEGA o estado de PAUSA do jogo
				bool bIsPaused = g_pr_Main->IsPaused();
				//o codigo a seguir PRINTA o jogo com ele pausado, pois nao deve
				//haver atualizacoes de tempo e dos OBJs
				if (!bIsPaused) 
				{
					//PAUSA o jogo(CASO NAO ESTEJA PAUSADO)
					g_pr_Main->Pause();
				}
				//DESENHAO O JOGO
				g_pr_Main->Loop();
				if (!bIsPaused) 
				{
					//CONTINUA o jogo (CASO NAO ESTIVESSE PAUSADO)
					g_pr_Main->Resume();
				}
			}
			return DefWindowProc(hwnd, msg, wParam, lParam);
			break;
		}
		case WM_GETDLGCODE:
		{
			//diz p/ o windows que essa aplicacao requer teclado
			return DLGC_WANTALLKEYS;
			break;
		}
		case WM_SETCURSOR:
		{
			//O COD abaixo faz o cursor do mouse do windows desaparecewr
			//qndo o mouse estiver em "cima" da janela (USANDO CURSOR VIA NGL)
			SetCursor(NULL);
			return TRUE;
			break;
		}
		case WM_SIZE:
		{
			//SE a janela for REDIMENSIONADA, atualizar o frame do video
			(g_pr_Main) ? g_pr_Main->VideoManager.UpdateFrame() : 0;
			return 0;
			break;
		}
		case WM_ACTIVATE:
		{
			//indica SE  a aplicacao ganhou foco ou nao
			if (LOWARD(wParam) == WA_INACTIVE)
			{
				//aplicacao perdeu o foco
				g_bActive = false;
			}
			else 
			{
				if (HIWORD(wParam) == 0)
				{
					//aplicacao ganhou foco
					//deve-se resetar o tempo da NGL p/ os OBJs do jogo
					//mantenham-se na mesma posicao de quando a janela foi desativada
					(g_pr_Main) ? g_pr_Main->TimeHandler.reset() : 0;
					g_bActive = true;
				}
			}
			break;
		}
		case WM_EXITMENULOOP:
		{
			//Quando sai do MENU da janela
			(g_pr_Main) ? g_pr_Main->TimeHandler.Reset() : 0;
			break;
		}
		case WM_EXITSIZEMOVE:
		{
			//qndo PARAR de mover ou redimensionar a janela
			(g_pr_Main) ? g_pr_Main->TimeHandler.Reset() : 0;
			break;
		}
		case WM_SYSCOMMAND:
		{
			//PREVINE contra a movimentacao/ redimensionamento/ maximizacao/ desligamento
			//do monitor (protetor de tela)
			switch (wParam)
			{
				case SC_MOVE:
				case SC_SIZE:
				case SC_MAXIMIZE:
				case SC_MONITORPOWER:
				return TRUE;
			}
			break;
		}
		case WM_CLOSE:
		{
			//CASO seja aplicado o "X" da janela ou ALT+F4 deve-se fechar a aplicacao
			PostQuitMessage(0);
			return 0;
			break;
		}
	}

	//CHAMA o tratamento padrao de MENSAGENS
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//-----------------------------------------------------------------------------------------------------------------------------
//NOME: WinMain(HISNTANCE (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
//DESC: Funcao de entrada da aplicacao
//-----------------------------------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CNGLMain Main; //OBJ principal da lib_NGL
	WNDCLASS winclass; //DESCRITORA da classe de janela
	MSG msg; //ESTRUTURA de mensagem do windows
	HWND hwnd; //HANDLE da janela da aplicacao
	char chName[11] = "NGL_Window"; //NOME da janela

	//AJUSTA o ponteiro global da CNGLMain
	g_pr_Main = &Main;

	//COLOCA os parametros da janela a ser criada
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hInstance;
	winclass.hIcon = NULL;
	winclass.hCursor = NULL;
	winclass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = chName;

	//REGISTRANDO a classe
	if (!RegisterClass(&winclass))
	{
		return -1;
	}
	//Ajustando DIMENSAO do video (640x480)
	Main.VideoManager.VideoSize = CNGLVector(640, 480);

	//CRIA a janela principal do jogo, com a dimensao ajustada acima
	if (!(hWdn = CreateWindowExW(0, chName, "NGL Game", WS_CAPTION | WS_SYSMENU | WS_POPUP | WS_VISIBLE, 0, 0, (int)Main.VideoManager.VideoSize.fx,
		(int)Main.VideoManager.VideoSize.fy, NULL, NULL, hInstance, NULL)))
	{
		//RETORNA se deu ERRO!
		return -1;
	}

	//ATRIBUI instancia e window handle da aplicacao (Valores utilizadas usados pelo DirecX)
	Main.pr_Inst = (void*)hInstance;
	Main.pr_Wnd = (void*)hwnd;

	//CENAS do jogo
	CLevel Level;
	CPresentation Presentation;

	//ler arquivo de opções do jogo para a NGL saber se 
	//deve iniciar em Janela ou Tela Cheia
	Level.Menu.Loadoptions(&Main);

	//ADICIONANDO 2 cenas a NGL
	Main.AddScene(&Presentation);
	Main.AddScene(&Level);

	//INICIALIZA o MAIN
	if (!Main.initializa())
	{
		//RETORNA SE der erro
		Main.Release();
		return -1;
	}

	//LACO de recebimento e encaminahmento de mensagens
	while (!Main.Ended())//ENQUANTO a NGL nao terminou
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//CASO a mensagem seja de saida, terminar a aplicacao
			if (WM_QUIT == msg.message)
			{
				//CHAMADA de saida da NGL
				Main.ExitNGL();
			}
			//ENCAMINHA  amensagem p/ o WindowProc p/ ser tratada
			DispatchMessage(&msg);
		}

		//SE a janela estiver ativa
		if (g_bActive)
		{
			//FAZ a atualizacao da NGL
			Main.Loop();
		}
		else 
		{
			//SE a janela nao esta ativa, deve-se sempre reinicializar otempo do jogo
			Main.TimeHandler.reset();
		}
	}
	DeleteObject(winclass.hbrBackground);
	ClipCursor(NULL);

	return 0;
}

#endif