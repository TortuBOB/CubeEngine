

// Autor: Laura Rosas


#include <iostream>
#include <Window.hpp>
#include <Scene.hpp>


int main()
{    
    // crear ventana
    Window window("DemoCubeEngine", 800, 600, false);

    // Crear escena
    const char* audioPath = "../../assets/CollisionCut.wav";
    Scene scene(&window, audioPath);

    // Cargar escena
    std::string path = "../../assets/Escena.xml";
    if (!scene.LoadScene(path)) 
    {
        std::cout << "Error loading scene";
        //Si falla se carga la escena demo
        scene.LoadScene();
    }
    

    // Ejecutar escena
    scene.Run();
    


    return 0;

}