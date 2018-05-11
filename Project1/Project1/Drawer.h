#pragma once

class Drawer
{
public:
	void update(void* subject); /*Dependiendo del estado de Menu,
dibuja acordemente. En MAINMENU dibuja la pantalla preguntando si se desea comprimir, 
descomprimir, o salir. En ENCODE se deben mostrar todas las imagenes que esten seleccionadas*/
};

