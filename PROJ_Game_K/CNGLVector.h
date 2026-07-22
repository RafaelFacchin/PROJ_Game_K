//-----------------------------------------------------------------------------------------------------
//CLASSE: CNGLVector
//DESCR: Classe utilizada p/ posicionamento de objetos e calculos matematicos
//-----------------------------------------------------------------------------------------------------

#ifndef CNGLVECTOR_H
#define CNGLVECTOR_H

#include "CNGLObject.h"

class CNGLVector : public CNGLObject 
{
public:

	//EIXO "X" do vetor
	float fx;

	//EIXO "Y" do vetor
	float fy;

public:
	//***CONSTRUTOR-PADRAO c/ parametros
	//param ix: posicao em X
	//param iy: posicao em Y
	CNGLVector(int ix, int iy);

	//***CONSTRUTOR-PADRAO c/ parametros
	//param fxPam: posicao em X
	//param fyPam: posicao em Y
	CNGLVector(int fxPam, int fyPam);

	//***CONSTRUTOR-PADRAO:
	CNGLVector();

	//***DESTRUTOR-PADRAO:
	~CNGLVector();

	//FINALIZA  a classe; DEVERA ser implementado nas classes filhas; (return = true) SE bem sucedida
	bool Release() { return true };

	//OPERADOR de comparacao de igualdade
	//PARAM cv: vetor a comparar
	bool operator ==(const CNGLVector & cv);

	//OPERADOR de comparacao de diferenca
	//PARAM cv: vetor a comparar
	bool operator !=(const CNGLVector& cv);

	//OPERADOR p/ calcular MODULO vetor; RETORNA o modulo do vetor
	float Magnitude();

	//TRANSFORMA este vetor em vetor unitário mantendo a direção.
	void Normalize();

	//OPERACAO de subtração de dois vetores.
	//PARAM cv: vetor a subtrair
	CNGLVector operator-(const CNGLVector & cv);

	//OPERACAO de soma de dois vetores.
	//PARAM cv: vetor a somar
	CNGLVector operator+(const CNGLVector & cv);

	//OPERACAO de somar outro vetor a este.
	//PARAM cv: vetor a somar
	void operator+=(const CNGLVector & cv);

	//OPERACAO de subtrair outro vetor a este.
	//PARAM cv: vetor a subtrair
	void operator-=(const CNGLVector & cv);

	//OPERACAO de divisao deste vetor por constante.
	//PARAM cfVal: constante da divisao
	CNGLVector operator/(const float cfVal);

	//OPERACAO de multiploicar um valor p/ uma constante
	//PARAM cfVal: constante da multiplicacao
	void operator*=(const float cfVa);

	//OPERACAO de RETORNAR o priduto escalar de 2 vetores
	//PARAM cv: VETOR p/ calcular o produto escalar
	float DotProduct(const CNGLVector& cv);

	//op: ELIMINA as casas decimais dos elementos do vetor
	void floor();

	//OP: Arredonda p/ "CIMA" os elementos do vetor
	void Ceil();
};

#endif
