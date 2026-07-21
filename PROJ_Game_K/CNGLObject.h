//CABECALHO Object - 
//CLASSE: CLASSE BASE p/ todas as outras classes NGL

#ifndef CNGLOBJECT_H
#define CNGLOBJECT_H

//DEFINICAO DO TIPO: Byte
typedef unsigned char Byte;

class CNGLObject 
{
public:
	//**!! FINALIZA a classe: DEVE ser implementada nas classes filhas
	//"return = true" SE op.  bem sucedida
	virtual bool Release() = 0;

	//***CONSTRUTOR-PADRAO:
	CNGLObject();

	//***DESTRUTOR-PADRAO:
	virtual ~CNGLObject();
};

#endif
