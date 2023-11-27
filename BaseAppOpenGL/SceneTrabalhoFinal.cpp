//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ESSA É A CENA DO TRABALHO FINAL, TODOS OS CONCEITOS NECESSARIOS MOSTRADOS NO PROJETO DA DISCIPLINA SERÃO USADOS AQUI, ELES PODEM SER VISTOS ///
// DENTRO DO CORPO DA FUNÇÃO "DrawGLScene". //////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SceneTrabalhoFinal.h"

CSceneTrabalhoFinal::CSceneTrabalhoFinal()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;

	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	//pTextures = new CTexture();	

	/*fPosX = 15.0f;
	fPosY = 36.0f;
	fPosZ = 181.0f;*/

	fPosX = -600.0f;
	fPosY = 700.0f;
	fPosZ = 700.0f;

	// Texturas do Skybox aaa
	pTextures = new CTexture();
	pTextures->CreateTextureClamp(0, "../SceneTrabalhoFinal/back.bmp");
	pTextures->CreateTextureClamp(1, "../SceneTrabalhoFinal/front.bmp");
	pTextures->CreateTextureClamp(2, "../SceneTrabalhoFinal/down.bmp");
	pTextures->CreateTextureClamp(3, "../SceneTrabalhoFinal/up.bmp");
	pTextures->CreateTextureClamp(4, "../SceneTrabalhoFinal/right.bmp");
	pTextures->CreateTextureClamp(5, "../SceneTrabalhoFinal/left.bmp");
	pTextures->CreateTextureLinear(6, "../SceneTrabalhoFinal/water.bmp");
	pTextures->CreateTextureAnisotropic(7, "../SceneTrabalhoFinal/SweBas.jpg");

	//Carrega a Grove Street
	pModel_GroveStreet = NULL;
	pModel_GroveStreet = new CModel_3DS();
	pModel_GroveStreet->Load("../SceneTrabalhoFinal/GroveStreet.3DS");

	// Carrega a casa do CJ
	pModel_CasaCJ = NULL;
	pModel_CasaCJ = new CModel_3DS();
	pModel_CasaCJ->Load("../SceneTrabalhoFinal/CasaCJ.3DS");

	// Carrega a casa do Ryder
	pModel_CasaRyder = NULL;
	pModel_CasaRyder = new CModel_3DS();
	pModel_CasaRyder->Load("../SceneTrabalhoFinal/CasaRyder.3DS");

	// Carrega a casa do Swet
	pModel_CasaSweet = NULL;
	pModel_CasaSweet = new CModel_3DS();
	pModel_CasaSweet->Load("../SceneTrabalhoFinal/CasaSweet.3DS");

	// Definir a iluminação
	// Definição das configurações da fonte de luz (EMISSOR)
	LightAmbient[0] = 0.1f; LightAmbient[1] = 0.1f; LightAmbient[2] = 0.1f; LightAmbient[3] = 1.0f;
	LightDiffuse[0] = 1.0f; LightDiffuse[1] = 1.0f; LightDiffuse[2] = 1.0f; LightDiffuse[3] = 1.0f;
	LightSpecular[0] = 1.0f; LightSpecular[1] = 1.0f; LightSpecular[2] = 1.0f; LightSpecular[3] = 1.0f;
	LightPosition[0] = fPosX; LightPosition[1] = fPosY; LightPosition[2] = fPosZ; LightPosition[3] = 1.0f;
	//LightPosition[1][0] = 0.0f; LightPosition[1][1] = 26.0f; LightPosition[1][2] = 0.0f; LightPosition[1][3] = 1.0f;
	//LightPosition[2][0] = 0.0f; LightPosition[2][1] = 2500.0f; LightPosition[2][2] = 0.0f; LightPosition[2][3] = 1.0f;
	//LightPosition[3][0] = 0.0f; LightPosition[3][1] = 26.0f; LightPosition[3][2] = 0.0f; LightPosition[3][3] = 1.0f;
	//LightPosition[4][0] = 0.0f; LightPosition[4][1] = 26.0f; LightPosition[4][2] = 0.0f; LightPosition[4][3] = 1.0f;
	//LightDirection[0] = 0.0f; LightDirection[1] = -1.0f; LightDirection[2] = 0.0f;


	// Definição das configurações do material do objeto (REFLEXÂO)
	MatAmbient[0] = 0.1f; MatAmbient[1] = 0.1f; MatAmbient[2] = 0.1f; MatAmbient[3] = 1.0f;
	MatDiffuse[0] = 1.0f; MatDiffuse[1] = 1.0f; MatDiffuse[2] = 1.0f; MatDiffuse[3] = 1.0f;
	MatSpecular[0] = 0.0f; MatSpecular[1] = 0.0f; MatSpecular[2] = 0.0f; MatSpecular[3] = 1.0f;
	MatShininess = 128.0f;
}


CSceneTrabalhoFinal::~CSceneTrabalhoFinal(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}	

	if (pModel_CasaCJ) {
		delete pModel_CasaCJ;
		pModel_CasaCJ = NULL;
	}

	if (pModel_CasaRyder) {
		delete pModel_CasaRyder;
		pModel_CasaRyder = NULL;
	}

	if (pModel_CasaSweet) {
		delete pModel_CasaSweet;
		pModel_CasaSweet = NULL;
	}
}




int CSceneTrabalhoFinal::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter
	
	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posições da câmera
	pCamera->setView();

	// Desenha grid 
	Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	// Habilita mapeamento de texturas 2D
	glEnable(GL_TEXTURE_2D);



	////////////////////////////////////
	/////// TÉTCNICAS UTILIZADAS ///////
	////////////////////////////////////

	

	////////////////
	// g. SkyBox //
	//////////////
	CreateSkyBox(0.0f, 100.0f, 0.0f,
		2700.0f, 2700.0f, 2700.0f,
		pTextures);


	/////////////////////////////////////////////////////////
	// d. Iluminação com alguma fonte de luz(Point, Spot) //
	/////////////////////////////////////////////////////// 
	glEnable(GL_LIGHTING); //  Habilita iluminação

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition); //
	glLightf(GL_LIGHT0, GL_SHININESS, 255);
	glEnable(GL_LIGHT0); // Habilita a luz 2

	/////////////////////////////////////////////////////////////
	// a. Modelagem de objetos usando Modo Imediato(glVertex) //
	///////////////////////////////////////////////////////////

	///////////////////////////////////////////////////
	// b. Modelagem de objetos usando 3DS MAX(.3DS) //
	/////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////
	// c. Mapeamento de texturas usando Unrap UVW(3DS MAX) //
	//////////////////////////////////////////////////////// 
	

	// Renderizar a casa do CJ (b, c)
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(150.0f, 0.0f, -20.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	pModel_CasaCJ->Draw();
	glPopMatrix();

	// Renderizar a casa do Ryder (b, c)
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(120.0f, 5.0f, 130.0f);
	//glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	pModel_CasaRyder->Draw();
	glPopMatrix();

	//Renderizar a casa do Sweet (b, c)
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(0.0f, -3.0f, -190.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	pModel_CasaSweet->Draw();
	glPopMatrix();
	
	//Renderizar a Grove Street (b, c, f)
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	pModel_GroveStreet->Draw();
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(-60.0f, 2.0f, -180.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	pTextures->ApplyTexture(7);
	auxSolidSphere(1.0);
	glPopMatrix();

	///////////////////////////////////////////
	// e. Filtro Anisotrópico para texturas //
	/////////////////////////////////////////

	

	//////////////////////////////////////////////////
	// h. Environmap Mapping(SphereMap ou CubeMap) //
	////////////////////////////////////////////////

	////////////////////////////////
	// i. Bump ou Normal Mapping //
	//////////////////////////////
	
	// Desabilitar luz
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// Renderizar o sol

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(LightPosition[0], LightPosition[1], LightPosition[2]);
	auxSolidSphere(6.0);
	glPopMatrix();

	/////////////////////////////////
	// k. Transparência(Blending) //
	///////////////////////////////
	// 
	/////////////////////////
	// f. Multi - Textura //
	////////////////////////

	// Habilita Blending
	glEnable(GL_BLEND);
	// Configura função de Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
	
	// RENDERIZAR O OCEANO
	glPushAttrib(GL_TEXTURE_BIT);
	// Unidade de Textura 0
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	pTextures->ApplyTexture(6);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);

	// Unidade de Textura 1
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	pTextures->ApplyTexture(6);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f + fRenderPosY);
	glMultiTexCoord2f(GL_TEXTURE1, 0.0f + fRenderPosY, 0.0f);
	glVertex3f(-2000.0f, -20.0f, 2000.0f);

	glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f + fRenderPosY);
	glMultiTexCoord2f(GL_TEXTURE1, 1.0f + fRenderPosY, 0.0f);
	glVertex3f(2000.0f, -20.0f, 2000.0f);

	glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f + fRenderPosY);
	glMultiTexCoord2f(GL_TEXTURE1, 1.0f + fRenderPosY, 1.0f);
	glVertex3f(2000.0f, -20.0f, -2000.0f);

	glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f + fRenderPosY);
	glMultiTexCoord2f(GL_TEXTURE1, 0.0f + fRenderPosY, 1.0f);
	glVertex3f(-2000.0f, -20.0f, -2000.0f);
	glEnd();
	glPopMatrix();

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	

	////////////////////////////////////////////
	/////// TÉTCNICAS EXTRAS UTILIZADAS ////////
	////////////////////////////////////////////







	



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.00025f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 100, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime()/1000));


	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CSceneTrabalhoFinal::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CSceneTrabalhoFinal::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Senão, interrompe movimento do Player
	else
	{

	}

	if (GetKeyState(VK_LEFT) & 0x80)
		fPosX -= 0.1f;
	if (GetKeyState(VK_RIGHT) & 0x80)
		fPosX += 0.1f;
	if (GetKeyState(VK_UP) & 0x80)
		fPosZ -= 0.1f;
	if (GetKeyState(VK_DOWN) & 0x80)
		fPosZ += 0.1f;
	if (GetKeyState(VK_PRIOR) & 0x80)
		fPosY += 0.1f;
	if (GetKeyState(VK_NEXT) & 0x80)
		fPosY -= 0.1f;



}

void CSceneTrabalhoFinal::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CSceneTrabalhoFinal::Draw3DSGrid(float width, float length)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void CSceneTrabalhoFinal::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


void CSceneTrabalhoFinal::CreateSkyBox(float x, float y, float z,
	float width, float height, float length,
	CTexture* pTextures)
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();

	// Centraliza o Skybox em torno da posição especificada(x, y, z)
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;


	// Aplica a textura que representa a parte da frente do skybox (BACK map)
	pTextures->ApplyTexture(0);

	// Desenha face BACK do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (FRONT map)
	pTextures->ApplyTexture(1);

	// Desenha face FRONT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (DOWN map)
	pTextures->ApplyTexture(2);

	// Desenha face BOTTOM do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (UP map)
	pTextures->ApplyTexture(3);

	// Desenha face TOP do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (LEFT map)
	pTextures->ApplyTexture(4);

	// Desenha face LEFT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (RIGHT map)
	pTextures->ApplyTexture(5);

	// Desenha face RIGHT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopMatrix();
}

glm::vec3 CSceneTrabalhoFinal::CalculateTriangleNormalVector(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	/*
			   p3
			   /\
			  /  \
			 /    \
			/      \
			+------+
		   p1      p2
	*/

	// Encontrar os vetores v1 e v2, resultado da subtração dos vetores (p2 - p1) e 
	// (p3 - p1), respectivamente
	glm::vec3 v1, v2;
	v1.x = p2.x - p1.x;
	v1.y = p2.y - p1.y;
	v1.z = p2.z - p1.z;

	v2.x = p3.x - p1.x;
	v2.y = p3.y - p1.y;
	v2.z = p3.z - p1.z;

	// Calcular o Cross Product para achar o vetor Normal (não normalizado)
	glm::vec3 normal;
	normal.x = v1.y * v2.z - v1.z * v2.y;
	normal.y = v1.z * v2.x - v1.x * v2.z;
	normal.z = v1.x * v2.y - v1.y * v2.x;

	// Calcula a magnitude do vetor normal
	double magnitude = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

	// Normaliza o vetor normal
	glm::vec3 normalizedVector;
	normalizedVector.x = normal.x / magnitude;
	normalizedVector.y = normal.y / magnitude;
	normalizedVector.z = normal.z / magnitude;

	// Retorna o vetor Normal (normalizado)
	return normalizedVector;
}