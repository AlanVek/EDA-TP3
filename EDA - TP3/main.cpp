#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"

#include <iostream>
#include "Simulation.h"

#define babyBitmap "food.png"

using namespace std;

int main(int, char**)
{
	bool result = true;
	bool endOfInput = false;

	Simulation* mySim = new (nothrow) Simulation;

	srand(time(NULL));

	if (!mySim) {
		cout << "Failed to crate simulation\.";
		result = false;
	}

	//If mySim was successfully created...
	if (result) {
		//mySim->getGraphicControl()->setFontName(fontName);

		//Attempts to initialize simulation.
		if (!mySim->initializeAll()) {
			cout << "Failed to initialize simulation\n";
			result = false;
		}
	}
	mySim->getTimeControl()->startTimer();

	al_init_primitives_addon();

	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	// Setup de Dear ImGui

	IMGUI_CHECKVERSION();			// Control de version de Dear ImGui

	ImGui::CreateContext(); ImGui_ImplAllegro5_Init(mySim->getGraphicControl()->getDisplay()); // Inicializa Dear ImGui

	ImGuiIO& io = ImGui::GetIO();	// Me permite obtener informacion y cambiar parametros del mouse y de teclado.

									// Por ejemplo, puedo cambiar la velocidad a la que se repiten los caracteres 

									// cuando mantengo una tecla presionada, o puedo saber si el evento de 

									// mouse/teclado que acaba de llegar fue dentro de una ventana de ImGui o fuera.



	ImGui::StyleColorsLight();		// Opcional: cambiar la paleta de colores default por otra


	bool running = true;			// true hasta que se cierre el display.

	bool keep_open = true;			// true hasta que se cierre la ventana a la que se asigna.



	//variables auxiliares que usan los widgets

	bool show_another_window = false;

	bool show_demo_window = false;

	unsigned int counter = 0;

	float f = 0.0f;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (running)

	{

		ALLEGRO_EVENT ev;

		while (al_get_next_event(mySim->getEventControl()->getQueue(), &ev))

		{

			ImGui_ImplAllegro5_ProcessEvent(&ev);	// Mandar el evento a Dear ImGui para que lo procese



			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

				running = false;

			if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)

			{

				ImGui_ImplAllegro5_InvalidateDeviceObjects();

				al_acknowledge_resize(mySim->getGraphicControl()->getDisplay());

				ImGui_ImplAllegro5_CreateDeviceObjects();

			}

			if (ev.type == ALLEGRO_EVENT_TIMER) {
				mySim->moveCycle();
			}

			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
				running = false;

			if (mySim->getBlobAmount() == 0) {
				running = false;
			}

			// io.WantCaptureKeyboard devuelve true si el ultimo evento fue de teclado y ademas fue 

			// usado por el usuario para interactuar con las ventanas de Dear Imgui. Por este motivo, 

			// sabemos que no estaba dirigido a nuestra aplicacion principal y no debemos mandarselo a 

			// su dispatcher. Idem para io.WantCaptureMouse y los eventos de mouse

			if (!io.WantCaptureKeyboard && !io.WantCaptureMouse)

			{

				// Dispatch a nuestra aplicacion principal 

			}

		}


		// Inicio el frame. Se realiza una vez por cada pantalla que dibujo.

		ImGui_ImplAllegro5_NewFrame();

		ImGui::NewFrame();


		if (1)

		{

			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

			ImGui::Text("Hello from another window!");


			if (ImGui::Button("Close Me"))

				show_another_window = false;

			ImGui::End();

		}

		// Rendering

		ImGui::Render();	//No dibuja! Solamente calcula que es lo que tiene que dibujarse



		// Puedo usar funciones de dibujo de Allegro ademas de las de 

		// ImGui.

		// Todo lo que dibuje antes de ImGui_ImplAllegro5_RenderDrawData

		// va a quedar detras de las ventanas de DearImGui, y todo lo 

		// que dibuje despues va a quedar encima de las ventanas de 

		// DearImGui.

		ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());	//Dibuja las ventanas, pero no hace al_flip_display()



		//Todo lo que dibuje aca va a quedar por encima de las ventanas de DearImGui


		al_flip_display(); //DearImGui nunca hace al_flip_display()

	}

	// Cleanup final

	delete mySim;

	ImGui_ImplAllegro5_Shutdown();

	ImGui::DestroyContext();

	al_shutdown_primitives_addon();

	return 0;

}
