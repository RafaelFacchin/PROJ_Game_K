//-----------------------------------------------------------------------------------------------------
//CLASSE: CNGLFrame
//DESCR: Esta classe armazena as informações de um quadro de animação.
//-----------------------------------------------------------------------------------------------------

#ifndef CNGLFRAME_H
#define CNGLFRAME_H

class CNGLFrame 
{
public:
	//!Posição X à esquerda
	int iLeft;
	//!Posição Y acima
	int iTop;
	//!Posição X à direita
	int iRight;
	//!Posição Y abaixo
	int iBottom;

	//***CONSTRUTOR-PADRAO:
	CNGLFrame();

	//***CONSTRUTOR-PARAMETROS
	//PARAM1 iLeftPam : Posição esquerda do quadro
	//PARAM2 iTopPam : Posição do alto do quadro
	//PARAM3 iRightPam : Posição direita do quadro
	//PARAM4 iBottomPam : Posição de baixo do quadro
	CNGLFrame(int iLeftPam, int iTopPam, int iRightPam, int iBottomPam);

	//FUNC: GETWIDTH
	//DESCR: Obtém a largura do quadro
	//PARAM1: 
	//RETORNO: Largura do quadro em pixels.
	int GetWidth();

	//FUNC: GETHEIGHT
	//DESCR: Obtém a altura de um quadro.
	//PARAM1: 
	//RETORNO: Altura do quadro em pixels.
	int GetHeigth();

	//FUNC: ISVALID
	//DESCR: Verifica se o quadro é válido.
	//PARAM1: 
	//RETORNO: verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	bool IsValid();

	//FUNC: COLLIDE
	//DESCR: Retorna verdadeiro se os dois quadros colidem
	//PARAM1: Frame: outro quadro
	//RETORNO: verdadeiro se os quadros colidem
	bool Collide(const CNGLFrame & Frame);
};


#endif
