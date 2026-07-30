#include "CNGLFrame.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLFrame(void)
// Desc: CONSTRUTOR-PADRAO
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLFrame::CNGLFrame() 
{
	iLeft = iTop = iBottom = iRight = 0;
}

//---------------------------------------------------------------------------- 
// Nome: CNGLFrame(int iLeftPam, int iTopPam, int iRightPam, int iBottomPam);
// Desc: contrutor com parâmetros
// Pams: left, top, right, bottom
//----------------------------------------------------------------------------
CNGLFrame::CNGLFrame(int iLeftPam, int iTopPam, int iRightPam, int iBottomPam) 
{
	iLeft = iLeftPam;
	iTop = iTopPam;
	iRight = iRightPam;
	iBottom = iBottomPam;
}

//---------------------------------------------------------------------------- 
// Nome: GetWidth(void)
// Desc: RETORNA a largura do quadro
// Pams: nenhum
//----------------------------------------------------------------------------
int CNGLFrame::GetWidth() 
{
	return iRight - iLeft;
}

//---------------------------------------------------------------------------- 
// Nome: GetHeight(void)
// Desc: RETORNA a altura do quadro
// Pams: nenhum
//---------------------------------------------------------------------------- 
int CNGLFrame::GetHeigth()
{
	return iBottom - iTop;
}

//---------------------------------------------------------------------------- 
// Nome: IsValid(void)
// Desc: RETORNA verdadeiro se o quadro for válido
// Pams: nenhum
//---------------------------------------------------------------------------
bool CNGLFrame::IsValid()
{
	return(iBottom >= iTop && iRight >= iLeft);
}

//---------------------------------------------------------------------------- 
// Nome: Collide(const CNGLFrame & Frame)
// Desc: retorna verdadeiro se os dois quadros colidem
// Pams: outro quadro para testar colisão
//---------------------------------------------------------------------------- 
bool CNGLFrame::Collide(const CNGLFrame& Frame) 
{
	return((iLeft < Frame.iRight) && (iRight > Frame.iLeft) &&
		(iTop < Frame.iBottom) && (iBottom > Frame.iTop));
}