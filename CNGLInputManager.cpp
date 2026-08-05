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
bool CNGLInputManager::CreateMouse() 
{
	if (p_DInput) 
	{
		//CRIA dispositivo de teclado
		if (FAILED(p_DInput->CreateDevice(GUID_SysMouse, &p_DevMouse, NULL))) 
		{
			return false;
		}

		//CONFIGURA FORMATO de dados: TECLADO
		if(FAILED(p_DevMouse->SetDataFormat(&c_dfDIMouse)))
		{
			return false;
		}

		//REQUISICAO de leitura do dispositivo
		p_DevMouse->Acquire();

		//SETA posicao inicial do mouse no centro da tela
		MousePos.fx = pr_Main->VideoManager.VideoSize.fx / 2;
		MousePos.fy = pr_Main->VideoManager.VideoSize.fy / 2;

		//**SE TUDO for criado sem ERROS:
		return true;
	}

	//SE OBJ da Direct Input nao for criado...
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: READ(void)
// Desc: Lê entradas do teclado e mouse.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLInputManager::Read() 
{
	if (p_DevKeyboard)
	{
		if (!ReadKeyboard())
		{
			return false;
		}
	}
	if (p_DevMouse)
	{
		if (!ReadMouse())
		{
			return false;
		}
	}
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: ReadKeyboard(void)
// Desc: Lê dados do teclado.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLInputManager::ReadKeyboard()
{
	HRESULT hr;

	//COPIA o estado atual p/ o estado anterior
	memcpy(LastKeyboardState, KeyboardState, sizeof(LastKeyboardState));

	//ZERA os estados do vetor
	ZeroMemory(KeyboardState, sizeof(KeyboardState));

	//PEGA O ESTADO CORRENTE DO TECLADO
	hr = p_DevKeyboard->GetDeviceState(sizeof(KeyboardState), (LPVOID)&KeyboardState);

	//VERIFICA se deu erro
	if (FAILED(hr))
	{
		//SE falhou, provavelmente o dispositivo foi perdido
		//DEVE-SE recupera-lo por aqui
		hr = p_DevKeyboard->Acquire();

		//DEFINE loop ateh conseguir acesso aos dispositivos
		while (hr == DIERR_INPUTLOST)
		{
			hr = p_DevKeyboard->Acquire();
		}

		//SE houve algum outro ERRO
		if (FAILED(hr))
		{
			return false;
		}
	}
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: ReadMouse(void)
// Desc: Lê dados do mouse.
// Pams: nenhum
//----------------------------------------------------------------------------
bool CNGLInputManager::ReadMouse()
{
	HRESULT hr;

	//COPIA o estado atual p/ o estado anterior
	memcpy(&LastMouseState, &MouseState, sizeof(LastMouseState));

	//ZERA os estados do vetor
	ZeroMemory(&MouseState, sizeof(MouseState));

	//PEGA o estado corrente do mouse
	hr = p_DevMouse->GetDeviceState(sizeof(MouseState), (LPVOID)&MouseState);

	//VERIFICA ERRO
	if (FAILED(hr))
	{
		//SE falhou provavelmente o dispositivo foi perdido
		//ENTAO deve-se tentar recuperalo
		hr = p_DevKeyboard->Acquire();

		//LOOP ate conseguir acesso ao dispositivo
		while (hr == DIERR_INPUTLOST)
		{
			hr = p_DevKeyboard->Acquire();
		}

		//SE houve algum outro ERRO
		if (FAILED(hr))
		{
			return false;
		}
	}

	if (pr_Main->VideoManager.WindowFrame.GetWidth() > 0 && pr_Main->VideoManager.WindowFrame.GetHeight() > 0)
	{
		//CONVERTE a coordenada do mouse do windows p/  a coordenada equivalente no BackBuffer
		CNGLVector NewPos = MouseWindowsPos;

		NewPos.fx = (NewPos.fx * pr_Main->VideoManager.VideoSize.fx) / (float)pr_Main->VideoManager.WindowFrame.GetWidth();
		NewPos.fy = (NewPos.fy * pr_Main->VideoManager.VideoSize.fy) / (float)pr_Main->VideoManager.WindowFrame.GetHeight();

		//NOVA posicao do mouse
		MousePos = NewPos;
	}

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: IsMouseOn(void)
// Desc: Retorna verdadeiro se o mouse estiver ligado, senão retorna falso
// Pams: nenhum
//----------------------------------------------------------------------------
bool CNGLInputManager::isMouseOn()
{
	return (p_DevMouse != NULL);
}

//---------------------------------------------------------------------------- 
// Nome: KeyDown(const Byte cbyKeyCode)
// Desc: Verifica se uma tecla está abaixada.
// Pams: código da tecla
//----------------------------------------------------------------------------
bool CNGLInputManager::KeyDown(const Byte cbyKeyCode)
{
	return (NGLKEYDOWN(KeyboardState, cbyKeyCode)) ? true : false;
}

//---------------------------------------------------------------------------- 
// Nome: KeyPressed(const Byte cbyKeyCode)
// Desc: Verifica se uma tecla foi pressionada neste instante.
// Pams: código da tecla
//----------------------------------------------------------------------------
bool CNGLInputManager::KeyPressed(const Byte cbyKeyCode)
{
	//se o estado anterior da tecla for não pressionado e o estado atual for pressionado,
	//logo a tecla foi pressionada exatamente neste momento.
	return (!NGLKEYDOWN(LastKeyboardState, cybKeyCode) && NGLKEYDOWN(KeyboardState, cbyKeyCode)) ? true : false;
}

//---------------------------------------------------------------------------- 
// Nome: KeyReleased(const Byte cbyKeyCode)
// Desc: Verifica se uma tecla foi largada neste instante.
// Pams: código da tecla
//----------------------------------------------------------------------------
bool CNGLInputManager::KeyReleased(const Byte cbyKeyCode)
{
	//SE o estado anterior da tecla for pressionado e o estado atual for não pressionado,
	//logo a tecla foi largada exatamente neste momento.
	return (NGLKEYDOWN(LastKeyboardState, cbyKeyCode) && !NGLKEYDOWN(KeyboardState, cbyKeyCode)) ? true : false;
}

//---------------------------------------------------------------------------- 
// Nome: MouBtnDown(Byte cbyBtnCode)
// Desc: Verifica se um botão do mouse está abaixado.
// Pams: código do botão (ex: 0, 1, 2)
//----------------------------------------------------------------------------
bool CNGLInputManager::MouBtnDown(const Byte cbyBtnCode)
{
	return (NGLMOUBTNDOWN(MouseState, cbyBtnCode)) ? true : false;
}

//---------------------------------------------------------------------------- 
// Nome: MouBtnPressed(Byte cbyBtnCode)
// Desc: Verifica se um botão do mouse foi pressionado neste instante.
// Pams: código do botão (ex: 0, 1, 2)
//----------------------------------------------------------------------------
bool CNGLInputManager::MouBtnPressed(const Byte cbyBtnCode)
{
	return (!NGLKEYDOWN(LastMouseState, cbyBtnCode) && NGLMOUBTNDOWN(MouseState, cbyBtnCode)) ? true : false;
}

//---------------------------------------------------------------------------- 
// Nome: MouBtnReleased(Byte cbyBtnCode)
// Desc: Verifica se um botão do mouse foi largado neste instante.
// Pams: código do botão (ex: 0, 1, 2)
//----------------------------------------------------------------------------
bool CNGLInputManager::MouBtnreleased(const Byte cbyBtnCode)
{
	return (NGLMOUBTNDOWN(LastMouseState, cbyBtnCode) && !NGLMOUBTNDOWN(MouseState, cbyBtnCode)) ? true : false;
}

//---------------------------------------------------------------------------- 
// Nome: SetWindowsMousePos(const CNGLVector &cNewPos)
// Desc: Ajusta a nova posição do mouse vinda da aplicação Windows.
// Pams: posição
//----------------------------------------------------------------------------
void CNGLInputManager::SetWindowsMousePos(const CNGLVector& cNewPos)
{
	MouseWindowsPos = cNewPos;
}