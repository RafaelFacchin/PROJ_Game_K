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
	bool DeleteSprite(CNGLSprite **p_Sprite);

	//FAZ o Scroll (deslocamento) da layer.
	//param cScroll: Tamanho do deslocamento.
	//return:
	void scroll(const CNGLVector& cScroll);

	//CRIA os bricks da layer.
	//param cNumBricks: Tamanho da Matriz de Bricks (ex: 40x40).
	//return:
	void CreateBricks(const CNGLVector& cNumBricks);

	//APAGA todos os bricks da layer.
	//param 
	//return:
	void ClearBricks();

	//AJUSTA a configuração de um brick
	//param cBrickPos : posição do brick no vetor de Bricks.
	//param iImage : indice da imagem na cena.
	//param iFrame : indice do quadro na imagem.
	//return:
	void SetBrick(const CNGLVector& cBrickPos, int iImage, int iFrame);

	//CRIA uma layer com bricks a partir de um bitmap.
	//param cp_chFileName: imagem que contém a disposição dos bricks.
	//param pr_BrickConfigs: configuração de cada brick (onde se associa a cor do pixel com o brick correspondente).
	//param iConfigCount: número de configurações de bricks.
	//return:
	void CreateBricksFromBitmap(const char * cp_chFileName, stCNGLBrickConfig, int iConfigCount);

	//RETORNA o tamanho da layer em pixels
	//param
	//return: Vetor com o tamanho da layer em pixels(x,y)
	CNGLVector GetLayerSize();

	//RETORNA a posição na layer dada a posição no back buffer
	//param BkBuffPos: Posição no back buffer
	//return: Vetor com a posiçao na layer
	CNGLVector GetLayerPos(const CNGLVector& BkBuffPos);

	//RETORNA a posição no back buffer dada a posição na layer e o tamanho do quadro do objeto que utilizará esta posição.
	//PARAM: LayerPos: Posição na layer
	//PARAM: FrameSize: Tamanho do quadro do objeto
	//RETURN:
	CNGLVector GetbackBufferPos(const CNGLVector& LayerPos, const CNGLVector& FrameSize = CNGLVector(0.0f, o.of));

};

#endif
