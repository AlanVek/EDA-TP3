#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "GUIS.h"

#define minRelSpeedLimit 0.0f
#define maxRelSpeedLimit 1.0f
#define minMaxSpeedLimit 0.0f
#define maxMaxSpeedLimit 30.0f
#define minBlobCount 1
#define maxBlobCount 30
#define minRandomJiggleLimit 0
#define maxRandomJiggleLimit 0.5
#define minSmellRadiusLimit 0.0f
#define maxSmellRadiusLimit 200.0f
#define minFoodCountLimit 1
#define maxFoodCountLimit 30


//Sets up the necessary data to use ImGUI.
void GUILoop(Simulation* mySim) {

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ALLEGRO_DISPLAY* newDisp;
    newDisp = al_create_display(750,400);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplAllegro5_Init(newDisp);

    //Sets screen to black.
    al_clear_to_color(al_map_rgb(0, 0, 0));

    //GUISetTHIS(mySim);

    // Main loop
    bool running = true;

    bool starting = true;

    float relSpeed = 0.0f, maxSpeed = 0.0f;
    float randomJL = 0.0f, babyDeathProb = 0.0f, grownDeathProb = 0.0f, goodOldDeathProb = 0.0f;


    bool keepRunning;
    int foodCount = 1, blobCount = 1, smellRadius = 0;
    /*If it's the first run, it shows the set up menu
    and waits until all initial parameters are set. */
    
    keepRunning = GUI_firstLoop(&mode, &blobCount, mySim);
    
    //Otherwise, it shows the general menu and does a move cycle.
    if (keepRunning){
        GUI_Game_Loop(&relSpeed, &maxSpeed, &smellRadius, &randomJL, &babyDeathProb,
            &grownDeathProb, &goodOldDeathProb, &foodCount, mySim);
    }
    
    //Cleanup.
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    al_destroy_display(newDisp);
    
}
//Cycle that shows menu (called with every iteration).
void GUI_Game_Loop(bool *mode, int * blobCount, float * relSpeed, float* maxSpeed, int*smellRadius, 
    float* randomJL, float* babyDeathProb, float* grownDeathProb, float* goodOldDeathProb, int* foodCount, bool* pause, Simulation* mySim) {
    
    bool keepGoing = true;
    while (keepGoing){
        if (checkEndOfProgram(mySim))
            keepGoing = false;
        
        
        ImGui_ImplAllegro5_NewFrame();
        ImGui::NewFrame();

        //Sets speed sliders according to mode.
        if (mode) {
            ImGui::SliderFloat("General relative speed", relSpeed, minRelSpeedLimit, maxRelSpeedLimit);
            ImGui::SliderFloat("General maximum speed", maxSpeed, minMaxSpeedLimit, maxMaxSpeedLimit);
        }
        else
            ImGui::SliderFloat("General relative speed", relSpeed, minRelSpeedLimit, maxRelSpeedLimit);

        //Sets sliders for death probabilities.
        ImGui::SliderFloat("Death probability - Baby Blob", babyDeathProb, 0.0f, 1.0f);
        ImGui::SliderFloat("Death probability - Grown Blob", grownDeathProb, 0.0f, 1.0f);
        ImGui::SliderFloat("Death probability - Good Old Blob", goodOldDeathProb, 0.0f, 1.0f);
        ImGui::SliderFloat("Random Jiggle Limit", randomJL, minRandomJiggleLimit, maxRandomJiggleLimit);

        //Sets input bars for smell radius(float), random jiggle limit(float) and food count (int).
        if (ImGui::InputInt("Smell radius", smellRadius)) {
            if (*smellRadius < minSmellRadiusLimit)
                *smellRadius = minSmellRadiusLimit;
            else if (*smellRadius > maxSmellRadiusLimit)
                *smellRadius = maxSmellRadiusLimit;
        }
        if (ImGui::InputInt("Food count", foodCount)) {
            if (*foodCount < minFoodCountLimit)
                *foodCount = minFoodCountLimit;
            else if (*foodCount > maxFoodCountLimit)
                *foodCount = maxFoodCountLimit;
        }

        //Sets pause button.
        if (ImGui::Button("Pause"))
            *pause = !*pause;

        //Shows current state next to button.
        ImGui::SameLine();
        ImGui::Text("%s", *pause ? "Paused" : "Unpaused");

        ImGui::Render();
        al_clear_to_color(al_map_rgb(0, 0, 0));
        ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());

        al_flip_display();

        //mySim->moveCycle();
    }

};

//Starting GUI setup.
bool GUI_firstLoop(bool* mode, int* blobCount, Simulation* mySim) {
    
    bool endOfSetUp = false;
    bool result = true;

    //Drawing loop.
    while (!endOfSetUp) {

        //Starts the Dear ImGui frame.

        if (checkEndOfProgram(mySim)) {
            endOfSetUp = true;
            result = false;
        }
        ImGui_ImplAllegro5_NewFrame();
        ImGui::NewFrame();

        //Sets window.
        ImGui::Begin("EDA - TP3");
        ImGui::Text("Initial Set up: ");

        //Button to select mode.
        if (ImGui::Button("Click here to change mode"))
            *mode = !*mode;

        //Shows selected mode next to button.
        ImGui::SameLine();
        ImGui::Text("%s", *mode ? "Modo 1" : "Modo 2");

        //Sets an integer input for blob amount and a button to let the program know the setup has ended.
        if (ImGui::InputInt("Blob amount", blobCount)) {
            if (*blobCount > maxBlobCount)
                *blobCount = maxBlobCount;
            else if (*blobCount < 1)
                *blobCount = 1;
        }
               
        if (ImGui::Button("Initial setup done!"))
            endOfSetUp = true;
        ImGui::End();
        //Rendering.
        ImGui::Render();
        al_clear_to_color(al_map_rgb(0, 0, 0));
        ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
       
        al_flip_display();
    }
    return result;
}

bool checkEndOfProgram(Simulation* mySim) {
 
    ALLEGRO_EVENT guiEvent;
    bool result = false;
    
    //Gets events. 
    while ((mySim->getEventControl()->getNextEventType()))
    {
        guiEvent = mySim->getEventControl()->getEvent();
        ImGui_ImplAllegro5_ProcessEvent(&guiEvent);

        /*If the display has been closed or if the user has pressed ESC,
         the program ends. */
        if (guiEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE || (guiEvent.type == ALLEGRO_EVENT_KEY_DOWN &&
            guiEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE))
            result = true;

        //If the display has been resized, it tells ImGUI to take care of it.
        else if (guiEvent.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
        {
            ImGui_ImplAllegro5_InvalidateDeviceObjects();
            al_acknowledge_resize(mySim->getGraphicControl()->getDisplay());
            ImGui_ImplAllegro5_CreateDeviceObjects();
        }

    }
    return result;
}