#pragma once

#include "AbstractWindow.h"

class IInputEventAcceptor;
namespace sdl
{
	// ��������� ��������������� ������� SDL �� ����������.
	void DispatchEvent(const SDL_Event & event, IInputEventAcceptor & acceptor);
}

// ��������� ������� SDL, ���������� �� ����������.
// ������� �������� � ����� ���� ��������.
class IInputEventAcceptor
{
public:
	virtual ~IInputEventAcceptor() = default;

	virtual void OnMouseUp(const SDL_MouseButtonEvent &) {}
	virtual void OnMouseDown(const SDL_MouseButtonEvent &) {}
	virtual void OnMouseMotion(const SDL_MouseMotionEvent &) {}
	virtual void OnMouseWheel(const SDL_MouseWheelEvent &) {}
	virtual void OnKeyDown(const SDL_KeyboardEvent &) {}
	virtual void OnKeyUp(const SDL_KeyboardEvent &) {}
};

// ����, ����������� ��������������� ������� SDL
class CAbstractInputControlWindow
	: public CAbstractWindow
	, public IInputEventAcceptor
{
protected:
	void OnWindowEvent(const SDL_Event &event) final
	{
		sdl::DispatchEvent(event, *this);
	}
};

