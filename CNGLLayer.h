//-----------------------------------------------------------------------------------------------------
//CLASSE: CNGLLayer
//DESCR: Controla a criação e exibição da layer no jogo.
//-----------------------------------------------------------------------------------------------------

#ifndef CNGLLAYER_H
#define CNGLLAYER_H

//INCLUDES
#include "CNGLBrick.h"
#include "CNGLObject.h"
#include "CNGLSprite.h"
#include "CNGLVector.h"
#include "CNGLStlFiles.h"

//PROTOTIPOS
class CNGLScene;

	//FUNC: NGLBrickConfig
	//DESCR: Usada para criar uma layer a partir de um bitmap; Indica que, quando a cor for encontrada deve - se utilizar a imagem e o quadro no brick
	//PARAM1: Frame: outro quadro
	//RETORNO: verdadeiro se os quadros colidem
typedef struct stCNGLBrickConfig
{
	//COR a ser utilizada p/ esta configuracao
	unsigned int uiColor;

	//INDICE da imagem da cena
	int iImage;

	//INDICE do quadro da imagem
	int iFrame;

}CNGLBrickConfig;

class CNGLLayer : public CNGLObject
{
public:
	//PONTEIRO p/ a cena
	CNGLScene *pr_Scene;

	//NUMERO de bricks em "x" e "y" na layer
	CNGLVector NumBricks;

	//TAMANHO dos bbricks na layer
	CNGLVector BrickSize;

	//LAYER offSet - DESLOCAMENTO da layer em relacao ao video
	CNGLVector Offset;

	//VELOCIDADE da Layer no Scroll
	CNGLVector Speed;

	//VETOR de Bricks`s p/ preenchimento da layer
	CNGLBrick** p_Bricks;

	//LISTA de sprites da layer
	vector<CNGLSprite*> Sprites;

	//FLAG que indica se a layer esta visivel ou nao
	bool bVisible;

public:

	//***CONSTRUTOR-PADRAO: CNGLLAYER
	CNGLLayer();

	//***DESTRUTOR-PADRAO
	virtual ~CNGLLayer();

	//**FINALIZA a classe
	bool Released();

	//ATUALIZA  A LAYER
	void Update();

	//DESENAH A lAYER
	void Draw();

	//CRIA um sprite e adiciona ele à layer.
	//param cp_chFileName : Imagem de origem do sprite.
	//param cFrameSize : Tamanho do quadro do sprite.
	//return Ponteiro para o sprite criado
	CNGLSprite* CreateSprite(const char* cp_chFileName, const CNGLVector& cFrameSize);

	//Deleta um sprite e o remove da layer.
	//param p_Sprite : referência ao ponteiro para um sprite que será desalocado.
	//return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.


};


#endif
