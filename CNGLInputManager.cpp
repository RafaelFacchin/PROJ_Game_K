#include "CNGLInputManager.h"
#include "CNGLMain.h"
#include "windows.h"

//Essa macro retorna se uma tecla está pressionada. No DirectInput cada tecla é representada por um Byte.
//Caso o bit mais alto deste Byte estiver em 1, quer dizer que a tecla está pressionada (por isso se faz um AND com 0x80).
#define NGLKEYDOWN(KeyBuffer, key) (KeyBuffer[key] & 0x80)

//Essa macro retorna se um botão do mouse está pressionado. No DirectInput cada botão é representado por um Byte.
//Caso o bit mais alto deste Byte estiver em 1, quer dizer que o botão está pressionado (por isso se faz um AND com 0x80).
#define NGLMOUBTNDOWN(MouBuffer, btn) (MouBuffer.rgbButtons[btn] & 0x80)

//---------------------------------------------------------------------------- 
// Nome: CNGLInputManager(void)
// Desc: CONSTRUTOR-PADRAO
// Pams: nenhum
//----------------------------------------------------------------------------
CNGLInputManager::CNGLInputManager() 
{
	p_DInput = NULL;
	p_DevMouse = NULL;
	p_DevKeyboard = NULL;
	pr_Main = NULL;
	ZeroMemory(KeyboardState,sizeof(KeyboardState));
	ZeroMemory(LastKeyboardState,sizeof(LastKeyboardState));
	ZeroMemory(&MouseState,sizeof(MouseState));
	ZeroMemory(&LastMouseState,sizeof(LastMouseState));
}

//---------------------------------------------------------------------------- 
// Nome: CNGLInputManager(void)
// Desc: DESTRUTOR-PADRAO
// Pams: nenhum
//----------------------------------------------------------------------------
CNGLInputManager::~CNGLInputManager() 
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: FINALIZA o input manager
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLInputManager::Release() 
{
	//LIBERA o teclado
	if (p_DevKeyboard)
	{
		//SEMPRE chamar "unacquire" do dispositivo antes de chamar o "Release()"
		p_DevKeyboard->Unacquire();
		p_DevKeyboard->Release();
		p_DevKeyboard = NULL;
	}

	//LIBERA o mouse
	if (p_DevMouse)
	{
		//SEMPRE chamar "unacquire" do dispositivo antes de chamar o "Release()"
		p_DevMouse->Unacquire();
		p_DevMouse->Release();
		p_DevMouse = NULL;
	}

	//LIBERANDO o OBJ "DirectInput"
	//OBS: (esse deve ser o último a ser destruído por causa da ordem de alocação)
	if (p_DInput)
	{
		p_DInput->Release();
		p_DInput = NULL;
	}
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize(void)
// Desc: INICIA o teclado e mouse, usando DirectInput.
// Pams: nenhum
//----------------------------------------------------------------------------
bool CNGLInputManager::Initialize()
{
	//INICIA ONJ do DirectInput
	if (FAILED(DirectInputCreate((HINSTANCE)pr_Main->pr_Inst, DIRECTINPUT_VERSION, &p_DInput, NULL)))
	{
		//ERRO de criacao do OBJ DirectInput
		return false;
	}

	//CRIA o teclado
	CreateKeyboard();

	//CRIA o mouse
	CreateMouse();

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: CreateKeyboard(void)
// Desc: CRIA o dispositivo de teclado.
// Pams: nenhum
//----------------------------------------------------------------------------
bool CNGLInputManager::CreateKeyboard() 
{
	if (p_DInput) 
	{
		//CRIANDO dispositivo de teclado
		if (FAILED(p_DInput->CreateDevice(GUID_SysKeyboard, &p_DevKeyboard, NULL))) 
		{
			return false;
		}

		//CONFIGURA o formato de dados do teclado
		if (FAILED(p_DevKeyboard->SetDataFormat(&c_dfDIKeyboard))) 
		{
			return false;
		}

		//PREIMEIRA requisicao de leitura do dispositivo
		p_DevKeyboard->Acquire();

		//SE tudo foi criado sem ERROS
		return true;
	}

	//OBJ do direct Input nao foi criado....
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: CreateMouse(void)
// Desc: Cria o dispositivo de mouse.
// Pams: nenhum
//----------------------------------------------------------------------------