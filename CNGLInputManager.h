//-----------------------------------------------------------------------------------------------------
//CLASSE: CNGLInputManager
//DESCR: GERENCIA as atividades de INPUT (teclado e mouse)
//-----------------------------------------------------------------------------------------------------

#ifndef CNGLINPUTMANAGER_H
#define CNGLINPUTMANAGER_H

#ifndef DIRECTINPUT_VERSION
		#define DIRECTINPUT_VERSION         0x0300
#endif

#include "dinput.h"
#include "CNGLObject.h"
#include "CNGLVector.h"

class CNGLMain;

//NUMERO DE TECLAS DO TECLADO
#define NGLNUM_KEYS 256

class CNGLInputManager : public CNGLObject 
{
public:

	//PTR de referencia p/ a CNGLMain
	CNGLMain* pr_Main;

	//***CONSTRUTOR-PADRAO
	CNGLInputManager();

	//***DESTRUTOR-PADRAO
	virtual ~CNGLInputManager();

	//FINALIZA a classe; (return=true) SE a op. for bem sucedida
	bool Release();

	//INICIA o teclado e mouse, usando o "DirectInput"; (return=true) SE a op. for bem sucedida
	bool Initialize();

	//LEH entradas do teclado e mouse; (return=true) SE a op. for bem sucedida
	bool Read();

	//RETORNA posicao atual do cursor do mouse; (return= CNGLVector), contendo o posicao do mouse
	inline CNGLVector GetMousePos() { return MousePos; };

private:

	//LEH dados do teclado; (return=true) SE conseguiu ler.
	bool ReadKeyboard();

	//LEH dados do mouse; (return=true) SE conseguiu ler.
	bool ReadMouse();

private:

	//OBJ do DirectInput
	IDirectInput *p_DInput;

	//DISPOSITIVO de teclado do DirectInput
	IDirectInputDevice *p_DevKeyboard;

	//DISPOSITIVO de mouse do DirectInput
	IDirectInputDevice *p_DevMouse;

	//**ESTRUT_DADOS: guarda o estado atual do TECLADO
	Byte KeyboardState[NGLNUM_KEYS];

	//**ESTRUT_DADOS: guarda o estado anterior do TECLADO; USADA p/ verificar se uma tecla foi recem pressionada ou largada
	Byte LastKeyboardState[NGLNUM_KEYS];

	//**ESTRUT_DADOS: guarda o estado atual do MOUSE
	DIMOUSESTATE MouseState;

	//**ESTRUT_DADOS: guarda o estado anterior do MOUSE; USADA p/ verificar se uma tecla foi recem pressionada ou largada
	DIMOUSESTATE LastMouseState;

	//POSICAO ATUAL do mouse
	CNGLVector MousePos;

	//POSICAO do mouse ORIUNDA WINDOWS
	CNGLVector MouseWindowsPos;

public:

	//CRIA o dispositivo do teclado; (return=true) SE conseguiu ler.
	bool CreateKeyboard();

	//CRIA o dispositivo de mouse; (return=true) SE conseguiu ler.
	bool CreateMouse();

	//VERIFICA SE o mouse esta ligado; (return=true) SE conseguiu ler.
	bool isMouseOn();

	//VERIFICA SE uma tecla estah presionada; (return=true) SE conseguiu ler.
	//PARAM cbyKeyCode: código da tecla. Usar tabela de constantes de teclas do DirectInput.
	bool KeyDown(const Byte cbyKeyCode);

	//VERIFICA SE uma tecla FOI presionada neste instante; (return=true) SE conseguiu ler.
	//PARAM cbyKeyCode: código da tecla. Usar tabela de constantes de teclas do DirectInput.
	bool KeyPressed(const Byte cbyKeyCode);

	//VERIFICA SE uma tecla FOI LARGADA neste instante; (return=true) SE conseguiu ler.
	//PARAM cbyKeyCode: código da tecla. Usar tabela de constantes de teclas do DirectInput.
	bool KeyReleased(const Byte cbyKeyCode);

	//VERIFICA SE uma botao do mouse ESTA PRESSIONADA; (return=true) SE estiver pressionado.
	//PARAM cbyKeyCode: código do botao (ex: 0,1,2)
	bool MouBtnDown(const Byte cbyKeyCode);

	//VERIFICA SE uma botao do mouse FOI PRESSIONADA; (return=true) SE estiver pressionado.
	//PARAM cbyKeyCode: código do botao (ex: 0,1,2)
	bool MouBtnPressed(const Byte cbyKeyCode);

	//VERIFICA SE uma botao do mouse FOI LARGADA; (return=true) SE estiver largada.
	//PARAM cbyKeyCode: código do botao (ex: 0,1,2)
	bool MouBtnreleased(const Byte cbyKeyCode);

	//AJUSTA  a nova posicao do mouse vinda da aplic. WINDOWS
	//PARAM cNewPos: CNGLVector contendo a nova posicao do mouse
	void SetWindowsMousePos(const CNGLVector &cNewPos);

};

#endif