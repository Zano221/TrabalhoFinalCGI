#pragma once
#include "SceneBaseClass.h"
#include "CTexture.h"
#include "CTimer.h"
#include "CTexto.h"
#include "CCamera.h"
#include "CModel_3DS.h"



class CSceneTrabalhoFinal : public CSceneBaseClass
{
public:
	CSceneTrabalhoFinal();
	~CSceneTrabalhoFinal(void);


	virtual void MouseMove(void);					// Tratamento de movimento do mouse
	virtual void KeyPressed(void);					// Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);					// Função que desenha a cena

	void Draw3DSGrid(float width, float length);
	void DrawAxis();


	///////////// FUNÇÕES DO TRABALHO FINAL /////////////////
	void DrawGround();
	void DrawHouse();
	void DrawOcean();
	void CreateSkyBox(float x, float y, float z,
		float width, float height, float length,
		CTexture* pTextures);

private:

	bool	keys[256];		// Array usado para rotinas do teclado
	bool	active;			// Window Active Flag Set To TRUE By Default
	bool	fullscreen;		// Exibir janela em modo fullscreem (TRUE) ou em janela (FALSE)


	CCamera* pCamera;	// Gerencia câmera OpenGL
	float fDeltaY;				// Rotação da câmera OpenGL no eixo Y
	float fDeltaX;				// Rotação da câmera OpenGL no eixo X

	CTexto* pTexto;	// Objeto que gerencia texto
	CTexture* pTextures;	// Objeto que gerencia texturas
	CTimer* pTimer;	// Objeto que gerencia o timer


	int		iFPS;			// FPS and FPS Counter
	int		iFrames;		// FPS and FPS Counter
	DWORD	ulLastFPS;		// FPS and FPS Counter
	char	szTitle[256];	// FPS and FPS Counter


	bool bIsWireframe;	// Modos Wireframe/Solid
	bool bIsCameraFPS;	// Ativa modo de camera First Person Shooter (true) ou Third Person Shooter (false)

	float fRenderPosY;
	float fTimerPosY;


	///////////// VARIAVEIS DO TRABALHO FINAL /////////////////


	float fPosX;
	float fPosY;
	float fPosZ;

	//Texutras
	//CTexture* pTextures;

	// Modelos 3DS
	CModel_3DS* pModel_CasaCJ; // Casa do CJ
	CModel_3DS* pModel_GroveStreet; // Mapa da Grove Street


	// Definição das configurações da fonte de luz (EMISSOR)
	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightSpecular[4];
	GLfloat LightPosition[4];

	// Definição das configurações do material do objeto (REFLEXÂO)
	GLfloat MatAmbient[4];
	GLfloat MatDiffuse[4];
	GLfloat MatSpecular[4];
	float MatShininess;

};

