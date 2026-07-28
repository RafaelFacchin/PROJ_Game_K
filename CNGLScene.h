//-----------------------------------------------------------------------------------------------------
//CLASSE: CNGLScene
//DESCR: Representa a cena de um jogo e gerencia layers e tiles.
//-----------------------------------------------------------------------------------------------------

#ifndef CNGLSCENE_H
#define CNGLSCENE_H

#include "CNGLObject.h"
#include "CNGLStlFiles.h"
#include "CNGLLayer.h"
#include "CNGLImage.h"
#include "CNGLSound.h"

//PROTOTIPOS
class CNGLMain;

class CNGLScene : public CNGLObject 
{
public:
	//LISTA de zero ou mais layers
	vector<CNGLLayer*> Layers;

	//LISTA DE IMAGENS que contem os tiles
	vector<CNGLImage*> TileImages;

	//PONTEIRO P/ "CNGLMain"
	CNGLMain *pr_Main;

public: 

	//FUNC: SCROLL
	//DESCR: Faz o Scroll de todas as layers da cena.
	//PARAM1: cScroll: tamanho do deslocamento das layers na cena.
	//RETORNO: vazio
	void Scroll(const CNGLVector &cScroll);

	//FUNC: LAYER_1
	//DESCR: Cria uma layer e adiciona na cena.
	//PARAM1: cBrickSize : tamanho dos bricks da layer.
	//PARAM2: cNumBricks : tamanho da matriz de bricks.
	//RETORNO:  Ponteiro para a Layer criada.
	CNGLLayer *CreateLayer(const CNGLVector &cBrickSize, const CNGLVector &cNumBricks);

	//FUNC: LAYER_2
	//DESCR: Cria uma layer e adiciona na cena.
	//PARAM1: cBrickSize : tamanho dos bricks da layer.
	//RETORNO:  Ponteiro para a Layer criada.
	CNGLLayer *CreateLayer(const CNGLVector& cBrickSize);

	//FUNC: DELETE LAYER
	//DESCR: Desaloca a layer e a remove da cena.
	//PARAM1 p_Layer : referência ao ponteiro para uma layer que será desalocada.
	//RETORNO: verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	bool DeleteLayer(CNGLLayer **p_Layer);

	//FUNC: UPDATE
	//DESCR: Atualiza as informaçoes da cena.
	void Update();

	//FUNC: DRAW
	//DESCR:	Desenha a cena. Esta rotina é virtual porque ela pode ser reescrita na cena.
	//			Isso é usado em ocasiões onde a cena do usuário desenha objetos que a cena da NGL não
	//			tem controle.Caso essa rotina seja reescrita na classe filha, deve - se chamar a Draw()
	//			da classe pai, para que continue se desenhando os objetos já adicionados na cena.
	virtual void Draw();

	//***CONSTRUTOR-PADRAO:
	CNGLScene();

	//***DESTRUTOR-PADRAO:
	virtual ~CNGLScene();

	//FUNC: RELEASE
	//DESCR: Finaliza a classe.
	//RETURN: verdadeiro se a operação foi bem sucedida
	bool Release();

	//FUNC: ADD TILE IMAGE
	//DESCR: Adiciona uma imagem para ser utilizada como tile nas layers e retorna seu indice no vetor de imagens da cena.
	//PARAM1 cp_chFileName: Nome do arquivo da imagem.
	//PARAM2 cFrameSize: Tamanho do quadro na imagem.
	//RETORNO: Índice da imagem no vetor da cena.
	int AddTileImage(const char *cp_chFileName, const CNGLVector &cFrameSize);

	//FUNC: INITIALIZA
	//DESCR:	Inicializa a cena. Essa rotina deve ser reescrita na cena, para que se possa
	//			criar todos os objetos e fazer inicializações necessárias.
	//RETORNO: verdadeiro se a operação foi bem sucedida
	virtual bool Initializa() = 0;

	//FUNC: EXECUTE
	//DESCR:	Executa a cena. Essa rotina deve ser reescrita na cena, para que se possa
	//			fazer a execução da cena.
	virtual void Execute() = 0;
};

#endif
