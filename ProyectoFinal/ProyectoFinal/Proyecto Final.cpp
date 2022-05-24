/*--------------------------------------------------------*/
/* ----------------  Proyecto Final --------------------------*/
/*-----------------    2022-2  ---------------------------*/
/*-------- Alumno: Saúl Abraham Esparza Rivera -----------*/
/*-------- Cuenta: 314041502 -----------------------------*/
/*-------- Alumno: Andrew Sánchez Manjarrez  -----------*/
/*-------- Cuenta: 416041343 -----------------------------*/

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Properties
const GLuint WIDTH = 1280, HEIGHT = 720;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 1.0f, -45.0f);
bool active;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );
void animacion();



// Camera
Camera camera(glm::vec3(0.5f, 1.5f, 29.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;

bool keys[1024];
bool firstMouse = true;


float range = 0.0f;
float rot = 90.0f, rot2 = 0.0f, rot3 = -90.0f;
bool anim = false;

float posVueloX = -13.74f, posVueloY = 7.4f, posVueloZ = 13.69f;

float R2PosX = -4.756f, R2PosY = 1.2f, R2PosZ = 8.93f;




bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = true;
bool recorrido6 = false;
bool recorrido7 = false;
bool recorrido8 = false;
bool recorrido9 = false;
bool recorrido10 = false;
bool recorrido11 = false;
bool recorrido12 = false;
bool recorrido13 = false;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame


float tiempo;


float RaptorX = 21.0f, RaptorY = 1.5f, RaptorZ = 15.0f, RaptorRot = -90.0f, RaptorPataI, RaptorPataD, RaptorCola;
float JeepX = 0.5f, JeepY = 1.0f, JeepZ = 19.0f, JeepAng= 180.0f;

#define MAX_FRAMES 60
int i_max_steps = 90;
int i_curr_steps = 0;

// Keyframes

//Guardo los moviemes de la animacion ....VARIABLES GLOBALES
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z;

typedef struct _frame
{
    //Variables para GUARDAR Key Frames

    //Variables del raptor
    //Posición
    float RaptorX; //Posición
    float RapIncX; //Incremento
    float RaptorY;
    float RapIncY;
    float RaptorZ;
    float RapIncZ;
    //Ángulo Cuerpo
    float RaptorRot;
    float RapIncRot;
    //Ángulo patas
    float RaptorPataI;
    float RapIncPI;
    float RaptorPataD;
    float RapIncPD;
    //Ángulo cola
    float RaptorCola;
    float RapIncCola;

    //Variables del coche
    float JeepX;
    float JeepIncX;
    float JeepY;
    float JeepIncY;
    float JeepZ;
    float JeepIncZ;
    float JeepAng;
    float JeepIncAng;



}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;	//introducir datos
bool play = false;
int playIndex = 0;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    //PuertaIZQ
    glm::vec3(-1.14f,1.91f,23.0f),
    glm::vec3(-1.13f,2.94f,23.0f),
    glm::vec3(-1.14f,3.78f,23.0f),
    //PuertaDER
    glm::vec3(2.26f,1.91f,23.0f),
    glm::vec3(2.26f,2.94f,23.0f),
    glm::vec3(2.26f,3.78f,23.0f),
    //Dentro del café
    glm::vec3(-9.45f,2.74f,9.0f),
    //Letrero cafe
    glm::vec3(-6.58f,2.61f,10.45f),
    //Parque
    glm::vec3(-4.93f,3.23f,1.36f),
    glm::vec3(-11.48f,3.23f,1.31f),
    glm::vec3(-17.66,3.23f,1.30f),
    glm::vec3(-17.82,3.23f,-6.32f),
    glm::vec3(-17.52f,3.23f,-15.45),
    glm::vec3(-11.02f,3.23f,-15.77),
    glm::vec3(-4.89f,3.23f,-15.82f),
    glm::vec3(2.08f,3.23f,-15.33f),
    //Edificio
    glm::vec3(11.69f,0.1f,-6.04f),
    glm::vec3(18.07f,0.1f,-6.04f),
    glm::vec3(14.69f,2.24f,-9.69f),
    glm::vec3(14.81f,1.28f,-11.43f),
    glm::vec3(2.05f,3.23f,-5.83f)
};

glm::vec3 LightP1;

//void saveFrame(void)
//{
//
//    printf("\nFrameIndex %d\n", FrameIndex);
//
//    KeyFrame[FrameIndex].posX = posX;
//    KeyFrame[FrameIndex].posY = posY;
//    KeyFrame[FrameIndex].posZ = posZ;
//
//    KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
//    KeyFrame[FrameIndex].rotRodDer = rotRodDer;
//
//    KeyFrame[FrameIndex].rotBraDer = rotBraDer;
//    KeyFrame[FrameIndex].rotBraIzq = rotBraIzq;
//
//
//    FrameIndex++;
//}

void resetElements(void)
{
    

    //Raptor Posición
    RaptorX = KeyFrame[0].RaptorX;
    RaptorY = KeyFrame[0].RaptorY;
    RaptorZ = KeyFrame[0].RaptorZ;
    //Raptor Posición
    RaptorRot = KeyFrame[0].RaptorRot;
    //Angulos patas y cola
    RaptorPataI = KeyFrame[0].RaptorPataI;
    RaptorPataD = KeyFrame[0].RaptorPataD;
    RaptorCola = KeyFrame[0].RaptorCola;

    //Jeep Posición
    JeepX = KeyFrame[0].JeepX;
    JeepY = KeyFrame[0].JeepY;
    JeepZ = KeyFrame[0].JeepZ;
    JeepAng = KeyFrame[0].JeepAng;
    

}

void interpolation(void)
{


    //Raptor Posición
    KeyFrame[playIndex].RapIncX = (KeyFrame[playIndex + 1].RaptorX - KeyFrame[playIndex].RaptorX) / i_max_steps;
    KeyFrame[playIndex].RapIncY = (KeyFrame[playIndex + 1].RaptorY - KeyFrame[playIndex].RaptorY) / i_max_steps;
    KeyFrame[playIndex].RapIncZ = (KeyFrame[playIndex + 1].RaptorZ - KeyFrame[playIndex].RaptorZ) / i_max_steps;
    //Raptor Ángulo
    KeyFrame[playIndex].RapIncRot = (KeyFrame[playIndex + 1].RaptorRot - KeyFrame[playIndex].RaptorRot) / i_max_steps;
    //Patas y cola
    KeyFrame[playIndex].RapIncPI = (KeyFrame[playIndex + 1].RaptorPataI - KeyFrame[playIndex].RaptorPataI) / i_max_steps;
    KeyFrame[playIndex].RapIncPD = (KeyFrame[playIndex + 1].RaptorPataD - KeyFrame[playIndex].RaptorPataD) / i_max_steps;
    KeyFrame[playIndex].RapIncCola = (KeyFrame[playIndex + 1].RaptorCola - KeyFrame[playIndex].RaptorCola) / i_max_steps;

    //Jeep Posición
    KeyFrame[playIndex].JeepIncX = (KeyFrame[playIndex + 1].JeepX - KeyFrame[playIndex].JeepX) / i_max_steps;
    KeyFrame[playIndex].JeepIncY = (KeyFrame[playIndex + 1].JeepY - KeyFrame[playIndex].JeepY) / i_max_steps;
    KeyFrame[playIndex].JeepIncZ = (KeyFrame[playIndex + 1].JeepZ - KeyFrame[playIndex].JeepZ) / i_max_steps;
    //Jeep Ángulo
    KeyFrame[playIndex].JeepIncAng = (KeyFrame[playIndex + 1].JeepAng - KeyFrame[playIndex].JeepAng) / i_max_steps;

    



}


int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto Final - Esparza-Sanchez", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback(window, MouseCallback);
    printf("%f", glfwGetTime());
    
    // GLFW Options -- Activado para contener el mouse y poder mirar el escenario más fácil
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
    Shader lampshader( "Shaders/lamp.vs", "Shaders/lamp.frag" );
    Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");



    // Load models

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    GLfloat vertices[] =
    {
        // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 

    };


    GLfloat skyboxVertices[] = {
        // Positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };


    GLuint indices[] =
    {  // Note that we start from 0!
        0,1,3,
        1,2,3

    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Load textures \\


    ////Base del escenario
    Model Base((char*)"Models/Base2/Base.obj");

    ////Cafetería
    Model Cafe((char*)"Models/Cafe New/Cafe.obj");

    ////Dinosaurio volador
    Model CuerpoDino((char*)"Models/Dino/body.obj");
    Model AlaIzq((char*)"Models/Dino/AlaIzq.obj");
    Model AlaDer((char*)"Models/Dino/AlaDer.obj");

    ////Ventilador
    Model BaseVentilador((char*)"Models/Vent/Base.obj");
    Model Aspas((char*)"Models/Vent/Aspas.obj");
    Model Vader((char*)"Models/Vader/Vader.obj");
    Model R2D2((char*)"Models/R2D2/R2.obj");

    ////Edificio
    Model Edif((char*)"Models/EdificioA/Edif.obj");

    //Planta
    Model Plant((char*)"Models/Plant/Fern.obj");

    //Raptor
    Model RaptorC((char*)"Models/Raptor/Cuerpo.obj");
    Model RaptorPD((char*)"Models/Raptor/PataDer.obj");
    Model RaptorPI((char*)"Models/Raptor/PataIzq.obj");
    Model RaptorT((char*)"Models/Raptor/Cola.obj");

    //Jeep al fin
    Model Jeep((char*)"Models/Jeep/Jeep.obj");




    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  
    

    //Valores de los keyframes para los movimientos de las animaciones
 
    //Movimiento 0
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = 21.0f;
    KeyFrame[FrameIndex].RaptorY = 1.5f;
    KeyFrame[FrameIndex].RaptorZ = 15.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -90.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 0.5f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = 19.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = 180.0f;
    //Aumentar el índice
    FrameIndex++;

    //Movimiento 1
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = 17.0f;
    KeyFrame[FrameIndex].RaptorY = 1.5f;
    KeyFrame[FrameIndex].RaptorZ = 15.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -90.0f;
    //KF Patas
    KeyFrame[FrameIndex].RaptorPataD = 12.0f;
    KeyFrame[FrameIndex].RaptorPataI = -10.0f;
    //KF Cola
    KeyFrame[FrameIndex].RaptorCola = -5.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 5.0f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = 13.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = 90.0f;
    //Aumentar el índice
    FrameIndex++;

    //Movimiento 2
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = 13.0f;
    KeyFrame[FrameIndex].RaptorY = 1.5f;
    KeyFrame[FrameIndex].RaptorZ = 15.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -90.0f;
    //KF Patas
    KeyFrame[FrameIndex].RaptorPataD = -10.0f;
    KeyFrame[FrameIndex].RaptorPataI = 12.0f;
    //KF Cola
    KeyFrame[FrameIndex].RaptorCola = 12.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 10.0f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = 10.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = 90.0f;
    //Aumentar el índice
    FrameIndex++;

    //Movimiento 2.1
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = 13.0f;
    KeyFrame[FrameIndex].RaptorY = 1.5f;
    KeyFrame[FrameIndex].RaptorZ = 10.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -130.0f;
    //KF Patas
    KeyFrame[FrameIndex].RaptorPataD = -10.0f;
    KeyFrame[FrameIndex].RaptorPataI = 12.0f;
    //KF Cola
    KeyFrame[FrameIndex].RaptorCola = 12.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 13.0f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = 5.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = 180.0f;
    //Aumentar el índice
    FrameIndex++;

    //Movimiento 2.2
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = 13.0f;
    KeyFrame[FrameIndex].RaptorY = 1.5f;
    KeyFrame[FrameIndex].RaptorZ = 5.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -160.0f;
    //KF Patas
    KeyFrame[FrameIndex].RaptorPataD = -10.0f;
    KeyFrame[FrameIndex].RaptorPataI = 12.0f;
    //KF Cola
    KeyFrame[FrameIndex].RaptorCola = 12.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 13.0f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = -1.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = 180.0f;
    //Aumentar el índice
    FrameIndex++;

    //Movimiento 3
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = 13.0f;
    KeyFrame[FrameIndex].RaptorY = 1.5f;
    KeyFrame[FrameIndex].RaptorZ = 0.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -190.0f;
    //KF Patas
    KeyFrame[FrameIndex].RaptorPataD = 12.0f;
    KeyFrame[FrameIndex].RaptorPataI = -10.0f;
    //KF Cola
    KeyFrame[FrameIndex].RaptorCola = -5.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 13.0f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = -6.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = 180.0f;
    //Aumentar el índice
    FrameIndex++;

    //Movimiento 4
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = 10.0f;
    KeyFrame[FrameIndex].RaptorY = 1.5f;
    KeyFrame[FrameIndex].RaptorZ = -10.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -90.0f;
    //KF Patas
    KeyFrame[FrameIndex].RaptorPataD = -10.0f;
    KeyFrame[FrameIndex].RaptorPataI = 12.0f;
    //KF Cola
    KeyFrame[FrameIndex].RaptorCola = 12.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 13.0f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = -9.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = -90.0f;
    //Aumentar el índice
    FrameIndex++;

    //Movimiento 4.1
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = 6.0f;
    KeyFrame[FrameIndex].RaptorY = 1.5f;
    KeyFrame[FrameIndex].RaptorZ = -10.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -90.0f;
    //KF Patas
    KeyFrame[FrameIndex].RaptorPataD = -10.0f;
    KeyFrame[FrameIndex].RaptorPataI = 12.0f;
    //KF Cola
    KeyFrame[FrameIndex].RaptorCola = 12.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 16.0f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = -9.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = -90.0f;
    //Aumentar el índice
    FrameIndex++;

    //Movimiento 5
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = 4.0f;
    KeyFrame[FrameIndex].RaptorY = 1.5f;
    KeyFrame[FrameIndex].RaptorZ = -10.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -90.0f;
    //KF Patas
    KeyFrame[FrameIndex].RaptorPataD = 12.0f;
    KeyFrame[FrameIndex].RaptorPataI = -10.0f;
    //KF Cola
    KeyFrame[FrameIndex].RaptorCola = -5.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 16.0f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = -9.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = -90.0f;
    //Aumentar el índice
    FrameIndex++;

    //Movimiento 6
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = 0.0f;
    KeyFrame[FrameIndex].RaptorY = 1.5f;
    KeyFrame[FrameIndex].RaptorZ = -10.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -90.0f;
    //KF Patas
    KeyFrame[FrameIndex].RaptorPataD = -10.0f;
    KeyFrame[FrameIndex].RaptorPataI = 12.0f;
    //KF Cola
    KeyFrame[FrameIndex].RaptorCola = 12.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 16.0f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = -9.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = -90.0f;
    //Aumentar el índice
    FrameIndex++;

    //Movimiento 7
    //KF Movimiento Raptor
    KeyFrame[FrameIndex].RaptorX = -1.0f;
    KeyFrame[FrameIndex].RaptorY = -3.0f;
    KeyFrame[FrameIndex].RaptorZ = -10.0f;
    //KF Ángulo Raptor
    KeyFrame[FrameIndex].RaptorRot = -90.0f;
    //KF Patas
    KeyFrame[FrameIndex].RaptorPataD = 12.0f;
    KeyFrame[FrameIndex].RaptorPataI = -10.0f;
    //KF Cola
    KeyFrame[FrameIndex].RaptorCola = -5.0f;
    //KF Jeep Movimiento
    KeyFrame[FrameIndex].JeepX = 16.0f;
    KeyFrame[FrameIndex].JeepY = 1.0f;
    KeyFrame[FrameIndex].JeepZ = -9.0f;
    //Ángulo jeep
    KeyFrame[FrameIndex].JeepAng = -90.0f;
    //Aumentar el índice
    FrameIndex++;


    //SkyBox
    GLuint skyboxVBO, skyboxVAO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    // Load textures
    vector<const GLchar*> faces;
    faces.push_back("SkyBox/right.tga");
    faces.push_back("SkyBox/left.tga");
    faces.push_back("SkyBox/up.tga");
    faces.push_back("SkyBox/down.tga");
    faces.push_back("SkyBox/back.tga");
    faces.push_back("SkyBox/front.tga");

    GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);



    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();
        animacion();

        // Clear the colorbuffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.Use();
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
        // == ==========================
        // Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
        // the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
        // by defining light types as classes and set their values in there, or by using a more efficient uniform approach
        // by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
        // == ==========================
        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.7f, 0.7f, 0.7f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.4f, 0.4f, 0.4f);


        //Luces Puerta
        // Point light 1
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.921f, 0.807f, 0.239f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 1.8f);
        // Point light 2
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.921f, 0.807f, 0.239f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 1.8f);
        // Point light 3
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.921f, 0.807f, 0.239f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 1.8f);
        // Point light 4
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.921f, 0.807f, 0.239f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 1.8f);
        // Point light 5
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].position"), pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].ambient"), 0.921f, 0.807f, 0.239f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].quadratic"), 1.8f);
        // Point light 6
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[5].position"), pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[5].ambient"), 0.921f, 0.807f, 0.239f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[5].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[5].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[5].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[5].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[5].quadratic"), 1.8f);

        //Luces café
        // Point light 7
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[6].position"), pointLightPositions[6].x, pointLightPositions[6].y, pointLightPositions[6].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[6].ambient"), 0.972f, 1.0f, 0.078f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[6].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[6].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[6].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[6].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[6].quadratic"), 1.8f);
        //Letrero CAFE
        // Point light 8
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[7].position"), pointLightPositions[7].x, pointLightPositions[7].y, pointLightPositions[7].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[7].ambient"), 0.423f, 0.878f, 0.956f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[7].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[7].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[7].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[7].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[7].quadratic"), 1.8f);

        //Luces del parque
        // Point light 9
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[8].position"), pointLightPositions[8].x, pointLightPositions[8].y, pointLightPositions[8].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[8].ambient"), 0.423f, 0.878f, 0.956f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[8].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[8].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[8].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[8].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[8].quadratic"), 0.20f);
        // Point light 10
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[9].position"), pointLightPositions[9].x, pointLightPositions[9].y, pointLightPositions[9].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[9].ambient"), 0.423f, 0.878f, 0.956f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[9].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[9].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[9].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[9].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[9].quadratic"), 0.20f);
        // Point light 11
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[10].position"), pointLightPositions[10].x, pointLightPositions[10].y, pointLightPositions[10].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[10].ambient"), 0.423f, 0.878f, 0.956f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[10].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[10].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[10].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[10].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[10].quadratic"), 0.20f);
        // Point light 12
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[11].position"), pointLightPositions[11].x, pointLightPositions[11].y, pointLightPositions[11].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[11].ambient"), 0.423f, 0.878f, 0.956f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[11].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[11].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[11].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[11].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[11].quadratic"), 0.20f);
        // Point light 13
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[12].position"), pointLightPositions[12].x, pointLightPositions[12].y, pointLightPositions[12].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[12].ambient"), 0.423f, 0.878f, 0.956f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[12].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[12].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[12].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[12].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[12].quadratic"), 0.20f);
        // Point light 14
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[13].position"), pointLightPositions[13].x, pointLightPositions[13].y, pointLightPositions[13].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[13].ambient"), 0.423f, 0.878f, 0.956f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[13].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[13].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[13].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[13].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[13].quadratic"), 0.20f);
        // Point light 15
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[14].position"), pointLightPositions[14].x, pointLightPositions[14].y, pointLightPositions[14].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[14].ambient"), 0.423f, 0.878f, 0.956f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[14].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[14].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[14].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[14].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[14].quadratic"), 0.20f);
        // Point light 16
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[15].position"), pointLightPositions[15].x, pointLightPositions[15].y, pointLightPositions[15].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[15].ambient"), 0.423f, 0.878f, 0.956f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[15].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[15].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[15].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[15].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[15].quadratic"), 0.20f);
        // Point light 17
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[16].position"), pointLightPositions[16].x, pointLightPositions[16].y, pointLightPositions[16].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[16].ambient"), 0.423f, 0.878f, 0.956f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[16].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[16].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[16].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[16].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[16].quadratic"), 0.20f);

        //Luces del edificio
        // Point light 18
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[17].position"), pointLightPositions[17].x, pointLightPositions[17].y, pointLightPositions[17].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[17].ambient"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[17].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[17].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[17].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[17].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[17].quadratic"), 0.44f);
        // Point light 19
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[18].position"), pointLightPositions[18].x, pointLightPositions[18].y, pointLightPositions[18].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[18].ambient"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[18].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[18].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[18].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[18].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[18].quadratic"), 0.44f);
        // Point light 20
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[19].position"), pointLightPositions[19].x, pointLightPositions[19].y, pointLightPositions[19].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[19].ambient"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[19].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[19].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[19].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[19].linear"), 0.1f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[19].quadratic"), 3.5f);
        // Point light 20
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[20].position"), pointLightPositions[20].x, pointLightPositions[20].y, pointLightPositions[20].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[20].ambient"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[20].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[20].specular"), 1.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[20].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[20].linear"), 0.1f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[20].quadratic"), 3.5f);

        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 30.0f);

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();
        //pe
        //glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the loaded model
        glm::mat4 tmp = glm::mat4(1);
        glm::mat4 tmp2 = glm::mat4(1);



        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 100.0f);
        //Base del escenario
        glm::mat4 model(1);
        view = camera.GetViewMatrix();
        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Base.Draw(lightingShader);
        glBindVertexArray(0);
        

        //Edificio
        view = camera.GetViewMatrix();
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(15.0f, 0.5f, -16.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.30f, 0.30f, 0.30f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Edif.Draw(lightingShader);
        glBindVertexArray(0);


        //Planta
        view = camera.GetViewMatrix();
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(19.0f, 0.5f, 15.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Plant.Draw(lightingShader);
        glBindVertexArray(0);

        
        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 8.0f);
        //Café
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        tmp = model = glm::translate(model, glm::vec3(-9.5f, 0.48f, 12.0f));
        model = glm::scale(model, glm::vec3(0.13f, 0.13f, 0.13f));
        //model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Cafe.Draw(lightingShader);
        glBindVertexArray(0);


        //Cuerpo del dinosaurio
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        tmp = model = glm::translate(model, glm::vec3(posVueloX, posVueloY, posVueloZ));
        model = glm::scale(model, glm::vec3(0.13f, 0.13f, 0.13f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        CuerpoDino.Draw(lightingShader);
        glBindVertexArray(0);

        //Ala izquierda del dinosaurio
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.13f, 0.13f, 0.13f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        AlaIzq.Draw(lightingShader);
        glBindVertexArray(0);

        //Ala derecha del dinosaurio
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.13f, 0.13f, 0.13f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        AlaDer.Draw(lightingShader);
        glBindVertexArray(0);


        //Base del ventilador
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        tmp = model = glm::translate(model, glm::vec3(-7.2f, 3.1f, 8.83f));
        model = glm::scale(model, glm::vec3(0.13f, 0.13f, 0.13f));
        model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        BaseVentilador.Draw(lightingShader);
        glBindVertexArray(0);
        //Aspas del ventilador
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        model = glm::translate(model, glm::vec3(-7.2f, 3.09f, 8.83f));
        model = glm::scale(model, glm::vec3(0.13f, 0.13f, 0.13f));
        model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Aspas.Draw(lightingShader);
        glBindVertexArray(0);


        //Vader
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        model = glm::translate(model, glm::vec3(-6.46f, 1.60f, 8.93f));
        model = glm::scale(model, glm::vec3(0.20f, 0.20f, 0.20f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Vader.Draw(lightingShader);
        glBindVertexArray(0);


        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 20.0f);
        //R2D2
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        model = glm::translate(model, glm::vec3(R2PosX, R2PosY, R2PosZ));
        model = glm::scale(model, glm::vec3(0.20f, 0.20f, 0.20f));
        model = glm::rotate(model, glm::radians(rot3), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        R2D2.Draw(lightingShader);
        glBindVertexArray(0);


        //Raptor cuerpo
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        tmp = model = glm::translate(model, glm::vec3(RaptorX, RaptorY, RaptorZ));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::rotate(model, glm::radians(RaptorRot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        RaptorC.Draw(lightingShader);
        glBindVertexArray(0);

        //Raptor pata izquierda
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::rotate(model, glm::radians(RaptorRot), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(RaptorPataI), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        RaptorPI.Draw(lightingShader);
        glBindVertexArray(0);

        //Raptor pata derecha
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::rotate(model, glm::radians(RaptorRot), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(RaptorPataD), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        RaptorPD.Draw(lightingShader);
        glBindVertexArray(0);

        //Raptor cola
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::rotate(model, glm::radians(RaptorRot), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(RaptorCola), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        RaptorT.Draw(lightingShader);
        glBindVertexArray(0);

        //Jeep
        model = glm::mat4(1);
        view = camera.GetViewMatrix();
        model = glm::translate(model, glm::vec3(JeepX, JeepY, JeepZ));
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        model = glm::rotate(model, glm::radians(JeepAng), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Jeep.Draw(lightingShader);
        glBindVertexArray(0);



        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        lampshader.Use();
 
        glBindVertexArray(0);


        // Draw skybox as last
        glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
        SkyBoxshader.Use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        //glDepthFunc(GL_LESS); // Set depth function back to default


        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);

    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

    if (keys[GLFW_KEY_I])
    {
        anim = true;
    }

    if (keys[GLFW_KEY_O])
    {
        anim = false;
    }
    //Rotación de la pata izquierda
    if (keys[GLFW_KEY_2])
    {
        
            JeepAng += 1.0f;
            std::cout << "\nEl ángulo es: " << to_string(JeepAng) << "\n" << std::endl;


    }

    if (keys[GLFW_KEY_3])
    {
        JeepAng -= 1.0f;
        std::cout << JeepAng;
        std::cout << "\nEl ángulo es: " << to_string(JeepAng) << "\n" << std::endl;

    }

    if (keys[GLFW_KEY_4])
    {
        
        RaptorCola += 0.2f;
        std::cout << "\nEl ángulo es: " << to_string(RaptorCola) << "\n" << std::endl;

    }

    if (keys[GLFW_KEY_5])
    {

        RaptorCola -= 0.2f;
        std::cout << "\nEl ángulo es: " << to_string(RaptorCola) << "\n" << std::endl;

    }


}

void animacion() {
    if (anim) {

        //Mov Dinosaurio
        if (recorrido1) {
            rot = 90;
            posVueloX += 0.05f;
            if (posVueloX > 1) {
                recorrido1 = false;
                recorrido2 = true;
            }
        }

        if (recorrido2) {
            rot = 180;
            posVueloZ -= 0.05f;
            if (posVueloZ < 2) {
                recorrido2 = false;
                recorrido3 = true;

            }

        }

        if (recorrido3) {
            rot = -90;
            posVueloX -= 0.05f;
            if (posVueloX < -12) {
                recorrido3 = false;
                recorrido4 = true;
            }
        }

        if (recorrido4) {
            rot = 0;
            posVueloZ += 0.05f;
            if (posVueloZ > 13) {
                recorrido4 = false;
                recorrido1 = true;
            }
        }


        //Mov R2D2
        if (recorrido5) {
            rot3 = 0;
            R2PosZ += 0.03f;
            if (R2PosZ > 15.0) {
                recorrido5 = false;
                recorrido6 = true;
            }
        }

        if (recorrido6) {
            rot3 = -90;
            R2PosX -= 0.03f;
            if (R2PosX < -7.0) {
                rot3 = 0;
                recorrido6 = false;
                recorrido7 = true;

            }

        }

        if (recorrido7) {
            rot3 = -90;
            R2PosX -= 0.03f;
            if (R2PosX < -12) {
                rot3 = 0;
                recorrido7 = false;
                recorrido8 = true;
            }
        }

        if (recorrido8) {
            rot3 = -90;
            R2PosX -= 0.03f;
            if (R2PosX < -10) {
                rot3 = 0;
                recorrido8 = false;
                recorrido9 = true;
            }
        }

        if (recorrido9) {
            rot3 =-90;
            R2PosX -= 0.03f;
            if (R2PosX < -13) {
                rot3 = 0;
                recorrido9 = false;
                recorrido10 = true;
            }
        }

        if (recorrido10) {
            rot3 = -180;
            R2PosZ -= 0.03f;
            if (R2PosZ < 13) {
                recorrido10 = false;
                recorrido11 = true;
            }
        }

        if (recorrido11) {
            rot3 = 90;
            R2PosX += 0.03f;
            if (R2PosZ > -11) {
                rot3 = 90;
                recorrido11 = false;
                recorrido12 = true;
            }
        }

        if (recorrido12) {
            rot3 = 90;
            R2PosX += 0.03f;
            if (R2PosX > -11) {
                recorrido12 = false;
                recorrido13 = true;
            }
        }

        if (recorrido13) {
            rot3 = 90;
            R2PosX += 0.03f;
            if (R2PosX > -3.8) {
                recorrido13 = false;
                recorrido5 = true;
            }
        }

        rot2 += 0.1;
    }

    if (play)
    {
        if (i_curr_steps >= i_max_steps) //end of animation between frames?
        {
            playIndex++;
            if (playIndex > FrameIndex - 2)	//end of total animation?
            {
                printf("termina anim\n");
                playIndex = 0;
                play = false;
            }
            else //Next frame interpolations
            {
                i_curr_steps = 0; //Reset counter
                                  //Interpolation
                interpolation();
            }
        }
        else
        {
            //Draw animation

            //Movimiento Raptor
            RaptorX += KeyFrame[playIndex].RapIncX;
            RaptorY += KeyFrame[playIndex].RapIncY;
            RaptorZ += KeyFrame[playIndex].RapIncZ;
            //Ángulo Raptor
            RaptorRot += KeyFrame[playIndex].RapIncRot;

            //Ángulos patas
            RaptorPataD += KeyFrame[playIndex].RapIncPD;
            RaptorPataI += KeyFrame[playIndex].RapIncPI;

            //Ángulo cola
            RaptorCola += KeyFrame[playIndex].RapIncCola;

            //Movimiento Jeep
            JeepX += KeyFrame[playIndex].JeepIncX;
            JeepY += KeyFrame[playIndex].JeepIncY;
            JeepZ += KeyFrame[playIndex].JeepIncZ;

            //Ángulo Jeep
            JeepAng += KeyFrame[playIndex].JeepIncAng;


            i_curr_steps++;
        }

    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (keys[GLFW_KEY_L])
    {
        if (play == false && (FrameIndex > 1))
        {

            resetElements();
            //First Interpolation				
            interpolation();

            play = true;
            playIndex = 0;
            i_curr_steps = 0;
        }
        else
        {
            play = false;
        }

    }


    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{

    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

