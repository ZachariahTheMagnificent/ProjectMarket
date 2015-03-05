#include "Graphics.h"
#include "MeshBuilder.h"

static const unsigned NUM_OF_LIGHT_PARAMETERS = 11;

Graphics::Graphics()
	:
meshText(L"text")
{
}

Graphics::~Graphics()
{
	if(meshText.GetMesh())
	{
		delete meshText.GetMesh();
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void Graphics::Init(GLFWwindow* window)
{
	m_window = window;
	// Set background color to blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);
	//Enable back face culling
	glEnable(GL_CULL_FACE);
	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//MultiLight.fragmentshader" );

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	for(int index = 0; index < MAX_LIGHTS; ++index)
	{
		char typeBuffer[126];
		char directionBuffer[126];
		char cutoffBuffer[126];
		char innerBuffer[126];
		char exponentBuffer[126];
		char positionBuffer[126];
		char colorBuffer[126];
		char powerBuffer[126];
		char kCBuffer[126];
		char kLBuffer[126];
		char kQBuffer[126];

		sprintf(typeBuffer, "lights[%d].type", index);
		sprintf(directionBuffer, "lights[%d].spotDirection", index);
		sprintf(cutoffBuffer, "lights[%d].cosCutoff", index);
		sprintf(innerBuffer, "lights[%d].cosInner", index);
		sprintf(exponentBuffer, "lights[%d].exponent", index);
		sprintf(positionBuffer, "lights[%d].position_cameraspace", index);
		sprintf(colorBuffer, "lights[%d].color", index);
		sprintf(powerBuffer, "lights[%d].power", index);
		sprintf(kCBuffer, "lights[%d].kC", index);
		sprintf(kLBuffer, "lights[%d].kL", index);
		sprintf(kQBuffer, "lights[%d].kQ", index);

		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, typeBuffer);
		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, directionBuffer);
		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, cutoffBuffer);
		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, innerBuffer);
		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, exponentBuffer);
		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, positionBuffer);
		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, colorBuffer);
		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_POWER] = glGetUniformLocation(m_programID, powerBuffer);
		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_KC] = glGetUniformLocation(m_programID, kCBuffer);
		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_KL] = glGetUniformLocation(m_programID,kLBuffer);
		m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_KQ] = glGetUniformLocation(m_programID, kQBuffer);
	}

	glUseProgram(m_programID);

	for(int index = 0; index < MAX_LIGHTS + 1; ++index)
	{
		lights[index] = NULL;
	}
	currentNumOfLights = 0;
}

void Graphics::InitText(std::wstring filepath)
{
	meshText.SetMeshTo(MeshBuilder::GenerateText(filepath,16,16));
	textMaterial = Material(L"mat", Component(1,1,1), Component(1,1,1), Component(1,1,1), 20,LoadTGA(filepath));
	meshText.SetMaterialTo(&textMaterial);
}

void Graphics::SetViewAt(const Camera& camera)
{
	viewStack.LoadIdentity();
	Vector3 position, target, up;
	position = camera.ReturnPosition();
	target = camera.ReturnTarget();
	up = camera.ReturnUp();
	viewStack.LookAt(position.x, position.y, position.z, target.x, target.y, target.z, up.x, up.y, up.z);
}

void Graphics::SetProjectionTo(const float FOVy, const float aspectRatio, const float nearPlane, const float farPlane)
{
	Mtx44 projection;
	projection.SetToPerspective(FOVy, aspectRatio, nearPlane, farPlane);
	projectionStack.LoadMatrix(projection);
}

bool Graphics::AddLight(Light* light)
{
	if(currentNumOfLights < MAX_LIGHTS)
	{
		lights[currentNumOfLights] = light;

		glUniform1i(m_parameters[U_NUMLIGHTS], currentNumOfLights + 1);

		glUniform1i(m_parameters[currentNumOfLights*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_TYPE], lights[currentNumOfLights]->type);
		glUniform3fv(m_parameters[currentNumOfLights*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_COLOR], 1, &lights[currentNumOfLights]->color.r);
		glUniform1f(m_parameters[currentNumOfLights*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_POWER], lights[currentNumOfLights]->power);
		glUniform1f(m_parameters[currentNumOfLights*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_KC], lights[currentNumOfLights]->kC);
		glUniform1f(m_parameters[currentNumOfLights*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_KL], lights[currentNumOfLights]->kL);
		glUniform1f(m_parameters[currentNumOfLights*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_KQ], lights[currentNumOfLights]->kQ);
		glUniform1f(m_parameters[currentNumOfLights*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_COSCUTOFF], lights[currentNumOfLights]->cosCutoff);
		glUniform1f(m_parameters[currentNumOfLights*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_COSINNER], lights[currentNumOfLights]->cosInner);
		glUniform1f(m_parameters[currentNumOfLights*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_EXPONENT], lights[currentNumOfLights]->exponent);

		++currentNumOfLights;
		return true;
	}
	return false;
}

void Graphics::UpdateLights()
{
	for(Light** light = lights; *light != NULL; ++light)
	{
		const unsigned index = light - lights;
		if((*light)->type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir = (*light)->position;
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if((*light)->type == Light::LIGHT_SPOT)
		{
			Vector3 lightPosition_cameraspace = viewStack.Top() * (*light)->position;
			glUniform3fv(m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * (*light)->spotDirection;
			glUniform3fv(m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Vector3 lightPosition_cameraspace = viewStack.Top() * (*light)->position;
			glUniform3fv(m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		}
		//Vector3 lightPosition_cameraspace = viewStack.Top() * (*light)->position;
		//glUniform3fv(m_parameters[index*NUM_OF_LIGHT_PARAMETERS + U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
}

void Graphics::RenderMesh(const drawOrder& object, const Mtx44& matrix)
{
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.MultMatrix(matrix);
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
	if(object.IsLightEnabled())
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		Component kAmbient = object.GetMaterial()->GetAmbient();
		Component kDiffuse = object.GetMaterial()->GetDiffuse();
		Component kSpecular = object.GetMaterial()->GetSpecular();

		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], object.GetMaterial()->GetShininess());
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if(object.GetMaterial()->GetTexture() > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	object.Render();
	modelStack.PopMatrix();
}

void Graphics::RenderText(const std::string text, const Color color)
{
	if(!meshText.GetMesh() || meshText.GetMaterial()->GetTexture() <= 0) //Proper error check
	{
		return;
	}

	glDisable(GL_DEPTH_TEST);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);

	glUniform1i(m_parameters[U_LIGHTENABLED], 0);

	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); // 1.0f is the size of one letter.
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		
		const unsigned numofverts = 6;
		meshText.GetMesh()->Render((unsigned)text[i] * numofverts, numofverts);
	}
	
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void Graphics::RenderTextOnScreen(const std::string text, const Color color, const float size, const float x, const float y, ORIENTATION orientation)
{
	if(!meshText.GetMesh() || meshText.GetMaterial()->GetTexture() <= 0) //Proper error check
	{
		return;
	}

	glDisable(GL_DEPTH_TEST);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);

	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	Mtx44 ortho;
	int screenX, screenY;
	glfwGetWindowSize(m_window, &screenX, &screenY);
	ortho.SetToOrtho(0, screenX, 0, screenY, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	switch(orientation)
	{
	case ORIENTATION_TOP:
		modelStack.Translate(x, screenY - y, 0);
		modelStack.Scale(size, size, 1);
		break;
	case ORIENTATION_BOTTOM:
		modelStack.Translate(x, y, 0);
		modelStack.Scale(size, size, 1);
		break;
	case ORIENTATION_CENTRE:
		modelStack.Translate(screenX/2 + x, screenY/2 + y, 0);
		modelStack.Scale(size, size, 1);
		break;
	}
	
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1, 0, 0); // 1.0f is the size of one letter.
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		
		const unsigned numofverts = 6;
		meshText.RenderPartial((unsigned)text[i] * numofverts, numofverts);
	}

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void Graphics::RenderMeshOnScreen(const drawOrder& object, const Mtx44& matrix, ORIENTATION orientation)
{
	if(!meshText.GetMesh() || meshText.GetMaterial()->GetTexture() <= 0) //Proper error check
	{
		return;
	}

	Mtx44 ortho;
	int screenX, screenY;
	glfwGetWindowSize(m_window, &screenX, &screenY);
	ortho.SetToOrtho(0, screenX, 0, screenY, -1000, 1000);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	Mtx44 translate;
	modelStack.PushMatrix();
	Vector3 translation;
	switch(orientation)
	{
	case ORIENTATION_TOP:
		translation = matrix * Vector3();
		translate.SetToTranslation(0, screenY - translation.y * 2, 0);
		break;
	case ORIENTATION_BOTTOM:
		translate.SetToIdentity();
		break;
	case ORIENTATION_CENTRE:
		translate.SetToTranslation(screenX/2, screenY/2, 0);
		break;
	}
	modelStack.LoadMatrix(translate * matrix);


	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	if(object.GetMaterial()->GetTexture() > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	object.Render();

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	//glEnable(GL_DEPTH_TEST);
}